#ifndef H73194152_F36D_43B4_9853_42D3637B494A
#define H73194152_F36D_43B4_9853_42D3637B494A

#include <muse/fact/FactHelper.h>
#include <muse/fact/CompositeFact.h>
#include <initializer_list>

MUSE_NS_BEGIN

DEF_FACT_BASE_OF(FactAll, CompositeFact)
{
    FactAll() { }

    explicit FactAll(std::initializer_list<Fact*>);

private:
    OVERRIDE(bool doComfirm(const Event&));
};

MUSE_NS_END

#endif
