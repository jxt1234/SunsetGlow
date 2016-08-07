extern "C" {
#include "protobuf-c-rpc/protobuf-c-rpc.h"
}
#include "lowlevelAPI/IParallelMachine.h"
#include <map>
#include <string>
class SGComputeServer :public GPRefCount
{
public:
    static SGComputeServer* getInstance();
    void runLoop();
    
    //Pieces manager
    uint64_t createCache(unsigned int* keyDimesions, int keyNumber);
    bool releaseCache(uint64_t number);
    GPPieces* findCache(uint64_t number);
    
private:
    static SGComputeServer* gServer;

    SGComputeServer();
    virtual ~SGComputeServer();
    
    ProtobufC_RPC_Server* mServer;
    std::map<std::string, GPPieces*> mInputPieces;
    std::map<std::string, GPPieces*> mOutputPieces;
    std::map<uint64_t, GPPieces*> mCachePieces;
    uint64_t mCacheOrder = 0;
};
