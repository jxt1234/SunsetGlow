#include "SGParallelMachine.h"
#include "SGPiecesCreatorClient.h"

int SGParallelMachine::vMap(GPFLOAT* values)
{
    return 0;
}

std::pair<IParallelMachine::Creator*, IParallelMachine::Executor*> SGParallelMachine::vGenerate(const GPParallelType* data, PARALLELTYPE type) const
{
    IParallelMachine::Creator* creator = new SGPiecesCreatorClient;
    IParallelMachine::Executor* executor = NULL;
    return std::make_pair(creator, executor);
}
