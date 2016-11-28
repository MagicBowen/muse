#include <muse/promise/UntilPromise.h>

MUSE_NS_BEGIN

UntilPromise::UntilPromise(Promise& until, Promise& promise)
: DecoratorPromise(until, promise)
{
}

bool UntilPromise::isFinished() const
{
    if(decorator.evaluate().isFailed() ||
       promise.evaluate().isFailed())
    {
        return true;
    }
    if(decorator.evaluate().isSuccess() ||
       promise.evaluate().isSuccess())
    {
        return true;
    }
    return false;
}

void UntilPromise::fixResult()
{
    if(decorator.evaluate().isSuccess())
    {
        result = promise.evaluate();
        return;
    }
    if(promise.evaluate().isSuccess())
    {
        result = Result::SUCCESS;
        return;
    }

    result = Result::FAILED;
}

MUSE_NS_END
