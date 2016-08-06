extern "C"{
#include "SGCompute.CS.pb-c.h"
}
#include <assert.h>
#include "SGComputeClient.h"

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

static void
handle_create_response (const SGCompute__CS__Result *result,
                       void *closure_data)
{
    if (result == NULL)
        printf ("Error processing request.\n");
    else if (result->code == SGCOMPUTE__CS__RESULT__STATUS_CODE__FAIL)
        printf ("Error!!!.\n");
    printf("Success\n");
    *(protobuf_c_boolean *) closure_data = 1;
}
static void
do_nothing (ProtobufCRPCDispatch *dispatch, void *unused)
{
}
static void
run_main_loop_without_blocking (ProtobufCRPCDispatch *dispatch)
{
    protobuf_c_rpc_dispatch_add_idle (dispatch, do_nothing, NULL);
    protobuf_c_rpc_dispatch_run (dispatch);
}


GPPieces* SGComputeClient::vPrepare(GPPieces** inputs, int inputNumber) const
{
    protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    while (!protobuf_c_rpc_client_is_connected (mClient))
    {
        printf("Connect Failed\n");
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    ProtobufCService* server = (ProtobufCService*)mClient;
    SGCompute__CS__PieceInfo pieceInfo = SGCOMPUTE__CS__PIECE_INFO__INIT;

    run_main_loop_without_blocking(protobuf_c_rpc_dispatch_default());

    char* describe = "XXX";
    char* type = "YYY";
    pieceInfo.n_keydimesion = 0;
    pieceInfo.keydimesion= NULL;
    pieceInfo.describe = describe;
    pieceInfo.type = type;
    /*TODO*/
//    pieceInfo.keydimesion = inputs[0]->pKeySize;
//    pieceInfo.n_keydimesion = inputs[0]->nKeyNumber;
    protobuf_c_boolean is_done = 0;

    sgcompute__cs__compute_server__create(server, &pieceInfo, handle_create_response, &is_done);
    while (!is_done)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
    return NULL;
}



void SG_compute__create (SGCompute__CS__ComputeServer_Service *service, const SGCompute__CS__PieceInfo *input, SGCompute__CS__Result_Closure closure, void *closure_data)
{
    printf("describe = %s\n", input->describe);
    SGCompute__CS__Result result =  {
        PROTOBUF_C_MESSAGE_INIT (&sgcompute__cs__result__descriptor), SGCOMPUTE__CS__RESULT__STATUS_CODE__SUCCESS
    };
    result.code = SGCOMPUTE__CS__RESULT__STATUS_CODE__SUCCESS;
    printf("create__create Server Received\n");
    closure (&result, closure_data);
}
