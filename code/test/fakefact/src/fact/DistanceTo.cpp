#include <fakefact/include/fact/DistanceTo.h>
#include <fakefact/include/event/FakeEvent.h>
#include <sstream>

MUSE_NS_BEGIN

DistanceTo::DistanceTo(int id) : id(id)
{
}

bool DistanceTo::handleEvent(const FakeEvent& event)
{
    if(event.type != DISTANCE) return false;

    return pred(event.value);
}

std::string DistanceTo::detail() const
{
    std::stringstream ss;

    ss << "Distance to " << id <<" fact, " << predInfo();
    return ss.str();
}

MUSE_NS_END
