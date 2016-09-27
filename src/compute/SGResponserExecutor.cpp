#include "SGResponserExecutor.h"
#include "thread/MGPThread.h"
#include "SGDebug.h"
#include "SGCompute.SR.pb-c.h"
#include "utils/AutoStorage.h"
#include <sstream>
#include "SGMacro.h"

SGResponserExecutor::SGResponserExecutor(const std::vector<ProtobufC_RPC_Client*>& responsers, GPPtr<Handler> handler, const GPParallelType* data)
{
    mTaskClients = responsers;
    mHandler = handler;
    mFormula = data->sFuncInfo.formula;
    std::ostringstream os;
    for (auto t : data->sFuncInfo.inputs)
    {
        os << t->name() <<" ";
    }
    mInputTypes = os.str();
}
SGResponserExecutor::~SGResponserExecutor()
{
}


static void SGCompute__SR__ResultInfo_Closure_CreateWork(const SGCompute__SR__ResultInfo *message, void *closure_data)
{
    uint64_t* magicP = (uint64_t*)closure_data;
    *magicP = message->magic;
}

class IntWrap : public GPRefCount
{
public:
    IntWrap(uint32_t* p)
    {
        mP = p;
    }
    virtual ~IntWrap()
    {
        delete [] mP;
    }
private:
    uint32_t* mP;
};

static void _copyFileInfo(SGCompute__SR__WorkInfo__FileInfo* dst, GPPieces* src)
{
    dst->n_key_dimesion = src->nKeyNumber;
    dst->key_dimesion = new uint32_t[src->nKeyNumber];
    for (int i=0; i<src->nKeyNumber; ++i)
    {
        dst->key_dimesion[i] = src->pKeySize[i];
    }
    dst->path = ::strdup(src->sInfo.c_str());
    std::ostringstream os;
    for (auto t : src->pTypes)
    {
        os << t->name() << " ";
    }
    dst->type = ::strdup(os.str().c_str());
//    FUNC_PRINT_ALL(dst->path, s);
//    FUNC_PRINT_ALL(dst->type, s);
}


static SGCompute__SR__WorkInfo__FileInfo* _newFileInfo()
{
    auto info = new SGCompute__SR__WorkInfo__FileInfo;
    *info = SGCOMPUTE__SR__WORK_INFO__FILE_INFO__INIT;
    return info;
}

static void _freeFileInfo(SGCompute__SR__WorkInfo__FileInfo* info)
{
    SGASSERT(NULL!=info);
    if (NULL!=info->type)
    {
        free(info->type);
    }
    if (NULL!=info->path)
    {
        free(info->path);
    }
    delete info;
}

static SGCompute__SR__WorkInfo* _newWorkInfo()
{
    SGCompute__SR__WorkInfo* info = new SGCompute__SR__WorkInfo;
    *info = SGCOMPUTE__SR__WORK_INFO__INIT;
    return info;
}

static void _freeWorkInfo(SGCompute__SR__WorkInfo* info)
{
    for (int i=0; i<info->n_inputs; ++i)
    {
        _freeFileInfo(info->inputs[i]);
    }
    delete [] info->inputs;
    _freeFileInfo(info->output);
    if (NULL!=info->parameters)
    {
        free(info->parameters);
    }
    if (NULL!=info->formula)
    {
        free(info->formula);
    }
    if (NULL!=info->inputtypes)
    {
        free(info->inputtypes);
    }
    delete info;
}

void SGResponserExecutor::WORK_START_(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    SGCompute__SR__WorkInfo* inputP = _newWorkInfo();
    SGCompute__SR__WorkInfo& input = *inputP;
    SGCompute__SR__WorkInfo__FileInfo* outputInfo = _newFileInfo();
    _copyFileInfo(outputInfo, output);
    auto totalInputP = new SGCompute__SR__WorkInfo__FileInfo*[inputNumber];
    for (int ip=0; ip<inputNumber; ++ip)
    {
        totalInputP[ip] = _newFileInfo();
        _copyFileInfo(totalInputP[ip], inputs[ip]);
    }

    input.type = SGCOMPUTE__SR__WORK_INFO__TYPE__MAP;//TODO
    input.n_inputs = inputNumber;
    input.output = outputInfo;
    input.inputs = totalInputP;
    input.formula = strdup(mFormula.c_str());
    input.inputtypes = strdup(mInputTypes.c_str());
    input.parameters = NULL;
    SGASSERT(mFormula.size()>0);
    //SGASSERT(mInputTypes.size()>0);
    
    std::map<ProtobufC_RPC_Client*, uint64_t*> *maps = new std::map<ProtobufC_RPC_Client*, uint64_t*>;
    SGASSERT(NULL==mWorkContent);
    mWorkContent = maps;
    for (auto s : mTaskClients)
    {
        uint64_t* magic = new uint64_t;
        *magic = 0;
        SGASSERT(NULL!=magic);
        sgcompute__sr__compute_responser__create_work((ProtobufCService*)s, inputP, SGCompute__SR__ResultInfo_Closure_CreateWork, magic);
        maps->insert(std::make_pair(s, magic));
    }
    SGASSERT(NULL == mMessageRemain);
    mMessageRemain = inputP;
    mStaus = WORK_CREATING;
}
void SGResponserExecutor::WORK_CREATING_(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    SGASSERT(NULL!=mWorkContent);
    auto mapsP = (std::map<ProtobufC_RPC_Client*, uint64_t*> *)mWorkContent;
    auto& maps = *mapsP;
    bool valid = true;
    for (auto s : maps)
    {
        if (*s.second == 0)
        {
            valid = false;
            break;
        }
    }
    if (valid)
    {
        mStaus = WORK_CREATED;
    }
}
void SGResponserExecutor::WORK_CREATED_(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    std::map<ProtobufC_RPC_Client*, uint64_t>* workMaps = new std::map<ProtobufC_RPC_Client*, uint64_t>;
    auto mapsP = (std::map<ProtobufC_RPC_Client*, uint64_t*> *)mWorkContent;
    auto& maps = *mapsP;
    for (auto s : maps)
    {
        SGASSERT(*s.second > 0);
        workMaps->insert(std::make_pair(s.first, *s.second));
        delete s.second;
    }
    delete mapsP;
    _freeWorkInfo((SGCompute__SR__WorkInfo*)mMessageRemain);
    mMessageRemain = NULL;
    
    mWorkContent = workMaps;
    mStaus = WORK_EXECUTING;
}
void SGResponserExecutor::WORK_EXECUTING_(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    SGASSERT(NULL!=mWorkContent);
    auto maps = (std::map<ProtobufC_RPC_Client*, uint64_t>*)mWorkContent;
    bool result = mHandler->vRun(output, inputs, inputNumber, *maps);
    if (result)
    {
        mStaus = WORK_EXECUTED;
    }
}
void SGResponserExecutor::WORK_EXECUTED_(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    SGASSERT(NULL!=mWorkContent);
    auto maps = (std::map<ProtobufC_RPC_Client*, uint64_t>*)mWorkContent;
    std::vector<uint64_t*>* result = new std::vector<uint64_t*>;
    std::vector<SGCompute__SR__ResultInfo*> *messageRemain = new std::vector<SGCompute__SR__ResultInfo*>;
    for (auto kv : *maps)
    {
        uint64_t* magic = new uint64_t;
        SGASSERT(NULL!=magic);
        *magic = 0;
        SGCompute__SR__ResultInfo* resultInput = new SGCompute__SR__ResultInfo;
        *resultInput = SGCOMPUTE__SR__RESULT_INFO__INIT;
        resultInput->magic = kv.second;
        resultInput->status = SGCOMPUTE__SR__RESULT_INFO__STATUS__SUCCESS;
        sgcompute__sr__compute_responser__release_work((ProtobufCService*)kv.first, resultInput, SGCompute__SR__ResultInfo_Closure_CreateWork, magic);
        result->push_back(magic);
        messageRemain->push_back(resultInput);
    }
    delete maps;
    mWorkContent = result;
    mStaus = WORK_RELEASING;
    mMessageRemain = messageRemain;
}
void SGResponserExecutor::WORK_RELEASING_(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    auto r = (std::vector<uint64_t*>*)mWorkContent;
    for (auto m : *r)
    {
        if (*m == 0)
        {
            return;
        }
    }
    mStaus = WORK_RELEASED;
    for (auto m : *r)
    {
        delete m;
    }
    delete r;
    
    auto mv = (std::vector<SGCompute__SR__ResultInfo*>*)mMessageRemain;
    for (auto m : *mv)
    {
        delete m;
    }
    delete mv;
    
    mMessageRemain = NULL;
    mWorkContent = NULL;
}
void SGResponserExecutor::WORK_RELEASED_(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    mStaus = WORK_START;
}


bool SGResponserExecutor::vRun(GPPieces* output, GPPieces** inputs, int inputNumber) const
{
    FUNC_PRINT(mStaus);
    switch (mStaus) {
        case WORK_START:
            WORK_START_(output, inputs, inputNumber);
            return false;
        case WORK_CREATING:
            WORK_CREATING_(output, inputs, inputNumber);
            return false;
        case WORK_CREATED:
            WORK_CREATED_(output, inputs, inputNumber);
            return false;
        case WORK_EXECUTING:
            WORK_EXECUTING_(output, inputs, inputNumber);
            return false;
        case WORK_EXECUTED:
            WORK_EXECUTED_(output, inputs, inputNumber);
            return false;
        case WORK_RELEASING:
            WORK_RELEASING_(output, inputs, inputNumber);
            return false;
        case WORK_RELEASED:
            WORK_RELEASED_(output, inputs, inputNumber);
            return true;
        default:
            break;
    }
    return false;
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
