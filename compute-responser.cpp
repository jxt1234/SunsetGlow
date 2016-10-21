#include "SGComputeResponser.h"
#include "SGMacro.h"
#include "SGHdfsStreamFactory.h"
#include "core/GPStreamFactory.h"
#include <fstream>
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
    auto responserPort = argv[1];
    std::string mastPort;
    {
        std::ifstream input("conf/responser.conf");
        getline(input, mastPort);
    }
    SGComputeResponser::init(responserPort, mastPort.c_str());
    SGComputeResponser::getInstance()->install("func.xml");
    SGHdfsStreamFactory::initWithConf("/home/jxt/InWork/secret/hdfs.txt");
    GPStreamFactory::setStreamCreator(SGHdfsStreamFactory::getInstance());
    SGComputeResponser::getInstance()->runLoop();
    return 1;
}
