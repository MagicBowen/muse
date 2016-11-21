#ifndef H73194152_F36D_43B4_9853_42D3637B494A
#define H73194152_F36D_43B4_9853_42D3637B494A

#include <muse/fact/FactHelper.h>
#include <initializer_list>
#include <vector>

MUSE_NS_BEGIN

DEF_FACT(AllOfFact)
{
    explicit AllOfFact(std::initializer_list<Fact*>);

private:
    OVERRIDE(bool doComfirm(const Event&));

private:
    std::vector<Fact*> facts;
};

MUSE_NS_END

#endif
