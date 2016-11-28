#include <muse/promise/UntilPromise.h>

MUSE_NS_BEGIN

UntilPromise::UntilPromise(Promise& until, Promise& promise)
: until(until), promise(promise)
{
}

void UntilPromise::start()
{
    until.start();
    promise.start();
}

void UntilPromise::stop()
{
    if(result.isFixed()) return;

    until.stop();
    promise.stop();

    updateResult();
}

void UntilPromise::onEvent(const Event& event)
{
    until.onEvent(event);
    promise.onEvent(event);

    if(until.evaluate().isFailed() ||
       promise.evaluate().isFailed())
    {
        until.stop();
        promise.stop();
        result = Result::FAILED;
        return;
    }

    if(until.evaluate().isSuccess())
    {
        promise.stop();
        result = promise.evaluate();
        return;
    }
}

void UntilPromise::updateResult()
{
    if(until.evaluate().isSuccess())
    {
        result = promise.evaluate();
        return;
    }

    result = Result::FAILED;
}

Result UntilPromise::evaluate() const
{
    return result;
}

MUSE_NS_END
