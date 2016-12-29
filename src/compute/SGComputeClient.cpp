#include "SGCompute.CS.pb-c.h"
#include <assert.h>
#include "SGComputeClient.h"
#include "SGDebug.h"
#include "utils/AutoStorage.h"
#include "core/GPPieceFactory.h"
#include "ALDynamicBuffer.h"
#include <sstream>
#include <fstream>
#include "SGMacro.h"

SGComputeClient::SGComputeClient()
{
    //FIXME
    std::ifstream serverConf("conf/server.conf");
    std::string serverPort;
    std::getline(serverConf, serverPort);
    auto service = protobuf_c_rpc_client_new(PROTOBUF_C_RPC_ADDRESS_TCP, serverPort.c_str(), &sgcompute__cs__compute_server__descriptor, NULL);
    SGASSERT(NULL!=service);
    mClient = (ProtobufC_RPC_Client*)service;
    protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    while (!protobuf_c_rpc_client_is_connected (mClient))
    {
        FUNC_PRINT(1);
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    //protobuf_c_rpc_client_set_autoreconnect_period (mClient, 10);
}
SGComputeClient::~SGComputeClient()
{
    auto service = (ProtobufCService*)mClient;
    service->destroy(service);
}

struct ClosureDataGPPieces
{
    GPPieces* pResult;
    const IStatusType* pType = NULL;
    const char* pPath = NULL;
    ProtobufCService* pServer;
};

static void Magic_Handle_Release(const SGCompute__CS__Result *message, void *closure_data)
{
    protobuf_c_boolean* closure = (protobuf_c_boolean*)closure_data;
    *closure = 1;
}

struct FileClosureData
{
    GPContents** contents;
    const IStatusType* type;
};

class MemoryStream:public GPStream
{
public:
    MemoryStream(uint8_t* buffer, size_t len):mBuffer(buffer), mLength(len){}
    virtual ~ MemoryStream(){}
    virtual size_t vRead(void* buffer, size_t size)
    {
        if (size > mLength - mCur)
        {
            size = mLength-mCur;
        }
        if (size == 0)
        {
            return 0;
        }
        ::memcpy(buffer, mBuffer+mCur, size);
        
        mCur+=size;
        return size;
    }
    virtual bool vIsEnd() const
    {
        return mCur>=mLength;
    }
    virtual bool vRewind()
    {
        mCur = 0;
        return true;
    }
private:
    size_t mCur = 0;
    uint8_t* mBuffer;
    size_t mLength;
};

class MemoryWStream:public GPWStream
{
public:
    MemoryWStream(ALDynamicBuffer* buffer):mBuffer(buffer){}
    virtual ~MemoryWStream() {}
    virtual size_t vWrite(const void* buffer, size_t size)
    {
        mBuffer->load((char*)buffer, size);
        return size;
    }
    virtual bool vFlush()
    {
        return true;
    }
private:
    ALDynamicBuffer* mBuffer;
};


static void __Load__FileContent_Closure(const SGCompute__CS__FileContent *message, void *closure_data)
{
    SGASSERT(NULL!=message);
    SGASSERT(message->has_contents);
    auto fileClosureData = (FileClosureData*)closure_data;
    SGASSERT(NULL!=fileClosureData->contents);
    SGASSERT(NULL!=fileClosureData->type);
    MemoryStream memoryStream(message->contents.data, message->contents.len);
    auto result = new GPContents;
    result->push(fileClosureData->type->vLoad(&memoryStream), fileClosureData->type);
    *fileClosureData->contents = result;
}

static void __Write__FileContent_Closure(const SGCompute__CS__FileContent *message, void *closure_data)
{
    SGASSERT(NULL!=message);
    //SGASSERT(message->has_contents);
    auto fileClosureData = (FileClosureData*)closure_data;
    
    //Mark it as NULL
    fileClosureData->type = NULL;
    fileClosureData->contents = NULL;
}



class GPPiecesClient:public GPPieces
{
public:
    GPPiecesClient(const char* path, const IStatusType* type, uint64_t magic, ProtobufCService* server):mMagic(magic), mServer(server)
    {
        mPath = path;
        mType = type;
    }
    virtual ~ GPPiecesClient()
    {
        SGCompute__CS__Result pieceInfo = SGCOMPUTE__CS__RESULT__INIT;
        pieceInfo.magic = mMagic;
        protobuf_c_boolean ClosureDataGPPieces = 0;
        SGPRINT_FL("release pieces: %ld", mMagic);
        sgcompute__cs__compute_server__release(mServer, &pieceInfo, Magic_Handle_Release, &ClosureDataGPPieces);
        while (0 == ClosureDataGPPieces)
        {
            protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
        }
    }
    uint64_t get() const {return mMagic;}
    
    virtual GPContents* vLoad(unsigned int* pKey, unsigned int keynum)
    {
        auto filePath = GPPieceFactory::getFilePath(pKey, keynum, mType->name(), mPath);
        SGCompute__CS__FileContent input;
        sgcompute__cs__file_content__init(&input);
        input.file_name = (char*)filePath.c_str();
        FileClosureData data;
        GPContents* c = NULL;
        data.contents = &c;
        data.type = mType;
        sgcompute__cs__compute_server__download(mServer, &input, __Load__FileContent_Closure, &data);
        while (NULL == *data.contents)
        {
            protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
        }
        return c;
    }
    
    virtual long vPreMeasure(unsigned int* pKey, unsigned int keynum) const {return -1;}
    
    virtual void vSave(unsigned int* pKey, unsigned int keynum, GPContents* c)
    {
        SGASSERT(NULL!=c);
        ALDynamicBuffer buffer(4096);
        MemoryWStream output(&buffer);
        c->getContent(0)->type()->vSave(c->get(0), &output);

        auto filePath = GPPieceFactory::getFilePath(pKey, keynum, mType->name(), mPath);
        SGCompute__CS__FileContent input;
        sgcompute__cs__file_content__init(&input);
        input.file_name = (char*)filePath.c_str();
        input.contents.data = (uint8_t*)buffer.content();
        input.contents.len = buffer.size();
        FileClosureData data;
        data.contents = NULL;
        data.type = mType;
        sgcompute__cs__compute_server__upload(mServer, &input, __Write__FileContent_Closure, &data);

        while (data.type == NULL)
        {
            protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
        }
        
    }
private:
    uint64_t mMagic;
    ProtobufCService* mServer;
    const IStatusType* mType;
    std::string mPath;

};

class ExecutorClient:public IParallelMachine::Executor
{
public:
    ExecutorClient(uint64_t magic, ProtobufCService* server):mMagic(magic), mServer(server){}
    virtual ~ ExecutorClient()
    {
        SGCompute__CS__Result pieceInfo = SGCOMPUTE__CS__RESULT__INIT;
        pieceInfo.magic = mMagic;
        protobuf_c_boolean result = 0;
        sgcompute__cs__compute_server__release(mServer, &pieceInfo, Magic_Handle_Release, &result);
        while (0 == result)
        {
            protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
        }
    }
    uint64_t get() const {return mMagic;}
    
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber) const override
    {
        SGCompute__CS__ComputeInfo computeInfo = SGCOMPUTE__CS__COMPUTE_INFO__INIT;
        computeInfo.n_inputpieces = inputNumber;
        computeInfo.executor = mMagic;
        computeInfo.outputpiece = ((GPPiecesClient*)output)->get();
        AUTOSTORAGE(inputMagics, uint64_t, inputNumber);
        for (int i=0; i<inputNumber; ++i)
        {
            inputMagics[i] = ((GPPiecesClient*)inputs[i])->get();
        }
        computeInfo.inputpieces = inputMagics;
        protobuf_c_boolean result = 0;
        sgcompute__cs__compute_server__execute(mServer, &computeInfo, Magic_Handle_Release, &result);
        while (0 == result)
        {
            protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
        }
        return true;
    }

private:
    uint64_t mMagic;
    ProtobufCService* mServer;
    
};

static void handle_create_response_cache(const SGCompute__CS__Result *result,
                       void *closure_data)
{
    if (NULL == result)
    {
        SGASSERT(false);
        return;
    }
    /*TODO check result*/
    ClosureDataGPPieces* _r = (ClosureDataGPPieces*)closure_data;
    FUNC_PRINT((int)result->magic);
    
    GPPieces* piece_result = new GPPiecesClient(_r->pPath, _r->pType, result->magic, _r->pServer);
    _r->pResult = piece_result;
}

struct ClosureDataExecutor
{
    ProtobufCService* pServer;
    IParallelMachine::Executor* pResult;
};

static void handle_create_response_execute(const SGCompute__CS__Result *result,
                                         void *closure_data)
{
    if (NULL == result)
    {
        SGASSERT(false);
        return;
    }
    /*TODO check result*/
    ClosureDataExecutor* _r = (ClosureDataExecutor*)closure_data;
    FUNC_PRINT((int)result->magic);
    IParallelMachine::Executor* executor = new ExecutorClient(result->magic, _r->pServer);
    _r->pResult = executor;
}


static void do_nothing (ProtobufCRPCDispatch *dispatch, void *unused)
{
}

static void run_main_loop_without_blocking (ProtobufCRPCDispatch *dispatch)
{
    protobuf_c_rpc_dispatch_add_idle (dispatch, do_nothing, NULL);
    protobuf_c_rpc_dispatch_run (dispatch);
}

IParallelMachine::Executor* SGComputeClient::vPrepare(const GPParallelType* data, PARALLELTYPE type) const
{
    SGASSERT(NULL!=data);
    FUNC_PRINT_ALL(data->sFuncInfo.formula.c_str(), s);
    SGCompute__CS__ExecuteInfo executoInfo = SGCOMPUTE__CS__EXECUTE_INFO__INIT;
    
    executoInfo.n_outputkey = data->mOutputKey.size();
    AUTOSTORAGE(outputKey, SGCompute__CS__ExecuteInfo__Key, (int)data->mOutputKey.size());
    AUTOSTORAGE(outputKeyPoint, SGCompute__CS__ExecuteInfo__Key*, (int)data->mOutputKey.size());
    for (int i=0; i<data->mOutputKey.size(); ++i)
    {
        outputKey[i] = SGCOMPUTE__CS__EXECUTE_INFO__KEY__INIT;
        outputKey[i].index = data->mOutputKey[i].first;
        outputKey[i].pos = data->mOutputKey[i].second;
        outputKeyPoint[i] = outputKey + i;
    }
    executoInfo.outputkey = outputKeyPoint;

    _SGCompute__CS__ExecuteInfo__FuncInfo sfuncinfo = SGCOMPUTE__CS__EXECUTE_INFO__FUNC_INFO__INIT;
    executoInfo.sfuncinfo = &sfuncinfo;
    executoInfo.sfuncinfo->n_variablekey = data->sFuncInfo.variableKey.size();
    executoInfo.sfuncinfo->formula = (char*)data->sFuncInfo.formula.c_str();

    AUTOSTORAGE(variableKey, SGCompute__CS__ExecuteInfo__Key, (int)data->sFuncInfo.variableKey.size());
    AUTOSTORAGE(variableKeyPoint, SGCompute__CS__ExecuteInfo__Key*, (int)data->sFuncInfo.variableKey.size());
    for (int i=0; i<data->sFuncInfo.variableKey.size(); ++i)
    {
        variableKey[i] = SGCOMPUTE__CS__EXECUTE_INFO__KEY__INIT;
        variableKey[i].index = data->sFuncInfo.variableKey[i].first;
        variableKey[i].pos = data->sFuncInfo.variableKey[i].second;
        variableKeyPoint[i] = variableKey + i;
    }
    executoInfo.sfuncinfo->variablekey = variableKeyPoint;
    executoInfo.sfuncinfo->parameter = (char*)data->sFuncInfo.parameter.c_str();
    std::ostringstream os;
    for (auto t : data->sFuncInfo.inputs)
    {
        os << t->name() <<" ";
    }
    auto typeString = os.str();
    executoInfo.sfuncinfo->inputstype = (char*)typeString.c_str();

    SGCompute__CS__ExecuteInfo__FormulaInfo sconditioninfo = SGCOMPUTE__CS__EXECUTE_INFO__FORMULA_INFO__INIT;
    if (data->sConditionInfo.sConditionFormula.size() > 0)
    {
        executoInfo.sconditioninfo = &sconditioninfo;
        executoInfo.sconditioninfo->sconditionformula = (char*)data->sConditionInfo.sConditionFormula.c_str();
        executoInfo.sconditioninfo->svariableinfo = (char*)data->sVariableInfo.c_str();
    }
    
    if (IParallelMachine::REDUCE == type)
    {
        executoInfo.type = 1;
    }
    else
    {
        executoInfo.type = 0;
    }

    ClosureDataExecutor closure;
    closure.pResult = NULL;
    closure.pServer = (ProtobufCService*)mClient;
    sgcompute__cs__compute_server__create_executor((ProtobufCService*)mClient, &executoInfo, handle_create_response_execute, &closure);
    while (NULL == closure.pResult)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    return closure.pResult;
}

GPPieces* SGComputeClient::vCreatePieces(const char* description, std::vector<const IStatusType*> types, unsigned int* keys, int keyNum, USAGE usage) const
{
    SGASSERT(1 == types.size());
    ProtobufCService* server = (ProtobufCService*)mClient;
    SGCompute__CS__PieceInfo pieceInfo = SGCOMPUTE__CS__PIECE_INFO__INIT;
    
    char* describe = (char*)description;
    char* cacheDescribe = (char*)"CACHE";
    std::string dataTypeString;
    pieceInfo.n_keydimesion = keyNum;
    pieceInfo.keydimesion= keys;
    pieceInfo.path = describe;
    std::ostringstream os;
    for (auto t : types)
    {
        os << t->name() << " ";
    }
    dataTypeString = os.str();
    pieceInfo.datatype = (char*)dataTypeString.c_str();
    switch (usage)
    {
        case IParallelMachine::INPUT:
        {
            pieceInfo.piecetype = 0;
            break;
        }
        case IParallelMachine::CACHE:
            pieceInfo.path = cacheDescribe;
            pieceInfo.piecetype = 1;
            break;
        case IParallelMachine::OUTPUT:
            pieceInfo.piecetype = 2;
            break;
        default:
            SGASSERT(false);
            break;
    }
    ClosureDataGPPieces closureDataGPPieces;
    closureDataGPPieces.pResult = NULL;
    closureDataGPPieces.pServer = server;
    closureDataGPPieces.pType = types[0];
    closureDataGPPieces.pPath = pieceInfo.path;
    sgcompute__cs__compute_server__create(server, &pieceInfo, handle_create_response_cache, &closureDataGPPieces);
    while (NULL == closureDataGPPieces.pResult)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    closureDataGPPieces.pResult->nKeyNumber = keyNum;
    for (int i=0; i<keyNum; ++i)
    {
        closureDataGPPieces.pResult->pKeySize[i] = keys[i];
    }
    return closureDataGPPieces.pResult;
}

bool SGComputeClient::vCopyPieces(GPPieces* readPieces, GPPieces* writePieces) const
{
    SGCompute__CS__CopyInfo copyInfo = SGCOMPUTE__CS__COPY_INFO__INIT;
    copyInfo.read_magic = ((GPPiecesClient*)readPieces)->get();
    copyInfo.write_magic = ((GPPiecesClient*)writePieces)->get();
    protobuf_c_boolean result = 0;
    sgcompute__cs__compute_server__copy((ProtobufCService*)mClient, &copyInfo, Magic_Handle_Release, &result);
    while (0 == result)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    return true;
}

IParallelMachine* libSunsetGlow_PARALLELMACHINE_CREATE_FUNC(const std::string& name)
{
    if (name == "server")
    {
        return new SGComputeClient;
    }
    return NULL;
}
