#include <muse/fact/BaseFact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>
#include <sstream>

MUSE_NS_BEGIN

void BaseFact::confirm(const Event& event)
{
    DBG_LOG("%s confirm event: %s", name(), event.info().c_str());

    occurred = doComfirm(event);
}

bool BaseFact::isOccurred() const
{
    return occurred;
}

std::string BaseFact::info() const
{
    static const char* S_OCCURRED[] = {"not occurred", "occurred"};

    std::stringstream ss;
    ss << name() << " is " << S_OCCURRED[occurred] << ".\n";
    ss << "------------------------------------------------------\n";
    ss << (detail().empty() ? "No details......" : detail()) << "\n";
    ss << "------------------------------------------------------";

    return ss.str();
}

MUSE_NS_END
