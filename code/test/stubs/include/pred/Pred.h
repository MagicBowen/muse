#ifndef H8AFAEEA4_1A5C_491E_8343_9ED4B68948B1
#define H8AFAEEA4_1A5C_491E_8343_9ED4B68948B1

#include <muse/muse.h>
#include <functional>

MUSE_NS_BEGIN

template<typename T>
using Pred = std::function<bool (T)>;

MUSE_NS_END

#endif
