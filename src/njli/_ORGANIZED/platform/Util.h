//
//  Util.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/9/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_Util_h
#define JLIGameEngineTest_Util_h

//#include "Game.h"
#include "Log.h"
//#include <csignal>
//#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
//#include <string>
#include <math.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#define PI 3.14159265358979323846264338327f

//#if defined(DEBUG) || defined(_DEBUG)
//#define JLI_DEBUG
//#endif

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define BUFFER_SIZE 512

inline char IsOn(const s32 value, const s32 bit)
{
    int v = value & bit;
    char ret = (v == 0) ? 0 : 1;
    return ret;
}

inline u32 On(const s32 value, const s32 bit)//, bool on = true)
{
    return value | bit;
}

inline u32 Off(const s32 value, const s32 bit)
{
    if (IsOn(value, bit)) {
        return value ^ bit;
    }
    return value;
}

inline f32 clampf(const f32 value, const f32 min, const f32 max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

inline s32 clamp(const s32 value, const s32 min, const s32 max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

inline f32 clampColor(const f32 color)
{
    return clampf(color, 0.0f, 1.0f);
}

inline s32 isPowerOfTwo(s32 v)
{
    return v && !(v & (v - 1));
}

inline s32 fixPowerOfTwo(s32 v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    
    return v;
}

typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv;

inline hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;
    
    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;
    
    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;
    
    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
        if( in.g >= max )
            out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan
    
    out.h *= 60.0;                              // degrees
    
    if( out.h < 0.0 )
        out.h += 360.0;
    
    return out;
}


inline rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;
    
    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));
    
    switch(i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;
            
        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
    }
    return out;     
}



#endif
