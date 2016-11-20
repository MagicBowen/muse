#ifndef HF6D07F91_ACE5_45D9_9390_80A7DEB5301E
#define HF6D07F91_ACE5_45D9_9390_80A7DEB5301E

#include <muse/promise/ExistPromise.h>
#include <muse/promise/NegativePromise.h>

MUSE_NS_BEGIN

struct NotExistPromise : NegativePromise
{
    NotExistPromise(Fact& fact);

private:
    ExistPromise promise;
};

MUSE_NS_END

#endif
