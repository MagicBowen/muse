#ifndef H52FD45C9_AA40_4333_8FA5_9E0912230018
#define H52FD45C9_AA40_4333_8FA5_9E0912230018

#include <muse/fact/BaseFact.h>

//////////////////////////////////////////////////////
#define BASE_FACT(FACT)  FACT##Base

#define DEF_FACT_BASE_OF(FACT, BASE)        \
struct BASE_FACT(FACT) : BASE               \
{                                           \
private:                                    \
    OVERRIDE(const char* name() const)      \
    {                                       \
        return #FACT;                       \
    }                                       \
};                                          \
struct FACT : BASE_FACT(FACT)

#define DEF_FACT(FACT)    DEF_FACT_BASE_OF(FACT, BaseFact)

#endif
