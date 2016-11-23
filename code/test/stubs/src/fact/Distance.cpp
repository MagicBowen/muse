#include <stubs/include/fact/Distance.h>
#include <stubs/include/event/FakeEvent.h>

MUSE_NS_BEGIN

Distance::Distance(Pred<double> pred)
:pred(pred)
{
}

bool Distance::handleEvent(const FakeEvent& event)
{
    if(event.type != DISTANCE) return false;

    return pred(event.value);
}

MUSE_NS_END
