#include <stubs/include/event/FakeEvent.h>
#include <sstream>
#include <string>

MUSE_NS_BEGIN

namespace
{
    const char* EventNames[] = {"NOTHING", "COLLISION", "DISTANCE", "SPEED"};
}

std::string FakeEvent::info() const
{
    std::stringstream ss;

    ss << "FakeEvent(type = " << EventNames[type] << ", value = " << value <<")";
    return ss.str();
}

MUSE_NS_END
