#include "SGResponserExecutor.h"
#include "thread/MGPThread.h"
#include "SGDebug.h"
#include "SGCompute.SR.pb-c.h"
#include "utils/AutoStorage.h"
#include <sstream>
#include "SGMacro.h"

SGResponserExecutor::SGResponserExecutor(const std::vector<ProtobufC_RPC_Client*>& responsers, SGComputeServer::Reporter* report, GPPtr<Handler> handler, const GPParallelType* data)
{
    mTaskClients = responsers;
    mReport = report;
    mHandler = handler;
    mFormula = data->sFuncInfo.formula;
    std::ostringstream os;
    for (auto t : data->sFuncInfo.inputs)
    {
        os << t->name() <<" ";
    }
    mInputTypes = os.str();
}
SGResponserExecutor::~SGResponserExecutor()
{
}


static void SGCompute__SR__ResultInfo_Closure_CreateWork(const SGCompute__SR__ResultInfo *message, void *closure_data)
{
    uint64_t* magicP = (uint64_t*)closure_data;
    *magicP = message->magic;
}

class IntWrap : public GPRefCount
{
public:
    IntWrap(uint32_t* p)
    {
        mP = p;
    }
    virtual ~IntWrap()
    {
        delete [] mP;
    }
private:
    uint32_t* mP;
};

static void _copyFileInfo(SGCompute__SR__WorkInfo__FileInfo* dst, GPPieces* src, std::vector<std::string>& forrelease, std::vector<GPPtr<IntWrap>>& forReleaseKey)
{
    *dst = SGCOMPUTE__SR__WORK_INFO__FILE_INFO__INIT;
    dst->n_key_dimesion = src->nKeyNumber;
    dst->key_dimesion = new uint32_t[src->nKeyNumber];
    forReleaseKey.push_back(new IntWrap(dst->key_dimesion));
    for (int i=0; i<src->nKeyNumber; ++i)
    {
        dst->key_dimesion[i] = src->pKeySize[i];
    }
    dst->path = (char*)src->sInfo.c_str();
    std::ostringstream os;
    for (auto t : src->pTypes)
    {
        os << t->name() << " ";
    }
    size_t n = forrelease.size();
    forrelease.push_back(os.str());
    dst->type = (char*)forrelease[n].c_str();
    SGASSERT(0<src->sInfo.size());
//    FUNC_PRINT_ALL(dst->path, s);
//    FUNC_PRINT_ALL(dst->type, s);
}

bool SGResponserExecutor::vRun(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    uint64_t magic;
    SGCompute__SR__WorkInfo input = SGCOMPUTE__SR__WORK_INFO__INIT;
    SGCompute__SR__WorkInfo__FileInfo outputInfo = SGCOMPUTE__SR__WORK_INFO__FILE_INFO__INIT;
    std::vector<std::string> forRelease;
    std::vector<GPPtr<IntWrap>> forReleaseKey;
    _copyFileInfo(&outputInfo, output, forRelease, forReleaseKey);
    
    AUTOSTORAGE(totalInput, SGCompute__SR__WorkInfo__FileInfo, inputNumber);
    AUTOSTORAGE(totalInputP, SGCompute__SR__WorkInfo__FileInfo*, inputNumber);
    for (int ip=0; ip<inputNumber; ++ip)
    {
        _copyFileInfo(totalInput+ip, inputs[ip], forRelease, forReleaseKey);
        totalInputP[ip] = totalInput + ip;
    }
    
    input.type = SGCOMPUTE__SR__WORK_INFO__TYPE__MAP;//TODO
    input.n_inputs = inputNumber;
    input.output = &outputInfo;
    input.inputs = totalInputP;
    input.formula = (char*)mFormula.c_str();
    input.inputtypes = (char*)mInputTypes.c_str();
    input.parameters = NULL;
    SGASSERT(mFormula.size()>0);
    //SGASSERT(mInputTypes.size()>0);
    
    
    std::map<ProtobufC_RPC_Client*, uint64_t> maps;
    for (auto s : mTaskClients)
    {
        magic = 0;
        sgcompute__sr__compute_responser__create_work((ProtobufCService*)s, &input, SGCompute__SR__ResultInfo_Closure_CreateWork, &magic);
        while (magic == 0)
        {
//            SGServerBasicElement::getInstance()->waitForMessage();
        }
        maps.insert(std::make_pair(s, magic));
    }
    bool result = mHandler->vRun(output, inputs, inputNumber, mReport, maps);
    for (auto kv : maps)
    {
        magic = 0;
        SGCompute__SR__ResultInfo resultInput = SGCOMPUTE__SR__RESULT_INFO__INIT;
        resultInput.magic = kv.second;
        resultInput.status = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
        sgcompute__sr__compute_responser__release_work((ProtobufCService*)kv.first, &resultInput, SGCompute__SR__ResultInfo_Closure_CreateWork, &magic);
        while (magic == 0)
        {
//            SGServerBasicElement::getInstance()->waitForMessage();
        }
    }
    return result;
}


MapHandler::MapHandler(GPPtr<GPKeyIteratorFactory> factory)
{
    mFactory = factory;
}

MapHandler::~MapHandler()
{
}


static void Handler_SGCompute__SR__ResultInfo_Closure(const SGCompute__SR__ResultInfo *message, void *closure_data)
{
    bool* result = (bool*)closure_data;
    if (SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS == message->status)
    {
        *result = true;
    }
}


bool MapHandler::vRun(GPPieces* output, GPPieces** inputs, int inputNumber, SGComputeServer::Reporter* report, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const
{
    SGASSERT(NULL!=output);
    SGASSERT(NULL!=inputs);
    SGASSERT(NULL!=report);
    SGASSERT(slaveMagicMap.size() > 1);
    for (auto s : slaveMagicMap)
    {
        SGASSERT(NULL!=s.first);
    }
    GPPtr<IGPKeyIterator> iterator = mFactory->create(inputs, inputNumber, output);
    auto keySize = iterator->vGetSize();
    std::vector<SGResponserExecutor::WorkKey*> keys;
    SGResponserExecutor::WorkKey::generate(iterator.get(), keys);
    size_t pieceNumber = keys.size() / slaveMagicMap.size();
    if (pieceNumber <= 0)
    {
        pieceNumber = 1;
    }
    size_t sta = 0;
    int waitNumber = 0;
    for (auto kv : slaveMagicMap)
    {
        auto fin = sta + pieceNumber;
        if (fin > slaveMagicMap.size())
        {
            fin = slaveMagicMap.size();
        }
        if (sta >= fin)
        {
            break;
        }
        report->addListenContent(kv.second, waitNumber++);
        auto n = fin-sta;
        SGCompute__SR__RunInfo runInfo = SGCOMPUTE__SR__RUN_INFO__INIT;
        runInfo.n_work_content = n;
        runInfo.work_magic = kv.second;
        AUTOSTORAGE(units, SGCompute__SR__RunInfo__Unit, (int)(n));
        AUTOSTORAGE(units_inputsKeysTotal, uint32_t, (int)(n*keySize.first));
        AUTOSTORAGE(units_outputKeysTotal, uint32_t, (int)(n*keySize.second));
        for (size_t k=0; k<n; ++k)
        {
            units[k] = SGCOMPUTE__SR__RUN_INFO__UNIT__INIT;
            auto keyInput = keys[k+sta]->input();
            units[k].n_inputkeys = keySize.first;
            units[k].inputkeys = units_inputsKeysTotal + k*keySize.first;
            for (int p=0; p<keySize.first; ++p)
            {
                units[k].inputkeys[p] = keyInput[p];
            }

            auto keyOutput = keys[k+sta]->output();
            units[k].n_outputkeys = keySize.second;
            units[k].outputkeys = units_outputKeysTotal + k*keySize.second;
            for (int p=0; p<keySize.second; ++p)
            {
                units[k].outputkeys[p] = keyOutput[p];
            }
        }
        bool complete = false;
        sgcompute__sr__compute_responser__run_work((ProtobufCService*)kv.first, &runInfo, Handler_SGCompute__SR__ResultInfo_Closure, &complete);
        while (!complete)
        {
            //SGServerBasicElement::getInstance()->waitForMessage();
        }
        sta+=pieceNumber;
    }
    for (auto kv : slaveMagicMap)
    {
        report->waitForListener(kv.second);
    }
    for(auto k : keys)
    {
        delete k;
    }
    return true;
}

SGResponserExecutor::WorkKey::WorkKey(unsigned int inputSize, unsigned int outputSize)
{
    mInputKey = new unsigned int[inputSize];
    mOutputKey = new unsigned int[outputSize];
}

SGResponserExecutor::WorkKey::~WorkKey()
{
    delete [] mInputKey;
    delete [] mOutputKey;
}

void SGResponserExecutor::WorkKey::generate(IGPKeyIterator* iterator, std::vector<SGResponserExecutor::WorkKey*>& output)
{
    SGASSERT(NULL!=iterator);
    auto size = iterator->vGetSize();
    WorkKey* key = new WorkKey(size.first, size.second);
    bool hasData = iterator->vRewind(key->input(), key->output());
    if (!hasData)
    {
        delete key;
        return;
    }
    do
    {
        output.push_back(key);
        key = new WorkKey(size.first, size.second);
    }while(iterator->vNext(key->input(), key->output()));
    delete key;
}
