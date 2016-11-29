#ifndef HAAFF9149_5D61_4210_BF3A_BC8A369B3E46
#define HAAFF9149_5D61_4210_BF3A_BC8A369B3E46

#include <muse/muse.h>
#include <sstream>

MUSE_NS_BEGIN

template<typename T>
struct EqualTo
{
    EqualTo(const T& bound)
    : bound(bound)
    {
    }

    bool operator()(const T& value) const
    {
        return value == bound;
    }

    std::string info() const
    {
        std::stringstream ss;

        ss << "equal to " << bound;
        return ss.str();
    }

private:
    T bound;
};

MUSE_NS_END

#endif
