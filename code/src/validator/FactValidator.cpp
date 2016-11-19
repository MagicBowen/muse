#include <muse/validator/FactValidator.h>
#include <muse/fact/core/Fact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>
#include <muse/base/TypeName.h>

MUSE_NS_BEGIN

__DEF_GOF_STATE_INTERFACE(FactValidator)
{
    DEFAULT(void, start(FactValidator&));
    DEFAULT(void, stop(FactValidator&));
    DEFAULT(void, onEvent(FactValidator&, const Event&));
    DEFAULT(Result, evaluate(const FactValidator&) const);
};

__DEF_GOF_STATE(FactValidator, Waited)
{
private:
    OVERRIDE(void start(FactValidator& THIS))
    {
        THIS.onStarted();
        THIS.__GOTO_STATE(Started);
    }

    OVERRIDE(void stop(FactValidator& THIS))
    {
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }
};

__DEF_GOF_STATE(FactValidator, Started)
{
private:
    OVERRIDE(void stop(FactValidator& THIS))
    {
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }

    OVERRIDE(void onEvent(FactValidator& THIS, const Event& event))
    {
        DBG_LOG("%s deal event[type = %d, value = %f].", nameOf(&THIS.fact), event.type, event.value);
        THIS.occurred = THIS.fact.satisfyWith(event);

        if(THIS.occurred)
        {
            THIS.onStopped();
            THIS.__GOTO_STATE(Stopped);
        }
    }
};

__DEF_GOF_STATE(FactValidator, Stopped)
{
private:
    OVERRIDE(Result evaluate(const FactValidator& THIS) const)
    {
        return THIS.occurred ? Result::SUCCESS : Result::FAILED;
    }
};

__REGISTER_STATE(FactValidator, Waited);
__REGISTER_STATE(FactValidator, Started);
__REGISTER_STATE(FactValidator, Stopped);


FactValidator::FactValidator(Fact& fact)
: fact(fact)
{
    __GOTO_STATE(Waited);
}

void FactValidator::start()
{
    state->start(*this);
}

void FactValidator::stop()
{
    state->stop(*this);
}

void FactValidator::onEvent(const Event& event)
{
    state->onEvent(*this, event);
}

Result FactValidator::evaluate() const
{
    return state->evaluate(*this);
}

void FactValidator::onStarted()
{
    INFO_LOG("%s is started!", nameOf(this));
}

void FactValidator::onStopped()
{
    INFO_LOG("%s is stopped!", nameOf(this));

    occurred ? onSuccess() : onFailed();
}

void FactValidator::onSuccess()
{
    INFO_LOG("%s is success!", nameOf(this));
}

void FactValidator::onFailed()
{
    ERR_LOG("%s is Failed!", nameOf(this));
}

MUSE_NS_END
