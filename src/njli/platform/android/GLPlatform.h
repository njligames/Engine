

//#include <EGL/egl.h>
//#include <EGL/eglext.h>
//#include <EGL/eglplatform.h>

#define GL_GLEXT_PROTOTYPES

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include <GLES2/gl2platform.h>

#define NANOVG_GLES2_IMPLEMENTATION

#include <dlfcn.h>

#include <android/asset_manager_jni.h>
//
//extern AAssetManager* asset_manager;

#ifndef __ANDROID__
#define __ANDROID__
#endif

#define USE_FMOD
