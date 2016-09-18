#include "SGDebug.h"
#include "SGHdfsStream.h"
SGHdfsStream::SGHdfsStream(hdfsFS pFs, const char* fileName)
{
    SGASSERT(NULL!=pFs);
    SGASSERT(NULL!=fileName);
    mFs = pFs;
    mFile = hdfsOpenFile(pFs, fileName, O_RDONLY, 0, 0, 0);
    SGASSERT(NULL!=mFile);
}
SGHdfsStream::~SGHdfsStream()
{
    hdfsCloseFile(mFs, mFile);
}

size_t SGHdfsStream::vRead(void* buffer, size_t size)
{
    auto realSize = hdfsRead(mFs, mFile, buffer, (tSize)size);
    if (0 >= realSize)
    {
        mEnd = true;
    }
    return realSize;
}
bool SGHdfsStream::vIsEnd() const
{
    return mEnd;
}


bool SGHdfsStream::vRewind()
{
    auto status = hdfsSeek(mFs, mFile, 0);
    if (0 == status)
    {
        mEnd = false;
        return true;
    }
    return false;
}

