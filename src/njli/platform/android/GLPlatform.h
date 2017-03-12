// #define GL_GLEXT_PROTOTYPES
//
//
// #ifndef _ANDROID_DECLARE_GL_OES_
// #define _ANDROID_DECLARE_GL_OES_

#include <dlfcn.h>

// //these ugly typenames are defined in GLES2/gl2ext.h
// PFNGLBINDVERTEXARRAYOESPROC bindVertexArrayOES;
// PFNGLDELETEVERTEXARRAYSOESPROC deleteVertexArraysOES;
// PFNGLGENVERTEXARRAYSOESPROC genVertexArraysOES;
// PFNGLISVERTEXARRAYOESPROC isVertexArrayOES;

// void initialiseFunctions () {

// //[check here that VAOs are actually supported]

// void *libhandle = dlopen("libGLESv2.so", RTLD_LAZY);

// bindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC) dlsym(libhandle, "glBindVertexArrayOES");
// deleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC) dlsym(libhandle, "glDeleteVertexArraysOES");
// genVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)dlsym(libhandle,"glGenVertexArraysOES");
// isVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC)dlsym(libhandle, "glIsVertexArrayOES");

// // [...]
// }

// #endif

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

#include <android/asset_manager_jni.h>

// #ifndef _ANDROID_DECLARE_GL_OES_
// #define _ANDROID_DECLARE_GL_OES_
// PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress ( "glGenVertexArraysOES" );
// PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress ( "glBindVertexArrayOES" );
// PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress ( "glDeleteVertexArraysOES" );
// PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC)eglGetProcAddress ( "glIsVertexArrayOES" );
// #endif

//#ifndef _ANDROID_DECLARE_GL_OES_
//#define _ANDROID_DECLARE_GL_OES_

//#include <dlfcn.h>
//
//#ifndef glGenVertexArraysOES
////#define glGenVertexArraysOES (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress ( "glGenVertexArraysOES" );
//#define glGenVertexArraysOES (PFNGLGENVERTEXARRAYSOESPROC)dlsym(dlopen("libGLESv2.so", RTLD_LAZY), "glGenVertexArraysOES");
//#endif
//
//#ifndef glBindVertexArrayOES
////#define glBindVertexArrayOES (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress ( "glBindVertexArrayOES" );
//#define glBindVertexArrayOES (PFNGLBINDVERTEXARRAYOESPROC) dlsym(dlopen("libGLESv2.so", RTLD_LAZY), "glBindVertexArrayOES");
//#endif
//
//
//#ifndef glDeleteVertexArraysOES
////#define glDeleteVertexArraysOES (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress ( "glDeleteVertexArraysOES" );
//#define glDeleteVertexArraysOES (PFNGLDELETEVERTEXARRAYSOESPROC) dlsym(dlopen("libGLESv2.so", RTLD_LAZY), "glDeleteVertexArraysOES");
//#endif
//
//#ifndef glIsVertexArrayOES
////#define glIsVertexArrayOES (PFNGLISVERTEXARRAYOESPROC)eglGetProcAddress ( "glIsVertexArrayOES" );
//#define glIsVertexArrayOES (PFNGLISVERTEXARRAYOESPROC)dlsym(dlopen("libGLESv2.so", RTLD_LAZY), "glIsVertexArrayOES");
//#endif

//#ifndef initialiseFunctions_ASDF
//#define initialiseFunctions_ASDF
//#include <dlfcn.h>
////these ugly typenames are defined in GLES2/gl2ext.h
//PFNGLBINDVERTEXARRAYOESPROC bindVertexArrayOES;
//PFNGLDELETEVERTEXARRAYSOESPROC deleteVertexArraysOES;
//PFNGLGENVERTEXARRAYSOESPROC genVertexArraysOES;
//PFNGLISVERTEXARRAYOESPROC isVertexArrayOES;
//
////static void initialiseFunctions () {
//
//    //[check here that VAOs are actually supported]
//
//    void *libhandle = dlopen("libGLESv2.so", RTLD_LAZY);
//
//    bindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC) dlsym(libhandle,
//                                                             "glBindVertexArrayOES");
//    deleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC) dlsym(libhandle,
//                                                                   "glDeleteVertexArraysOES");
//    genVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)dlsym(libhandle,
//                                                            "glGenVertexArraysOES");
//    isVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC)dlsym(libhandle,
//                                                        "glIsVertexArrayOES");
////}
////initialiseFunctions();
//#endif

extern AAssetManager* asset_manager;

#ifndef __ANDROID__
#define __ANDROID__
#endif

#define USE_FMOD