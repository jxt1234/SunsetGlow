#ifndef SRC_COMPUTE_SGRESPONSEREXECUTOR_H
#define SRC_COMPUTE_SGRESPONSEREXECUTOR_H
#include "lowlevelAPI/IParallelMachine.h"
extern "C"{
#include "protobuf-c-rpc/protobuf-c-rpc.h"
}
#include <vector>
#include <string>
#include "backend/IGPKeyIterator.h"
#include "backend/GPKeyIteratorFactory.h"
#include "SGComputeServer.h"
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
        virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, SGComputeServer::Reporter* report, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const = 0;
    };
    
    
    SGResponserExecutor(const std::vector<ProtobufC_RPC_Client*>& responsers, SGComputeServer::Reporter* report, GPPtr<Handler> handler, const GPParallelType* data);
    virtual ~SGResponserExecutor();
    
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber) const override;
private:
    SGComputeServer::Reporter* mReport;
    std::vector<ProtobufC_RPC_Client*> mTaskClients;
    GPPtr<Handler> mHandler;
    std::string mFormula;
    std::string mInputTypes;
};
class MapHandler:public SGResponserExecutor::Handler
{
public:
    MapHandler(GPPtr<GPKeyIteratorFactory> factory);
    virtual ~ MapHandler();
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, SGComputeServer::Reporter* report, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const override;
private:
    GPPtr<GPKeyIteratorFactory> mFactory;
};
#endif