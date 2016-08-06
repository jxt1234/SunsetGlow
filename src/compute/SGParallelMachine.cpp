#include "SGParallelMachine.h"

int SGParallelMachine::vMap(GPFLOAT* values)
{
    return 0;
}

IParallelMachine::Executor* SGParallelMachine::vPrepare(const GPParallelType* data, PARALLELTYPE type) const
{
    IParallelMachine::Executor* executor = NULL;
    return NULL;
}

GPPieces* SGParallelMachine::vCreatePieces(const char* description, std::vector<const IStatusType*> types, unsigned int* keys, int keyNum, USAGE usage) const
{
    //TODO
    return mClient->vPrepare(NULL, 0);
}

SGParallelMachine::SGParallelMachine()
{
    mClient = new SGComputeClient;
}
SGParallelMachine::~SGParallelMachine()
{
    delete mClient;
}

bool SGParallelMachine::vCopyPieces(GPPieces* readPieces, GPPieces* writePieces) const
{
    //TODO
    return false;
}
