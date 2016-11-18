#include <muse/base/log.h>
#include <stdarg.h>
#include <cstring>
#include <cstdio>

MUSE_NS_BEGIN

///////////////////////////////////////////////////////////////////////////
#define DEBUG_LEVEL     (unsigned char)0x01
#define INFO_LEVEL      (unsigned char)0x02
#define WARN_LEVEL      (unsigned char)0x04
#define ERROR_LEVEL     (unsigned char)0x08
#define FATAL_LEVEL     (unsigned char)0x10

unsigned int Infra_Printf
    ( unsigned short   /* module */
    , unsigned int   /* errId */
    , unsigned char     level
    , const void * format
    , ...);

namespace
{
    const char* getBaseName(const char* absPath)
    {
        if (absPath == 0) return "";

        const char* p = absPath + ::strlen(absPath);
        while ((p != absPath) && (*(p - 1) != '/'))
        {
            p--;
        }

        return p;
    }

    void logTrace( const char* file, unsigned int line, unsigned char prnLevel, const char* fmt, va_list paramList)
    {
        const  int   BUFF_SIZE = 350;

        char errInfo[BUFF_SIZE];

        if (fmt != nullptr)
        {
            vsnprintf(errInfo, BUFF_SIZE, fmt, paramList);
        }

        Infra_Printf( 0, 0, prnLevel, "%s:%lu: %s ", getBaseName(file), line, errInfo);
    }
}

#define DEF_LOG_TRACE(name, level)                                          \
void log_##name(const char* file, unsigned int line, const char* fmt, ...)           \
{                                                                           \
    va_list valist;                                                         \
    va_start(valist, fmt);                                                  \
    logTrace(file, line, level, fmt, valist);                               \
    va_end(valist);                                                         \
}

DEF_LOG_TRACE(fatal, FATAL_LEVEL);
DEF_LOG_TRACE(error, ERROR_LEVEL);
DEF_LOG_TRACE(warn,  WARN_LEVEL);
DEF_LOG_TRACE(info,  INFO_LEVEL);
DEF_LOG_TRACE(debug, DEBUG_LEVEL);

MUSE_NS_END
