#include <muse/fact/StopFact.h>
#include <muse/event/Event.h>

MUSE_NS_BEGIN

bool StopFact::occurred(const Event& event)
{
    if(event.type != SPEED) return false;

    return (event.value == 0);
}


MUSE_NS_END
