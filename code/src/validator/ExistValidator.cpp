#include <muse/validator/ExistValidator.h>
#include "../../include/muse/fact/core/BaseFact.h"
#include <muse/event/Event.h>
#include <muse/base/log.h>
#include <muse/base/TypeName.h>

MUSE_NS_BEGIN

__DEF_GOF_STATE_INTERFACE(ExistValidator)
{
    DEFAULT(void, start(ExistValidator&));
    DEFAULT(void, stop(ExistValidator&));
    DEFAULT(void, onEvent(ExistValidator&, const Event&));
};

__DEF_GOF_STATE(ExistValidator, Waited)
{
private:
    OVERRIDE(void start(ExistValidator& THIS))
    {
        THIS.onStarted();
        THIS.__GOTO_STATE(Started);
    }

    OVERRIDE(void stop(ExistValidator& THIS))
    {
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }
};

__DEF_GOF_STATE(ExistValidator, Started)
{
private:
    OVERRIDE(void stop(ExistValidator& THIS))
    {
        THIS.result = Result::FAILED;
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }

    OVERRIDE(void onEvent(ExistValidator& THIS, const Event& event))
    {
        DBG_LOG("%s deal event[type = %d, value = %f].", nameOf(&THIS.fact), event.type, event.value);

        if(THIS.fact.confirm(event))
        {
            THIS.result = Result::SUCCESS;
            THIS.onStopped();
            THIS.__GOTO_STATE(Stopped);
        }
    }
};

__DEF_GOF_STATE(ExistValidator, Stopped)
{
};

__REGISTER_STATE(ExistValidator, Waited);
__REGISTER_STATE(ExistValidator, Started);
__REGISTER_STATE(ExistValidator, Stopped);


ExistValidator::ExistValidator(BaseFact& fact)
: fact(fact)
{
    __GOTO_STATE(Waited);
}

void ExistValidator::start()
{
    state->start(*this);
}

void ExistValidator::stop()
{
    state->stop(*this);
}

void ExistValidator::onEvent(const Event& event)
{
    state->onEvent(*this, event);
}

Result ExistValidator::evaluate() const
{
    return result;
}

void ExistValidator::onStarted()
{
    INFO_LOG("%s is started!", nameOf(this));
}

void ExistValidator::onStopped()
{
    INFO_LOG("%s is stopped!", nameOf(this));

    if(result == Result::CONTINUE) result = Result::FAILED;
    (result == Result::SUCCESS) ? onSuccess() : onFailed();
}

void ExistValidator::onSuccess()
{
    INFO_LOG("%s is success!", nameOf(this));
}

void ExistValidator::onFailed()
{
    ERR_LOG("%s is Failed!", nameOf(this));
}

MUSE_NS_END
