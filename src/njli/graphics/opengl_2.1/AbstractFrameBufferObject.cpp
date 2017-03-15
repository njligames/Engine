//
//  AbstractFrameBufferObject.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/27/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "AbstractFrameBufferObject.h"
#include "GLPlatform.h"
#include "Camera.h"
#include "World.h"
#include "WorldHUD.h"

//http://blog.angusforbes.com/openglglsl-render-to-texture/

namespace njli
{
    AbstractFrameBufferObject::AbstractFrameBufferObject() :
    m_textureA(-1),
    m_textureB(-1),
    m_height(0),
    m_width(0),
    m_counter(0),
    m_frameBufferA(-1),
    m_frameBufferB(-1),
    m_stencilBufferA(-1),
    m_stencilBufferB(-1),
    m_isHidden(false)
    {
        njli::World::getInstance()->getWorldHUD()->addFBO(this);
        
    }
    
    AbstractFrameBufferObject::~AbstractFrameBufferObject()
    {
        njli::World::getInstance()->getWorldHUD()->removeFBO(this);
        unLoadGPU();
    }
    
    bool AbstractFrameBufferObject::isLoadedGPU()const
    {
        return ((m_frameBufferA != -1) && (m_frameBufferB != -1) && (m_textureA != -1) && (m_textureB != -1));
    }
    
    static void createFBO(GLuint &frameBuffer, GLuint &texColorBuffer, GLuint &rboDepthStencil, GLsizei width, GLsizei height)
    {
        //gl begin createFBO
        GLint defaultFBO;
        GLint defaultRBO;
        
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &defaultRBO);

        // Create frame buffer
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        
        // Create texture to hold color buffer
        glGenTextures(1, &texColorBuffer);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
        
        // Create Renderbuffer Object to hold depth and stencil buffers
        glGenRenderbuffers(1, &rboDepthStencil);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
        
        glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
        glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);
        //gl end createFBO
    }
    void AbstractFrameBufferObject::loadGPU(u32 width, u32 height)
    {
        if (isLoadedGPU())
            unLoadGPU();
     
        if(width > 2048)
            width = 2048;
        if(height > 2048)
            height = 2048;
        
        m_width = width;
        m_height = height;

        createFBO(m_frameBufferA, m_textureA, m_stencilBufferA, m_width, m_height);
        createFBO(m_frameBufferB, m_textureB, m_stencilBufferB, m_width, m_height);
        
        //initialize a counter so we know if we are "pinging" or "ponging"
        //(i.e. if counter is even then FBO A is current, if odd, FBO B is current.)
        m_counter = 0;
    }
    
    void AbstractFrameBufferObject::render(Camera *camera)
    {
        //gl begin render
        if(!isLoadedGPU())
            loadGPU();
     
        GLint defaultFBO;
        GLint defaultRBO;
        
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &defaultRBO);
        GLint viewPort[4] = {0};
        glGetIntegerv(GL_VIEWPORT, viewPort);
        
        if (m_counter % 2 == 0)
            renderInternal(m_frameBufferA, camera);
        else
            renderInternal(m_frameBufferB, camera);
        m_counter++;
        
        glViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
        glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);
        //gl end render
    }
    
    u32 AbstractFrameBufferObject::getTextureID()const
    {
        if (m_counter % 2 == 0)
            return m_textureB;
        
        return m_textureA;
    }
    
    void AbstractFrameBufferObject::unLoadGPU()
    {
        //gl begin unloadGPU
        if(m_stencilBufferA != -1)
            glDeleteRenderbuffers(1, &m_stencilBufferA);
        m_stencilBufferA = -1;
        
        if(m_stencilBufferB != -1)
            glDeleteRenderbuffers(1, &m_stencilBufferB);
        m_stencilBufferB = -1;
        
        if(m_frameBufferA != -1)
            glDeleteFramebuffers(1, &m_frameBufferA);
        m_frameBufferA = -1;
        
        if(m_frameBufferB != -1)
            glDeleteFramebuffers(1, &m_frameBufferB);
        m_frameBufferB = -1;
        
        if(m_textureA != -1)
            glDeleteTextures(1, &m_textureA);
        m_textureA = -1;
        
        if(m_textureB != -1)
            glDeleteTextures(1, &m_textureB);
        m_textureB = -1;
        //gl end unloadGPU
    }
    
    u32 AbstractFrameBufferObject::getWidth()
    {
        return m_width;
    }
    
    u32 AbstractFrameBufferObject::getHeight()
    {
        return m_height;
    }
    
    f32 AbstractFrameBufferObject::getAspectRatio()
    {
        return fabsf((f32)getWidth() / (f32)getHeight());
    }
    
    bool AbstractFrameBufferObject::isHidden()const
    {
        return m_isHidden;
    }
    
    void AbstractFrameBufferObject::hide()
    {
        m_isHidden = true;
    }
    
    void AbstractFrameBufferObject::show()
    {
        m_isHidden = false;
    }
    
    void AbstractFrameBufferObject::renderInternal(u32 fbo, Camera *camera)
    {
        //gl begin renderInternal
        
        //bind FBO to set textureA as the output texture.
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        
        //set the viewport to be the size of the texture
        glViewport(0, 0, m_width, m_height);
        
        glClearColor(0.0, 0.0, 0.0, 0.0);
        
        s32 srcRGB, dstRGB, srcAlpha, dstAlpha;
        
        glGetIntegerv(GL_BLEND_SRC_RGB, &srcRGB);
        glGetIntegerv(GL_BLEND_DST_RGB, &dstRGB);
        glGetIntegerv(GL_BLEND_SRC_ALPHA, &srcAlpha);
        glGetIntegerv(GL_BLEND_DST_ALPHA, &dstAlpha);
        
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        
        //clear the ouput texture
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        renderFunction(camera);
        
        
        glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
        //gl end renderInternal
    }
    
}