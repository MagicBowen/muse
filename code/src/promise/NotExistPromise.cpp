#include <muse/promise/NotExistPromise.h>

MUSE_NS_BEGIN

NotExistPromise::NotExistPromise(Fact& fact)
: NegativePromise(promise)
, promise(fact)
{
}

MUSE_NS_END
