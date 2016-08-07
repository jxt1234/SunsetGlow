#include "SGComputeServer.h"
extern "C"{
#include "SGCompute.CS.pb-c.h"
}
#include <assert.h>
#include "SGDebug.h"

SGComputeServer* SGComputeServer::gServer = NULL;

static void SG_compute__compute (SGCompute__CS__ComputeServer_Service *service,
                          const SGCompute__CS__ComputeInfo *input,
                          SGCompute__CS__Result_Closure closure,
                          void *closure_data)
{
    
}

static bool _checkInput(const SGCompute__CS__PieceInfo* input)
{
    //TODO
    printf("describe = %s\n", input->describe);
    printf("keysize=");
    for (int i=0; i<input->n_keydimesion; ++i)
    {
        printf("%d,", input->keydimesion[i]);
    }
    printf("\n");
    return true;
}


void SG_compute__release (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__PieceInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    auto server = SGComputeServer::getInstance();
    bool success = server->releaseCache(input->magic);
    SGCompute__CS__Result cs_result = SGCOMPUTE__CS__RESULT__INIT;
    if (!success)
    {
        cs_result.code = SGCOMPUTE__CS__RESULT__STATUS_CODE__FAIL;
    }
    closure(&cs_result, closure_data);
}

class GPPiecesServer:public GPPieces
{
public:
    GPPiecesServer(){}
    virtual ~ GPPiecesServer(){}
    
    virtual GPContents* vLoad(unsigned int* pKey, unsigned int keynum)
    {
        SGASSERT(false);//TODO
        return NULL;
    }
    
    virtual long vPreMeasure(unsigned int* pKey, unsigned int keynum) const {return -1;}
    
    virtual void vSave(unsigned int* pKey, unsigned int keynum, GPContents* c)
    {
        SGASSERT(false);//TODO
    }
    
};


static void SG_compute__create (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__PieceInfo *input, SGCompute__CS__PieceInfo_Closure closure, void *closure_data)
{
    if (!_checkInput(input))
    {
        SGASSERT(false);//TODO
    }
    SGCompute__CS__PieceInfo result =  SGCOMPUTE__CS__PIECE_INFO__INIT;
    result.n_keydimesion = input->n_keydimesion;
    result.keydimesion = input->keydimesion;
    result.type = input->type;
    result.describe = input->describe;
    if (SGCOMPUTE__CS__PIECE_INFO__TYPE__CACHE == input->type)
    {
        unsigned int convertKeys[10];
        for (int i=0; i<input->n_keydimesion; ++i)
        {
            convertKeys[i] = input->keydimesion[i];
        }
        unsigned int number = SGComputeServer::getInstance()->createCache(convertKeys, (int)(input->n_keydimesion));
        result.magic = number;
    }
    closure(&result, closure_data);
}


static SGCompute__CS__ComputeServer_Service create_service = SGCOMPUTE__CS__COMPUTE_SERVER__INIT(SG_compute__);




SGComputeServer::SGComputeServer()
{
    //TODO
    mServer = protobuf_c_rpc_server_new(PROTOBUF_C_RPC_ADDRESS_LOCAL, "3306", (ProtobufCService *) &create_service, NULL);
}

SGComputeServer::~SGComputeServer()
{
    protobuf_c_rpc_server_destroy(mServer, true);
    for (auto iter:mCachePieces)
    {
        iter.second->decRef();
    }
    for (auto iter:mOutputPieces)
    {
        iter.second->decRef();
    }
    for (auto iter:mInputPieces)
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
    uint64_t number = mCacheOrder + 1;
    mCacheOrder = mCacheOrder + 1;
    GPPieces* pieces = new GPPiecesServer;
    mCachePieces.insert(std::make_pair(number, pieces));
    FUNC_PRINT((int)mCachePieces.size());
    return number;
}
bool SGComputeServer::releaseCache(uint64_t number)
{
    auto iter = mCachePieces.find(number);
    if (iter == mCachePieces.end())
    {
        FUNC_PRINT(1);
        return false;
    }
    iter->second->decRef();
    mCachePieces.erase(iter);
    FUNC_PRINT((int)mCachePieces.size());
    return true;
}
GPPieces* SGComputeServer::findCache(uint64_t number)
{
    auto iter = mCachePieces.find(number);
    if (iter == mCachePieces.end())
    {
        FUNC_PRINT(1);
        return NULL;
    }
    return iter->second;
}

