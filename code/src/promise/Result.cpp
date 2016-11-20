#include <muse/promise/Result.h>

MUSE_NS_BEGIN

Result negativeOf(Result result)
{
    if(result == Result::UNKNOWN) return Result::UNKNOWN;

    return (result == Result::FAILED) ? Result::SUCCESS : Result::FAILED;
}

bool isSuccess(Result result)
{
    return result == Result::SUCCESS;
}

bool isFailed(Result result)
{
    return result == Result::FAILED;
}

bool isFixed(Result result)
{
    return result != Result::UNKNOWN;
}

MUSE_NS_END
