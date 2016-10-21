#include "SGHdfsStreamFactory.h"
#include "libhdfs/hdfs.h"
#include "SGDebug.h"
#include "SGHdfsStream.h"
#include "SGHdfsWStream.h"
#include "SGPathUtils.h"
#include <string>
#include <fstream>
#include <sstream>


struct SGHdfsStreamFactory::Context
{
    hdfsFS pFs;
    std::string sRootPath;
};

SGHdfsStreamFactory* SGHdfsStreamFactory::gInstance = NULL;
void SGHdfsStreamFactory::initWithConf(const char* confName)
{
    std::string ipAddress;
    std::string user;
    std::string hdfsBasicPath;
    {
        std::ifstream input(confName);
        getline(input, ipAddress);
        getline(input, user);
        getline(input, hdfsBasicPath);
    }
    SGHdfsStreamFactory::init(ipAddress.c_str(), user.c_str(), hdfsBasicPath);
}
void SGHdfsStreamFactory::init(const char* namenode, const char* user, std::string root)
{
    SGASSERT(NULL == gInstance);
    gInstance = new SGHdfsStreamFactory(namenode, user, root);
}

void SGHdfsStreamFactory::destroy()
{
    SGASSERT(NULL!=gInstance);
    delete gInstance;
}



const SGHdfsStreamFactory* SGHdfsStreamFactory::getInstance()
{
    return gInstance;
}

static std::string _merge(const std::string& root, const std::string& fileName)
{
    std::ostringstream os;
    os <<root <<"/"<<fileName;
    return os.str();
}

GPStream* SGHdfsStreamFactory::vRead(const char* fileName) const
{
    FUNC_PRINT_ALL(fileName, s);
    auto newFile = _merge(mContext->sRootPath, fileName);
    if (0 != hdfsExists(mContext->pFs, newFile.c_str()))
    {
        return NULL;
    }
    return new SGHdfsStream(mContext->pFs, newFile.c_str());
}
GPWStream* SGHdfsStreamFactory::vWrite(const char* fileName) const
{
    FUNC_PRINT_ALL(fileName, s);
    auto newFile = _merge(mContext->sRootPath, fileName);
    auto path = SGPathUtils::getDirectory(newFile);
    if (!path.empty())
    {
        if (0 != hdfsExists(mContext->pFs, path.c_str()))
        {
            hdfsCreateDirectory(mContext->pFs, path.c_str());
        }
    }
    return new SGHdfsWStream(mContext->pFs, newFile.c_str());
}

SGHdfsStreamFactory::SGHdfsStreamFactory(const char* nameNode, const char* user, const std::string& root)
{
    hdfsBuilder* builder = hdfsNewBuilder();
    hdfsBuilderSetNameNode(builder, nameNode);
    hdfsBuilderSetUserName(builder, user);
    hdfsFS fs = hdfsBuilderConnect(builder);
    mContext = new Context;
    mContext->pFs = fs;
    mContext->sRootPath = root;
}

SGHdfsStreamFactory::~SGHdfsStreamFactory()
{
    hdfsDisconnect(mContext->pFs);
    delete mContext;
}

