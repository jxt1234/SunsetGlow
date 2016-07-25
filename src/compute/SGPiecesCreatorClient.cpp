extern "C"{
#include "SGCompute.CS.pb-c.h"
}
#include <assert.h>
#include "SGPiecesCreatorClient.h"

SGPiecesCreatorClient::SGPiecesCreatorClient()
{
    //FIXME
    auto service = protobuf_c_rpc_client_new(PROTOBUF_C_RPC_ADDRESS_LOCAL, "Test", &sgcompute__cs__compute_server__descriptor, NULL);
    assert(NULL!=service);
    mClient = (ProtobufC_RPC_Client*)service;
}
SGPiecesCreatorClient::~SGPiecesCreatorClient()
{
    auto service = (ProtobufCService*)mClient;
    service->destroy(service);
}

GPPieces* SGPiecesCreatorClient::vPrepare(GPPieces** inputs, int inputNumber) const
{
    return NULL;
}
