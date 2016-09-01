#include "SGComputeResponser.h"
#include "SGMacro.h"
int main()
{
    SGComputeResponser::init(SGRESPONSE_PORT, SGREPORT_PORT);
    SGComputeResponser::getInstance()->install("func.xml");
    SGComputeResponser::getInstance()->runLoop();
    return 1;
}
