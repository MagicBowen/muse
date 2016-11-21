#include <muse/promise/NotExistPromise.h>
#include <muse/promise/Result.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

NotExistPromise::NotExistPromise(Fact& fact)
: FactPromise(fact)
{
}

Result NotExistPromise::evaluate() const
{
    return result.negative();
}

void NotExistPromise::onSuccess()
{
    ERR_LOG("[PROMISE FAIL]: expect fact not occurred, but occurred actually!");
}

void NotExistPromise::onFailed()
{
    INFO_LOG("[PROMISE PASS]: expect fact not occurred, and not occurred actually!");
}

MUSE_NS_END
