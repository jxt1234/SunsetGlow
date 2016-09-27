#include "SGResponserExecutor.h"
class SGMapHandler:public SGResponserExecutor::Handler
{
public:
    SGMapHandler(GPPtr<GPKeyIteratorFactory> factory);
    virtual ~ SGMapHandler();
    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const override;
    
    typedef enum {
        START,
        RUNNING,
        FINISH
    } STATUS;
    
    void START_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const;
    void RUNNING_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const;
    void FINISH_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const;
private:
    mutable STATUS mStaus = START;
    mutable void* mWorkContent = NULL;
    mutable void* mMessage = NULL;
    
    
    GPPtr<GPKeyIteratorFactory> mFactory;
};


//class SGReduceHandler:public SGResponserExecutor::Handler
//{
//public:
//    SGReduceHandler(GPPtr<GPKeyIteratorFactory> factory);
//    virtual ~ SGReduceHandler();
//    virtual bool vRun(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const override;
//    
//    typedef enum {
//        START,
//        RUNNING,
//        FINISH
//    } STATUS;
//    
//    void START_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const;
//    void RUNNING_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const;
//    void FINISH_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const;
//private:
//    mutable STATUS mStaus = START;
//    mutable void* mWorkContent = NULL;
//    mutable void* mMessage = NULL;
//    
//    
//    GPPtr<GPKeyIteratorFactory> mFactory;
//};
