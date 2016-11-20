#include <muse/fact/CollisionFact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

bool CollisionFact::doComfirm(const Event& event)
{
    DBG_LOG("CollisionFact confirms event(type = %d, value = %f)", event.type, event.value);
    return (event.type == COLLISION);
}

MUSE_NS_END
