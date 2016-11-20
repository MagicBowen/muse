#include <muse/promise/ExistPromise.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

ExistPromise::ExistPromise(Fact& fact)
: FactPromise(fact)
{
}

Result ExistPromise::evaluate() const
{
    return result;
}

void ExistPromise::onSuccess()
{
    INFO_LOG("[PROMISE PASS]: expect fact occurred, and occurred actually!");
}

void ExistPromise::onFailed()
{
    ERR_LOG("[PROMISE FAIL]: expect fact occurred, but not occurred actually!");
}

MUSE_NS_END
