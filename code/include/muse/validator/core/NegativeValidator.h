#ifndef H618021C8_54AB_4046_93C8_62E7E0E77EA2
#define H618021C8_54AB_4046_93C8_62E7E0E77EA2

#include <muse/validator/core/Validator.h>

MUSE_NS_BEGIN

struct NegativeValidator : Validator
{
    NegativeValidator(Validator&);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    Validator& validator;
};

MUSE_NS_END

#endif
