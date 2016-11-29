#ifndef H3E6519C9_1F4B_41B9_A2DB_E39DAB8FF770
#define H3E6519C9_1F4B_41B9_A2DB_E39DAB8FF770

#include <muse/muse.h>
#include <sstream>

MUSE_NS_BEGIN

template<typename T>
struct LessThan
{
    LessThan(const T& bound)
    : bound(bound)
    {
    }

    bool operator()(const T& value) const
    {
        return value < bound;
    }

    std::string info() const
    {
        std::stringstream ss;

        ss << "less than " << bound;
        return ss.str();
    }

private:
    T bound;
};

MUSE_NS_END

#endif
