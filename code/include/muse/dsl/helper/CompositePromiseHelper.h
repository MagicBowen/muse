#ifndef H80BF7CE0_62C4_4C56_BD4F_635404CB0ECC
#define H80BF7CE0_62C4_4C56_BD4F_635404CB0ECC

#include <muse/muse.h>
#include <tuple>

MUSE_NS_BEGIN

template<typename SUPPER, typename ... PROMISES>
struct CompositePromiseHelper : SUPPER
{
    CompositePromiseHelper(PROMISES&& ... ps)
    : promises(std::forward<PROMISES>(ps) ...)
    {
        apply(std::integral_constant<size_t, 0>{});
    }

    CompositePromiseHelper(const CompositePromiseHelper& rhs)
    : promises(rhs.promises)
    {
        this->clear();
        apply(std::integral_constant<size_t, 0>{});
    }

private:
    template<size_t N>
    void apply(std::integral_constant<size_t, N>)
    {
        this->addPromise(std::get<N>(promises));
        apply(std::integral_constant<size_t, N+1>{});
    }

    static const size_t size = sizeof ... (PROMISES);
    void apply(std::integral_constant<size_t, size - 1>)
    {
        this->addPromise(std::get<size-1>(promises));
    }

private:
    std::tuple<PROMISES ...> promises;
};

MUSE_NS_END

#endif
