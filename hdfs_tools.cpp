#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "SGHdfsStreamFactory.h"
#include "core/GPStreamFactory.h"
#include "core/GPPieceFactory.h"

class AutoRecycle
{
public:
    AutoRecycle(){}
    ~ AutoRecycle()
    {
        SGHdfsStreamFactory::destroy();
    }
};

static std::string gHdfsBasicPath;
static std::string gLocalBasicPath;


static void download(const char* path, long pieceNumber)
{
    int size = 32768;
    void* buffer = ::malloc(size);
    for (int i=0; i<pieceNumber; ++i)
    {
        std::ostringstream ospath;
        ospath << path << "_"<<i;
        auto mergePath = ospath.str();
        GPStreamFactory::setStreamCreator(SGHdfsStreamFactory::getInstance());
        GPStreamFactory::setParentPath(gHdfsBasicPath.c_str());
        GPPtr<GPStream> readStream = GPStreamFactory::NewStream(mergePath.c_str());

        GPStreamFactory::setStreamCreator(NULL);
        GPStreamFactory::setParentPath(gLocalBasicPath.c_str());
        GPPtr<GPWStream> writeStream = GPStreamFactory::NewWStream(mergePath.c_str());
        while (0 < readStream->vRead(buffer, size))
        {
            writeStream->vWrite(buffer, size);
        }
    }
    std::free(buffer);
}



static void upload(const char* path, long pieceNumber)
{
    int size = 32768;
    void* buffer = ::malloc(size);
    for (int i=0; i<pieceNumber; ++i)
    {
        std::ostringstream ospath;
        ospath << path << "_"<<i;
        auto mergePath = ospath.str();
        GPStreamFactory::setStreamCreator(NULL);
        GPStreamFactory::setParentPath(gLocalBasicPath.c_str());
        GPPtr<GPStream> readStream = GPStreamFactory::NewStream(mergePath.c_str());
        GPStreamFactory::setStreamCreator(SGHdfsStreamFactory::getInstance());
        GPStreamFactory::setParentPath(gHdfsBasicPath.c_str());
        GPPtr<GPWStream> writeStream = GPStreamFactory::NewWStream(mergePath.c_str());
        while (0 < readStream->vRead(buffer, size))
        {
            writeStream->vWrite(buffer, size);
        }
    }
    std::free(buffer);
}


int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Example:  ./hdfs_tools.out upload path 5\n");
        printf("Example:  ./hdfs_tools.out download path 5\n");
        return 0;
    }
    const char* path = argv[2];
    long pieceNumber = ::strtol(argv[3], NULL, 10);
    
    printf("path = %s, pieceNumber=%ld\n", path, pieceNumber);
    
    if (strcmp("upload",argv[1]) != 0 && strcmp("download", argv[1]) != 0)
    {
        return 0;
    }
    std::string ipAddress;
    std::string user;
    std::string hdfsBasicPath;
    {
        std::ifstream input("/Users/jiangxiaotang/InWork/secret/hdfs.txt");
        getline(input, ipAddress);
        getline(input, user);
        getline(input, gHdfsBasicPath);
        getline(input, gLocalBasicPath);
    }
    
    SGHdfsStreamFactory::init(ipAddress.c_str(), user.c_str());
    AutoRecycle __r;
    if (strcmp("upload", argv[1]) == 0)
    {
        upload(path, pieceNumber);
    }
    else
    {
        download(path, pieceNumber);
    }
    
}
