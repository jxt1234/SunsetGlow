#include "lowlevelAPI/IParallelMachine.h"
class SGParallelMachine:public IParallelMachine
{
public:
    /*Basic API*/
    virtual std::pair<Creator*, Executor*> vGenerate(const GPParallelType* data, PARALLELTYPE type) const;
    
    /*For Parameter adjust*/
    virtual int vMap(GPFLOAT* values);

};