#ifndef H6FC48B50_F70E_4036_8EFA_2E9A7709B949
#define H6FC48B50_F70E_4036_8EFA_2E9A7709B949

#include <muse/fact/ClosureFact.h>

MUSE_NS_BEGIN

template<typename FACT>
struct ClosureFactHelper : ClosureFact
{
    ClosureFactHelper(const FACT& f)
    : ClosureFact(fact), fact(f)
    {
    }

    ClosureFactHelper(const ClosureFactHelper& rhs)
    : ClosureFact(fact), fact(rhs.fact)
    {
    }

private:
    FACT fact;
};

MUSE_NS_END

#define __closure(...)  ::MUSE_NS::ClosureFactHelper<decltype(__VA_ARGS__)>(__VA_ARGS__)

#endif
