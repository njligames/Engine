#define GL_GLEXT_PROTOTYPES

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "GLES2/gl2platform.h"

#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "EGL/eglplatform.h"

#define NANOVG_GLES2_IMPLEMENTATION

#ifndef __MACOSX__
#define __MACOSX__
#endif

#define USE_FMOD
