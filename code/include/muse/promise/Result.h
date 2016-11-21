#ifndef HFF41C447_37AF_4F2E_8CC9_28A2CF6D48D1
#define HFF41C447_37AF_4F2E_8CC9_28A2CF6D48D1

#include <muse/muse.h>

MUSE_NS_BEGIN

struct Result
{
    enum Value{UNKNOWN, SUCCESS, FAILED};

    Result(Value value);
    Result negative() const;
    bool isSuccess() const;
    bool isFailed() const;
    bool isFixed() const;
    Value getValue() const;

private:
    Value value{UNKNOWN};
};

MUSE_NS_END

#endif
