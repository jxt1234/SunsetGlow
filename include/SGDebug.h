#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/*Print method*/
#ifdef BUILD_FOR_ANDROID
#include <android/log.h>
#define SGPRINT(format, ...) __android_log_print(ANDROID_LOG_INFO, "SG", format,##__VA_ARGS__)
#define SGPRINT_FL(format,...) __android_log_print(ANDROID_LOG_INFO, "SG", format", FUNC: %s, LINE: %d \n",##__VA_ARGS__, __func__, __LINE__)
#else
#define SGPRINT(format, ...) printf(format,##__VA_ARGS__)
#define SGPRINT_FL(format,...) printf(format", FUNC: %s, LINE: %d \n", ##__VA_ARGS__,__func__, __LINE__)
#endif
/*Add with line and function*/
#define FUNC_PRINT(x) SGPRINT(#x"=%d in %s, %d \n",x,  __func__, __LINE__);
#define FUNC_PRINT_ALL(x, type) SGPRINT(#x"= "#type" %"#type" in %s, %d \n",x,  __func__, __LINE__);

#define CHECK_POINTER(x) {if(NULL==x){FUNC_PRINT_ALL(x,p);break;}}

#ifndef BUILD_FOR_ANDROID
#define SGASSERT(x) assert(x)
#else
#define SGASSERT(x) \
    {bool ___result = (x);\
        if (!(___result))\
        FUNC_PRINT((___result));}
#endif

#ifdef BUILD_FOR_ANDROID
#define SGCONVERT(t, c) ((t*)(c))
#else
#define SGCONVERT(t, c) (dynamic_cast<t*>(c))
#endif
#define SGFORCECONVERT(t, c) ((t*)(c))

