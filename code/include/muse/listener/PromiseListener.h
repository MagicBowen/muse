#ifndef H10FB845A_FE45_43B5_ADD1_3A79860B71C0
#define H10FB845A_FE45_43B5_ADD1_3A79860B71C0

#include <muse/base/keywords.h>

MUSE_NS_BEGIN

struct Event;

DEF_INTERFACE(PromiseListener)
{
    DEFAULT(void, onStarted());
    DEFAULT(void, onStopped());
    DEFAULT(void, onEvent(const Event&));
    DEFAULT(void, onSuccess());
    DEFAULT(void, onFailed());
};

MUSE_NS_END

#endif
