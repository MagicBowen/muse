#ifndef HCA5EEF79_FF00_44F1_B6F7_F66EEF48D506
#define HCA5EEF79_FF00_44F1_B6F7_F66EEF48D506

#include <muse/muse.h>
#include <sstream>

MUSE_NS_BEGIN

template<typename T, typename R = double>
struct Average
{
    R operator()(const T& value) const
    {
        average = (average * n + value) / (n + 1);
        n++;
        return average;
    }

    std::string info() const
    {
        std::stringstream ss;

        ss << "average(" << average << ")";
        return ss.str();
    }

private:
    mutable R average{0};
    mutable unsigned int n{0};
};

MUSE_NS_END

#endif
