#include <stubs/include/fact/DistanceLessFact.h>
#include <stubs/include/event/FakeEvent.h>

MUSE_NS_BEGIN

DistanceLessFact::DistanceLessFact(double range)
:range(range)
{
}

bool DistanceLessFact::handleEvent(const FakeEvent& event)
{
    if(event.type != DISTANCE) return false;

    return (event.value < range);
}

MUSE_NS_END
