#include "SGComputeServer.h"
#include "SGHdfsStreamFactory.h"
#include "core/GPStreamFactory.h"
int main()
{
    SGComputeServer::init("");
    SGComputeServer* server = SGComputeServer::getInstance();
    server->addMetaFile("conf/func.xml");
    SGHdfsStreamFactory::initWithConf("/home/jxt/InWork/secret/hdfs.txt");
    GPStreamFactory::setStreamCreator(SGHdfsStreamFactory::getInstance());
    server->runLoop();
    return 1;
}
