#ifndef H746F98DF_64A2_4180_B583_A428C8D6F374
#define H746F98DF_64A2_4180_B583_A428C8D6F374

#include <muse/promise/FactPromise.h>

MUSE_NS_BEGIN

struct ExistPromise : FactPromise
{
    explicit ExistPromise(Fact& fact);

private:
    OVERRIDE(Result evaluate() const);
    OVERRIDE(void onSuccess());
    OVERRIDE(void onFailed());
};

MUSE_NS_END

#endif
