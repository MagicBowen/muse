#include <muse/validator/NotValidator.h>

MUSE_NS_BEGIN

NotValidator::NotValidator(Validator& validator)
: validator(validator)
{
}

void NotValidator::start()
{
    validator.start();
}

void NotValidator::stop()
{
    validator.stop();
}

void NotValidator::onEvent(const Event& event)
{
    validator.onEvent(event);
}

Result NotValidator::evaluate() const
{
    return negtiveOf(validator.evaluate());
}

MUSE_NS_END
