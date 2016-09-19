#ifndef INCLUDE_SGHDFSSTREAMFACTORY_H
#define INCLUDE_SGHDFSSTREAMFACTORY_H
#include "lowlevelAPI/GPIStreamCreator.h"
#include "lowlevelAPI/GPRefCount.h"
class SGHdfsStreamFactory :public GPIStreamCreator
{
public:
    struct Context;
    static void init(const char* namenode, const char* user);
    static void destroy();
    static const SGHdfsStreamFactory* getInstance();
    
    virtual GPStream* vRead(const char* fileName) const override;
    virtual GPWStream* vWrite(const char* fileName) const override;
private:
    SGHdfsStreamFactory(const char* nameNode, const char* user);
    virtual ~ SGHdfsStreamFactory();
    
    Context* mContext;
    
    static SGHdfsStreamFactory* gInstance;
};
#endif
