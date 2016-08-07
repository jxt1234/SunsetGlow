/******************************************************************
   Copyright 2016, Jiang Xiao-tang

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************/
#ifndef SGCOMPUTESERVER_H
#define SGCOMPUTESERVER_H
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
    bool release(uint64_t number);
    GPPieces* find(uint64_t number);
    
private:
    static SGComputeServer* gServer;
    SGComputeServer();
    virtual ~SGComputeServer();
    
    ProtobufC_RPC_Server* mServer;
    std::map<uint64_t, GPPieces*> mCachePieces;
    uint64_t mCacheOrder = 0;
};
#endif
