#include "SGComputeResponser.h"
#include "SGDebug.h"
#include "SGCompute.SR.pb-c.h"

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


void SG_Response__create_work (SGCompute__SR__ComputeResponser_Service *service,
                    const SGCompute__SR__WorkInfo *input,
                    SGCompute__SR__ResultInfo_Closure closure,
                               void *closure_data)
{
}
void SG_Response__run_work (SGCompute__SR__ComputeResponser_Service *service,
                 const SGCompute__SR__RunInfo *input,
                 SGCompute__SR__ResultInfo_Closure closure,
                 void *closure_data)
{
    
}


static SGCompute__SR__ComputeResponser_Service gResponser = SGCOMPUTE__SR__COMPUTE_RESPONSER__INIT(SG_Response__);


SGComputeResponser::SGComputeResponser(const char* port, const char* master_port)
{
    SGASSERT(NULL!=port);
    SGASSERT(NULL!=master_port);
    //TODO
    mComputeService = protobuf_c_rpc_server_new(PROTOBUF_C_RPC_ADDRESS_LOCAL, port, (ProtobufCService *) &gResponser, NULL);
    auto service = protobuf_c_rpc_client_new(PROTOBUF_C_RPC_ADDRESS_LOCAL, master_port, &sgcompute__sr__compute_server_waiter__descriptor, NULL);
    SGASSERT(NULL!=service);
    mReportClient = (ProtobufC_RPC_Client*)service;
}

SGComputeResponser::~SGComputeResponser()
{
}

void SGComputeResponser::runLoop()
{
    
}
bool SGComputeResponser::install(const char* meta)
{
    return true;
}

