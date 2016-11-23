#include <muse/fact/FactOr.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

FactOr::FactOr(std::initializer_list<Fact*> facts)
{
    foreach(facts, [this](Fact* f){ this->addFact(*f); });
}

bool FactOr::doComfirm(const Event& event)
{
    return anyof(facts, [&event](Fact* f){return f->confirm(event);});
}

MUSE_NS_END
