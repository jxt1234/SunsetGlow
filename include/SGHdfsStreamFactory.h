#ifndef INCLUDE_SGHDFSSTREAMFACTORY_H
#define INCLUDE_SGHDFSSTREAMFACTORY_H
#include "lowlevelAPI/GPStream.h"
#include "lowlevelAPI/GPRefCount.h"
class SGHdfsStreamFactory
{
public:
    struct Context;
    static void init(const char* namenode, const char* user);
    static SGHdfsStreamFactory* getInstance();
    
    GPStream* read(const char* fileName);
    GPWStream* write(const char* fileName);
private:
    SGHdfsStreamFactory(const char* nameNode, const char* user);
    virtual ~ SGHdfsStreamFactory();
    
    Context* mContext;
    
    static SGHdfsStreamFactory* gInstance;
};
#endif
