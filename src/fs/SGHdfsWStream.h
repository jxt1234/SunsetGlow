#ifndef SRC_FS_SGHDFSWSTREAM_H
#define SRC_FS_SGHDFSWSTREAM_H
#include "lowlevelAPI/GPStream.h"
#include "libhdfs/hdfs.h"
class SGHdfsWStream:public GPWStream
{
public:
    SGHdfsWStream(hdfsFS fs, const char* path);
    virtual ~ SGHdfsWStream();
    virtual size_t vWrite(const void* buffer, size_t size) override;
    virtual bool vFlush() override;
private:
    hdfsFS mFs;
    hdfsFile mFile;
};

#endif
