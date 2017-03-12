//
//  AbstractFrameBufferObject.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/27/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__AbstractFrameBufferObject__
#define __JLIGameEngineTest__AbstractFrameBufferObject__

#include "Util.h"

namespace njli {
class Camera;

/// <#Description#>
class AbstractFrameBufferObject {
    friend class MaterialProperty;
    friend class WorldHUD;
    friend class Material;

public:
    /**
         *  <#Description#>
         */
    AbstractFrameBufferObject();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~AbstractFrameBufferObject();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isHidden() const;

    /**
         *  <#Description#>
         */
    void hide();

    /**
         *  <#Description#>
         */
    void show();

protected:
    bool isLoadedGPU() const;
    void loadGPU(u32 width = 2048, u32 height = 2048);
    void render(Camera* camera);
    u32 getTextureID() const;
    void unLoadGPU();

    u32 getWidth();
    u32 getHeight();
    f32 getAspectRatio();

    virtual void renderFunction(Camera* camera) = 0;

private:
    AbstractFrameBufferObject(const AbstractFrameBufferObject& copy);
    AbstractFrameBufferObject& operator=(const AbstractFrameBufferObject& rhs);

    void renderInternal(u32 fbo, Camera* camera);

    u32 m_textureA;
    u32 m_textureB;
    s32 m_height;
    s32 m_width;
    s32 m_counter;
    u32 m_frameBufferA;
    u32 m_frameBufferB;
    u32 m_stencilBufferA;
    u32 m_stencilBufferB;
    u32 m_depthBufferA;
    u32 m_depthBufferB;
    bool m_isHidden;
};
}

#endif /* defined(__JLIGameEngineTest__AbstractFrameBufferObject__) */
