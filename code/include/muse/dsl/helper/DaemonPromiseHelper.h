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

    DaemonPromiseHelper(DAEMON&& d, PROMISE&& p)
    : DaemonPromise(daemon, promise), daemon(std::move(d)), promise(std::move(p))
    {
    }

    DaemonPromiseHelper(DaemonPromiseHelper&& rhs)
    : DaemonPromise(daemon, promise), daemon(std::move(rhs.daemon)), promise(std::move(rhs.promise))
    {
    }

private:
    DAEMON daemon;
    PROMISE promise;
};

MUSE_NS_END

#define __daemon(DAEMON, PROMISE)     \
::MUSE_NS::DaemonPromiseHelper<std::decay_t<decltype(DAEMON)>, std::decay_t<decltype(PROMISE)>>(DAEMON, PROMISE)

#endif
