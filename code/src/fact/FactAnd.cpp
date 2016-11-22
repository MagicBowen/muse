#include <muse/fact/FactAnd.h>
#include <muse/base/Algorithm.h>

MUSE_NS_BEGIN

FactAnd::FactAnd(std::initializer_list<Fact*> facts)
{
    foreach(facts, [this](Fact* f){ this->addFact(*f); });
}

bool FactAnd::doComfirm(const Event& event)
{
    return allof(facts, [&event](Fact* f){return f->confirm(event);});
}

MUSE_NS_END
