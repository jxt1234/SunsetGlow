#include "SGParallelMachine.h"

int SGParallelMachine::vMap(GPFLOAT* values)
{
    return 0;
}

std::pair<IParallelMachine::Creator*, IParallelMachine::Executor*> SGParallelMachine::vGenerate(const GPParallelType* data, PARALLELTYPE type) const
{
    IParallelMachine::Creator* creator = NULL;
    IParallelMachine::Executor* executor = NULL;
    return std::make_pair(creator, executor);
}
