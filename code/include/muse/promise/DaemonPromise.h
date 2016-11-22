#ifndef H551580F8_9AED_4C2C_8D3C_ACA616288098
#define H551580F8_9AED_4C2C_8D3C_ACA616288098

#include <muse/promise/Promise.h>

MUSE_NS_BEGIN

struct DaemonPromise : Promise
{
    DaemonPromise(Promise& daemon, Promise& promise);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    Promise& daemon;
    Promise& promise;
    Result result;
};

MUSE_NS_END

#endif
