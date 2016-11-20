#ifndef H618021C8_54AB_4046_93C8_62E7E0E77EA2
#define H618021C8_54AB_4046_93C8_62E7E0E77EA2

#include <muse/promise/Promise.h>

MUSE_NS_BEGIN

struct NegativePromise : Promise
{
    NegativePromise(Promise&);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    Promise& promise;
};

MUSE_NS_END

#endif
