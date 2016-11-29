#ifndef H50F78FAC_6267_4B32_81BF_4DB0139B7FC8
#define H50F78FAC_6267_4B32_81BF_4DB0139B7FC8

#include <muse/pred/Average.h>
#include <sstream>
#include <cmath>

MUSE_NS_BEGIN

template<typename T, typename R = double>
struct Variance
{
    R operator()(const T& value) const
    {
        auto average = calcAverage(value);
        return calcVariance(value, average);
    }

    std::string info() const
    {
        std::stringstream ss;

        ss << "variance(" << variance << ")";
        return ss.str();
    }

private:
    R calcVariance(const T& value, const R& average) const
    {
        values.push_back(value);
        if(values.size() == 1) return 0;

        R acc{0};
        for(auto v : values)
        {
            acc += (v - average) * (v - average);
        }

        variance = sqrt(acc / (values.size() - 1));
        return variance;
    }

private:
    Average<T, R> calcAverage;
    mutable R variance{0};
    mutable std::vector<T> values;
};

MUSE_NS_END

#endif
