#include <muse/promise/FactPromise.h>
#include <muse/fact/Fact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

__DEF_GOF_STATE_INTERFACE(FactPromise)
{
    DEFAULT(void, start(FactPromise&));
    DEFAULT(void, stop(FactPromise&));
    DEFAULT(void, onEvent(FactPromise&, const Event&));
};

__DEF_GOF_STATE(FactPromise, Waited)
{
private:
    OVERRIDE(void start(FactPromise& THIS))
    {
        THIS.onStarted();
        THIS.__GOTO_STATE(Started);
    }

    OVERRIDE(void stop(FactPromise& THIS))
    {
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }
};

__DEF_GOF_STATE(FactPromise, Started)
{
private:
    OVERRIDE(void stop(FactPromise& THIS))
    {
        THIS.onStopped();
        THIS.__GOTO_STATE(Stopped);
    }

    OVERRIDE(void onEvent(FactPromise& THIS, const Event& event))
    {
        THIS.fact.confirm(event);

        if(THIS.fact.isOccurred())
        {
            THIS.onStopped();
            THIS.__GOTO_STATE(Stopped);
        }
    }
};

__DEF_GOF_STATE(FactPromise, Stopped)
{
};

__REGISTER_STATE(FactPromise, Waited);
__REGISTER_STATE(FactPromise, Started);
__REGISTER_STATE(FactPromise, Stopped);


FactPromise::FactPromise(Fact& fact)
: fact(fact)
{
    __GOTO_STATE(Waited);
}

void FactPromise::start()
{
    state->start(*this);
}

void FactPromise::stop()
{
    state->stop(*this);
}

void FactPromise::handle(const Event& event)
{
    state->onEvent(*this, event);
}

void FactPromise::onStarted()
{
    INFO_LOG("Promise is started!");
    fact.start();
}

void FactPromise::onStopped()
{
    INFO_LOG("Promise is stopped!");
    WARN_LOG("%s", fact.info().c_str());

    fact.stop();

    result = fact.isOccurred()? Result::SUCCESS : Result::FAILED;
    (result.isSuccess()) ? onSuccess() : onFailed();
}

MUSE_NS_END
