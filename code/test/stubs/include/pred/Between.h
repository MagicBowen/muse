#ifndef H28CA2765_1052_44AA_8D97_D4D08AC190E7
#define H28CA2765_1052_44AA_8D97_D4D08AC190E7

#include <stubs/include/pred/GreaterThan.h>
#include <stubs/include/pred/LessThan.h>

MUSE_NS_BEGIN

template<typename T>
struct Between
{
    Between(const T& leftBound, const T& rightBound)
    : leftBound(leftBound), rightBound(rightBound)
    {
    }

    bool operator()(const T& value) const
    {
        return GreaterThan<T>(leftBound)(value) && LessThan<T>(rightBound)(value);
    }

    std::string info() const
    {
        std::stringstream ss;

        ss << "between(" << leftBound << ", " << rightBound << ")";
        return ss.str();
    }

private:
    T leftBound;
    T rightBound;
};


MUSE_NS_END

#endif
