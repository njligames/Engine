//
//  btPrint.h
//  JLIGameEngineTest
//
//  Created by James Folk on 9/9/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_btPrint_h
#define JLIGameEngineTest_btPrint_h

//#include "JsonJLI.h"
//
//#include "LinearMath/btScalar.h"
//#include "btVector2.h"
//#include "LinearMath/btVector3.h"
//#include "BulletCollision/NarrowPhaseCollision/btManifoldPoint.h"
//#include "LinearMath/btTransform.h"
//#include "LinearMath/btQuaternion.h"
//#include "LinearMath/btMatrix3x3.h"
//#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
//#include "BulletDynamics/Dynamics/btRigidBody.h"

//#define btVector2_BASE "{\"btVector2\":[{\"x\":\"%f\", \"y\":\"%f\"}]}"
//#define btVector3_BASE "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}"
//#define btVector4_BASE "{\"btVector4\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\", \"w\":\"%f\"}]}"
//#define btManifold_BASE "{\"btManifoldPoint\":[{\"distance\":\"%f\", \"lifetime\":\"%d\", \"Position On A\":%s, \"Position On B\":%s, \"Applied Impulse\":\"%f\"}]}"
//#define btQuaternion_BASE "{\"btQuaternion\":[{\"angle\":\"%f\", \"axis\":%s}]}"
//#define btMatrix3x3_BASE "{\"btMatrix3x3\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\"}]}"
//#define btTransform_BASE "{\"btTransform\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", \"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", \"ww\":\"%f\"}]}"
//
//std::string string_format(const std::string fmt, ...);
//std::string createJsonKeyValue(const std::string &key, const std::string &value);
//
//std::string toJsonString(const bool b);
//std::string toJsonString(const btScalar &v);
//std::string toJsonString(const btVector2 &v);
//std::string toJsonString(const btVector3 &v);
//std::string toJsonString(const btVector4 &v);
//std::string toJsonString(const btManifoldPoint &v);
//std::string toJsonString(const btTransform &v);
//std::string toJsonString(const btQuaternion &v);
//std::string toJsonString(const btMatrix3x3 &v);
//std::string toJsonString(const std::string &v);
//std::string toJsonString(const btCollisionObject &v);
//std::string toJsonString(const btRigidBody &v);

//SIMD_FORCE_INLINE std::string string_format(const std::string fmt, ...) {
//    std::vector<char> str(100,'\0');
//    va_list ap;
//    while (1) {
//        va_start(ap, fmt);
//        auto n = vsnprintf(str.data(), str.size(), fmt.c_str(), ap);
//        va_end(ap);
//        if ((n > -1) && (size_t(n) < str.size())) {
//            return str.data();
//        }
//        if (n > -1)
//            str.resize( n + 1 );
//        else
//            str.resize( str.size() * 2);
//    }
//    return str.data();
//}
//
//SIMD_FORCE_INLINE std::string createJsonKeyValue(const std::string &key, const std::string &value)
//{
//    return string_format("{\"%s\":%s}", key.c_str(), value.c_str());
////    return jli::JsonJLI::parse(v.c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const bool b)
//{
//    return njli::JsonJLI::parse(string_format("\"%s\"", (b)?"true":"false").c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btScalar &v)
//{
//    return njli::JsonJLI::parse(string_format("\"%f\"", v).c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btVector2 &v)
//{
//    return njli::JsonJLI::parse(string_format(btVector2_BASE, v.x(), v.y()).c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btVector3 &v)
//{
//    return njli::JsonJLI::parse(string_format(btVector3_BASE, v.x(), v.y(), v.z()).c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btVector4 &v)
//{
//    return njli::JsonJLI::parse(string_format(btVector4_BASE, v.x(), v.y(), v.z(), v.w()).c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btManifoldPoint &v)
//{
//    std::string pa = toJsonString(v.getPositionWorldOnA());
//    std::string pb = toJsonString(v.getPositionWorldOnB());
//    return njli::JsonJLI::parse(string_format(btManifold_BASE,
//                                  v.getDistance(),
//                                  v.getLifeTime(),
//                                  pa.c_str(),
//                                  pb.c_str(),
//                                  v.getAppliedImpulse()).c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btTransform &v)
//{
////    static btScalar m[16];
//    btScalar *m = new btScalar[16];
//    v.getOpenGLMatrix(m);
//    
//    std::string ret = njli::JsonJLI::parse(string_format(btTransform_BASE,
//                                  m[0],
//                                  m[1],
//                                  m[2],
//                                  m[3],
//                                  m[4],
//                                  m[5],
//                                  m[6],
//                                  m[7],
//                                  m[8],
//                                  m[9],
//                                  m[10],
//                                  m[11],
//                                  m[12],
//                                  m[13],
//                                  m[14],
//                                  m[15]).c_str());
//    delete [] m;
//    return ret;
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btQuaternion &v)
//{
//    std::string axis = toJsonString(v.getAxis());
//    return njli::JsonJLI::parse(string_format(btQuaternion_BASE,
//                                  v.getAngle(),
//                                  axis.c_str()).c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const btMatrix3x3 &v)
//{
//    return njli::JsonJLI::parse(string_format(btMatrix3x3_BASE,
//                                  v.getRow(0).x(),
//                                  v.getRow(0).y(),
//                                  v.getRow(0).z(),
//                                  v.getRow(1).x(),
//                                  v.getRow(1).y(),
//                                  v.getRow(1).z(),
//                                  v.getRow(2).x(),
//                                  v.getRow(2).y(),
//                                  v.getRow(2).z()).c_str());
//}
//
//SIMD_FORCE_INLINE std::string toJsonString(const std::string &v)
//{
//    return njli::JsonJLI::parse(string_format("\"%s\"", v.c_str()).c_str());
//}

//SIMD_FORCE_INLINE void transformValues(const btTransform &t,
//                                       float &x1, float &y1, float &z1, float &w1,
//                                       float &x2, float &y2, float &z2, float &w2,
//                                       float &x3, float &y3, float &z3, float &w3,
//                                       float &x4, float &y4, float &z4, float &w4)
//{
//    btScalar *m = new btScalar[16];
//    
//    t.getOpenGLMatrix(m);
//    
//    x1=m[0];
//    y1=m[1];
//    z1=m[2];
//    w1=m[3];
//    
//    x2=m[4];
//    y2=m[5];
//    z2=m[6];
//    w2=m[7];
//    
//    x3=m[8];
//    y3=m[9];
//    z3=m[10];
//    w3=m[11];
//    
//    x4=m[12];
//    y4=m[13];
//    z4=m[14];
//    w4=m[15];
//    
//    delete [] m;
//}
#endif
