#include <muse/promise/ExistPromise.h>
#include <muse/fact/core/Fact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

__DEF_GOF_STATE_INTERFACE(ExistPromise)
{
    DEFAULT(void, start(ExistPromise&));
    DEFAULT(void, stop(ExistPromise&));
    DEFAULT(void, onEvent(ExistPromise&, const Event&));
};

__DEF_GOF_STATE(ExistPromise, Waited)
{
private:
    OVERRIDE(void start(ExistPromise& THIS))
    {
        THIS.onStarted();
        THIS.__GOTO_STATE(Started);
    }

    OVERRIDE(void stop(ExistPromise& THIS))
    {
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }
};

__DEF_GOF_STATE(ExistPromise, Started)
{
private:
    OVERRIDE(void stop(ExistPromise& THIS))
    {
        THIS.result = Result::FAILED;
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }

    OVERRIDE(void onEvent(ExistPromise& THIS, const Event& event))
    {
        DBG_LOG("Promise verify event[type = %d, value = %f].", event.type, event.value);

        if(THIS.fact.confirm(event))
        {
            THIS.result = Result::SUCCESS;
            THIS.onStopped();
            THIS.__GOTO_STATE(Stopped);
        }
    }
};

__DEF_GOF_STATE(ExistPromise, Stopped)
{
};

__REGISTER_STATE(ExistPromise, Waited);
__REGISTER_STATE(ExistPromise, Started);
__REGISTER_STATE(ExistPromise, Stopped);


ExistPromise::ExistPromise(Fact& fact)
: fact(fact)
{
    __GOTO_STATE(Waited);
}

void ExistPromise::start()
{
    state->start(*this);
}

void ExistPromise::stop()
{
    state->stop(*this);
}

void ExistPromise::onEvent(const Event& event)
{
    state->onEvent(*this, event);
}

Result ExistPromise::evaluate() const
{
    return result;
}

void ExistPromise::onStarted()
{
    INFO_LOG("Promise is started!");
}

void ExistPromise::onStopped()
{
    INFO_LOG("Promise is stopped!");

    if(result == Result::UNKNOWN) result = Result::FAILED;
    (result == Result::SUCCESS) ? onSuccess() : onFailed();
}

void ExistPromise::onSuccess()
{
    INFO_LOG("Promise is success!");
}

void ExistPromise::onFailed()
{
    ERR_LOG("Promise is Failed!");
}

MUSE_NS_END
