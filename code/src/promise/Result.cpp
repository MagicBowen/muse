#include <muse/promise/Result.h>

MUSE_NS_BEGIN

Result::Result(Value value)
: value(value)
{
}

Result Result::negative() const
{
    if(value == UNKNOWN) return Result(UNKNOWN);

    return (value == FAILED) ? Result(SUCCESS) : Result(FAILED);
}

bool Result::isSuccess() const
{
    return value == SUCCESS;
}

bool Result::isFailed() const
{
    return value == FAILED;
}

bool Result::isFixed() const
{
    return value != UNKNOWN;
}

Result::Value Result::getValue() const
{
    return value;
}

MUSE_NS_END
