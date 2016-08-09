#include "test/GPTest.h"
#include "SGComputeClient.h"
class GPCreatorClientTest:public GPTest
{
    public:
        virtual void run();
        GPCreatorClientTest(){}
        virtual ~GPCreatorClientTest(){}
};
void GPCreatorClientTest::run()
{
    SGComputeClient parallelMachine;
    unsigned int keySize = 5;
    auto pieces = parallelMachine.vCreatePieces(NULL, std::vector<const IStatusType*>(), &keySize, 1, IParallelMachine::CACHE);
    delete pieces;
}

static GPTestRegister<GPCreatorClientTest> a("GPCreatorClientTest");
