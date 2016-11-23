#ifndef H7216BB7D_7A31_4182_91EE_15BBE703B02C
#define H7216BB7D_7A31_4182_91EE_15BBE703B02C

#include <muse/fact/FactAny.h>

MUSE_NS_BEGIN

template<typename ...FACTS> struct FactAnyHelper;

template<typename FACT, typename ...OTHERS>
struct FactAnyHelper<FACT, OTHERS...> : FactAnyHelper<OTHERS...>
{
    FactAnyHelper(const FACT& f, OTHERS... others)
    : FactAnyHelper<OTHERS...>(others...), fact(f)
    {
        this->addFact(fact);
    }

private:
    FACT fact;
};

template<>
struct FactAnyHelper<> : FactAny
{
};

template<typename ...FACTS>
FactAnyHelper<FACTS...> createFactAny(FACTS ... facts)
{
    return FactAnyHelper<FACTS...>(facts...);
}

MUSE_NS_END

#define __any(...)  createFactAny(__VA_ARGS__)

#endif

