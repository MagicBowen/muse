#ifndef H15739F41_ECEF_4EF7_AED5_C11E5A1304D6
#define H15739F41_ECEF_4EF7_AED5_C11E5A1304D6

#include <muse/promise/ConcurrentPromise.h>
#include <muse/dsl/helper/CompositePromiseHelper.h>

MUSE_NS_BEGIN

template<typename ...PROMISES>
using ConcurrentPromiseHelper = CompositePromiseHelper<ConcurrentPromise, PROMISES...>;

template<typename ...PROMISES>
auto make_concurrent_promise(PROMISES&&... promises)
{
    return ConcurrentPromiseHelper<std::decay_t<PROMISES>...>(std::forward<PROMISES>(promises)...);
}

MUSE_NS_END

#define __con(...)  ::MUSE_NS::make_concurrent_promise(__VA_ARGS__)

#endif

