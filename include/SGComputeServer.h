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
#include "core/GPProducer.h"
#include "core/GPFactory.h"
#include "SGBasicServer.h"


class SGComputeServer :public SGBasicServer
{
public:

    static void init(const char* configFile);
    static SGComputeServer* getInstance();
    
    //Pieces manager
    uint64_t createCache(unsigned int* keyDimesions, int keyNumber, const char* type);
    uint64_t createInput(const char* path, const char* type, unsigned int* keyDimesions, int keyNumber);
    uint64_t createOutput(const char* path, const char* type, unsigned int* keyDimesions, int keyNumber);
    bool release(uint64_t number);
    GPPieces* find(uint64_t number);
    void addMetaFile(const char* metaFile);
    
    IParallelMachine::Executor* findExecutor(uint64_t number);
    uint64_t createExecutor(GPParallelType* data, IParallelMachine::PARALLELTYPE type);
    
    std::vector<const IStatusType*> translateTypes(const std::string& typeInfos) const;
    
    void addResponser(ProtobufC_RPC_Client* client);
    
    virtual bool onSetup();

private:
    static SGComputeServer* gServer;
    SGComputeServer();
    virtual ~SGComputeServer();
    
    ProtobufC_RPC_Server* mServer;
    ProtobufC_RPC_Server* mReportServer;
    std::map<uint64_t, GPPieces*> mCachePieces;
    uint64_t mCacheOrder;

    std::map<uint64_t, IParallelMachine::Executor*> mExecutors;
    uint64_t mExecutorOrder;
    
    GPPtr<GPFunctionDataBase> mDataBase;
    GPPtr<GPProducer> mProducer;
    std::vector<ProtobufC_RPC_Client*> mResponseClients;
};
#endif
