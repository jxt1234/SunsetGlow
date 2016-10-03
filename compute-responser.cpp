#include "SGComputeResponser.h"
#include "SGMacro.h"
int main(int argc, const char* argv[])
{
    if (argc < 1)
    {
        GPPRINT_FL("Usage: ./compute-responser port");
        return 0;
    }
    auto responserPort = argv[1];
    
    SGComputeResponser::init(responserPort, "127.0.0.1:3307");
    SGComputeResponser::getInstance()->install("func.xml");
    SGComputeResponser::getInstance()->runLoop();
    return 1;
}
