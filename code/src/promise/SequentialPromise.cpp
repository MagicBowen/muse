#include <muse/promise/SequentialPromise.h>
#include <muse/base/Log.h>

MUSE_NS_BEGIN

SequentialPromise::SequentialPromise(std::initializer_list<Promise*> promises)
: promises(promises)
{
    currentPromise = this->promises.begin();
}

Promise& SequentialPromise::current()
{
    return **currentPromise;
}

void SequentialPromise::start()
{
    current().start();
}

void SequentialPromise::stop()
{
    if(isFinish()) return;

    doStop();
}

void SequentialPromise::doStop()
{
    for(auto promise : promises)
    {
        promise->stop();
    }

    result = Result::FAILED;
}

void SequentialPromise::onEvent(const Event& event)
{
    if(isFixed(result)) return;

    processEvent(event);
}

Result SequentialPromise::evaluate() const
{
    if(isFixed(result))  return result;
    return isFinish() ? Result::SUCCESS : Result::UNKNOWN;
}

void SequentialPromise::processEvent(const Event& event)
{
    current().onEvent(event);

    switch(current().evaluate())
    {
        case Result::UNKNOWN:   /* need do nothing*/    return;
        case Result::FAILED:    onCurrentFailed();      return;
        case Result::SUCCESS:   onCurrentSuccess();     return;
    }

    return;
}

void SequentialPromise::onCurrentFailed()
{
    doStop();
}

void SequentialPromise::onCurrentSuccess()
{
    if(gotoNext())
    {
        current().start();
        return;
    }

    result = Result::SUCCESS;
}

bool SequentialPromise::isFinish() const
{
    return currentPromise == promises.end();
}

bool SequentialPromise::gotoNext()
{
    return ++currentPromise != promises.end();
}

MUSE_NS_END
