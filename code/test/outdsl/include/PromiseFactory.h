#ifndef H293F1C24_CEDB_4418_A9CE_17EF2A80FFCF
#define H293F1C24_CEDB_4418_A9CE_17EF2A80FFCF

#include <muse/muse.h>

MUSE_NS_BEGIN

struct Promise;

struct PromiseFactory
{
    static Promise* create(const char* json);
};

MUSE_NS_END

#endif
