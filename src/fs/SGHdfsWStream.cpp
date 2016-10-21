#include "SGHdfsWStream.h"
#include "SGDebug.h"
SGHdfsWStream::SGHdfsWStream(hdfsFS fs, const char* path)
{
    SGASSERT(NULL!=fs);
    SGASSERT(NULL!=path);
    mFs = fs;
    mFile = hdfsOpenFile(fs, path, O_WRONLY|O_CREAT, 0, 0, 0);
    SGASSERT(NULL!=mFile);
}
SGHdfsWStream::~ SGHdfsWStream()
{
    hdfsCloseFile(mFs, mFile);
}
size_t SGHdfsWStream::vWrite(const void* buffer, size_t size)
{
    auto real_size = hdfsWrite(mFs, mFile, buffer, (tSize)size);
    return real_size;
}

bool SGHdfsWStream::vFlush()
{
    auto status = hdfsFlush(mFs, mFile);
    return 0 == status;
}
