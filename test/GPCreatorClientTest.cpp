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
    auto pair = parallelMachine.vGenerate(NULL, IParallelMachine::REDUCE);
    delete pair.first;
}

static GPTestRegister<GPCreatorClientTest> a("GPCreatorClientTest");
