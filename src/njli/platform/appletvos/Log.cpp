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

#import <UIKit/UIKit.h>


#include "JsonJLI.h"


#include "btVector2.h"
#include "LinearMath/btVector3.h"
#include "BulletCollision/NarrowPhaseCollision/btManifoldPoint.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btQuaternion.h"
#include "LinearMath/btMatrix3x3.h"
#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"


njli::NJLIGameEngine::PlatformID njli::NJLIGameEngine::platformID()
{
    return njli::NJLIGameEngine::PlatformID_iOS;
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

void _script_error(const char* tag, const char* fmt, ...)
{
    char buffer[2048];
    va_list args;
    
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    njli::World::getInstance()->getWorldLuaVirtualMachine()->error(buffer);
    
}

void _script_crash()
{
    njli::World::getInstance()->getWorldLuaVirtualMachine()->error("");
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
//    va_list args;
//    
//    va_start(args, fmt);
//    vfprintf(stderr, fmt, args);
//    va_end(args);
    
    char buffer[2048];
    va_list args;
    
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    njli::World::getInstance()->getWorldLuaVirtualMachine()->error(buffer);
}

void njliSleep( unsigned int _ms )
{
    int microsecs;
    
    struct timeval tv;
    
    double seconds = _ms / 1000.0f;
    
    microsecs = _ms * 1000;
    
    tv.tv_sec  = microsecs / 1000000;
    tv.tv_usec = microsecs % 1000000;
    
    [NSThread sleepForTimeInterval:seconds];
    
//    select( 0, NULL, NULL, NULL, &tv );
    
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

//const char* createJsonKeyValue(const char* key, const char* value)
//{
//    return string_format("{\"%s\":%s}", key, value);
//    //    return jli::JsonJLI::parse(v);
//}

//const char* btoJsonString(const bool b)
//{
//    return njli::JsonJLI::parse(string_format("\"%s\"", (b)?"true":"false"));
//}
//
//const char* btScalartoJsonString(const btScalar &)
//{
//    return njli::JsonJLI::parse(string_format("\"%f\"", v));
//}
//
//const char* btVector2toJsonString(const btVector2 &v)
//{
//    return njli::JsonJLI::parse(string_format(btVector2_BASE, v.x(), v.y()));
//}
//
//const char* btVector3toJsonString(const btVector3 &v)
//{
//    return njli::JsonJLI::parse(string_format(btVector3_BASE, v.x(), v.y(), v.z()));
//}
//
//const char* btVector4toJsonString(const btVector4 &v)
//{
//    return njli::JsonJLI::parse(string_format(btVector4_BASE, v.x(), v.y(), v.z(), v.w()));
//}
//
//const char* btManifoldPointtoJsonString(const btManifoldPoint &v)
//{
//    std::string pa = toJsonString(v.getPositionWorldOnA());
//    std::string pb = toJsonString(v.getPositionWorldOnB());
//    return njli::JsonJLI::parse(string_format(btManifold_BASE,
//                                              v.getDistance(),
//                                              v.getLifeTime(),
//                                              pa.c_str(),
//                                              pb.c_str(),
//                                              v.getAppliedImpulse()).c_str());
//}
//
//const char* btTransformtoJsonString(const btTransform &v)
//{
//    //    static btScalar m[16];
//    btScalar *m = new btScalar[16];
//    v.getOpenGLMatrix(m);
//    
//    std::string ret = njli::JsonJLI::parse(string_format(btTransform_BASE,
//                                                         m[0],
//                                                         m[1],
//                                                         m[2],
//                                                         m[3],
//                                                         m[4],
//                                                         m[5],
//                                                         m[6],
//                                                         m[7],
//                                                         m[8],
//                                                         m[9],
//                                                         m[10],
//                                                         m[11],
//                                                         m[12],
//                                                         m[13],
//                                                         m[14],
//                                                         m[15]).c_str());
//    delete [] m;
//    return ret;
//}
//
//const char* btQuaterniontoJsonString(const btQuaternion &v)
//{
//    const char* axis = toJsonString(v.getAxis());
//    return njli::JsonJLI::parse(string_format(btQuaternion_BASE,
//                                              v.getAngle(),
//                                              axis.c_str()).c_str());
//}
//
//const char* btMatrix3x3toJsonString(const btMatrix3x3 &v)
//{
//    return njli::JsonJLI::parse(string_format(btMatrix3x3_BASE,
//                                              v.getRow(0).x(),
//                                              v.getRow(0).y(),
//                                              v.getRow(0).z(),
//                                              v.getRow(1).x(),
//                                              v.getRow(1).y(),
//                                              v.getRow(1).z(),
//                                              v.getRow(2).x(),
//                                              v.getRow(2).y(),
//                                              v.getRow(2).z()).c_str());
//}
//
//const char* toJsonString(const char* &v)
//{
//    return njli::JsonJLI::parse(string_format("\"%s\"", v.c_str()).c_str());
//}

