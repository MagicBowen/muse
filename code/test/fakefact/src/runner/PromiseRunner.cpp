#include <fakefact/include/runner/PromiseRunner.h>
#include <muse/promise/Promise.h>
#include <fakefact/include/event/EventFetcher.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

PromiseRunner::PromiseRunner(EventFetcher& fetcher)
: fetcher(fetcher)
{
}

void PromiseRunner::setPromise(Promise& promise)
{
    this->promise = &promise;
}

void PromiseRunner::setDuration(unsigned int seconds)
{
    this->durationSeconds = seconds;
}

void PromiseRunner::run()
{
    if(!promise)
    {
        ERR_LOG("should set the promise to simulation first!");
        return;
    }

    INFO_LOG("Simulation play...")
    promise->start();
    proceed();
}

void PromiseRunner::stop()
{
    if(!promise) return;
    if(result) return;

    terminate();
}

void PromiseRunner::proceed()
{
    while(auto event = fetcher.fetch())
    {
        if(!processEvent(*event)) break;
    }

    terminate();
}

void PromiseRunner::terminate()
{
    promise->stop();
    result = (promise->evaluate().isSuccess());
}

bool PromiseRunner::processEvent(const Event& event)
{
    updateTime();

    if(isTimeOut())
    {
        INFO_LOG("Simulation is timeout!");
        return false;
    }

    promise->handle(event);
    if(promise->evaluate().isFixed())
    {
        INFO_LOG("Simulation is finish!");
        return false;
    }

    return true;
}

bool PromiseRunner::isSuccess() const
{
    return result;
}

void PromiseRunner::updateTime()
{
    elaspedSeconds++;
}

bool PromiseRunner::isTimeOut() const
{
    return elaspedSeconds > durationSeconds;
}

MUSE_NS_END
