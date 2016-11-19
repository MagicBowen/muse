#include <muse/validator/NotExistValidator.h>

MUSE_NS_BEGIN

NotExistValidator::NotExistValidator(Fact& fact)
: NegativeValidator(validator)
, validator(fact)
{
}

MUSE_NS_END
