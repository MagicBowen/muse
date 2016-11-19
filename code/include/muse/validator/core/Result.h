#ifndef HFF41C447_37AF_4F2E_8CC9_28A2CF6D48D1
#define HFF41C447_37AF_4F2E_8CC9_28A2CF6D48D1

#include <muse/muse.h>

MUSE_NS_BEGIN

enum class Result
{
    CONTINUE,
    SUCCESS,
    FAILED
};

Result negtiveOf(Result result);

MUSE_NS_END

#endif
