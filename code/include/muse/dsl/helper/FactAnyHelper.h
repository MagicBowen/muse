#ifndef H7216BB7D_7A31_4182_91EE_15BBE703B02C
#define H7216BB7D_7A31_4182_91EE_15BBE703B02C

#include <muse/fact/FactAny.h>
#include <muse/dsl/helper/CompositeFactHelper.h>

MUSE_NS_BEGIN

template<typename ...FACTS>
using FactAnyHelper = CompositeFactHelper<FactAny, FACTS...>;

template<typename ...FACTS>
auto make_fact_any(FACTS&&... facts)
{
    return FactAnyHelper<std::decay_t<FACTS>...>(std::forward<FACTS>(facts)...);
}

MUSE_NS_END

#define __any(...)    ::MUSE_NS::make_fact_any(__VA_ARGS__)

#endif

