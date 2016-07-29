#include "SGComputeServer.h"
extern "C"{
#include "SGCompute.CS.pb-c.h"
}
#include <assert.h>

void SG_compute__by_info (SGCompute__CS__ComputeServer_Service *service,
                          const SGCompute__CS__ComputeInfo *input,
                          SGCompute__CS__Result_Closure closure,
                          void *closure_data);
void SG_compute__create (SGCompute__CS__ComputeServer_Service *service,
                         const SGCompute__CS__PieceInfo *input,
                         SGCompute__CS__Result_Closure closure,
                         void *closure_data);


static SGCompute__CS__ComputeServer_Service create_service = SGCOMPUTE__CS__COMPUTE_SERVER__INIT(SG_compute__);

SGComputeServer::Operator gOperator;

SGComputeServer::Operator& SGComputeServer::getOperator()
{
    return gOperator;
}


SGComputeServer::SGComputeServer()
{
    mServer = protobuf_c_rpc_server_new(PROTOBUF_C_RPC_ADDRESS_LOCAL, "3306", (ProtobufCService *) &create_service, NULL);
    for (;;)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
    }
}

SGComputeServer::~SGComputeServer()
{
}
