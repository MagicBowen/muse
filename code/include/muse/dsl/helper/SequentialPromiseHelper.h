#ifndef HFB8BFAE7_6E9E_46ED_81BA_F16B8CADE558
#define HFB8BFAE7_6E9E_46ED_81BA_F16B8CADE558

#include <muse/promise/SequentialPromise.h>
#include <muse/dsl/helper/CompositePromiseHelper.h>

MUSE_NS_BEGIN

template<typename ...PROMISES>
using SequentialPromiseHelper = CompositePromiseHelper<SequentialPromise, PROMISES...>;

template<typename ...PROMISES>
auto make_sequential_promise(PROMISES&&... promises)
{
    return SequentialPromiseHelper<std::decay_t<PROMISES>...>(std::forward<PROMISES>(promises)...);
}

MUSE_NS_END

#define __seq(...)    ::MUSE_NS::make_sequential_promise(__VA_ARGS__)

#endif

