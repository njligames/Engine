//
//  Log.c
//  JLIGameEngineTest
//
//  Created by James Folk on 1/31/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "Log.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "Game.h"

#include "World.h"
#include "WorldSocket.h"
#include <stdio.h>

njli::NJLIGameEngine::PlatformID njli::NJLIGameEngine::platformID()
{
    return njli::NJLIGameEngine::PlatformID_tvOS;
}

//fwrite(("(" priority ") %s: "), sizeof(char), (strlen("(" priority ") %s: ")), stdout)
#include <string>

#define LOG_VPRINTF(priority)	printf("(" priority ") %s: ", tag); \
va_list args; \
va_start(args, fmt); \
vprintf(fmt, args); \
va_end(args);

void _debug_log_v(const char *tag, const char *fmt, ...)
{
    LOG_VPRINTF("VERBOSE");
}

void _debug_log_d(const char *tag, const char *fmt, ...)
{
    LOG_VPRINTF("DEBUG");
}

void _debug_log_w(const char *tag, const char *fmt, ...)
{
    LOG_VPRINTF("WARN");
}

void _debug_log_e(const char *tag, const char *fmt, ...)
{
    LOG_VPRINTF("ERROR");
}

void LUA_WRITE(const char * c)
{
#if defined(DEBUG) || defined (_DEBUG)
    fwrite(c, sizeof(char), strlen(c), stdout);
    if(njli::World::hasInstance())
        njli::World::getInstance()->getWorldSocket()->sendMessage(c);
#endif
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
    int microsecs;
    
    struct timeval tv;
    
    microsecs = _ms * 1000;
    
    tv.tv_sec  = microsecs / 1000000;
    tv.tv_usec = microsecs % 1000000;
    
    select( 0, NULL, NULL, NULL, &tv );
}

