#include <muse/fact/FactAny.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

FactAny::FactAny(std::initializer_list<Fact*> facts)
{
    foreach(facts, [this](Fact* f){ this->addFact(*f); });
}

bool FactAny::doComfirm(const Event& event)
{
    return anyof(facts, [&event](Fact* f){return f->confirm(event);});
}

MUSE_NS_END
