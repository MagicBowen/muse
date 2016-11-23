#include <muse/fact/FactAll.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

FactAll::FactAll(std::initializer_list<Fact*> facts)
{
    foreach(facts, [this](Fact* f){ this->addFact(*f); });
}

bool FactAll::doComfirm(const Event& event)
{
    return allof(facts, [&event](Fact* f){return f->confirm(event);});
}

MUSE_NS_END
