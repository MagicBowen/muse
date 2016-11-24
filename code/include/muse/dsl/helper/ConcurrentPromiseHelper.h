#ifndef H15739F41_ECEF_4EF7_AED5_C11E5A1304D6
#define H15739F41_ECEF_4EF7_AED5_C11E5A1304D6

#include <muse/promise/ConcurrentPromise.h>

MUSE_NS_BEGIN

template<typename ...PROMISES> struct ConcurrentPromiseHelper;

template<typename PROMISE, typename ...OTHERS>
struct ConcurrentPromiseHelper<PROMISE, OTHERS...> : ConcurrentPromiseHelper<OTHERS...>
{
    ConcurrentPromiseHelper(const PROMISE& p, const OTHERS&... others)
    : ConcurrentPromiseHelper<OTHERS...>(others...), promise(p)
    {
        this->addPromise(promise);
    }

    ConcurrentPromiseHelper(const ConcurrentPromiseHelper& rhs)
    : ConcurrentPromiseHelper<OTHERS...>(rhs), promise(rhs.promise)
    {
        this->addPromise(promise);
    }

private:
    PROMISE promise;
};

template<>
struct ConcurrentPromiseHelper<> : ConcurrentPromise
{
    ConcurrentPromiseHelper()
    {
        this->clear();
    }

    ConcurrentPromiseHelper(const ConcurrentPromiseHelper&)
    {
        this->clear();
    }
};

template<typename ...PROMISES>
ConcurrentPromiseHelper<PROMISES...> createConcurrentPromise(const PROMISES&... promises)
{
    return ConcurrentPromiseHelper<PROMISES...>(promises...);
}

MUSE_NS_END

#define __con(...)  createConcurrentPromise(__VA_ARGS__)

#endif

