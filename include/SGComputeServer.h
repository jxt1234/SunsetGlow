extern "C" {
#include "protobuf-c-rpc/protobuf-c-rpc.h"
}
#include "lowlevelAPI/IParallelMachine.h"
class SGComputeServer :public GPRefCount
{
public:
    SGComputeServer();
    virtual ~SGComputeServer();
    class Operator
    {
    public:
        Operator(){}
        ~Operator(){}
    };
    
    static Operator& getOperator();
    
private:
    ProtobufC_RPC_Server* mServer;
};
