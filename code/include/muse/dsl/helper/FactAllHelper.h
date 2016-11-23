#ifndef H1D79944E_10E9_4295_BCFC_4514E86F1B8E
#define H1D79944E_10E9_4295_BCFC_4514E86F1B8E

#include <muse/fact/FactAll.h>

MUSE_NS_BEGIN

template<typename ...FACTS> struct FactAllHelper;

template<typename FACT, typename ...OTHERS>
struct FactAllHelper<FACT, OTHERS...> : FactAllHelper<OTHERS...>
{
    FactAllHelper(const FACT& f, OTHERS... others)
    : FactAllHelper<OTHERS...>(others...), fact(f)
    {
        this->addFact(fact);
    }

private:
    FACT fact;
};

template<>
struct FactAllHelper<> : FactAll
{
};

template<typename ...FACTS>
FactAllHelper<FACTS...> createFactAll(FACTS ... facts)
{
    return FactAllHelper<FACTS...>(facts...);
}

MUSE_NS_END

#define __all(...)  createFactAll(__VA_ARGS__)

#endif

