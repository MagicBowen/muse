#include <muse/promise/DaemonPromise.h>

MUSE_NS_BEGIN

DaemonPromise::DaemonPromise(Promise& daemon, Promise& promise)
: daemon(daemon), promise(promise)
{
}

void DaemonPromise::start()
{
    daemon.start();
    promise.start();
}

void DaemonPromise::stop()
{
    if(result.isFailed()) return;

    daemon.stop();
    promise.stop();
}

void DaemonPromise::onEvent(const Event& event)
{
    daemon.onEvent(event);
    promise.onEvent(event);

    if(daemon.evaluate().isFailed() ||
       promise.evaluate().isFailed())
    {
        daemon.stop();
        promise.stop();
        result = Result::FAILED;
        return;
    }

    if(promise.evaluate().isSuccess())
    {
        daemon.stop();
        result = Result::SUCCESS;
        return;
    }
}

Result DaemonPromise::evaluate() const
{
    return result;
}

MUSE_NS_END
