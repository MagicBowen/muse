#ifndef H1D79944E_10E9_4295_BCFC_4514E86F1B8E
#define H1D79944E_10E9_4295_BCFC_4514E86F1B8E

#include <muse/fact/FactAll.h>
#include <muse/dsl/helper/CompositeFactHelper.h>

MUSE_NS_BEGIN

template<typename ...FACTS>
using FactAllHelper = CompositeFactHelper<FactAll, FACTS...>;

template<typename ...FACTS>
auto make_fact_all(FACTS&&... facts)
{
    return FactAllHelper<std::decay_t<FACTS>...>(std::forward<FACTS>(facts)...);
}

MUSE_NS_END

#define __all(...)    ::MUSE_NS::make_fact_all(__VA_ARGS__)

#endif

