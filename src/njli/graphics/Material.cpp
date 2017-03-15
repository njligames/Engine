//
//  Material.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Material.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "MaterialBuilder.h"
#include "MaterialProperty.h"
#include "ShaderProgram.h"
#define FORMATSTRING "{\"njli::Material\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    Material::Material():
    AbstractFactoryObject(this),
    m_Diffuse(MaterialProperty::create()),
    m_Ambient(MaterialProperty::create()),
    m_Specular(MaterialProperty::create()),
    m_Normal(MaterialProperty::create()),
    m_Reflective(MaterialProperty::create()),
    m_Emission(MaterialProperty::create()),
    m_Transparent(MaterialProperty::create()),
    m_Multiply(MaterialProperty::create()),
//    m_Name("MyMaterial"),
    m_Shininess(1.0f),
    m_FresnelExponent(1.0f),
    m_Transparency(1.0f),
    m_LitPerPixel(true),
    m_DoubleSided(false),
    m_TransparencyMode(JLI_TRANSPARENCY_AlphaOne),
    m_CullMode(JLI_CULLMODE_Front)
    {
        addChild(m_Multiply);
        addChild(m_Transparent);
        addChild(m_Emission);
        addChild(m_Reflective);
        addChild(m_Normal);
        addChild(m_Specular);
        addChild(m_Ambient);
        addChild(m_Diffuse);
        
//        m_Diffuse->loadGPU();
//        m_Ambient->loadGPU();
//        m_Specular->loadGPU();
//        m_Normal->loadGPU();
//        m_Reflective->loadGPU();
//        m_Emission->loadGPU();
//        m_Transparent->loadGPU();
//        m_Multiply->loadGPU();
        
        
//        m_TextureIDReferences.reset();
    }
    
    Material::Material(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_Diffuse(MaterialProperty::create()),
    m_Ambient(MaterialProperty::create()),
    m_Specular(MaterialProperty::create()),
    m_Normal(MaterialProperty::create()),
    m_Reflective(MaterialProperty::create()),
    m_Emission(MaterialProperty::create()),
    m_Transparent(MaterialProperty::create()),
    m_Multiply(MaterialProperty::create()),
//    m_Name("MyMaterial"),
    m_Shininess(1.0f),
    m_FresnelExponent(1.0f),
    m_Transparency(1.0f),
    m_LitPerPixel(true),
    m_DoubleSided(false),
    m_TransparencyMode(JLI_TRANSPARENCY_AlphaOne),
    m_CullMode(JLI_CULLMODE_Front)
    {
        addChild(m_Multiply);
        addChild(m_Transparent);
        addChild(m_Emission);
        addChild(m_Reflective);
        addChild(m_Normal);
        addChild(m_Specular);
        addChild(m_Ambient);
        addChild(m_Diffuse);
        
//        m_Diffuse->loadGPU();
//        m_Ambient->loadGPU();
//        m_Specular->loadGPU();
//        m_Normal->loadGPU();
//        m_Reflective->loadGPU();
//        m_Emission->loadGPU();
//        m_Transparent->loadGPU();
//        m_Multiply->loadGPU();
        
//        m_TextureIDReferences.reset();
    }
    
    Material::Material(const Material &copy):
    AbstractFactoryObject(this),
    m_Diffuse(MaterialProperty::clone(*(copy.m_Diffuse))),
    m_Ambient(MaterialProperty::clone(*(copy.m_Ambient))),
    m_Specular(MaterialProperty::clone(*(copy.m_Specular))),
    m_Normal(MaterialProperty::clone(*(copy.m_Normal))),
    m_Reflective(MaterialProperty::clone(*(copy.m_Reflective))),
    m_Emission(MaterialProperty::clone(*(copy.m_Emission))),
    m_Transparent(MaterialProperty::clone(*(copy.m_Transparent))),
    m_Multiply(MaterialProperty::clone(*(copy.m_Multiply))),
//    m_Name(copy.m_Name + " copy"),
    m_Shininess(copy.m_Shininess),
    m_FresnelExponent(copy.m_FresnelExponent),
    m_Transparency(copy.m_Transparency),
    m_LitPerPixel(copy.m_LitPerPixel),
    m_DoubleSided(copy.m_DoubleSided),
    m_TransparencyMode(copy.m_TransparencyMode),
    m_CullMode(copy.m_CullMode)
    {
        addChild(m_Multiply);
        addChild(m_Transparent);
        addChild(m_Emission);
        addChild(m_Reflective);
        addChild(m_Normal);
        addChild(m_Specular);
        addChild(m_Ambient);
        addChild(m_Diffuse);
        
//        m_Diffuse->loadGPU();
//        m_Ambient->loadGPU();
//        m_Specular->loadGPU();
//        m_Normal->loadGPU();
//        m_Reflective->loadGPU();
//        m_Emission->loadGPU();
//        m_Transparent->loadGPU();
//        m_Multiply->loadGPU();
        
//        m_TextureIDReferences.reset();
    }
    
    Material::~Material()
    {
//        removeChild(m_Multiply);
//        removeChild(m_Transparent);
//        removeChild(m_Emission);
//        removeChild(m_Reflective);
//        removeChild(m_Normal);
//        removeChild(m_Specular);
//        removeChild(m_Ambient);
//        removeChild(m_Diffuse);
        
        
    }
    
    Material &Material::operator=(const Material &rhs)
    {
        if(this != &rhs)
        {
            MaterialProperty::destroy(m_Multiply);
            MaterialProperty::destroy(m_Transparent);
            MaterialProperty::destroy(m_Emission);
            MaterialProperty::destroy(m_Reflective);
            MaterialProperty::destroy(m_Normal);
            MaterialProperty::destroy(m_Specular);
            MaterialProperty::destroy(m_Ambient);
            MaterialProperty::destroy(m_Diffuse);
            
            m_Diffuse = MaterialProperty::clone(*(rhs.m_Diffuse));
            m_Ambient = MaterialProperty::clone(*(rhs.m_Ambient));
            m_Specular = MaterialProperty::clone(*(rhs.m_Specular));
            m_Normal = MaterialProperty::clone(*(rhs.m_Normal));
            m_Reflective = MaterialProperty::clone(*(rhs.m_Reflective));
            m_Emission = MaterialProperty::clone(*(rhs.m_Emission));
            m_Transparent = MaterialProperty::clone(*(rhs.m_Transparent));
            m_Multiply = MaterialProperty::clone(*(rhs.m_Multiply));
            
            addChild(m_Multiply);
            addChild(m_Transparent);
            addChild(m_Emission);
            addChild(m_Reflective);
            addChild(m_Normal);
            addChild(m_Specular);
            addChild(m_Ambient);
            addChild(m_Diffuse);
            
//            setName(rhs.m_Name.c_str());
            setShininess(rhs.m_Shininess);
            setFresnelExponenet(rhs.m_FresnelExponent);
            setTransparency(rhs.m_Transparency);
            enableLitPerPixel(rhs.m_LitPerPixel);
            enableDoubleSided(rhs.m_DoubleSided);
            setTransparencyMode(rhs.m_TransparencyMode);
            setCullMode(rhs.m_CullMode);
        }
        return *this;
    }
    
    s32	Material::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Material::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Material::getClassName()const
    {
        return "Material";
    }
    
    s32 Material::getType()const
    {
        return Material::type();
    }
    
    Material::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Material **Material::createArray(const u32 size)
    {
        return (Material**)World::getInstance()->getWorldFactory()->createArray(Material::type(), size);
    }
    
    void Material::destroyArray(Material **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Material *Material::create()
    {
        return dynamic_cast<Material*>(World::getInstance()->getWorldFactory()->create(Material::type()));
    }
    
    Material *Material::create(const MaterialBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Material*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Material *Material::clone(const Material &object)
    {
        return dynamic_cast<Material*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Material *Material::copy(const Material &object)
    {
        return dynamic_cast<Material*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Material::destroy(Material *object)
    {
        if(object)
        {
            MaterialProperty *m = NULL;
            
            m = object->getMultiply();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeMultiply();
            
            m = object->getTransparent();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeTransparent();
            
            m = object->getEmission();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeEmission();
            
            m = object->getReflective();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeReflective();
            
            m = object->getNormal();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeNormal();
            
            m = object->getSpecular();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeSpecular();
            
            m = object->getAmbient();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeAmbient();
            
            m = object->getDiffuse();
            if(World::getInstance()->getWorldFactory()->has(m))
                MaterialProperty::destroy(m);
            object->removeDiffuse();
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
        
    }
    
    void Material::load(Material &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
        {
            // stack now contains: -1 => value; -2 => key; -3 => table
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                Material::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
//                    swig_lua_userdata *usr;
//                    swig_type_info *type;
//                    assert(lua_isuserdata(L,index));
//                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
//                    type = usr->type;
//                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
//                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 Material::type()
    {
        return JLI_OBJECT_TYPE_Material;
    }
    
    MaterialProperty *Material::getDiffuse()
    {
        s32 idx = getChildIndex(m_Diffuse);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    MaterialProperty *Material::getAmbient()
    {
        s32 idx = getChildIndex(m_Ambient);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    MaterialProperty *Material::getSpecular()
    {
        s32 idx = getChildIndex(m_Specular);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    MaterialProperty *Material::getNormal()
    {
        s32 idx = getChildIndex(m_Normal);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    MaterialProperty *Material::getReflective()
    {
        s32 idx = getChildIndex(m_Reflective);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    MaterialProperty *Material::getEmission()
    {
        s32 idx = getChildIndex(m_Emission);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    MaterialProperty *Material::getTransparent()
    {
        s32 idx = getChildIndex(m_Transparent);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    MaterialProperty *Material::getMultiply()
    {
        s32 idx = getChildIndex(m_Multiply);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<MaterialProperty*>(getChild(idx)));
            return dynamic_cast<MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getDiffuse()const
    {
        s32 idx = getChildIndex(m_Diffuse);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getAmbient()const
    {
        s32 idx = getChildIndex(m_Ambient);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getSpecular()const
    {
        s32 idx = getChildIndex(m_Specular);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getNormal()const
    {
        s32 idx = getChildIndex(m_Normal);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getReflective()const
    {
        s32 idx = getChildIndex(m_Reflective);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getEmission()const
    {
        s32 idx = getChildIndex(m_Emission);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getTransparent()const
    {
        s32 idx = getChildIndex(m_Transparent);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    const MaterialProperty *Material::getMultiply()const
    {
        s32 idx = getChildIndex(m_Multiply);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const MaterialProperty*>(getChild(idx)));
            return dynamic_cast<const MaterialProperty*>(getChild(idx));
        }
        return NULL;
    }
    
    void Material::setShininess(const f32 val)
    {
        DEBUG_ASSERT(val >= 0 && val <= 1.0f);
        m_Shininess = val;
    }
    
    f32 Material::getShininess()const
    {
        return m_Shininess;
    }
    
    void Material::setFresnelExponenet(const f32 val)
    {
        DEBUG_ASSERT(val >= 0 && val <= 1.0f);
        m_FresnelExponent = val;
    }
    
    f32 Material::getFresnelExponenet()const
    {
        return m_FresnelExponent;
    }
    
    void Material::setTransparency(const f32 val)
    {
        DEBUG_ASSERT(val >= 0 && val <= 1.0f);
        m_Transparency = val;
    }
    
    f32 Material::getTransparency()const
    {
        return m_Transparency;
    }
    
    void Material::enableLitPerPixel(const bool enable)
    {
        m_LitPerPixel = enable;
    }
    
    bool Material::isLitPerPixel()const
    {
        return m_LitPerPixel;
    }
    
    void Material::enableDoubleSided(const bool enable)
    {
        m_DoubleSided = enable;
    }
    
    bool Material::isDoubleSided()const
    {
        return m_DoubleSided;
    }
    
    void Material::setTransparencyMode(const njliTransparencyMode mode)
    {
        DEBUG_ASSERT(mode > JLI_TRANSPARENCY_NONE && mode < JLI_TRANSPARENCY_MAX);
        m_TransparencyMode = mode;
    }
    
    njliTransparencyMode Material::getTransparencyMode()const
    {
        return m_TransparencyMode;
    }
    
    void Material::setCullMode(const njliCullMode mode)
    {
        DEBUG_ASSERT(mode > JLI_CULLMODE_NONE && mode < JLI_CULLMODE_MAX);
        m_CullMode = mode;
    }
    
    njliCullMode Material::getCullMode()const
    {
        return m_CullMode;
    }
    
    Geometry *Material::getParent()
    {
        return dynamic_cast<Geometry*>(AbstractDecorator::getParent());
    }
    
    const Geometry *Material::getParent()const
    {
        return dynamic_cast<const Geometry*>(AbstractDecorator::getParent());
    }
    
    bool Material::hasOpacity()const
    {
        const MaterialProperty *d = getDiffuse();
        const MaterialProperty *a = getAmbient();
        const MaterialProperty *s = getSpecular();
        const MaterialProperty *n = getNormal();
        const MaterialProperty *r = getReflective();
        const MaterialProperty *e = getEmission();
        const MaterialProperty *t = getTransparent();
        const MaterialProperty *m = getMultiply();
        
        return d->hasOpacity() ||
        a->hasOpacity() ||
        s->hasOpacity() ||
        n->hasOpacity() ||
        r->hasOpacity() ||
        e->hasOpacity() ||
        t->hasOpacity() ||
        m->hasOpacity();
        
    }
    
//    void Material::addTextureIDReference(MaterialProperty *materialProperty)
//    {
//        DEBUG_ASSERT(! m_TextureIDReferences.all());
//        
//        for (s32 i = 0; i < m_TextureIDReferences.size(); ++i)
//        {
//            if (!m_TextureIDReferences[i])
//            {
//                m_TextureIDReferences[i] = 1;
//                //!!!: TODO: set the texture index
//                materialProperty->setTextureIndex(i);
//                return;
//            }
//        }
//    }
//    void Material::addTextureIDReference(MaterialProperty *materialProperty, AbstractFrameBufferObject *fbo)
//    {
//        DEBUG_ASSERT(! m_TextureIDReferences.all());
//        
//        DEBUG_ASSERT(m_TextureIDReferences[fbo->getTextureID()] == 0);
//        
//        MaterialProperty::addReference(materialProperty);
////        materialProperty->setTextureIndex(fbo->getTextureID());
//    }
//    void Material::removeTextureIDReference(MaterialProperty *materialProperty)
//    {
//        s64 index = materialProperty->getTextureIndex();
//        if(index >=0 && index < m_TextureIDReferences.size())
//        {
//            m_TextureIDReferences[index] = 0;
//            //            hideGeometry(node);
//        }
//    }
    
    
    
    
    
    
    
    
    void Material::removeDiffuse()
    {
        MaterialProperty *mp = getDiffuse();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Diffuse = NULL;
        }
    }
    
    void Material::removeAmbient()
    {
        MaterialProperty *mp = getAmbient();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Ambient = NULL;
        }
    }
    
    void Material::removeSpecular()
    {
        MaterialProperty *mp = getSpecular();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Specular = NULL;
        }
    }
    
    void Material::removeNormal()
    {
        MaterialProperty *mp = getNormal();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Normal = NULL;
        }
    }
    
    void Material::removeReflective()
    {
        MaterialProperty *mp = getReflective();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Reflective = NULL;
        }
    }
    
    void Material::removeEmission()
    {
        MaterialProperty *mp = getEmission();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Emission = NULL;
        }
    }
    
    void Material::removeTransparent()
    {
        MaterialProperty *mp = getTransparent();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Transparent = NULL;
        }
    }
    
    void Material::removeMultiply()
    {
        MaterialProperty *mp = getMultiply();
        if (mp != NULL)
        {
            removeChild(mp);
            m_Multiply = NULL;
        }
    }
    
    
    
    
    
    void Material::bind(ShaderProgram *shader)
    {
        DEBUG_ASSERT(shader);
        
        if(getDiffuse()->bind(shader))
            shader->setUniformValue("diffuseTexture2D", getDiffuse()->getTextureIndex());
        
//        getAmbient()->bind(shader, "Ambient");
//        getSpecular()->bind(shader, "Specular");
//        getNormal()->bind(shader, "Normal");
//        getReflective()->bind(shader, "Reflective");
//        getEmission()->bind(shader, "Emission");
//        getTransparent()->bind(shader, "Transparent");
//        getMultiply()->bind(shader, "Multiply");
    }
    void Material::unBind()
    {
//        getMultiply()->unBind();
//        getTransparent()->unBind();
//        getEmission()->unBind();
//        getReflective()->unBind();
//        getNormal()->unBind();
//        getSpecular()->unBind();
//        getAmbient()->unBind();
        getDiffuse()->unBind();
    }
    
//    void Material::render()
//    {
//        getDiffuse()->render();
//    }
}
