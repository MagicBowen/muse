#include <muse/promise/DecoratorPromise.h>

MUSE_NS_BEGIN

DecoratorPromise::DecoratorPromise(Promise& decorator, Promise& promise)
: decorator(decorator), promise(promise)
{
}

void DecoratorPromise::start()
{
    decorator.start();
    promise.start();
}

void DecoratorPromise::stop()
{
    if(result.isFixed()) return;

    terminate();
}

void DecoratorPromise::onEvent(const Event& event)
{
    decorator.onEvent(event);
    promise.onEvent(event);

    if(isFinished())
    {
        terminate();
    }
}

void DecoratorPromise::terminate()
{
    decorator.stop();
    promise.stop();

    fixResult();
}

Result DecoratorPromise::evaluate() const
{
    return result;
}

MUSE_NS_END
