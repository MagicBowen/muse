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
    if(result.isFixed()) return;

    daemon.stop();
    promise.stop();

    updateResult();
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

void DaemonPromise::updateResult()
{
    if(promise.evaluate().isSuccess())
    {
        result = Result::SUCCESS;
        return;
    }

    result = Result::FAILED;
}

Result DaemonPromise::evaluate() const
{
    return result;
}

MUSE_NS_END
