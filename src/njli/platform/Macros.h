//
//  Macros.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/31/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#if __GNUC__ >= 3
#define DEPRECATED __attribute__((deprecated))
#define SIMPLE_FUNCTION __attribute__((pure))
#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))
#define PRINTF(formatpos, argpos) __attribute__((format(printf, formatpos, argpos)))
#else
#define DEPRECATED
#define SIMPLE_FUNCTION
#define UNUSED
#define PACKED
#define PRINTF(formatpos, argpos)
#endif