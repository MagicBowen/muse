#ifndef H1D79944E_10E9_4295_BCFC_4514E86F1B8E
#define H1D79944E_10E9_4295_BCFC_4514E86F1B8E

#include <muse/fact/FactAll.h>

MUSE_NS_BEGIN

template<typename ...FACTS> struct FactAllHelper;

template<typename FACT, typename ...OTHERS>
struct FactAllHelper<FACT, OTHERS...> : FactAllHelper<OTHERS...>
{
    FactAllHelper(const FACT& f, const OTHERS&... others)
    : FactAllHelper<OTHERS...>(others...), fact(f)
    {
        this->addFact(fact);
    }

    FactAllHelper(const FactAllHelper& rhs)
    : FactAllHelper<OTHERS...>(rhs), fact(rhs.fact)
    {
        this->addFact(fact);
    }

private:
    FACT fact;
};

template<>
struct FactAllHelper<> : FactAll
{
    FactAllHelper()
    {
        this->clear();
    }

    FactAllHelper(const FactAllHelper&)
    {
        this->clear();
    }
};

template<typename ...FACTS>
FactAllHelper<FACTS...> createFactAll(const FACTS&... facts)
{
    return FactAllHelper<FACTS...>(facts...);
}

MUSE_NS_END

#define __all(...)  createFactAll(__VA_ARGS__)

#endif

