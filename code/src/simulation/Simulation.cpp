#include <muse/simulation/Simulation.h>
#include <muse/validator/core/Validator.h>
#include <muse/event/EventQueue.h>

MUSE_NS_BEGIN

Simulation::Simulation(Validator& validator)
: validator(validator)
{
}

void Simulation::play()
{
    validator.start();
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
    validator.stop();
    result = (validator.evaluate() == Result::SUCCESS);
}

bool Simulation::processEvent(const Event& event)
{
    updateTime();
    if(isTimeOut()) return false;

    validator.onEvent(event);
    if(validator.evaluate() != Result::CONTINUE) return false;

    return true;
}

bool Simulation::isSuccess() const
{
    return result;
}

MUSE_NS_END
