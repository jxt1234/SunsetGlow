#include "SGComputeResponser.h"
#include "SGMacro.h"
#include "SGHdfsStreamFactory.h"
#include "core/GPStreamFactory.h"
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        GPPRINT_FL("Usage: ./compute-responser port");
        return 0;
    }
    int number = 1;
    if (argc >= 3)
    {
        number = atoi(argv[2]);
    }
    auto responserPort = atoi(argv[1]);
    std::string mastPort;
    {
        std::ifstream input("conf/responser.conf");
        getline(input, mastPort);
    }
    for (int i=1; i<number; ++i)
    {
        if (0 == fork())
        {
            break;
        }
        responserPort++;
    }
    char portName[100];
    sprintf(portName, "%d", responserPort);
    printf("In %0x, portName is %s\n", getpid(), portName);
    SGComputeResponser::init(portName, mastPort.c_str());
    SGComputeResponser::getInstance()->install("func.xml");
    {
        std::ifstream input("./conf/hdfs.conf");
        std::string hdfsConf;
        getline(input, hdfsConf);
        SGHdfsStreamFactory::initWithConf(hdfsConf.c_str());
    }
    GPStreamFactory::setStreamCreator(SGHdfsStreamFactory::getInstance());
    SGComputeResponser::getInstance()->runLoop();
    return 1;
}
