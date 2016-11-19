#ifndef H15201CC8_BDD1_4F2A_AFD0_16E6D1772731
#define H15201CC8_BDD1_4F2A_AFD0_16E6D1772731

#include <muse/fact/core/BaseFact.h>
#include <initializer_list>
#include <vector>

MUSE_NS_BEGIN

struct OrFact : BaseFact
{
    OrFact(std::initializer_list<BaseFact*>);

private:
    OVERRIDE(bool doComfirm(const Event&));

private:
    std::vector<BaseFact*> facts;
};

MUSE_NS_END

#endif
