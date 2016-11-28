#ifndef HE49B3DA0_0C4E_46AA_90A0_27B45637012B
#define HE49B3DA0_0C4E_46AA_90A0_27B45637012B

#include <muse/promise/DecoratorPromise.h>

MUSE_NS_BEGIN

struct UntilPromise : DecoratorPromise
{
    UntilPromise(Promise& until, Promise& promise);

private:
    OVERRIDE(bool isFinished() const);
    OVERRIDE(void fixResult());
};

MUSE_NS_END

#endif
