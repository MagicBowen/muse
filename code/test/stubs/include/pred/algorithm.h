#ifndef H14B5085A_C339_4CB1_8B60_5EC7802F235F
#define H14B5085A_C339_4CB1_8B60_5EC7802F235F

#include <muse/muse.h>
#include <vector>
#include <numeric>
#include <cmath>
#include <utility>

MUSE_NS_BEGIN

template<typename T>
double calcAverage(const std::vector<T>& values)
{
    auto sum = std::accumulate(std::begin(values), std::end(values), 0.0);
    return sum / values.size();
}

template<typename T>
double calcVarianceBy(const std::vector<T>& values, double average)
{
    double accum  = 0.0;

    for(auto v : values)
    {
        accum  += (v - average)*(v - average);
    }

    return sqrt(accum/(values.size()-1));
}

template<typename T>
std::pair<double, double> calcAverageAndVariance(const std::vector<T>& values)
{
    auto average = calcAverage(values);
    auto variance = calcVarianceBy(values, average);
    return std::pair(average, variance);
}

MUSE_NS_END

#endif
