#include <muse/promise/ConcurrentPromise.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

bool ConcurrentPromise::isFailed() const
{
    return anyof(promises, [](auto p){ return p->evaluate().isFailed(); });
}

bool ConcurrentPromise::isSuccess() const
{
    return allof(promises, [](auto p){ return p->evaluate().isSuccess(); });
}

MUSE_NS_END
