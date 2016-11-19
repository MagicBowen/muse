#ifndef H73194152_F36D_43B4_9853_42D3637B494A
#define H73194152_F36D_43B4_9853_42D3637B494A

#include <muse/fact/core/BaseFact.h>
#include <initializer_list>
#include <vector>

MUSE_NS_BEGIN

struct AndFact : BaseFact
{
    AndFact(std::initializer_list<BaseFact*>);

private:
    OVERRIDE(bool doComfirm(const Event&));

private:
    std::vector<BaseFact*> facts;
};

MUSE_NS_END

#endif
