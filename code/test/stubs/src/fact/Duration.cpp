#include <stubs/include/fact/Duration.h>
#include <sstream>

MUSE_NS_BEGIN

bool Duration::handleEvent(const FakeEvent& event)
{
    return pred(++currentSeconds);
}

std::string Duration::detail() const
{
    std::stringstream ss;

    ss << "Duration " << currentSeconds << " s, " << predInfo();
    return ss.str();
}

MUSE_NS_END
