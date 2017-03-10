#include <fakefact/include/fact/Stop.h>
#include <fakefact/include/event/FakeEvent.h>

MUSE_NS_BEGIN

bool Stop::handleEvent(const FakeEvent& event)
{
    if(event.type != SPEED) return false;

    return (event.value == 0);
}


MUSE_NS_END
