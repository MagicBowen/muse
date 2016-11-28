#ifndef H551580F8_9AED_4C2C_8D3C_ACA616288098
#define H551580F8_9AED_4C2C_8D3C_ACA616288098

#include <muse/promise/DecoratorPromise.h>

MUSE_NS_BEGIN

struct DaemonPromise : DecoratorPromise
{
    DaemonPromise(Promise& daemon, Promise& promise);

private:
    OVERRIDE(bool isFinished() const);
    OVERRIDE(void fixResult());
};

MUSE_NS_END

#endif
