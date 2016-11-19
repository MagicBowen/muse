#include <muse/validator/core/Result.h>

MUSE_NS_BEGIN

Result negativeOf(Result result)
{
    if(result == Result::CONTINUE) return Result::CONTINUE;

    return (result == Result::FAILED) ? Result::SUCCESS : Result::FAILED;
}

MUSE_NS_END
