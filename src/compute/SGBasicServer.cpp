#include "SGBasicServer.h"
#include "protobuf-c-rpc/protobuf-c-rpc.h"
#include "SGDebug.h"

void SGBasicServer::_runRemainWork()
{
    std::vector<Work*> remainWork;
    for (auto w : mWorkQueue)
    {
        auto s = w->vRun();
        switch (s) {
            case Work::WAIT:
                remainWork.push_back(w);
                break;
            case Work::FAILED:
                SGASSERT(0);//TODO
            case Work::SUCCESS:
                delete w;
                break;
            default:
                SGASSERT(0);
                break;
        }
    }
    mWorkQueue = remainWork;
}


void SGBasicServer::runLoop()
{
    this->onSetup();
    for (;;)
    {
        protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default());
        _runRemainWork();
    }
}

void SGBasicServer::addWork(Work* w)
{
    mWorkQueue.push_back(w);
}

SGBasicServer::SGBasicServer()
{
}
SGBasicServer::~SGBasicServer()
{
    SGASSERT(!mWorkQueue.empty());
}
