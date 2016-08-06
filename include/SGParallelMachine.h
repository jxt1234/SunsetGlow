#include "lowlevelAPI/IParallelMachine.h"
#include "SGComputeClient.h"
class SGParallelMachine:public IParallelMachine
{
public:
    SGParallelMachine();
    virtual ~ SGParallelMachine();
    
    
    virtual Executor* vPrepare(const GPParallelType* data, PARALLELTYPE type) const override;
    virtual int vMap(GPFLOAT* values) override;
    virtual GPPieces* vCreatePieces(const char* description, std::vector<const IStatusType*> types, unsigned int* keys, int keyNum, USAGE usage) const override;
    virtual bool vCopyPieces(GPPieces* readPieces, GPPieces* writePieces) const override;

private:
    SGComputeClient* mClient;

};