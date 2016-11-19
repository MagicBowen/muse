#ifndef H1DCCD353_EA72_40E9_8C54_3C9E73A8E983
#define H1DCCD353_EA72_40E9_8C54_3C9E73A8E983

#include <muse/base/Singleton.h>

MUSE_NS_BEGIN

struct Event;

DEF_SINGLETON(EventQueue)
{
    const Event* fetch();
    void push(const Event&);
};

MUSE_NS_END

#endif
