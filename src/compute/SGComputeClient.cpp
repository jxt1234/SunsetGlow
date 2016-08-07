extern "C"{
#include "SGCompute.CS.pb-c.h"
}
#include <assert.h>
#include "SGComputeClient.h"
#include "SGDebug.h"

SGComputeClient::SGComputeClient()
{
    //FIXME
    auto service = protobuf_c_rpc_client_new(PROTOBUF_C_RPC_ADDRESS_LOCAL, "3306", &sgcompute__cs__compute_server__descriptor, NULL);
    assert(NULL!=service);
    mClient = (ProtobufC_RPC_Client*)service;
    //protobuf_c_rpc_client_set_autoreconnect_period (mClient, 10);
}
SGComputeClient::~SGComputeClient()
{
    auto service = (ProtobufCService*)mClient;
    service->destroy(service);
}

struct ClosureData
{
    GPPieces* pResult;
    ProtobufCService* pServer;
};

static void GPPiecesClient_Handle_Release(const SGCompute__CS__Result *message, void *closure_data)
{
    protobuf_c_boolean* closure = (protobuf_c_boolean*)closure_data;
    *closure = 1;
}


class GPPiecesClient:public GPPieces
{
public:
    GPPiecesClient(uint64_t magic, ProtobufCService* server):mMagic(magic), mServer(server){}
    virtual ~ GPPiecesClient()
    {
        SGCompute__CS__PieceInfo pieceInfo = SGCOMPUTE__CS__PIECE_INFO__INIT;
        char* describe = (char*)"CACHE";
        pieceInfo.describe = describe;
        pieceInfo.magic = mMagic;
        protobuf_c_boolean closureData = 0;
        sgcompute__cs__compute_server__release(mServer, &pieceInfo, GPPiecesClient_Handle_Release, &closureData);
        while (0 == closureData)
        {
            protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
        }
    }
    
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
private:
    uint64_t mMagic;
    ProtobufCService* mServer;

};

static void handle_create_response_cache(const SGCompute__CS__PieceInfo *result,
                       void *closure_data)
{
    if (NULL == result)
    {
        FUNC_PRINT(1);
        return;
    }
    /*TODO check result*/
    ClosureData* _r = (ClosureData*)closure_data;
    FUNC_PRINT((int)result->n_keydimesion);
    FUNC_PRINT_ALL(result->describe, s);
    FUNC_PRINT(result->type);
    
    GPPieces* piece_result = new GPPiecesClient(result->magic, _r->pServer);
    piece_result->nKeyNumber = result->n_keydimesion;
    for (int i=0; i<piece_result->nKeyNumber; ++i)
    {
        piece_result->pKeySize[i] = result->keydimesion[i];
    }
    _r->pResult = piece_result;
}

static void do_nothing (ProtobufCRPCDispatch *dispatch, void *unused)
{
}

static void run_main_loop_without_blocking (ProtobufCRPCDispatch *dispatch)
{
    protobuf_c_rpc_dispatch_add_idle (dispatch, do_nothing, NULL);
    protobuf_c_rpc_dispatch_run (dispatch);
}


GPPieces* SGComputeClient::createCache(unsigned int* keys, int keyNumber) const
{
    protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    while (!protobuf_c_rpc_client_is_connected (mClient))
    {
        FUNC_PRINT(1);
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    ProtobufCService* server = (ProtobufCService*)mClient;
    SGCompute__CS__PieceInfo pieceInfo = SGCOMPUTE__CS__PIECE_INFO__INIT;


    char* describe = (char*)"CACHE";
    pieceInfo.n_keydimesion = keyNumber;
    pieceInfo.keydimesion= keys;
    pieceInfo.describe = describe;
    pieceInfo.type = SGCOMPUTE__CS__PIECE_INFO__TYPE__CACHE;
    ClosureData closureData;
    closureData.pResult = NULL;
    closureData.pServer = server;

    sgcompute__cs__compute_server__create(server, &pieceInfo, handle_create_response_cache, &closureData);
    while (NULL == closureData.pResult)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    return closureData.pResult;
}
