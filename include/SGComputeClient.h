#ifndef COMPUTE_SGPIECESCREATORCLIENT_H
#define COMPUTE_SGPIECESCREATORCLIENT_H
#include "lowlevelAPI/IParallelMachine.h"
extern "C" {
#include "protobuf-c-rpc/protobuf-c-rpc.h"
}


class SGComputeClient:public IParallelMachine
{
public:
    SGComputeClient();
    virtual ~SGComputeClient();
    
    virtual Executor* vPrepare(const GPParallelType* data, PARALLELTYPE type) const override;
    virtual GPPieces* vCreatePieces(const char* description, std::vector<const IStatusType*> types, unsigned int* keys, int keyNum, USAGE usage) const override;
    virtual bool vCopyPieces(GPPieces* readPieces, GPPieces* writePieces) const override;

private:
    ProtobufC_RPC_Client* mClient;
};

extern "C"{
    IParallelMachine* libSunsetGlow_PARALLELMACHINE_CREATE_FUNC(const std::string& name);
};

#endif
