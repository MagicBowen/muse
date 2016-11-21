#include <muse/promise/OptionalPromise.h>
#include <muse/base/Algorithm.h>
#include <muse/promise/Promise.h>

MUSE_NS_BEGIN

OptionalPromise::OptionalPromise(std::initializer_list<Promise*> promises)
: ParallelPromise(promises)
{
}

bool OptionalPromise::isFailed() const
{
    return allof(promises, [](Promise* p){ return p->evaluate().isFailed(); });
}

bool OptionalPromise::isSuccess() const
{
    return anyof(promises, [](Promise* p){ return p->evaluate().isSuccess(); });
}

MUSE_NS_END
