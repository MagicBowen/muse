#include <muse/promise/ConcurrentPromise.h>
#include <muse/base/Algorithm.h>

MUSE_NS_BEGIN

ConcurrentPromise::ConcurrentPromise(std::initializer_list<Promise*> promises)
{
    foreach(promises, [this](Promise* promise){ addPromise(*promise); });
}

bool ConcurrentPromise::isFailed() const
{
    return anyof(promises, [](Promise* p){ return p->evaluate().isFailed(); });
}

bool ConcurrentPromise::isSuccess() const
{
    return allof(promises, [](Promise* p){ return p->evaluate().isSuccess(); });
}

MUSE_NS_END
