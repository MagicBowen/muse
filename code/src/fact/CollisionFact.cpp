#include <muse/fact/CollisionFact.h>
#include <muse/event/Event.h>

MUSE_NS_BEGIN

bool CollisionFact::doSatisfyWith(const Event& event)
{
    return (event.type == COLLISION);
}

MUSE_NS_END
