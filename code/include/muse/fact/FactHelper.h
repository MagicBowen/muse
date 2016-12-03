#ifndef H52FD45C9_AA40_4333_8FA5_9E0912230018
#define H52FD45C9_AA40_4333_8FA5_9E0912230018

#include <muse/fact/BaseFact.h>
#include <muse/pred/Preds.h>

//////////////////////////////////////////////////////
#define BASE_FACT(FACT)  FACT##Base

//////////////////////////////////////////////////////
#define NAME_FUNC(FACT)                             \
    OVERRIDE(const char* name() const)              \
    {                                               \
        return #FACT;                               \
    }                                               \

//////////////////////////////////////////////////////
#define DEF_FACT_BASE_OF(FACT, BASE)                \
struct BASE_FACT(FACT) : BASE                       \
{                                                   \
    using BASE::BASE;                               \
protected:                                          \
    using PredArgType = void;                       \
private:                                            \
    NAME_FUNC(FACT)                                 \
};                                                  \
struct FACT : BASE_FACT(FACT)

//////////////////////////////////////////////////////
#define DEF_PRED_FACT_BASE_OF(FACT, BASE, PRED_T)   \
struct BASE_FACT(FACT) : BASE                       \
                       , Preds<PRED_T>              \
{                                                   \
    using BASE::BASE;                               \
protected:                                          \
    using PredArgType = PRED_T;                     \
private:                                            \
    NAME_FUNC(FACT)                                 \
};                                                  \
struct FACT : BASE_FACT(FACT)

#endif
