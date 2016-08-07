#include "SGComputeServer.h"
int main()
{
    SGComputeServer* server = SGComputeServer::getInstance();
    server->runLoop();
    return 1;
}