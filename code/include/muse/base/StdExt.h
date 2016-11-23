#ifndef H041687BA_997B_4EBE_BCB6_E988FFA87906
#define H041687BA_997B_4EBE_BCB6_E988FFA87906

#include <muse/muse.h>
#include <algorithm>

MUSE_NS_BEGIN

template<typename Container, typename Func>
void foreach(Container& container, Func func)
{
    std::for_each(std::begin(container), std::end(container), func);
}

template<typename Container, typename Pred>
bool allof(Container& container, Pred pred)
{
    return std::all_of(std::begin(container), std::end(container), pred);
}

template<typename Container, typename Pred>
bool anyof(Container& container, Pred pred)
{
    return std::any_of(std::begin(container), std::end(container), pred);
}

MUSE_NS_END

#endif
