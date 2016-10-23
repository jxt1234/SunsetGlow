#include "SGHandler.h"
#include "SGDebug.h"
#include "SGCompute.SR.pb-c.h"


static void Handler_SGCompute__SR__ResultInfo_Closure(const SGCompute__SR__ResultInfo *message, void *closure_data)
{
    bool* result = (bool*)closure_data;
    if (SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS == message->status)
    {
        *result = true;
    }
}

static SGCompute__SR__RunInfo__Unit* _newRunInfoUnit(int input, int output)
{
    SGCompute__SR__RunInfo__Unit* u = new SGCompute__SR__RunInfo__Unit;
    *u = SGCOMPUTE__SR__RUN_INFO__UNIT__INIT;
    u->n_inputkeys = input;
    u->n_outputkeys = output;
    u->inputkeys = new uint32_t[input];
    u->outputkeys = new uint32_t[output];
    return u;
}
static void _freeRunInfoUnit(SGCompute__SR__RunInfo__Unit* unit)
{
    SGASSERT(NULL!=unit);
    SGASSERT(NULL!=unit->inputkeys);
    SGASSERT(NULL!=unit->outputkeys);
    delete unit->inputkeys;
    delete unit->outputkeys;
    delete unit;
}
static SGCompute__SR__RunInfo* _newRunInfo(size_t n, int input, int output)
{
    SGCompute__SR__RunInfo* info = new SGCompute__SR__RunInfo;
    *info = SGCOMPUTE__SR__RUN_INFO__INIT;
    info->n_work_content = n;
    info->work_content = new SGCompute__SR__RunInfo__Unit*[n];
    for (int i=0; i<n; ++i)
    {
        info->work_content[i] = _newRunInfoUnit(input, output);
    }
    return info;
}

static void _freeRunInfo(SGCompute__SR__RunInfo* info)
{
    for (int k=0; k<info->n_work_content; ++k)
    {
        _freeRunInfoUnit(info->work_content[k]);
    }
    delete [] info->work_content;
    delete info;
}


void SGMapHandler::START_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const
{
    SGASSERT(NULL!=output);
    SGASSERT(NULL!=inputs);
    SGASSERT(slaveMagicMap.size() >= 1);
    for (auto s : slaveMagicMap)
    {
        SGASSERT(NULL!=s.first);
    }
    GPPtr<IGPKeyIterator> iterator = mFactory->create(inputs, inputNumber, output);
    auto keySize = iterator->vGetSize();
    std::vector<SGResponserExecutor::WorkKey*> keys;
    SGResponserExecutor::WorkKey::generate(iterator.get(), keys);
    size_t pieceNumber = (keys.size()+slaveMagicMap.size()-1) / slaveMagicMap.size();
    if (pieceNumber <= 0)
    {
        pieceNumber = 1;
    }
    size_t sta = 0;
    std::vector<bool*> *workStatus = new std::vector<bool*>;
    std::vector<SGCompute__SR__RunInfo*> *messageVector = new std::vector<SGCompute__SR__RunInfo*>;
    for (auto kv : slaveMagicMap)
    {
        auto fin = sta + pieceNumber;
        if (fin > keys.size())
        {
            fin = keys.size();
        }
        if (sta >= fin)
        {
            break;
        }
        auto n = fin-sta;
        SGCompute__SR__RunInfo* runInfo = _newRunInfo(n, keySize.first, keySize.second);
        runInfo->work_magic = kv.second;
        messageVector->push_back(runInfo);
        for (size_t k=0; k<n; ++k)
        {
            auto keyInput = keys[k+sta]->input();
            for (int p=0; p<keySize.first; ++p)
            {
                runInfo->work_content[k]->inputkeys[p] = keyInput[p];
            }
            
            auto keyOutput = keys[k+sta]->output();
            for (int p=0; p<keySize.second; ++p)
            {
                runInfo->work_content[k]->outputkeys[p] = keyOutput[p];
                //FUNC_PRINT(runInfo->work_content[k]->outputkeys[p]);
            }
        }
        bool* complete = new bool;
        *complete = false;
        sgcompute__sr__compute_responser__run_work((ProtobufCService*)kv.first, runInfo, Handler_SGCompute__SR__ResultInfo_Closure, complete);
        sta+=pieceNumber;
        workStatus->push_back(complete);
    }
    for(auto k : keys)
    {
        delete k;
    }
    SGASSERT(NULL == mWorkContent && NULL == mMessage);
    mWorkContent = workStatus;
    mMessage = messageVector;
    mStaus = RUNNING;
}
void SGMapHandler::RUNNING_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const
{
    SGASSERT(NULL!=mWorkContent);
    auto v = (std::vector<bool*> *)mWorkContent;
    for (auto b : *v)
    {
        if (!(*b))
        {
            return;
        }
    }
    delete v;
    mWorkContent = NULL;
    
    auto message = (std::vector<SGCompute__SR__RunInfo*>*)mMessage;
    for (auto b : *message)
    {
        _freeRunInfo(b);
    }
    delete message;
    mMessage = NULL;
    
    mStaus = FINISH;
}
void SGMapHandler::FINISH_(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const
{
    mStaus = START;
}


bool SGMapHandler::vRun(GPPieces* output, GPPieces** inputs, int inputNumber, const std::map<ProtobufC_RPC_Client*, uint64_t>& slaveMagicMap) const
{
    FUNC_PRINT(mStaus);
    switch (mStaus) {
        case START:
            START_(output, inputs, inputNumber, slaveMagicMap);
            return false;
        case RUNNING:
            RUNNING_(output, inputs, inputNumber, slaveMagicMap);
            return false;
        case FINISH:
            FINISH_(output, inputs, inputNumber, slaveMagicMap);
            return true;
        default:
            break;
    }
    return false;
}

SGMapHandler::SGMapHandler(GPPtr<GPKeyIteratorFactory> factory)
{
    mFactory = factory;
}

SGMapHandler::~SGMapHandler()
{
}
