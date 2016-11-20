#ifndef HD5534454_10D7_4542_8E62_D2F84DDCBAA5
#define HD5534454_10D7_4542_8E62_D2F84DDCBAA5

#include <muse/base/keywords.h>
#include <muse/promise/Result.h>

MUSE_NS_BEGIN

struct Event;

DEF_INTERFACE(Promise)
{
    ABSTRACT(void start());
    ABSTRACT(void stop());
    ABSTRACT(void onEvent(const Event&));
    ABSTRACT(Result evaluate() const);
};

MUSE_NS_END

#endif
