#include <muse/promise/ListenedPromise.h>
#include <muse/listener/PromiseListener.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

ListenedPromise::ListenedPromise(Promise& p)
: promise(p)
{
}

void ListenedPromise::addListener(PromiseListener& listener)
{
    listeners.push_back(&listener);
}

void ListenedPromise::clear()
{
    listeners.clear();
}

void ListenedPromise::start()
{
    promise.start();
    foreach(listeners, [](auto listener){listener->onStarted();});
}
void ListenedPromise::stop()
{
    promise.stop();
    foreach(listeners, [](auto listener){listener->onStopped();});
}

void ListenedPromise::handle(const Event& event)
{
    promise.handle(event);
    foreach(listeners, [&event](auto listener){listener->onEvent(event);});

    auto result = promise.evaluate();
    if(result.isSuccess())
    {
        foreach(listeners, [](auto listener){listener->onSuccess();});
    }
    else if(result.isFailed())
    {
        foreach(listeners, [](auto listener){listener->onFailed();});
    }
}

Result ListenedPromise::evaluate() const
{
    return promise.evaluate();
}

MUSE_NS_END
