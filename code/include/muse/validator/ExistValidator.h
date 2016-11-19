#ifndef H746F98DF_64A2_4180_B583_A428C8D6F374
#define H746F98DF_64A2_4180_B583_A428C8D6F374

#include <muse/validator/core/Validator.h>
#include <muse/base/State.h>

MUSE_NS_BEGIN

struct Fact;

struct ExistValidator : Validator
{
    ExistValidator(Fact& fact);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    void onStarted();
    void onStopped();
    void onSuccess();
    void onFailed();

private:
    __USING_GOF_STATE;
    __HAS_STATE(Waited);
    __HAS_STATE(Started);
    __HAS_STATE(Stopped);

private:
    Fact& fact;
    Result result{Result::CONTINUE};
};

MUSE_NS_END

#endif
