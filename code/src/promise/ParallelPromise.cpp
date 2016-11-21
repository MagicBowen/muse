#include <muse/promise/ParallelPromise.h>
#include <muse/base/Algorithm.h>

MUSE_NS_BEGIN

ParallelPromise::ParallelPromise(std::initializer_list<Promise*> promises)
: promises(promises)
{
}

void ParallelPromise::start()
{
    foreach(promises, [](Promise* p){p->start();});
}

void ParallelPromise::stop()
{
    if(result.isFixed()) return;

    foreach(promises, [](Promise* p){ p-> stop(); });

    updateResult();
}

void ParallelPromise::onEvent(const Event& event)
{
    if(result.isFixed()) return;

    foreach(promises, [&event](Promise* p){ p->onEvent(event); });

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
