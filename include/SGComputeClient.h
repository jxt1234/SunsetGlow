#ifndef COMPUTE_SGPIECESCREATORCLIENT_H
#define COMPUTE_SGPIECESCREATORCLIENT_H
#include "lowlevelAPI/IParallelMachine.h"
extern "C" {
#include "protobuf-c-rpc/protobuf-c-rpc.h"
}


class SGComputeClient
{
public:
    SGComputeClient();
    virtual ~SGComputeClient();
    
    GPPieces* createCache(unsigned int* keys, int keyNumber) const;
private:
    ProtobufC_RPC_Client* mClient;
};

#endif
