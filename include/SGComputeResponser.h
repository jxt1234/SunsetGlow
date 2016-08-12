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

class SGComputeResponser
{
public:
    static bool init(const char* port, const char* master_port);

    //After init, can do this
    static SGComputeResponser* getInstance();
    
    void runLoop();
    bool install(const char* meta);

private:
    static SGComputeResponser* gInstance;
    
    SGComputeResponser(const char* port, const char* master_port);
    virtual ~ SGComputeResponser();
    
    ProtobufC_RPC_Server* mComputeService;
    ProtobufC_RPC_Client* mReportClient;
};
#endif
