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
}

static GPTestRegister<GPCreatorClientTest> a("GPCreatorClientTest");
