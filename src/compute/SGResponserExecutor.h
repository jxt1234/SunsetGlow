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
        virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const = 0;
    };
    
    
    SGResponserExecutor(const std::vector<ProtobufC_RPC_Client*>& responsers, GPPtr<Handler> handler, const GPParallelType* data);
    virtual ~SGResponserExecutor();
    
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber) const override;
    
    typedef enum {
        WORK_START,
        WORK_CREATING,
        WORK_CREATED,
        WORK_EXECUTING,
        WORK_EXECUTED,
        WORK_RELEASING,
        WORK_RELEASED
    } STATUS;
    
private:
    void WORK_START_(GPPieces* output, GPPieces** inputs, int inputNumber) const;
    void WORK_CREATING_(GPPieces* output, GPPieces** inputs, int inputNumber) const;
    void WORK_CREATED_(GPPieces* output, GPPieces** inputs, int inputNumber) const;
    void WORK_EXECUTING_(GPPieces* output, GPPieces** inputs, int inputNumber) const;
    void WORK_EXECUTED_(GPPieces* output, GPPieces** inputs, int inputNumber) const;
    void WORK_RELEASING_(GPPieces* output, GPPieces** inputs, int inputNumber) const;
    void WORK_RELEASED_(GPPieces* output, GPPieces** inputs, int inputNumber) const;
    

    mutable STATUS mStaus = WORK_START;
    mutable void* mWorkContent = NULL;
    mutable void* mMessageRemain = NULL;
    
    
    std::vector<ProtobufC_RPC_Client*> mTaskClients;
    GPPtr<Handler> mHandler;
    std::string mFormula;
    std::string mInputTypes;
};
#endif