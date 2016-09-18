#include "libhdfs/hdfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    std::string ipAddress;
    std::string user;
    {
        std::ifstream input("/Users/jiangxiaotang/InWork/secret/hdfs.txt");
        getline(input, ipAddress);
        getline(input, user);
    }
    
    hdfsBuilder* builder = hdfsNewBuilder();
    
    
    hdfsBuilderSetNameNode(builder, ipAddress.c_str());
    hdfsBuilderSetUserName(builder, user.c_str());
    
    hdfsFS fs = hdfsBuilderConnect(builder);
    if (!fs)
    {
        fprintf(stderr, "Error to connect\n");
        return 1;
    }
    const char* readPath = "/tmp/testfile.txt";
    hdfsFile readFile = hdfsOpenFile(fs, readPath, O_RDONLY, 0, 0, 0);
    if (!readFile)
    {
        fprintf(stderr, "Failed to read %s\n", readPath);
    }
    int readNumber = 5;
    char readBuffer[6];
    hdfsRead(fs, readFile, readBuffer, readNumber*sizeof(char));
    readBuffer[5] = 0;
    fprintf(stdout, "Read:%s\n", readBuffer);
    hdfsCloseFile(fs, readFile);
    
    //hdfsFreeBuilder(builder);
    const char* writePath = "/tmp/testfile.txt";
    hdfsFile writeFile = hdfsOpenFile(fs, writePath, O_WRONLY |O_CREAT, 0, 0, 0);
    if(!writeFile)
    {
        fprintf(stderr, "Failed to open %s for writing!\n", writePath);
        return 1;
    }
    const char* buffer = "Hello, World!";
    tSize num_written_bytes = hdfsWrite(fs, writeFile, (void*)buffer, strlen(buffer)+1);
    if (hdfsFlush(fs, writeFile))
    {
        fprintf(stderr, "Failed to 'flush' %s\n", writePath);
        return 1;
    }
    hdfsCloseFile(fs, writeFile);
    hdfsDisconnect(fs);
}
