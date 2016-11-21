#include <stubs/include/fact/CollisionFact.h>
#include <stubs/include/event/FakeEvent.h>

MUSE_NS_BEGIN

bool CollisionFact::handleEvent(const FakeEvent& event)
{
    return (event.type == COLLISION);
}

MUSE_NS_END
