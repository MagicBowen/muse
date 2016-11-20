#include <muse/fact/DistanceLessFact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

DistanceLessFact::DistanceLessFact(double range)
:range(range)
{
}

bool DistanceLessFact::doComfirm(const Event& event)
{
    DBG_LOG("DistanceLessFact confirms event(type = %d, value = %f)", event.type, event.value);

    if(event.type != DISTANCE) return false;

    return (event.value < range);
}

MUSE_NS_END
