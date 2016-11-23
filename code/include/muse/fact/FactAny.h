#ifndef H15201CC8_BDD1_4F2A_AFD0_16E6D1772731
#define H15201CC8_BDD1_4F2A_AFD0_16E6D1772731

#include <muse/fact/FactHelper.h>
#include <muse/fact/CompositeFact.h>
#include <initializer_list>

MUSE_NS_BEGIN

DEF_FACT_BASE_OF(FactAny, CompositeFact)
{
    FactAny() { }

    explicit FactAny(std::initializer_list<Fact*>);

private:
    OVERRIDE(bool doComfirm(const Event&));
};

MUSE_NS_END

#endif
