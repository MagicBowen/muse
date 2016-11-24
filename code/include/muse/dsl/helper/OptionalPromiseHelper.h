#ifndef HAE0F4466_B0F7_4E56_8BB1_7E355BB97FB4
#define HAE0F4466_B0F7_4E56_8BB1_7E355BB97FB4

#include <muse/promise/OptionalPromise.h>

MUSE_NS_BEGIN

template<typename ...PROMISES> struct OptionalPromiseHelper;

template<typename PROMISE, typename ...OTHERS>
struct OptionalPromiseHelper<PROMISE, OTHERS...> : OptionalPromiseHelper<OTHERS...>
{
    OptionalPromiseHelper(const PROMISE& p, const OTHERS&... others)
    : OptionalPromiseHelper<OTHERS...>(others...), promise(p)
    {
        this->addPromise(promise);
    }

    OptionalPromiseHelper(const OptionalPromiseHelper& rhs)
    : OptionalPromiseHelper<OTHERS...>(rhs), promise(rhs.promise)
    {
        this->addPromise(promise);
    }

private:
    PROMISE promise;
};

template<>
struct OptionalPromiseHelper<> : OptionalPromise
{
    OptionalPromiseHelper()
    {
        this->clear();
    }

    OptionalPromiseHelper(const OptionalPromiseHelper&)
    {
        this->clear();
    }
};

template<typename ...PROMISES>
OptionalPromiseHelper<PROMISES...> createOptionalPromise(const PROMISES&... promises)
{
    return OptionalPromiseHelper<PROMISES...>(promises...);
}

MUSE_NS_END

#define __opt(...)  createOptionalPromise(__VA_ARGS__)

#endif
