#include <muse/fact/StopFact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

bool StopFact::doComfirm(const Event& event)
{
    DBG_LOG("StopFact confirms event(type = %d, value = %f)", event.type, event.value);

    if(event.type != SPEED) return false;

    return (event.value == 0);
}


MUSE_NS_END
