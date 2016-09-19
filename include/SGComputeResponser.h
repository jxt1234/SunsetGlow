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
#ifndef COMPUTE_SGCOMPUTERESPONSER_H
#define COMPUTE_SGCOMPUTERESPONSER_H
extern "C" {
    #include "protobuf-c-rpc/protobuf-c-rpc.h"
}
#include "thread/MGPThreadPool.h"
#include "core/GPProducer.h"
#include "core/GPFactory.h"
#include "SGBasicServer.h"
#include "lowlevelAPI/GPIStreamCreator.h"


class SGComputeResponser:public SGBasicServer
{
public:
    static bool init(const char* port, const char* master_port);

    //After init, can do this
    static SGComputeResponser* getInstance();
    
    bool install(const char* meta);
    
    void setStreamCreator(const GPIStreamCreator* creator);

    virtual bool onSetup() override;

    struct KeyCombine
    {
        unsigned int* pInputKeys;
        unsigned int nInputKeyNumber;
        unsigned int* pOutputKeys;
        unsigned int nOutuptKeyNumber;
    };
    class Work
    {
    public:
        Work();
        virtual ~Work();
        
        virtual bool vRun(const std::vector<KeyCombine>& subWorks) = 0;

        GPPieces** pInputs;
        int nInput;
        GPPieces* pOutput;
        IGPFunction* pWorkFunction;
    };
    class MapWork:public Work
    {
    public:
        MapWork() = default;
        ~ MapWork() = default;
        
        virtual bool vRun(const std::vector<KeyCombine>& subWorks);
    };
    class ReduceWork:public Work
    {
    public:
        ReduceWork() = default;
        ~ ReduceWork() = default;

        virtual bool vRun(const std::vector<KeyCombine>& subWorks);
    };

    uint64_t insertWork(const void* workInfo);
    bool runWork(const void* runInfo);

    bool releaseWork(uint64_t magic);

private:
    static SGComputeResponser* gInstance;

    SGComputeResponser(const char* port, const char* master_port);
    virtual ~ SGComputeResponser();

    ProtobufC_RPC_Server* mComputeService;
    ProtobufC_RPC_Client* mReportClient;
    
    const GPIStreamCreator* mStreamCreator = NULL;

    GPPtr<MGPThreadPool> mPool;
    GPPtr<GPFunctionDataBase> mDataBase;
    GPPtr<GPProducer> mProducer;

    std::map<uint64_t, Work*> mWorks;
    uint64_t mWorkMagic;
    uint64_t mRunMagic;
};
#endif
