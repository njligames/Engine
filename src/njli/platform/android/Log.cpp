//http://mobilepearls.com/labs/native-android-api/
#include "Log.h"
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include <vector>

njli::NJLIGameEngine::PlatformID njli::NJLIGameEngine::platformID()
{
    return njli::NJLIGameEngine::PlatformID_Android;
}

#define ANDROID_LOG_VPRINT(priority)                   \
    va_list arg_ptr;                                   \
    va_start(arg_ptr, fmt);                            \
    __android_log_vprint(priority, tag, fmt, arg_ptr); \
    va_end(arg_ptr);

void _debug_log_v(const char* tag, const char* fmt, ...)
{
    ANDROID_LOG_VPRINT(ANDROID_LOG_VERBOSE);
}

void _debug_log_d(const char* tag, const char* fmt, ...)
{
    ANDROID_LOG_VPRINT(ANDROID_LOG_DEBUG);
}

void _debug_log_w(const char* tag, const char* fmt, ...)
{
    ANDROID_LOG_VPRINT(ANDROID_LOG_WARN);
}

void _debug_log_e(const char* tag, const char* fmt, ...)
{
    ANDROID_LOG_VPRINT(ANDROID_LOG_ERROR);
}

void LUA_WRITE(const char* c)
{
    __android_log_write(ANDROID_LOG_VERBOSE, "", c);
}

void _debug_log_assert(const char* cond, const char* tag, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    __android_log_assert(cond, tag, fmt, args);
    va_end(args);
}

void njliSleep(unsigned int _ms)
{
    // int microsecs;

    // struct timeval tv;

    // microsecs = _ms * 1000;

    // tv.tv_sec  = microsecs / 1000000;
    // tv.tv_usec = microsecs % 1000000;

    // select( 0, NULL, NULL, NULL, &tv );
}
///void __android_log_assert(const char *cond, const char *tag, const char *fmt, ...)

const char* string_format(const char* fmt, ...) {
    std::vector<char> str(100,'\0');
    va_list ap;
    while (1) {
        va_start(ap, fmt);
        auto n = vsnprintf(str.data(), str.size(), fmt, ap);
        va_end(ap);
        if ((n > -1) && (size_t(n) < str.size())) {
            return str.data();
        }
        if (n > -1)
            str.resize( n + 1 );
        else
            str.resize( str.size() * 2);
    }
    return str.data();
}
