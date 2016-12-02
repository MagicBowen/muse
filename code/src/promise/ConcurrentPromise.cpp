#include <muse/promise/ConcurrentPromise.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

ConcurrentPromise::ConcurrentPromise(std::initializer_list<Promise*> promises)
{
    foreach(promises, [this](auto p){ addPromise(*p); });
}

bool ConcurrentPromise::isFailed() const
{
    return anyof(promises, [](auto p){ return p->evaluate().isFailed(); });
}

bool ConcurrentPromise::isSuccess() const
{
    return allof(promises, [](auto p){ return p->evaluate().isSuccess(); });
}

MUSE_NS_END
