#include <muse/fact/FactAll.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

FactAll::FactAll(std::initializer_list<Fact*> facts)
{
    foreach(facts, [this](Fact* f){ this->addFact(*f); });
}

bool FactAll::doComfirm(const Event& event)
{
    auto result{true};

    for(auto fact : facts)
    {
        result = fact->confirm(event);
    }

    return result;
}

MUSE_NS_END
