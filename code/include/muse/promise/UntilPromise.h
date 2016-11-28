#ifndef HE49B3DA0_0C4E_46AA_90A0_27B45637012B
#define HE49B3DA0_0C4E_46AA_90A0_27B45637012B

#include <muse/promise/Promise.h>

MUSE_NS_BEGIN

struct UntilPromise : Promise
{
    UntilPromise(Promise& until, Promise& promise);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    void updateResult();

private:
    Promise& until;
    Promise& promise;
    Result result;
};

MUSE_NS_END

#endif
