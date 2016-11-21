#ifndef HF6D07F91_ACE5_45D9_9390_80A7DEB5301E
#define HF6D07F91_ACE5_45D9_9390_80A7DEB5301E

#include <muse/promise/FactPromise.h>

MUSE_NS_BEGIN

struct NotExistPromise : FactPromise
{
    explicit NotExistPromise(Fact& fact);

private:
    OVERRIDE(Result evaluate() const);
    OVERRIDE(void onSuccess());
    OVERRIDE(void onFailed());
};

MUSE_NS_END

#endif
