#include "SGComputeServer.h"
int main()
{
    SGComputeServer* server = SGComputeServer::getInstance();
    server->addMetaFile("func.xml");
    server->runLoop();
    return 1;
}