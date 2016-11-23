#include <stubs/include/fact/Stop.h>
#include <stubs/include/event/FakeEvent.h>

MUSE_NS_BEGIN

bool Stop::handleEvent(const FakeEvent& event)
{
    if(event.type != SPEED) return false;

    return (event.value == 0);
}


MUSE_NS_END
