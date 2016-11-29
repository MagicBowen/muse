#ifndef HC98D75AA_6C61_462B_BF12_9A517E245DF5
#define HC98D75AA_6C61_462B_BF12_9A517E245DF5

#include <muse/promise/DaemonPromise.h>

MUSE_NS_BEGIN

template<typename DAEMON, typename PROMISE>
struct DaemonPromiseHelper : DaemonPromise
{
    DaemonPromiseHelper(const DAEMON& d, const PROMISE& p)
    : DaemonPromise(daemon, promise), daemon(d), promise(p)
    {
    }

    DaemonPromiseHelper(const DaemonPromiseHelper& rhs)
    : DaemonPromise(daemon, promise), daemon(rhs.daemon), promise(rhs.promise)
    {
    }

private:
    DAEMON daemon;
    PROMISE promise;
};

MUSE_NS_END

#define __daemon(DAEMON, PROMISE)   ::MUSE_NS::DaemonPromiseHelper<decltype(DAEMON), decltype(PROMISE)>(DAEMON, PROMISE)

#endif
