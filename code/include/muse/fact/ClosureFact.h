#ifndef H0BCCE476_F032_411D_BDA5_AD9E1B5F5A06
#define H0BCCE476_F032_411D_BDA5_AD9E1B5F5A06

#include <muse/fact/Fact.h>

MUSE_NS_BEGIN

struct ClosureFact : Fact
{
    ClosureFact(Fact&);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void confirm(const Event&));
    OVERRIDE(bool isOccurred() const);
    OVERRIDE(std::string info() const);

private:
    Fact& fact;
    bool occurred{false};
};

MUSE_NS_END

#endif
