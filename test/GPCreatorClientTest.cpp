#include "test/GPTest.h"
#include "SGParallelMachine.h"
class GPCreatorClientTest:public GPTest
{
    public:
        virtual void run();
        GPCreatorClientTest(){}
        virtual ~GPCreatorClientTest(){}
};
void GPCreatorClientTest::run()
{
    SGParallelMachine parallelMachine;
    unsigned int keySize = 5;
    auto pieces = parallelMachine.vCreatePieces(NULL, std::vector<const IStatusType*>(), &keySize, 1, IParallelMachine::INPUT);
    delete pieces;
}

static GPTestRegister<GPCreatorClientTest> a("GPCreatorClientTest");
