#ifndef HF5B4FC2C_40CF_4A1A_AE93_580A3F4770A4
#define HF5B4FC2C_40CF_4A1A_AE93_580A3F4770A4

#include <muse/muse.h>
#include <tuple>

MUSE_NS_BEGIN

template<typename SUPPER, typename ... FACTS>
struct CompositeFactHelper : SUPPER
{
    CompositeFactHelper(FACTS&& ... fs)
    : facts(std::forward<FACTS>(fs) ...)
    {
        apply(std::integral_constant<size_t, 0>{});
    }

    CompositeFactHelper(const CompositeFactHelper& rhs)
    : facts(rhs.facts)
    {
        this->clear();
        apply(std::integral_constant<size_t, 0>{});
    }

private:
    template<size_t N>
    void apply(std::integral_constant<size_t, N>)
    {
        this->addFact(std::get<N>(facts));
        apply(std::integral_constant<size_t, N+1>{});
    }

    static const size_t size = sizeof ... (FACTS);
    void apply(std::integral_constant<size_t, size - 1>)
    {
        this->addFact(std::get<size-1>(facts));
    }

private:
    std::tuple<FACTS ...> facts;
};

MUSE_NS_END

#endif
