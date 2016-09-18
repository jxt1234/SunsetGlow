#ifndef SRC_FS_SGHDFSSTREAM_H
#define SRC_FS_SGHDFSSTREAM_H
#include "lowlevelAPI/GPStream.h"
#include "libhdfs/hdfs.h"
class SGHdfsStream:public GPStream
{
public:
    SGHdfsStream(hdfsFS pFs, const char* fileName);
    virtual ~SGHdfsStream();
    
    virtual size_t vRead(void* buffer, size_t size) override;
    virtual bool vIsEnd() const override;
    virtual bool vRewind() override;
private:
    hdfsFile mFile;
    hdfsFS mFs;
    
    bool mEnd = false;
};

#endif
