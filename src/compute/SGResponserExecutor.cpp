#include "SGResponserExecutor.h"
#include "MGPThread.h"
#include "SGDebug.h"
#include "SGCompute.SR.pb-c.h"
#include "utils/AutoStorage.h"


SGResponserExecutor::SGResponserExecutor(const std::vector<ProtobufC_RPC_Client*>& responsers, ProtobufC_RPC_Server* report, GPPtr<Handler> handler)
{
    mTaskClients = responsers;
    mReportServer = report;
    mHandler = handler;
}
SGResponserExecutor::~SGResponserExecutor()
{
}

bool SGResponserExecutor::vRun(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    return mHandler->vRun(output, inputs, inputNumber, mReportServer, mTaskClients);
}


MapHandler::MapHandler(GPPtr<GPKeyIteratorFactory> factory, uint64_t workMagic)
{
    mFactory = factory;
    mWorkMagic = workMagic;
}

MapHandler::~MapHandler()
{
}


static void Handler_SGCompute__SR__ResultInfo_Closure(const SGCompute__SR__ResultInfo *message, void *closure_data)
{
    bool* result = (bool*)closure_data;
    if (SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS == message->status)
    {
        *result = true;
    }
}


bool MapHandler::vRun(GPPieces* output, GPPieces** inputs, int inputNumber, ProtobufC_RPC_Server* server, const std::vector<ProtobufC_RPC_Client*>& slave) const
{
    SGASSERT(NULL!=output);
    SGASSERT(NULL!=inputs);
    SGASSERT(NULL!=server);
    SGASSERT(slave.size() > 1);
    for (auto s : slave)
    {
        SGASSERT(NULL!=s);
    }
    GPPtr<IGPKeyIterator> iterator = mFactory->create(inputs, inputNumber, output);
    auto keySize = iterator->vGetSize();
    std::vector<SGResponserExecutor::WorkKey*> keys;
    SGResponserExecutor::WorkKey::generate(iterator.get(), keys);
    size_t pieceNumber = keys.size() / slave.size();
    if (pieceNumber <= 0)
    {
        pieceNumber = 1;
    }
    size_t sta = 0;
    MGPSema taskSema;
    int waitNumber = 0;
    for (int i=0; i<slave.size(); ++i, sta+=pieceNumber)
    {
        auto fin = sta + pieceNumber;
        if (fin > slave.size())
        {
            fin = slave.size();
        }
        if (sta >= fin)
        {
            break;
        }
        waitNumber++;
        auto n = fin-sta;
        SGCompute__SR__RunInfo runInfo = SGCOMPUTE__SR__RUN_INFO__INIT;
        runInfo.n_work_content = n;
        AUTOSTORAGE(units, SGCompute__SR__RunInfo__Unit, (int)(n));
        AUTOSTORAGE(units_inputsKeysTotal, uint32_t, (int)(n*keySize.first));
        AUTOSTORAGE(units_outputKeysTotal, uint32_t, (int)(n*keySize.second));
        for (size_t k=0; k<n; ++k)
        {
            units[k] = SGCOMPUTE__SR__RUN_INFO__UNIT__INIT;
            auto keyInput = keys[k+sta]->input();
            units[k].n_inputkeys = keySize.first;
            units[k].inputkeys = units_inputsKeysTotal + k*keySize.first;
            for (int p=0; p<keySize.first; ++p)
            {
                units[k].inputkeys[p] = keyInput[p];
            }

            auto keyOutput = keys[k+sta]->output();
            units[k].n_outputkeys = keySize.second;
            units[k].outputkeys = units_outputKeysTotal + k*keySize.second;
            for (int p=0; p<keySize.second; ++p)
            {
                units[k].outputkeys[p] = keyOutput[p];
            }
        }
        bool complete = false;
        sgcompute__sr__compute_responser__run_work((ProtobufCService*)slave[i], &runInfo, Handler_SGCompute__SR__ResultInfo_Closure, &complete);
        while (!complete)
        {
            protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
        }
    }
    for (int i=0; i<waitNumber; ++i)
    {
        taskSema.wait();
    }
    
    for(auto k : keys)
    {
        delete k;
    }
    return true;
}

SGResponserExecutor::WorkKey::WorkKey(unsigned int inputSize, unsigned int outputSize)
{
    mInputKey = new unsigned int[inputSize];
    mOutputKey = new unsigned int[outputSize];
}

SGResponserExecutor::WorkKey::~WorkKey()
{
    delete [] mInputKey;
    delete [] mOutputKey;
}

void SGResponserExecutor::WorkKey::generate(IGPKeyIterator* iterator, std::vector<SGResponserExecutor::WorkKey*>& output)
{
    SGASSERT(NULL!=iterator);
    auto size = iterator->vGetSize();
    WorkKey* key = new WorkKey(size.first, size.second);
    bool hasData = iterator->vRewind(key->input(), key->output());
    if (!hasData)
    {
        delete key;
        return;
    }
    do
    {
        output.push_back(key);
        key = new WorkKey(size.first, size.second);
    }while(iterator->vNext(key->input(), key->output()));
    delete key;
}
