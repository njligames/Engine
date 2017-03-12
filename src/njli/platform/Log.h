

#include "Macros.h"


#if defined(DEBUG) || defined(_DEBUG)
#define LOGGING_ON 1
#define LUA_WRAPPER_LOGGING 0
#define FMOD_LOGGING_ON 0
#else
#define LOGGING_ON 0
#define LUA_WRAPPER_LOGGING 0
#define FMOD_LOGGING_ON 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include "LinearMath/btScalar.h"
//#include <string>
    
void _debug_log_v(const char* tag, const char* text, ...) PRINTF(2, 3);
void _debug_log_d(const char* tag, const char* text, ...) PRINTF(2, 3);
void _debug_log_w(const char* tag, const char* text, ...) PRINTF(2, 3);
void _debug_log_e(const char* tag, const char* text, ...) PRINTF(2, 3);
void _script_error(const char* tag, const char* text, ...) PRINTF(2, 3);
    void _script_crash();

void LUA_WRITE(const char* c);

void _debug_log_stderr(const char* tag, const char* fmt, ...);
    

//    void script_error(const char *description);

#ifdef __cplusplus
}
#endif


#if defined(DEBUG) || defined(_DEBUG)
#define SCRIPT_ERROR(tag, fmt, ...) \
_script_error(tag, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);
#else
#define SCRIPT_ERROR(fmt, ...) \
{           \
}
#endif


#if defined(DEBUG) || defined(_DEBUG)
#define CRASH() \
    /*__builtin_trap()*/_script_crash()
#else
#define CRASH() \
    {           \
    }
#endif




#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_ASSERT(cond) \
    do {                   \
        if (!(cond)) {     \
            CRASH();       \
        }                  \
    } while (0)
#else
#define DEBUG_ASSERT(cond) \
    {                      \
    }
#endif







#define DEBUG_LOG_PRINT_V(tag, fmt, ...)                                                      \
    do {                                                                                      \
        if (LOGGING_ON)                                                                       \
            _debug_log_v(tag, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
    } while (0)




#define DEBUG_LOG_PRINT_D(tag, fmt, ...)                                                      \
    do {                                                                                      \
        if (LOGGING_ON)                                                                       \
            _debug_log_d(tag, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
    } while (0)





#define DEBUG_LOG_PRINT_W(tag, fmt, ...)                                                      \
    do {                                                                                      \
        if (LOGGING_ON)                                                                       \
            _debug_log_w(tag, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
    } while (0)





#define DEBUG_LOG_PRINT_E(tag, fmt, ...)                                                      \
    do {                                                                                      \
        if (LOGGING_ON)                                                                       \
            _debug_log_e(tag, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
    } while (0)






#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_ASSERT_PRINT(condition, fmt, ...)                                                   \
    do {                                                                                          \
        if (!(condition)) {                                                                       \
            if (LOGGING_ON)                                                                       \
                _debug_log_stderr("%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
            CRASH();                                                                              \
        }                                                                                         \
    } while (0)
#else
#define DEBUG_ASSERT_PRINT(condition, fmt, ...) \
    {                                           \
    }
#endif






#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_WARN_PRINT(condition, fmt, ...)                                                   \
do {                                                                                          \
if (!(condition)) {                                                                       \
if (LOGGING_ON)                                                                       \
_debug_log_w("%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
}                                                                                         \
} while (0)
#else
#define DEBUG_WARN_PRINT(condition, fmt, ...) \
{                                           \
}
#endif











#define DEBUG_LOG_V(tag, fmt, ...)               \
    do {                                         \
        if (LOGGING_ON)                          \
            _debug_log_v(tag, fmt, __VA_ARGS__); \
    } while (0)







#define DEBUG_LOG_D(tag, fmt, ...)               \
    do {                                         \
        if (LOGGING_ON)                          \
            _debug_log_d(tag, fmt, __VA_ARGS__); \
    } while (0)






#define DEBUG_LOG_W(tag, fmt, ...)               \
    do {                                         \
        if (LOGGING_ON)                          \
            _debug_log_w(tag, fmt, __VA_ARGS__); \
    } while (0)







#define DEBUG_LOG_E(tag, fmt, ...)               \
    do {                                         \
        if (LOGGING_ON)                          \
            _debug_log_e(tag, fmt, __VA_ARGS__); \
    } while (0)













#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_WARN_LOG(condition, fmt, ...)        \
do {                                             \
if (!(condition)) {                          \
if (LOGGING_ON)                          \
_debug_log_w(fmt, __VA_ARGS__); \
}                                            \
} while (0)
#else
#define DEBUG_WARN_LOG(condition, fmt, ...) \
{                                         \
}
#endif









#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_PRINT(text) DEBUG_LOG_D("DEFAULT", "%s", text)
    
#define DEBUG_PRINTF(fmt, ...) DEBUG_LOG_D("DEFAULT", fmt, __VA_ARGS__)
    
    
#define DEBUG_VERBOSE(tag, text) DEBUG_LOG_V(tag, "%s", text)
#define DEBUG_DEBUG(tag, text) DEBUG_LOG_D(tag, "%s", text)
#define DEBUG_WARN(tag, text) DEBUG_LOG_W(tag, "%s", text)
#define DEBUG_ERROR(tag, text) DEBUG_LOG_E(tag, "%s", text)
    
    
#define DEBUG_LOG_WRITE_V(tag, text) DEBUG_LOG_PRINT_V(tag, "%s", text)
#define DEBUG_LOG_WRITE_D(tag, text) DEBUG_LOG_PRINT_D(tag, "%s", text)
#define DEBUG_LOG_WRITE_W(tag, text) DEBUG_LOG_PRINT_W(tag, "%s", text)
#define DEBUG_LOG_WRITE_E(tag, text) DEBUG_LOG_PRINT_E(tag, "%s", text)
#define DEBUG_ASSERT_WRITE(condition, text) DEBUG_ASSERT_PRINT(condition, "%s", text)
    #define DEBUG_WARN_WRITE(condition, text) DEBUG_WARN_PRINT(condition, "%s", text)



void njliSleep(unsigned int _ms);

//njli::NJLIGameEngine::PlatformID platformID();

#if LOGGING_ON
#define DEBUG_GL_ERROR_PRINT(op, fmt, ...)                                                                                                                                                                                                                                                                                                                                                               \
    do {                                                                                                                                                                                                                                                                                                                                                                                                 \
        for (int error = glGetError(); error; error = glGetError()) {                                                                                                                                                                                                                                                                                                                                    \
            DEBUG_LOG_PRINT_E("glGetError", "after %s(" fmt ")", #op, __VA_ARGS__);                                                                                                                                                                                                                                                                                                                      \
            switch (error) {                                                                                                                                                                                                                                                                                                                                                                             \
            case GL_NO_ERROR:                                                                                                                                                                                                                                                                                                                                                                            \
                DEBUG_LOG_WRITE_V("glGetError", "GL_NO_ERROR - No error has been recorded. The value of this symbolic constant is guaranteed to be 0.");                                                                                                                                                                                                                                                 \
                break;                                                                                                                                                                                                                                                                                                                                                                                   \
            case GL_INVALID_ENUM:                                                                                                                                                                                                                                                                                                                                                                        \
                DEBUG_LOG_WRITE_V("glGetError", "GL_INVALID_ENUM - An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.");                                                                                                                                                                           \
                break;                                                                                                                                                                                                                                                                                                                                                                                   \
            case GL_INVALID_VALUE:                                                                                                                                                                                                                                                                                                                                                                       \
                DEBUG_LOG_WRITE_V("glGetError", "GL_INVALID_VALUE - A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.");                                                                                                                                                                                                     \
                break;                                                                                                                                                                                                                                                                                                                                                                                   \
            case GL_INVALID_OPERATION:                                                                                                                                                                                                                                                                                                                                                                   \
                DEBUG_LOG_WRITE_V("glGetError", "GL_INVALID_OPERATION - The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.");                                                                                                                                                                        \
                break;                                                                                                                                                                                                                                                                                                                                                                                   \
            case GL_INVALID_FRAMEBUFFER_OPERATION:                                                                                                                                                                                                                                                                                                                                                       \
                DEBUG_LOG_WRITE_V("glGetError", "GL_INVALID_FRAMEBUFFER_OPERATION - The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete (i.e. the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE). The offending command is ignored and has no other side effect than to set the error flag."); \
                break;                                                                                                                                                                                                                                                                                                                                                                                   \
            case GL_OUT_OF_MEMORY:                                                                                                                                                                                                                                                                                                                                                                       \
                DEBUG_LOG_WRITE_V("glGetError", "GL_OUT_OF_MEMORY - There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");                                                                                                                                                                  \
                break;                                                                                                                                                                                                                                                                                                                                                                                   \
            default:                                                                                                                                                                                                                                                                                                                                                                                     \
                DEBUG_LOG_PRINT_V("glGetError", "Unknown (%x)", error);                                                                                                                                                                                                                                                                                                                                  \
            }                                                                                                                                                                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                                                                                                                                                                \
    } while (0)
#else
#define DEBUG_GL_ERROR_PRINT(op, fmt, ...) \
    {                                      \
    }
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_GL_ERROR_WRITE(op) DEBUG_GL_ERROR_PRINT(op, "%s", "")
#else
#define DEBUG_GL_ERROR_WRITE(op) \
    {                            \
    }
#endif

#define btVector2_BASE "{\"btVector2\":[{\"x\":\"%f\", \"y\":\"%f\"}]}"
#define btVector3_BASE "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}"
#define btVector4_BASE "{\"btVector4\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\", \"w\":\"%f\"}]}"
#define btManifold_BASE "{\"btManifoldPoint\":[{\"distance\":\"%f\", \"lifetime\":\"%d\", \"Position On A\":%s, \"Position On B\":%s, \"Applied Impulse\":\"%f\"}]}"
#define btQuaternion_BASE "{\"btQuaternion\":[{\"angle\":\"%f\", \"axis\":%s}]}"
#define btMatrix3x3_BASE "{\"btMatrix3x3\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\"}]}"
#define btTransform_BASE "{\"btTransform\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", \"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", \"ww\":\"%f\"}]}"
    
    
    const char* string_format(const char* fmt, ...);
//    const char* createJsonKeyValue(const char* key, const char* value);
    
//    class btVector2;
//    class btVector3;
//    class btVector4;
//    class btManifoldPoint;
//    class btTransform;
//    class btQuaternion;
//    class btMatrix3x3;
//    class btCollisionObject;
//    class btRigidBody;
//    
//    const char* btoJsonString(const bool b);
//    const char* btScalartoJsonString(const btScalar &v);
//    const char* btVector2toJsonString(const btVector2 &v);
//    const char* btVector3toJsonString(const btVector3 &v);
//    const char* btVector4toJsonString(const btVector4 &v);
//    const char* btManifoldPointtoJsonString(const btManifoldPoint &v);
//    const char* btTransformtoJsonString(const btTransform &v);
//    const char* btQuaterniontoJsonString(const btQuaternion &v);
//    const char* btMatrix3x3toJsonString(const btMatrix3x3 &v);
//    const char* toJsonString(const char* v);
//    const char* toJsonString(const btCollisionObject &v);
//    const char* toJsonString(const btRigidBody &v);
    
    
#ifdef __cplusplus
}
#endif







//njli::NJLIGameEngine::PlatformID platformID();
