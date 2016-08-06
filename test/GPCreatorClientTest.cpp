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
    parallelMachine.vCreatePieces(NULL, std::vector<const IStatusType*>(), NULL, 0, IParallelMachine::INPUT);
}

static GPTestRegister<GPCreatorClientTest> a("GPCreatorClientTest");
