#include "SGHdfsStreamFactory.h"
#include "libhdfs/hdfs.h"
#include "SGDebug.h"
#include "SGHdfsStream.h"
#include "SGHdfsWStream.h"


struct SGHdfsStreamFactory::Context
{
    hdfsFS pFs;
};

SGHdfsStreamFactory* SGHdfsStreamFactory::gInstance = NULL;
void SGHdfsStreamFactory::init(const char* namenode, const char* user)
{
    SGASSERT(NULL == gInstance);
    gInstance = new SGHdfsStreamFactory(namenode, user);
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

GPStream* SGHdfsStreamFactory::vRead(const char* fileName) const
{
    return new SGHdfsStream(mContext->pFs, fileName);
}
GPWStream* SGHdfsStreamFactory::vWrite(const char* fileName) const
{
    return new SGHdfsWStream(mContext->pFs, fileName);
}

SGHdfsStreamFactory::SGHdfsStreamFactory(const char* nameNode, const char* user)
{
    hdfsBuilder* builder = hdfsNewBuilder();
    hdfsBuilderSetNameNode(builder, nameNode);
    hdfsBuilderSetUserName(builder, user);
    hdfsFS fs = hdfsBuilderConnect(builder);
    mContext = new Context;
    mContext->pFs = fs;
}

SGHdfsStreamFactory::~SGHdfsStreamFactory()
{
    hdfsDisconnect(mContext->pFs);
    delete mContext;
}
