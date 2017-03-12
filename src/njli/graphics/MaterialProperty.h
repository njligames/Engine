//
//  MaterialProperty.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__MaterialProperty__
#define __JLIGameEngineTest__MaterialProperty__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "JLIFactoryTypes.h"
#include "btVector2.h"
#include "lua.hpp"

#include <bitset>

class btTransform;

namespace njli {
class MaterialPropertyBuilder;
class Image;
class ShaderProgram;
class AbstractFrameBufferObject;
class Material;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
MaterialProperty : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class Material;

protected:
    MaterialProperty();
    MaterialProperty(const AbstractBuilder&);
    MaterialProperty(const MaterialProperty&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~MaterialProperty();
    MaterialProperty& operator=(const MaterialProperty&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:47
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    operator std::string() const;

    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    static MaterialProperty** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(MaterialProperty * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static MaterialProperty* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static MaterialProperty* create(const MaterialPropertyBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static MaterialProperty* clone(const MaterialProperty& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static MaterialProperty* copy(const MaterialProperty& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(MaterialProperty * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(MaterialProperty & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Material* getParent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Material* getParent() const;

public:
    //TODO: fill in specific methods for Texture

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setMinificationFilter(njliTextureMinificationValueType val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliTextureMinificationValueType getMinificationFilter() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setMagnificationFilter(njliTextureMagnificationValueType val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliTextureMagnificationValueType getMagnificationFilter() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setWrapS(njliTextureWrapType val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliTextureWrapType getWrapS() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setWrapT(njliTextureWrapType val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliTextureWrapType getWrapT() const;

    /**
         *  <#Description#>
         */
    void loadGPU();
    /**
         *  <#Description#>
         *
         *  @param img <#img description#>
         */
    void loadGPU(const Image& img);
    /**
         *  <#Description#>
         *
         *  @param negativeX <#negativeX description#>
         *  @param negativeY <#negativeY description#>
         *  @param negativeZ <#negativeZ description#>
         *  @param positiveX <#positiveX description#>
         *  @param positiveY <#positiveY description#>
         *  @param positiveZ <#positiveZ description#>
         */
    void loadGPU(const Image& negativeX,
        const Image& negativeY,
        const Image& negativeZ,
        const Image& positiveX,
        const Image& positiveY,
        const Image& positiveZ);
    /**
         *  <#Description#>
         *
         *  @param fbo <#fbo description#>
         */
    void loadGPU(AbstractFrameBufferObject * fbo);

    /**
         *  <#Description#>
         */
    void unLoadGPU();

    /**
         *  <#Description#>
         *
         *  @param img <#img description#>
         *  @param offset   <#0 description#>
         */
    void reLoadGPU(const Image& img, const btVector2& offset = btVector2(0, 0));

    /**
         *  <#Description#>
         *
         *  @param img      <#img description#>
         *  @param cubeSide <#cubeSide description#>
         *  @param offset        <#0 description#>
         */
    void reLoadGPU(const Image& img, njliTextureCubeSides cubeSide, const btVector2& offset = btVector2(0, 0));

    /**
         *  <#Description#>
         *
         *  @param transform <#transform description#>
         */
    void setTextureTransform(const btTransform& transform);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btTransform& getTextureTransform() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u32 getWidth() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u32 getHeight() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isTextureCube() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isTexture2D() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool hasOpacity() const;

    static void initReferences();

protected:
    u8 getTextureIndex() const;
    void setTextureIndex(u8 index);

    bool bind(ShaderProgram * program);
    void unBind() ;

    void loadTexImage2DInternal(const Image& img, s32 target);
    void reLoadTexImage2DInternal(const Image& img, s32 target, const btVector2& offset = btVector2(0, 0));
    
    virtual void loadProperties() const;

//    void render();

private:
    bool m_diffuseBound;
    bool *m_materialBound;
    u32 m_textureID;
    njliTextureMinificationValueType m_minVal;
    njliTextureMagnificationValueType m_magVal;
    njliTextureWrapType m_sWrap;
    njliTextureWrapType m_tWrap;
    s32 m_textureType;
    btTransform* m_TextureTransform;
    u8 m_TextureIndex;
    u32 m_Width;
    u32 m_Height;
    u32 m_NumberOfComponents;

    u32 m_2DUniform;
    u32 m_CubeUniform;
    u32 m_is2DUniform;
    u32 m_isCubeUniform;
    AbstractFrameBufferObject* m_AbstractFrameBufferObject;
    bool m_hasOpacity;

private:
    static void addReference(MaterialProperty*);
    static void removeReference(MaterialProperty*);
    static bool hasReference(MaterialProperty*);

    static std::bitset<16> s_TextureIDReferences;
#if defined(DEBUG) || defined(_DEBUG)
    static u64 s_MaxTextureUnits;
    static u64 s_MaxTextureSize;
#endif

    enum njliLoadGPUType {
        JLI_LOAD_GPU_TYPE_NONE,
        JLI_LOAD_GPU_TYPE_2D_EMPTY,
        JLI_LOAD_GPU_TYPE_2D,
        JLI_LOAD_GPU_TYPE_CUBE,
        JLI_LOAD_GPU_TYPE_FBO,
        JLI_LOAD_GPU_TYPE_MAX
    };

    njliLoadGPUType m_njliLoadGPUType;
    AbstractFrameBufferObject* m_loadGPU_fbo;
//    Image** m_loadGPU_images;

    void loadGPU_Internal();
    void loadGPU_Internal(const Image& img);
    void loadGPU_Internal(const Image& negativeX,
        const Image& negativeY,
        const Image& negativeZ,
        const Image& positiveX,
        const Image& positiveY,
        const Image& positiveZ);
    void loadGPU_Internal(AbstractFrameBufferObject * fbo);
};
}

#endif /* defined(__JLIGameEngineTest__MaterialProperty__) */
