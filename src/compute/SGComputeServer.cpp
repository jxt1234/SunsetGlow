#include "SGComputeServer.h"
#include "SGCompute.CS.pb-c.h"
#include <assert.h>
#include "SGDebug.h"
#include "core/GPPieceFactory.h"
#include "core/GPStreamFactory.h"
#include <sstream>
#include "backend/GPSingleParallelMachine.h"


SGComputeServer* SGComputeServer::gServer = NULL;

static void SG_compute__copy (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__CopyInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    auto server = SGComputeServer::getInstance();
    auto read = server->find(input->read_magic);
    auto write = server->find(input->write_magic);
    GPSingleParallelMachine machine;
    machine.vCopyPieces(read, write);
    SGCompute__CS__Result report = SGCOMPUTE__CS__RESULT__INIT;
    report.code = 0;
    report.magic = 0;
    closure(&report, closure_data);
}


static void SG_compute__execute (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__ComputeInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    auto server = SGComputeServer::getInstance();
    auto executor = server->findExecutor(input->executor);
    auto output = server->find(input->outputpiece);
    int inputNumber = (int)input->n_inputpieces;
    AUTOSTORAGE(inputs, GPPieces*, inputNumber);
    for (int i=0; i<inputNumber; ++i)
    {
        inputs[i] = server->find(input->inputpieces[i]);
    }
    //TODO check inputs

    bool result = executor->vRun(output, inputs, inputNumber);
    FUNC_PRINT(result);
    SGCompute__CS__Result report = SGCOMPUTE__CS__RESULT__INIT;
    report.magic = 0;
    report.code = 0;
    closure(&report, closure_data);
}

static bool _checkInput(const SGCompute__CS__PieceInfo* input)
{
    //TODO
    printf("path = %s\n", input->path);
    printf("keysize=");
    for (int i=0; i<input->n_keydimesion; ++i)
    {
        printf("%d,", input->keydimesion[i]);
    }
    printf("\n");
    return true;
}


void SG_compute__release (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__Result *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    auto server = SGComputeServer::getInstance();
    bool success = server->release(input->magic);
    SGCompute__CS__Result cs_result = SGCOMPUTE__CS__RESULT__INIT;
    if (!success)
    {
        cs_result.code = 1;
    }
    closure(&cs_result, closure_data);
}

static void SG_compute__create (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__PieceInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    if (!_checkInput(input))
    {
        SGASSERT(false);//TODO
    }
    SGCompute__CS__Result result =  SGCOMPUTE__CS__RESULT__INIT;
    unsigned int convertKeys[10];
    for (int i=0; i<input->n_keydimesion; ++i)
    {
        convertKeys[i] = input->keydimesion[i];
    }
    switch (input->piecetype)
    {
        case 1:
        {
            auto number = SGComputeServer::getInstance()->createCache(convertKeys, (int)(input->n_keydimesion));
            result.magic = number;
            break;
        }
        case 0:
        {
            auto number = SGComputeServer::getInstance()->createInput(input->path, input->datatype, convertKeys, (int)input->n_keydimesion);
            result.magic = number;
            break;
        }
        case 2:
        {
            auto number = SGComputeServer::getInstance()->createOutput(input->path);
            result.magic = number;
            break;
        }
        default:
            SGASSERT(false);
            break;
    }
    closure(&result, closure_data);
}

static void SG_compute__create_executor (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__ExecuteInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    GPParallelType data;
    auto server = SGComputeServer::getInstance();
    data.sFuncInfo.inputs = server->translateTypes(input->sfuncinfo->inputstype);
    data.sFuncInfo.formula = input->sfuncinfo->formula;
    data.sFuncInfo.parameter = input->sfuncinfo->parameter;
    for (int i=0; i<input->sfuncinfo->n_variablekey; ++i)
    {
        data.sFuncInfo.variableKey.push_back(std::make_pair(input->sfuncinfo->variablekey[i]->index, input->sfuncinfo->variablekey[i]->pos));
    }

    if (NULL!=input->sconditioninfo)
    {
        data.sVariableInfo = input->sconditioninfo->svariableinfo;
        data.sConditionInfo.sConditionFormula = input->sconditioninfo->sconditionformula;
    }
    data.mOutputKey.clear();
    for (int i=0; i<input->n_outputkey; ++i)
    {
        data.mOutputKey.push_back(std::make_pair(input->outputkey[i]->index, input->outputkey[i]->pos));
    }

    IParallelMachine::PARALLELTYPE type = IParallelMachine::MAP;
    if (input->type == 1)
    {
        type = IParallelMachine::REDUCE;
    }
    auto number = server->createExecutor(&data, type);
    
    SGCompute__CS__Result result_message = SGCOMPUTE__CS__RESULT__INIT;
    result_message.magic = number;
    result_message.code = 0;
    closure(&result_message, closure_data);
}


static SGCompute__CS__ComputeServer_Service create_service = SGCOMPUTE__CS__COMPUTE_SERVER__INIT(SG_compute__);




SGComputeServer::SGComputeServer()
{
    //TODO
    mServer = protobuf_c_rpc_server_new(PROTOBUF_C_RPC_ADDRESS_LOCAL, "3306", (ProtobufCService *) &create_service, NULL);
    mDataBase = new GPFunctionDataBase;
    mProducer = NULL;
    mCacheOrder = 0;
    mExecutorOrder = 0;
}

SGComputeServer::~SGComputeServer()
{
    protobuf_c_rpc_server_destroy(mServer, true);
    for (auto iter:mCachePieces)
    {
        iter.second->decRef();
    }
    for (auto iter:mExecutors)
    {
        iter.second->decRef();
    }
}
SGComputeServer* SGComputeServer::getInstance()
{
    //TODO Add lock
    if (NULL == gServer)
    {
        gServer = new SGComputeServer;
    }
    return gServer;
}

void SGComputeServer::addMetaFile(const char* metaFile)
{
    auto input = GPStreamFactory::NewStream(metaFile);
    mDataBase->loadXml(input);
    input->decRef();
    mProducer = GPFactory::createProducer(mDataBase.get(), GPFactory::STREAM);
}

void SGComputeServer::runLoop()
{
    for (;;)
    {
        //TODO Add mechanism to stop
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default());
    }
}

uint64_t SGComputeServer::createCache(unsigned int* keyDimesions, int keyNumber)
{
    SGASSERT(NULL!=keyDimesions);
    SGASSERT(keyNumber>0);
    uint64_t number = mCacheOrder + 1;
    mCacheOrder = mCacheOrder + 1;
    std::vector<unsigned int> keyDV;
    for (int i=0; i<keyNumber; ++i)
    {
        keyDV.push_back(keyDimesions[i]);
    }
    GPPieces* pieces = GPPieceFactory::createMemoryPiece(keyDV);
    mCachePieces.insert(std::make_pair(number, pieces));
    FUNC_PRINT((int)mCachePieces.size());
    return number;
}

std::vector<const IStatusType*> SGComputeServer::translateTypes(const std::string& typeInfos) const
{
    std::vector<const IStatusType*> typesV;
    std::string typeName;
    std::istringstream input(typeInfos);
    while (input >> typeName)
    {
        auto typeP = mDataBase->vQueryType(typeName);
        SGASSERT(NULL!=typeP);
        typesV.push_back(typeP);
    }
    return typesV;
}


uint64_t SGComputeServer::createInput(const char* path, const char* type, unsigned int* keyDimesions, int keyNumber)
{
    SGASSERT(NULL!=path);
    SGASSERT(NULL!=type);
    SGASSERT(NULL!=keyDimesions);
    SGASSERT(keyNumber>0);
    uint64_t number = mCacheOrder + 1;
    mCacheOrder = mCacheOrder + 1;
    GPPieces* pieces = GPPieceFactory::createLocalFilePiece(translateTypes(type), path, 0, false);
    pieces->nKeyNumber = keyNumber;
    for (int i=0; i<keyNumber; ++i)
    {
        pieces->pKeySize[i] = keyDimesions[i];
    }
    mCachePieces.insert(std::make_pair(number, pieces));
    FUNC_PRINT((int)mCachePieces.size());
    return number;
}
uint64_t SGComputeServer::createOutput(const char* path)
{
    SGASSERT(NULL!=path);
    uint64_t number = mCacheOrder + 1;
    mCacheOrder = mCacheOrder + 1;
    GPPieces* pieces = GPPieceFactory::createLocalFilePiece(std::vector<const IStatusType*>(), path, 0, true);
    mCachePieces.insert(std::make_pair(number, pieces));
    FUNC_PRINT((int)mCachePieces.size());
    return number;
}

bool SGComputeServer::release(uint64_t number)
{
    auto iter = mCachePieces.find(number);
    if (iter != mCachePieces.end())
    {
        iter->second->decRef();
        mCachePieces.erase(iter);
        FUNC_PRINT((int)mCachePieces.size());
        return true;
    }
    auto iter2 = mExecutors.find(number);
    if (iter2 != mExecutors.end())
    {
        iter2->second->decRef();
        mExecutors.erase(iter2);
        FUNC_PRINT((int)mExecutors.size());
        return true;
    }
    return false;
}
GPPieces* SGComputeServer::find(uint64_t number)
{
    auto iter = mCachePieces.find(number);
    if (iter == mCachePieces.end())
    {
        FUNC_PRINT(1);
        return NULL;
    }
    return iter->second;
}

IParallelMachine::Executor* SGComputeServer::findExecutor(uint64_t number)
{
    auto iter = mExecutors.find(number);
    if (iter == mExecutors.end())
    {
        FUNC_PRINT(1);
        return NULL;
    }
    return iter->second;
}

uint64_t SGComputeServer::createExecutor(GPParallelType* data, IParallelMachine::PARALLELTYPE type)
{
    data->pContext = mProducer.get();
    GPSingleParallelMachine machine;
    auto executor = machine.vPrepare(data, type);
    mExecutors.insert(std::make_pair(mExecutorOrder, executor));
    return mExecutorOrder++;
}
