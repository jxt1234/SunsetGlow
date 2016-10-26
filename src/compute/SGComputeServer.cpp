#include "SGComputeServer.h"
#include "SGCompute.CS.pb-c.h"
#include "SGCompute.SR.pb-c.h"
#include <assert.h>
#include "SGDebug.h"
#include "SGMacro.h"
#include "core/GPPieceFactory.h"
#include "core/GPStreamFactory.h"
#include <sstream>
#include "backend/GPSingleParallelMachine.h"
#include "thread/MGPThread.h"
#include "SGResponserExecutor.h"
#include "SGHandler.h"
static void _setPieceKey(GPPieces* pieces, unsigned int* keyDimesions, int keyNumber)
{
    pieces->nKeyNumber = keyNumber;
    for (int i=0; i<keyNumber; ++i)
    {
        pieces->pKeySize[i] = keyDimesions[i];
    }
    if (0 == keyNumber)
    {
        pieces->nKeyNumber = 1;
        pieces->pKeySize[0] = 1;
    }
}


SGComputeServer* SGComputeServer::gServer = NULL;

class AddResponserWork : public SGBasicServer::Work
{
public:
    AddResponserWork(ProtobufC_RPC_Client* client, const char* message)
    {
        mClient = client;
        mMessage = message;
    }
    
    virtual ~ AddResponserWork()
    {
        
    }
    
    virtual STATUS vRun()
    {
        if (protobuf_c_rpc_client_is_connected(mClient))
        {
            GPPRINT_FL("Connected %s", mMessage.c_str());
            SGComputeServer::getInstance()->addResponser(mClient);
            return SUCCESS;
        }
        return WAIT;
    }
private:
    ProtobufC_RPC_Client* mClient;
    std::string mMessage;
};


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


class PieceExecuteWork : public SGBasicServer::Work
{
public:
    PieceExecuteWork(const SGCompute__CS__ComputeInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
    {
        auto server = SGComputeServer::getInstance();
        mExecutor = server->findExecutor(input->executor);
        mOutput = server->find(input->outputpiece);
        mInputNumber = (int)input->n_inputpieces;
        mInputs = new GPPieces*[mInputNumber];
        for (int i=0; i<mInputNumber; ++i)
        {
            mInputs[i] = server->find(input->inputpieces[i]);
        }
        //TODO check inputs
        
        mClosure = closure;
        mClosureData = closure_data;
    }
    virtual ~PieceExecuteWork()
    {
        delete [] mInputs;
    }
    
    virtual STATUS vRun()
    {
        bool success = mExecutor->vRun(mOutput, mInputs, mInputNumber);
        if (success)
        {
            SGCompute__CS__Result report = SGCOMPUTE__CS__RESULT__INIT;
            report.magic = 0;
            report.code = 0;
            mClosure(&report, mClosureData);
            return SUCCESS;
        }
        return WAIT;
    }
private:
    GPPieces* mOutput;
    GPPieces** mInputs;
    SGCompute__CS__Result_Closure mClosure;
    void* mClosureData;
    int mInputNumber;
    IParallelMachine::Executor* mExecutor;
};


static void SG_compute__execute (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__ComputeInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    auto server = SGComputeServer::getInstance();
    SGBasicServer::Work* work = new PieceExecuteWork(input, closure, closure_data);
    server->addWork(work);
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
            auto number = SGComputeServer::getInstance()->createCache(convertKeys, (int)(input->n_keydimesion), input->datatype);
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
            auto number = SGComputeServer::getInstance()->createOutput(input->path, input->datatype, convertKeys, (int)input->n_keydimesion);
            result.magic = number;
            break;
        }
        default:
            SGASSERT(false);
            break;
    }
    SGPRINT_FL("Create pieces: %d keys, key[0]=%d, magic = %ld", input->n_keydimesion, convertKeys[0], result.magic);
    closure(&result, closure_data);
}

static void SG_compute__create_executor (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__ExecuteInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    GPParallelType data;
    auto server = SGComputeServer::getInstance();
    data.sFuncInfo.inputs = server->translateTypes(input->sfuncinfo->inputstype);
    //SGASSERT(data.sFuncInfo.inputs.size()>0);
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

static void SG_compute_wait_report_success(SGCompute__SR__ComputeServerWaiter_Service *service,
                       const SGCompute__SR__ResultInfo *input,
                       SGCompute__SR__ResultInfo_Closure closure,
                       void *closure_data)
{
    SGCompute__SR__ResultInfo outputResult = SGCOMPUTE__SR__RESULT_INFO__INIT;
    outputResult.magic = input->magic;
    outputResult.status = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
    closure(&outputResult, closure_data);
}

static void SG_compute_wait_registor(SGCompute__SR__ComputeServerWaiter_Service *service,
                                           const SGCompute__SR__RegistorInfo *input,
                                           SGCompute__SR__ResultInfo_Closure closure,
                                           void *closure_data)
{
    SGCompute__SR__ResultInfo outputResult = SGCOMPUTE__SR__RESULT_INFO__INIT;
    auto type = PROTOBUF_C_RPC_ADDRESS_TCP;
    const char* port = input->info;
    FUNC_PRINT_ALL(port, s);
    if (input->type == SGCOMPUTE__SR__REGISTOR_INFO__TYPE__TCP)
    {
        type = PROTOBUF_C_RPC_ADDRESS_TCP;
    }
    auto responseClient = protobuf_c_rpc_client_new(type, port, &sgcompute__sr__compute_responser__descriptor, NULL);
    SGComputeServer::getInstance()->addWork(new AddResponserWork((ProtobufC_RPC_Client*)responseClient, port));
    outputResult.magic = -1;
    outputResult.status = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
    closure(&outputResult, closure_data);
}



static SGCompute__CS__ComputeServer_Service create_service = SGCOMPUTE__CS__COMPUTE_SERVER__INIT(SG_compute__);


static SGCompute__SR__ComputeServerWaiter_Service wait_service = SGCOMPUTE__SR__COMPUTE_SERVER_WAITER__INIT(SG_compute_wait_);



SGComputeServer::SGComputeServer()
{
    //TODO
    mServer = protobuf_c_rpc_server_new(PROTOBUF_C_RPC_ADDRESS_TCP, SGSERVER_PORT, (ProtobufCService *) &create_service, NULL);
    mReportServer = protobuf_c_rpc_server_new(PROTOBUF_C_RPC_ADDRESS_TCP, SGREPORT_PORT, (ProtobufCService *) &wait_service, NULL);
    mDataBase = new GPFunctionDataBase;
    mProducer = NULL;
    mCacheOrder = 0;
    
}

SGComputeServer::~SGComputeServer()
{
    protobuf_c_rpc_server_destroy(mServer, true);
    protobuf_c_rpc_server_destroy(mReportServer, true);
    for (auto iter:mCachePieces)
    {
        iter.second->decRef();
    }
    for (auto iter:mExecutors)
    {
        iter.second->decRef();
    }
    for (auto c : mResponseClients)
    {
        auto service = (ProtobufCService*)c;
        service->destroy(service);
    }
}


void SGComputeServer::addResponser(ProtobufC_RPC_Client* client)
{
    mResponseClients.push_back(client);
}


void SGComputeServer::init(const char* configFile)
{
    SGASSERT(NULL==gServer);
    gServer = new SGComputeServer;
    //GPPtr<GPStream> readStream = GPStreamFactory::NewStream(configFile);
}

SGComputeServer* SGComputeServer::getInstance()
{
    SGASSERT(NULL!=gServer);
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

uint64_t SGComputeServer::createCache(unsigned int* keyDimesions, int keyNumber, const char* type)
{
    SGASSERT(NULL!=keyDimesions);
    SGASSERT(keyNumber>0);
    uint64_t number = mCacheOrder + 1;
    mCacheOrder = mCacheOrder + 1;
    std::ostringstream os;
    os << "cache/"<<number;
    GPPieces* pieces = GPPieceFactory::createLocalFilePiece(translateTypes(type), os.str().c_str(), 0);
    mCachePieces.insert(std::make_pair(number, pieces));
    _setPieceKey(pieces, keyDimesions, keyNumber);
    pieces->sInfo = os.str();
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
    GPPieces* pieces = GPPieceFactory::createLocalFilePiece(translateTypes(type), path, 0);
    _setPieceKey(pieces, keyDimesions, keyNumber);
    mCachePieces.insert(std::make_pair(number, pieces));
    pieces->sInfo = path;
    return number;
}
uint64_t SGComputeServer::createOutput(const char* path, const char* type, unsigned int* keyDimesions, int keyNumber)
{
    SGASSERT(NULL!=path);
//    SGASSERT(NULL!=type);
//    SGASSERT(NULL!=keyDimesions);
//    SGASSERT(keyNumber>0);
    uint64_t number = mCacheOrder + 1;
    mCacheOrder = mCacheOrder + 1;
    GPPieces* pieces = GPPieceFactory::createLocalFilePiece(translateTypes(type), path, 0);
    _setPieceKey(pieces, keyDimesions, keyNumber);
    mCachePieces.insert(std::make_pair(number, pieces));
    pieces->sInfo = path;
    return number;

}

bool SGComputeServer::release(uint64_t number)
{
    auto iter = mCachePieces.find(number);
    if (iter != mCachePieces.end())
    {
        iter->second->decRef();
        mCachePieces.erase(iter);
        GPPRINT_FL("released %d cache, current size=%d", (int)number, (int)mCachePieces.size());
        return true;
    }
    auto iter2 = mExecutors.find(number);
    if (iter2 != mExecutors.end())
    {
        iter2->second->decRef();
        mExecutors.erase(iter2);
        return true;
    }
    return false;
}
GPPieces* SGComputeServer::find(uint64_t number)
{
    auto iter = mCachePieces.find(number);
    if (iter == mCachePieces.end())
    {
        FUNC_PRINT(number);
        return NULL;
    }
    return iter->second;
}

IParallelMachine::Executor* SGComputeServer::findExecutor(uint64_t number)
{
    auto iter = mExecutors.find(number);
    if (iter == mExecutors.end())
    {
        FUNC_PRINT(number);
        return NULL;
    }
    return iter->second;
}

bool SGComputeServer::onSetup()
{
    return true;
}


uint64_t SGComputeServer::createExecutor(GPParallelType* data, IParallelMachine::PARALLELTYPE type)
{
    data->pContext = mProducer.get();
    mCacheOrder+=1;
    if (type == IParallelMachine::REDUCE || mResponseClients.empty())
    {
        GPSingleParallelMachine machine;
        auto executor = machine.vPrepare(data, type);
        mExecutors.insert(std::make_pair(mCacheOrder, executor));
    }
    else
    {
        //FUNC_PRINT(data->mOutputKey.size());
        GPPtr<GPKeyIteratorFactory> keyIteratorFactory = new GPKeyIteratorFactory(data);
        GPPtr<SGResponserExecutor::Handler> handler = new SGMapHandler(keyIteratorFactory);
        SGResponserExecutor* executor = new SGResponserExecutor(mResponseClients, handler, data);
        mExecutors.insert(std::make_pair(mCacheOrder, executor));
    }
    return mCacheOrder;
}
