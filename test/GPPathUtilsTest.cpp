#include "test/GPTest.h"
#include "SGPathUtils.h"
class GPPathUtilsTest:public GPTest
{
    public:
        virtual void run();
        GPPathUtilsTest(){}
        virtual ~GPPathUtilsTest(){}
};
void GPPathUtilsTest::run()
{
    const char* path = "DFFDSDSDF/asdfasdfs/33fsfsd/asdfsda.txt/twet.sdf/fdsg.dd";
    printf("%s\n", path);
    printf("%s\n", SGPathUtils::getDirectory(path).c_str());
}

static GPTestRegister<GPPathUtilsTest> a("GPPathUtilsTest");
