#include <fakefact/include/fact/Distance.h>
#include <fakefact/include/event/FakeEvent.h>
#include <sstream>

MUSE_NS_BEGIN

bool Distance::handleEvent(const FakeEvent& event)
{
    if(event.type != DISTANCE) return false;

    return pred(event.value);
}

std::string Distance::detail() const
{
    std::stringstream ss;

    ss << "Distance fact, " << predInfo();
    return ss.str();
}

MUSE_NS_END
