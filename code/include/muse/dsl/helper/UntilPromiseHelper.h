#ifndef HD21BD807_81AB_4E9E_B801_50C008CE5E5D
#define HD21BD807_81AB_4E9E_B801_50C008CE5E5D

#include <muse/promise/UntilPromise.h>

MUSE_NS_BEGIN

template<typename UNTIL, typename PROMISE>
struct UntilPromiseHelper : UntilPromise
{
    UntilPromiseHelper(const UNTIL& u, const PROMISE& p)
    : UntilPromise(until, promise), until(u), promise(p)
    {
    }

    UntilPromiseHelper(const UntilPromiseHelper& rhs)
    : UntilPromise(until, promise), until(rhs.until), promise(rhs.promise)
    {
    }

private:
    UNTIL until;
    PROMISE promise;
};

MUSE_NS_END

#define __until(UNTIL, PROMISE) UntilPromiseHelper<decltype(UNTIL), decltype(PROMISE)>(UNTIL, PROMISE)

#endif
