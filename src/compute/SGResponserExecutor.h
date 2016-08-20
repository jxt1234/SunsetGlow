#include "lowlevelAPI/IParallelMachine.h"
extern "C"{
#include "protobuf-c-rpc/protobuf-c-rpc.h"
}
#include <vector>
#include <string>
#include "backend/IGPKeyIterator.h"
#include "backend/GPKeyIteratorFactory.h"

class SGResponserExecutor:public IParallelMachine::Executor
{
public:
    class WorkKey
    {
    public:
        WorkKey(unsigned int inputSize, unsigned int outputSize);
        virtual ~WorkKey();
        
        unsigned int* input() const {return mInputKey;}
        unsigned int* output() const {return mOutputKey;}
        
        static void generate(IGPKeyIterator* iterator, std::vector<SGResponserExecutor::WorkKey*>& output);
        
    private:
        unsigned int* mInputKey;
        unsigned int* mOutputKey;
        
    };
    
    class Handler:public GPRefCount
    {
    public:
        Handler(){}
        virtual ~ Handler(){}
        virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, ProtobufC_RPC_Server* server, const std::vector<ProtobufC_RPC_Client*>& slave) const = 0;
    };
    
    
    SGResponserExecutor(const std::vector<ProtobufC_RPC_Client*>& responsers, ProtobufC_RPC_Server* report, GPPtr<Handler> handler);
    virtual ~SGResponserExecutor();
    
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber) const override;
private:
    ProtobufC_RPC_Server* mReportServer;
    std::vector<ProtobufC_RPC_Client*> mTaskClients;
    GPPtr<Handler> mHandler;
};


class MapHandler:public SGResponserExecutor::Handler
{
public:
    MapHandler(GPPtr<GPKeyIteratorFactory> factory, uint64_t workMagic);
    virtual ~ MapHandler();
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, ProtobufC_RPC_Server* server, const std::vector<ProtobufC_RPC_Client*>& slave) const override;
private:
    GPPtr<GPKeyIteratorFactory> mFactory;
    uint64_t mWorkMagic;
};

class ReduceHandler:public SGResponserExecutor::Handler
{
public:
    ReduceHandler(GPPtr<GPKeyIteratorFactory> factory, uint64_t workMagic);
    virtual ~ ReduceHandler();
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, ProtobufC_RPC_Server* server, const std::vector<ProtobufC_RPC_Client*>& slave) const override;
private:
    GPPtr<GPKeyIteratorFactory> mFactory;
    uint64_t mWorkMagic;
};