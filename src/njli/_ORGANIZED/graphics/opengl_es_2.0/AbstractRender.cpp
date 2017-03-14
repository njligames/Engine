//
//  AbstractRender.h
//  JLIGameEngineTest
//
//  Created by James Folk on 5/10/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractRender_h
#define JLIGameEngineTest_AbstractRender_h

#define TAG "AbstractRender.cpp"
#include "GLPlatform.h"
#include "AbstractRender.h"
#include "Log.h"
#include <string>
#include "Util.h"

static f32 bgRed = 0.0f;
static f32 bgGreen = 0.0f;
static f32 bgBlue = 0.0f;
static f32 bgAlpha = 1.0f;

static int viewX;
static int viewY;
static int viewWidth;
static int viewHeight;

void initGL()
{
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void renderGL()
{
#if defined(DEBUG) || defined (_DEBUG)
    glPushGroupMarkerEXT(0, "renderGL()");
#endif
    glViewport(viewX, viewY, viewWidth, viewHeight);
//    glClearColor(bgRed, bgGreen, bgBlue, bgAlpha);
    glClearColor(0.52, 0.86, 0.99, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendEquation(GL_FUNC_ADD);
    
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
#if defined(DEBUG) || defined (_DEBUG)
    glPopGroupMarkerEXT();
#endif
}

void printGLInfo()
{
    //gl begin printGLInfo
    DEBUG_LOG_V(TAG, "%s = %s\n", "GL_VERSION", (const char *) glGetString(GL_VERSION));
    DEBUG_LOG_V(TAG, "%s = %s\n", "GL_VENDOR", (const char *) glGetString(GL_VENDOR));
    DEBUG_LOG_V(TAG, "%s = %s\n", "GL_RENDERER", (const char *) glGetString(GL_RENDERER));
    
    DEBUG_LOG_V(TAG, "%s\n", "GL_EXTENSIONS");
    const char *the_extensions = (const char *) glGetString(GL_EXTENSIONS);
    char *extensions = new char[strlen(the_extensions)+1];
    DEBUG_ASSERT(extensions);
    strcpy(extensions, the_extensions);
    char *extension = strtok(extensions, " ");
    DEBUG_LOG_V(TAG, "\t%s\n", extension);
    while (NULL != (extension = strtok(NULL, " ")))
    {
        DEBUG_LOG_V(TAG, "\t%s\n", extension);
    }
    delete [] extensions;
    extensions = NULL;
    //    DEBUG_LOG_PRINT_V(TAG, "%s = %s", "GL_EXTENSIONS", (const char *) glGetString(GL_EXTENSIONS));
    DEBUG_LOG_V(TAG, "%s = %s\n", "GL_SHADING_LANGUAGE_VERSION", (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    
    
    int param;
    
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The max texture size", param);
    
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The count texture units of allowed for usage in vertex shader", param);
    
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The count texture units of allowed for usage in fragmet shader", param);
    
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The count texture units of allowed for usage in both shaders", param);
    
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The maximumum amount of uniform vectors in the vertex shader", param);
    
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The maximumum amount of uniform vectors in the fragment shader", param);
    
    glGetIntegerv(GL_MAX_VARYING_VECTORS, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The maximumum amount of varying vectors", param);
    
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &param);
    DEBUG_LOG_V(TAG, "%s = %d\n", "The maximumum amount of vertex attributes", param);
  
    
//
    
//    GL_MAX_VERTEX_UNIFORM_VECTORS
//    GL_MAX_FRAGMENT_UNIFORM_VECTORS
    /*
     Actually there is GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, and GL_MAX_TEXTURE_IMAGE_UNITS and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS enums. First is for count texture units of allowed for usage in vertex shader, second one is for fragment shader, and third is combined for both shaders combined.
     */
    
    //gl end printGLInfo
}

void setGLBackgroundColor(float red, float green, float blue, float alpha)
{
    bgRed = red;
    bgGreen = green;
    bgBlue = blue;
    bgAlpha = alpha;
}
void setGLViewSize(int x, int y, int width, int height)
{
    viewX = x;
    viewY = y;
    viewWidth = width;
    viewHeight = height;
}

#endif
