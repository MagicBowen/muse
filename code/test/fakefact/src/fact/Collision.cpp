#include <fakefact/include/fact/Collision.h>
#include <fakefact/include/event/FakeEvent.h>

MUSE_NS_BEGIN

bool Collision::handleEvent(const FakeEvent& event)
{
    return (event.type == COLLISION);
}

MUSE_NS_END
