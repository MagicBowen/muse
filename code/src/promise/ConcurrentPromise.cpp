#include <muse/promise/ConcurrentPromise.h>
#include <muse/base/Algorithm.h>

MUSE_NS_BEGIN

ConcurrentPromise::ConcurrentPromise(std::initializer_list<Promise*> promises)
: promises(promises)
{
}

void ConcurrentPromise::start()
{
    foreach(promises, [](Promise* p){p->start();});
}

void ConcurrentPromise::stop()
{
    if(result.isFixed()) return;

    foreach(promises, [](Promise* p){ p-> stop(); });

    updateResult();
}

void ConcurrentPromise::onEvent(const Event& event)
{
    if(result.isFixed()) return;

    foreach(promises, [&event](Promise* p){ p->onEvent(event); });

    updateResult();
}

bool ConcurrentPromise::anyFailed() const
{
    return anyof(promises, [](Promise* p){ return p->evaluate().isFailed(); });
}

bool ConcurrentPromise::allSuccess() const
{
    return allof(promises, [](Promise* p){ return p->evaluate().isSuccess(); });
}

void ConcurrentPromise::updateResult()
{
    if(anyFailed())
    {
        result = Result::FAILED;
    }
    else if(allSuccess())
    {
        result = Result::SUCCESS;
    }
    else
    {
        result = Result::UNKNOWN;
    }
}

Result ConcurrentPromise::evaluate() const
{
    return result;
}

MUSE_NS_END
