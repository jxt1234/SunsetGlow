#ifndef COMPUTE_SGPIECESCREATORCLIENT_H
#define COMPUTE_SGPIECESCREATORCLIENT_H
#include "lowlevelAPI/IParallelMachine.h"
extern "C" {
#include "protobuf-c-rpc/protobuf-c-rpc.h"
}


class SGPiecesCreatorClient : public IParallelMachine::Creator
{
public:
    SGPiecesCreatorClient();
    virtual ~SGPiecesCreatorClient();
    
    virtual GPPieces* vPrepare(GPPieces** inputs, int inputNumber) const;
private:
    ProtobufC_RPC_Client* mClient;
};


#endif
