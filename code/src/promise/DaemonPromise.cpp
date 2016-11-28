#include <muse/promise/DaemonPromise.h>

MUSE_NS_BEGIN

DaemonPromise::DaemonPromise(Promise& daemon, Promise& promise)
: DecoratorPromise(daemon, promise)
{
}

bool DaemonPromise::isFinished() const
{
    if(decorator.evaluate().isFailed() ||
       promise.evaluate().isFailed())
    {
        return true;
    }
    if(promise.evaluate().isSuccess())
    {
        return true;
    }
    return false;
}

void DaemonPromise::fixResult()
{
    if(promise.evaluate().isSuccess())
    {
        result = Result::SUCCESS;
        return;
    }

    result = Result::FAILED;
}

MUSE_NS_END
