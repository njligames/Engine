#include "Log.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

int platformID()
{
    return 2;
}

#define LOG_VPRINTF(priority)	printf("(" priority ") %s: ", tag); \
								va_list arg_ptr; \
								va_start(arg_ptr, fmt); \
								vprintf(fmt, arg_ptr); \
								va_end(arg_ptr);

void _debug_log_v(const char *tag, const char *fmt, ...) {
	LOG_VPRINTF("VERBOSE");
}

void _debug_log_d(const char *tag, const char *fmt, ...) {
	LOG_VPRINTF("DEBUG");
}

void _debug_log_w(const char *tag, const char *fmt, ...) {
	LOG_VPRINTF("WARN");
}

void _debug_log_e(const char *tag, const char *fmt, ...) {
	LOG_VPRINTF("ERROR");
}
void LUA_WRITE(const char * c)
{
	fwrite(c, sizeof(char), strlen(c), stdout);
}

void _debug_log_assert(const char *cond, const char *tag, const char *fmt, ...)
{
    va_list args;
    
    printf("(%s) ASSERT(%s)", tag, cond);
    
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void _debug_log_stderr(const char* tag, const char* fmt, ...)
{
    va_list args;
    
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void njliSleep( unsigned int _ms )
{
    // int microsecs;
    
    // struct timeval tv;
    
    // microsecs = _ms * 1000;
    
    // tv.tv_sec  = microsecs / 1000000;
    // tv.tv_usec = microsecs % 1000000;
    
    // select( 0, NULL, NULL, NULL, &tv );
}

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
