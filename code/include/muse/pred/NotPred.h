#ifndef HD8FAA9EC_3298_40B6_80AD_BAEE19CF3DCF
#define HD8FAA9EC_3298_40B6_80AD_BAEE19CF3DCF

#include <muse/base/FunctionTraits.h>
#include <sstream>

MUSE_NS_BEGIN

template<typename PRED>
struct NotPred
{
    NotPred(PRED&& pred)
    : pred(pred)
    {
    }

    bool operator()(ARG_TYPE(PRED) value) const
    {
        return !pred(value);
    }

    std::string info() const
    {
        std::stringstream ss;

        ss << "not " << pred.info();
        return ss.str();
    }

private:
    PRED pred;
};

template<typename PRED>
auto make_not_pred(PRED&& pred)
{
    return NotPred<std::decay_t<PRED>>(std::forward<PRED>(pred));
}

MUSE_NS_END

#define __not_pred(...)    ::MUSE_NS::make_not_pred(__VA_ARGS__)

#endif
