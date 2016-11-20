#include <muse/simulation/Simulation.h>
#include <muse/promise/Promise.h>
#include <muse/event/EventQueue.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

void Simulation::setPromise(Promise& promise)
{
    this->promise = &promise;
}

void Simulation::setDuration(unsigned int seconds)
{
    this->durationSeconds = seconds;
}

void Simulation::play()
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

void Simulation::updateTime()
{
    elaspedSeconds++;
}

bool Simulation::isTimeOut() const
{
    return elaspedSeconds > durationSeconds;
}

void Simulation::proceed()
{
    while(auto event = EventQueue::getInstance().fetch())
    {
        if(!processEvent(*event)) break;
    }

    terminate();
}

void Simulation::terminate()
{
    INFO_LOG("Simulation terminate!")
    promise->stop();
    result = (promise->evaluate() == Result::SUCCESS);
}

bool Simulation::processEvent(const Event& event)
{
    updateTime();

    if(isTimeOut())
    {
        INFO_LOG("Simulation is timeout!");
        return false;
    }

    promise->onEvent(event);
    if(promise->evaluate() != Result::UNKNOWN)
    {
        INFO_LOG("Simulation is finish!");
        return false;
    }

    return true;
}

bool Simulation::isSuccess() const
{
    return result;
}

MUSE_NS_END
