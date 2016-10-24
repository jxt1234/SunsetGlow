#include "SGComputeResponser.h"
#include "SGDebug.h"
#include "SGCompute.SR.pb-c.h"
#include "core/GPStreamFactory.h"
#include "core/GPPieceFactory.h"
#include <fstream>
#include <sstream>


SGComputeResponser* SGComputeResponser::gInstance = NULL;
bool SGComputeResponser::init(const char* port, const char* master_port)
{
    SGASSERT(NULL!=port);
    SGASSERT(NULL == gInstance);
    //TODO add Lock
    gInstance = new SGComputeResponser(port, master_port);
    return true;
}

SGComputeResponser* SGComputeResponser::getInstance()
{
    SGASSERT(NULL!=gInstance);
    return gInstance;
}


void SGComputeResponser::setStreamCreator(const GPIStreamCreator* creator)
{
    mStreamCreator = creator;
}


void SG_Response__create_work (SGCompute__SR__ComputeResponser_Service *service,
                    const SGCompute__SR__WorkInfo *input,
                    SGCompute__SR__ResultInfo_Closure closure,
                               void *closure_data)
{
    uint64_t magic = SGComputeResponser::getInstance()->insertWork((const void*)input);
    SGCompute__SR__ResultInfo result = SGCOMPUTE__SR__RESULT_INFO__INIT;
    result.magic = magic;
    FUNC_PRINT(magic);
    result.status = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
    closure(&result, closure_data);
}

void SG_Response__release_work (SGCompute__SR__ComputeResponser_Service *service,
                            const SGCompute__SR__ResultInfo *input,
                            SGCompute__SR__ResultInfo_Closure closure,
                            void *closure_data)
{
    SGComputeResponser::getInstance()->releaseWork(input->magic);
    SGCompute__SR__ResultInfo result = SGCOMPUTE__SR__RESULT_INFO__INIT;
    result.magic = input->magic;
    result.status = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
    closure(&result, closure_data);
}


void SG_Response__run_work (SGCompute__SR__ComputeResponser_Service *service,
                 const SGCompute__SR__RunInfo *input,
                 SGCompute__SR__ResultInfo_Closure closure,
                 void *closure_data)
{
    bool res = SGComputeResponser::getInstance()->runWork((const void*)input);
    SGCompute__SR__ResultInfo result = SGCOMPUTE__SR__RESULT_INFO__INIT;
    result.magic = input->work_magic;
    FUNC_PRINT(result.magic);
    if (res)
    {
        result.status = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
    }
    else
    {
        result.status = SGCOMPUTE__SR__RESULT_INFO__STATUS__FAILED;
    }
    closure(&result, closure_data);
}




static SGCompute__SR__ComputeResponser_Service gResponser = SGCOMPUTE__SR__COMPUTE_RESPONSER__INIT(SG_Response__);


SGComputeResponser::SGComputeResponser(const char* port, const char* master_port)
{
    SGASSERT(NULL!=port);
    SGASSERT(NULL!=master_port);
    //TODO
    mComputeService = protobuf_c_rpc_server_new(PROTOBUF_C_RPC_ADDRESS_TCP, port, (ProtobufCService *) &gResponser, NULL);
    auto service = protobuf_c_rpc_client_new(PROTOBUF_C_RPC_ADDRESS_TCP, master_port, &sgcompute__sr__compute_server_waiter__descriptor, NULL);
    SGASSERT(NULL!=service);
    mReportClient = (ProtobufC_RPC_Client*)service;
    mDataBase = new GPFunctionDataBase;
    mWorkMagic = 1;
    mRunMagic = 1;
    mType = PROTOBUF_C_RPC_ADDRESS_TCP;//TODO
    mPort = port;
}

SGComputeResponser::~SGComputeResponser()
{
}

bool SGComputeResponser::install(const char* meta)
{
    auto stream_wrap = GPStreamFactory::NewStream(meta);
    mDataBase->loadXml(stream_wrap);
    stream_wrap->decRef();
    return true;
}

uint64_t SGComputeResponser::insertWork(const void* workInfo)
{
    const SGCompute__SR__WorkInfo* info = (const SGCompute__SR__WorkInfo*)workInfo;
    Work* work = NULL;
    if (SGCOMPUTE__SR__WORK_INFO__TYPE__REDUCE == info->type)
    {
        work = new ReduceWork;
    }
    else if (SGCOMPUTE__SR__WORK_INFO__TYPE__MAP == info->type)
    {
        work = new MapWork;
    }
    SGASSERT(NULL!=work);
    work->nInput = (int)info->n_inputs;
    work->pInputs = new GPPieces*[info->n_inputs];
    for (int i=0; i<info->n_inputs; ++i)
    {
        auto pieceInfo = info->inputs[i];
        char* path = pieceInfo->path;
        char* type = pieceInfo->type;
        GPPieces* piece = GPPieceFactory::createLocalFilePiece(mDataBase->queryType(type)
, path, 0);
        piece->nKeyNumber = (unsigned int)pieceInfo->n_key_dimesion;
        for (int j=0; j<pieceInfo->n_key_dimesion; ++j)
        {
            piece->pKeySize[j] = pieceInfo->key_dimesion[j];
        }
        work->pInputs[i] = piece;
    }
    {
        auto pieceInfo = info->output;
        char* path = pieceInfo->path;
        char* type = pieceInfo->type;
        GPPieces* piece = GPPieceFactory::createLocalFilePiece(mDataBase->queryType(type), path, 0);
        piece->nKeyNumber = (unsigned int)pieceInfo->n_key_dimesion;
        for (int j=0; j<pieceInfo->n_key_dimesion; ++j)
        {
            piece->pKeySize[j] = pieceInfo->key_dimesion[j];
        }
        work->pOutput = piece;
    }
    FUNC_PRINT_ALL(info->formula, s);
    FUNC_PRINT_ALL(info->inputtypes, s);
    //TODO
    work->pWorkFunction = mProducer->createFunction(info->formula, std::vector<const IStatusType*>());

    mWorks.insert(std::make_pair(mWorkMagic, work));
    return mWorkMagic++;
}

bool SGComputeResponser::releaseWork(uint64_t magic)
{
    auto iter = mWorks.find(magic);
    if (iter == mWorks.end())
    {
        return false;
    }
    delete iter->second;
    mWorks.erase(iter);
    return true;
}


SGComputeResponser::Work::Work()
{
    pInputs = NULL;
    nInput = 0;
    pOutput = NULL;
    pWorkFunction = NULL;
}

SGComputeResponser::Work::~Work()
{
    SGASSERT(NULL!=pInputs);
    SGASSERT(NULL!=pOutput);
    SGASSERT(NULL!=pWorkFunction);
    for (int i=0; i<nInput; ++i)
    {
        pInputs[i]->decRef();
    }
    delete [] pInputs;
    pOutput->decRef();
    pWorkFunction->decRef();
}

static GPContents* _getInputContent(GPPieces** pInputs, int nInput, unsigned int* pInputKeys, unsigned int keyNumber)
{
    GPContents* totalInput = new GPContents;
    int cur = 0;
    for (int i=0; i<nInput; ++i)
    {
        auto subInput = pInputs[i]->vLoad(pInputKeys+cur, pInputs[i]->nKeyNumber);
        cur+=pInputs[i]->nKeyNumber;
        SGASSERT(cur <= keyNumber);
        totalInput->merge(*subInput);
        subInput->decRef();
    }
    return totalInput;
}

bool SGComputeResponser::MapWork::vRun(const std::vector<GPPtr<KeyCombine>>& subWorks)
{
    /*TODO Filter subWorks, delete repeated outputkey*/
    for (auto key : subWorks)
    {
        //Construct input
        GPContents* totalInput = _getInputContent(pInputs, nInput, key->pInputKeys, key->nInputKeyNumber);
        auto output = pWorkFunction->vRun(totalInput);
        totalInput->decRef();
        pOutput->vSave(key->pOutputKeys, key->nOutuptKeyNumber, output);
        output->decRef();
    }
    return true;
}


bool SGComputeResponser::ReduceWork::vRun(const std::vector<GPPtr<KeyCombine>>& subWorks)
{
    /*Group Key by output*/
    std::vector<std::vector<GPPtr<KeyCombine>>> keygroups;
    for (auto key : subWorks)
    {
        auto outputKey = key->pOutputKeys;
        auto outputKeyNumber = key->nOutuptKeyNumber;
        bool find = false;
        for (auto& findKeyGroup : keygroups)
        {
            SGASSERT(!findKeyGroup.empty());
            find = true;
            SGASSERT(findKeyGroup[0]->nOutuptKeyNumber == outputKeyNumber);
            auto compareOutputKey = findKeyGroup[0]->pOutputKeys;
            for (int i=0; i<outputKeyNumber; ++i)
            {
                if (outputKey[i] != compareOutputKey[i])
                {
                    find = false;
                    break;
                }
            }
            if (find)
            {
                findKeyGroup.push_back(key);
                break;
            }
        }
        if (!find)
        {
            std::vector<GPPtr<KeyCombine>> group;
            group.push_back(key);
            keygroups.push_back(group);
        }
    }
    
    /*Run Work for Each Group*/
    for (auto group : keygroups)
    {
        SGASSERT(!group.empty());
        GPContents* output = _getInputContent(pInputs, nInput, group[0]->pInputKeys, group[0]->nInputKeyNumber);
        
        for (int i=1; i<group.size(); ++i)
        {
            GPContents* input = _getInputContent(pInputs, nInput, group[i]->pInputKeys, group[i]->nInputKeyNumber);
            input->merge(*output);
            auto newOutput = pWorkFunction->vRun(input);
            input->decRef();
            output->decRef();
            output = newOutput;
        }
        auto outputKey = group[0]->pOutputKeys;
        auto outputKeyNumber = group[0]->nOutuptKeyNumber;
        
        pOutput->vSave(outputKey, outputKeyNumber, output);
        output->decRef();
    }
    return true;
}

bool SGComputeResponser::runWork(const void* runInfo)
{
    auto input = (const SGCompute__SR__RunInfo*)runInfo;
    //FUNC_PRINT(input->n_work_content);
    auto iter = mWorks.find(input->work_magic);
    if (iter == mWorks.end())
    {
        return false;
    }
    auto work = iter->second;
    SGASSERT(NULL!=work);
    std::vector<GPPtr<SGComputeResponser::KeyCombine>> subWorks;
    for (int i=0; i<input->n_work_content; ++i)
    {
        auto w = input->work_content[i];
        GPPtr<SGComputeResponser::KeyCombine> keyCombine = new SGComputeResponser::KeyCombine((int)w->n_inputkeys, (int)w->n_outputkeys);
        
        for (int k=0; k<w->n_outputkeys; ++k)
        {
            keyCombine->pOutputKeys[k] = w->outputkeys[k];
        }
        for (int k=0; k<w->n_inputkeys; ++k)
        {
            keyCombine->pInputKeys[k] = w->inputkeys[k];
        }
        subWorks.push_back(keyCombine);
    }
    work->vRun(subWorks);
    return true;
}


static void Responser_Report(const SGCompute__SR__ResultInfo *message, void *closure_data)
{
    bool* c = (bool*)closure_data;
    *c = true;
}

bool SGComputeResponser::onSetup()
{
    mProducer = GPFactory::createProducer(mDataBase.get(), GPFactory::STREAM);
    while (!protobuf_c_rpc_client_is_connected(mReportClient))
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default());
    }
    
    SGCompute__SR__RegistorInfo info = SGCOMPUTE__SR__REGISTOR_INFO__INIT;
    std::ostringstream os;
    std::fstream inputIp("conf/ip.conf");
    std::string ipline;
    getline(inputIp, ipline);
    os << ipline << ":"<<mPort;
    auto ipinfo = os.str();
    info.info = (char*)ipinfo.c_str();
    info.type = SGCOMPUTE__SR__REGISTOR_INFO__TYPE__TCP;
    bool c = false;
    sgcompute__sr__compute_server_waiter__registor((ProtobufCService*)mReportClient, &info, Responser_Report, &c);
    while (!c)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default());
    }
    return true;
}
