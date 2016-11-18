#include <muse/fact/WithinDistanceFact.h>
#include <muse/event/Event.h>

MUSE_NS_BEGIN

WithinDistanceFact::WithinDistanceFact(double range)
:range(range)
{
}

bool WithinDistanceFact::occurred(const Event& event)
{
    if(event.type != DISTANCE) return false;

    return (event.value < range);
}

MUSE_NS_END
