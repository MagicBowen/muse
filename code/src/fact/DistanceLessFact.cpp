#include <muse/fact/DistanceLessFact.h>
#include <muse/event/Event.h>

MUSE_NS_BEGIN

DistanceLessFact::DistanceLessFact(double range)
:range(range)
{
}

bool DistanceLessFact::doComfirm(const Event& event)
{
    if(event.type != DISTANCE) return false;

    return (event.value < range);
}

MUSE_NS_END
