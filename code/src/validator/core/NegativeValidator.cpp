#include <muse/validator/core/NegativeValidator.h>

MUSE_NS_BEGIN

NegativeValidator::NegativeValidator(Validator& validator)
: validator(validator)
{
}

void NegativeValidator::start()
{
    validator.start();
}

void NegativeValidator::stop()
{
    validator.stop();
}

void NegativeValidator::onEvent(const Event& event)
{
    validator.onEvent(event);
}

Result NegativeValidator::evaluate() const
{
    return negativeOf(validator.evaluate());
}

MUSE_NS_END
