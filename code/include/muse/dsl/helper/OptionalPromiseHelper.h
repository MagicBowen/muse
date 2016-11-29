#ifndef HAE0F4466_B0F7_4E56_8BB1_7E355BB97FB4
#define HAE0F4466_B0F7_4E56_8BB1_7E355BB97FB4

#include <muse/promise/OptionalPromise.h>
#include <muse/dsl/helper/CompositePromiseHelper.h>

MUSE_NS_BEGIN

template<typename ...PROMISES>
using OptionalPromiseHelper = CompositePromiseHelper<OptionalPromise, PROMISES...>;

template<typename ...PROMISES>
auto make_optional_promise(PROMISES&&... promises)
{
    return OptionalPromiseHelper<std::decay_t<PROMISES>...>(std::forward<PROMISES>(promises)...);
}

MUSE_NS_END

#define __opt(...)    ::MUSE_NS::make_optional_promise(__VA_ARGS__)

#endif
