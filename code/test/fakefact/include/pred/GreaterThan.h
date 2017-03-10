#ifndef HF0287F48_EE5C_4F82_8D2A_80ABC7A6C0DA
#define HF0287F48_EE5C_4F82_8D2A_80ABC7A6C0DA

#include <muse/muse.h>
#include <sstream>

MUSE_NS_BEGIN

template<typename T>
struct GreaterThan
{
    GreaterThan(const T& bound)
    : bound(bound)
    {
    }

    bool operator()(const T& value) const
    {
        return value > bound;
    }

    std::string info() const
    {
        std::stringstream ss;

        ss << "greater than " << bound;
        return ss.str();
    }

private:
    T bound;
};


MUSE_NS_END

#endif
