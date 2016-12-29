#ifndef UTILS_ALDYNAMICBUFFER_H
#define UTILS_ALDYNAMICBUFFER_H
#include "SGDebug.h"
class ALDynamicBuffer
{
    public:
        ALDynamicBuffer(size_t batchSize);
        virtual ~ALDynamicBuffer();
        char* content() const {return mContent;}
        size_t size() const {return mSize;}
        void load(const char* src, size_t len);
        void reset();
    private:
        char* mContent;
        size_t mSize;
        size_t mCapacity;
};
#endif
