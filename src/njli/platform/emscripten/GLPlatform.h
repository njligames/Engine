#define GL_GLEXT_PROTOTYPES

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#define NANOVG_GLES2_IMPLEMENTATION

#ifndef __EMSCRIPTEN__
#define __EMSCRIPTEN__
#endif

#define USE_OPENAL
