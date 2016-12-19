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

void DecoratorPromise::handle(const Event& event)
{
    decorator.handle(event);
    promise.handle(event);

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
