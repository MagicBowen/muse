#include <muse/promise/ParallelPromise.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

void ParallelPromise::start()
{
    foreach(promises, [](auto p){p->start();});
}

void ParallelPromise::stop()
{
    if(result.isFixed()) return;

    foreach(promises, [](auto p){ p-> stop(); });

    updateResult();
}

void ParallelPromise::handle(const Event& event)
{
    if(result.isFixed()) return;

    foreach(promises, [&event](auto p){ p->handle(event); });

    updateResult();
}

void ParallelPromise::updateResult()
{
    if(isFailed())
    {
        result = Result::FAILED;
    }
    else if(isSuccess())
    {
        result = Result::SUCCESS;
    }
    else
    {
        result = Result::UNKNOWN;
    }
}

Result ParallelPromise::evaluate() const
{
    return result;
}

MUSE_NS_END
