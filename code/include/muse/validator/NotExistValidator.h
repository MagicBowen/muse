#ifndef HF6D07F91_ACE5_45D9_9390_80A7DEB5301E
#define HF6D07F91_ACE5_45D9_9390_80A7DEB5301E

#include <muse/validator/ExistValidator.h>
#include <muse/validator/core/NegativeValidator.h>

MUSE_NS_BEGIN

struct NotExistValidator : NegativeValidator
{
    NotExistValidator(BaseFact& fact);

private:
    ExistValidator validator;
};

MUSE_NS_END

#endif
