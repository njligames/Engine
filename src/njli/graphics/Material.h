//
//  Material.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Material__
#define __JLIGameEngineTest__Material__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "JLIFactoryTypes.h"
#include "lua.hpp"
#include <bitset>

namespace njli {
class MaterialBuilder;
class MaterialProperty;
class ShaderProgram;
class AbstractFrameBufferObject;
class Geometry;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Material : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class Geometry;
    friend class Sprite2D;
    friend class ParticleEmitter;
    friend class MaterialProperty;
    friend class Scene;

protected:
    Material();
    Material(const AbstractBuilder&);
    Material(const Material&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Material();
    Material& operator=(const Material&);

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
         *  @author James Folk, 16-02-11 15:02:32
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
    static Material** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Material * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Material* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Material* create(const MaterialBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Material* clone(const Material& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Material* copy(const Material& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Material * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Material & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for Material

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getDiffuse();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getAmbient();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getSpecular();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getNormal();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getReflective();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getEmission();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getTransparent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    MaterialProperty* getMultiply();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getDiffuse() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getAmbient() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getSpecular() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getNormal() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getReflective() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getEmission() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getTransparent() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const MaterialProperty* getMultiply() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setShininess(const f32 val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getShininess() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setFresnelExponenet(const f32 val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getFresnelExponenet() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setTransparency(const f32 val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getTransparency() const;

    /**
         *  <#Description#>
         *
         *  @param enable <#enable description#>
         */
    void enableLitPerPixel(const bool enable = true);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isLitPerPixel() const;

    /**
         *  <#Description#>
         *
         *  @param enable <#enable description#>
         */
    void enableDoubleSided(const bool enable = true);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isDoubleSided() const;

    /**
         *  <#Description#>
         *
         *  @param mode <#mode description#>
         */
    void setTransparencyMode(const njliTransparencyMode mode);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliTransparencyMode getTransparencyMode() const;

    /**
         *  <#Description#>
         *
         *  @param mode <#mode description#>
         */
    void setCullMode(const njliCullMode mode);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliCullMode getCullMode() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Geometry* getParent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Geometry* getParent() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool hasOpacity() const;

protected:
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeDiffuse();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeAmbient();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeSpecular();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeNormal();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeReflective();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeEmission();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeTransparent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    void removeMultiply();

    //        void addTextureIDReference(MaterialProperty *);
    //        void addTextureIDReference(MaterialProperty *, AbstractFrameBufferObject *);
    //        void removeTextureIDReference(MaterialProperty *);

    void bind(ShaderProgram * shader);
    void unBind() ;

//    void render();

private:
    MaterialProperty* m_Diffuse; //
    MaterialProperty* m_Ambient; //
    MaterialProperty* m_Specular; //
    MaterialProperty* m_Normal;
    MaterialProperty* m_Reflective;
    MaterialProperty* m_Emission;
    MaterialProperty* m_Transparent;
    MaterialProperty* m_Multiply;
    //        std::string m_Name;
    f32 m_Shininess;
    f32 m_FresnelExponent;
    f32 m_Transparency;
    bool m_LitPerPixel;
    bool m_DoubleSided;
    njliTransparencyMode m_TransparencyMode;
    njliCullMode m_CullMode;

    //        std::bitset<8> m_TextureIDReferences;

    //        u32 m_diffuseTexture2DUniform;
    //        u32 m_diffuseTextureCubeUniform;
    //        u32 m_ambientTexture2DUniform;
    //        u32 m_ambientTextureCubeUniform;
    //        u32 m_specularTexture2DUniform;
    //        u32 m_specularTextureCubeUniform;
    //        u32 m_normalTexture2DUniform;
    //        u32 m_normalTextureCubeUniform;
    //        u32 m_reflectiveTexture2DUniform;
    //        u32 m_reflectiveTextureCubeUniform;
    //        u32 m_emissionTexture2DUniform;
    //        u32 m_emissionTextureCubeUniform;
    //        u32 m_transparentTexture2DUniform;
    //        u32 m_transparentTextureCubeUniform;
    //        u32 m_multiplyTexture2DUniform;
    //        u32 m_multiplyTextureCubeUniform;
    //
    //        u32 m_isDiffuseTexture2D;
    //        u32 m_isDiffuseTextureCube;
    //        u32 m_isAmbientTexture2D;
    //        u32 m_isAmbientTextureCube;
    //        u32 m_isSpecularTexture2D;
    //        u32 m_isSpecularTextureCube;
    //        u32 m_isNormalTexture2D;
    //        u32 m_isNormalTextureCube;
    //        u32 m_isReflectiveTexture2D;
    //        u32 m_isReflectiveTextureCube;
    //        u32 m_isEmissionTexture2D;
    //        u32 m_isEmissionTextureCube;
    //        u32 m_isTransparentTexture2D;
    //        u32 m_isTransparentTextureCube;
    //        u32 m_isMultiplyTexture2D;
    //        u32 m_isMultiplyTextureCube;
};
}

#endif /* defined(__JLIGameEngineTest__Material__) */
