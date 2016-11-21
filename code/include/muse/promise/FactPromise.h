#ifndef HC41D416A_7053_462D_A6E5_D182D4B746ED
#define HC41D416A_7053_462D_A6E5_D182D4B746ED

#include <muse/promise/Promise.h>
#include <muse/base/State.h>

MUSE_NS_BEGIN

struct Fact;

struct FactPromise : Promise
{
    explicit FactPromise(Fact& fact);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));

private:
    void onStarted();
    void onStopped();

private:
    __USING_GOF_STATE;
    __HAS_STATE(Waited);
    __HAS_STATE(Started);
    __HAS_STATE(Stopped);

private:
    ABSTRACT(void onSuccess());
    ABSTRACT(void onFailed());

protected:
    Fact& fact;
    Result result{Result::UNKNOWN};
};

MUSE_NS_END

#endif
