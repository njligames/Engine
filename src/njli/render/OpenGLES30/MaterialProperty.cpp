//
//  MaterialProperty.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "MaterialProperty.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "MaterialPropertyBuilder.h"
#include "btTransform.h"
#include "Image.h"
#include "GLPlatform.h"
#include "ShaderProgram.h"
#include "AbstractFrameBufferObject.h"
#include "Material.h"

#define FORMATSTRING "{\"njli::MaterialProperty\":[]}"
#include "btPrint.h"

#define NUMBER_OF_IMAGES (6)

/*
 Skybox images:
 http://www.custommapmakers.org/skyboxes.php
 */
namespace njli
{

    
    MaterialProperty::MaterialProperty():
    AbstractFactoryObject(this),
    m_textureID(-1),
    m_minVal(JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR),
    m_magVal(JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_LINEAR),
    m_sWrap(JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE),
    m_tWrap(JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE),
    m_textureType(GL_TEXTURE_2D),
    m_TextureTransform(new btTransform(btTransform::getIdentity())),
    m_TextureIndex(-1),
    m_Width(0),
    m_Height(0),
    m_NumberOfComponents(0),
    m_2DUniform(-1),
    m_CubeUniform(-1),
    m_is2DUniform(-1),
    m_isCubeUniform(-1),
    m_AbstractFrameBufferObject(NULL),
    m_hasOpacity(false),
    m_njliLoadGPUType(JLI_LOAD_GPU_TYPE_NONE),
    m_loadGPU_fbo(NULL),
    m_loadGPU_images(Image::createArray(NUMBER_OF_IMAGES))
    {
        enableRenderObject();
        
        char buffer[1024];
        sprintf(buffer, "%s's Image", getName());
        
        for (s32 i = 0; i < NUMBER_OF_IMAGES; ++i)
        {
            Image *img = m_loadGPU_images[i];
            img->setName(buffer);
            addChild(img);
        }
    }
    
    MaterialProperty::MaterialProperty(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_textureID(-1),
    m_minVal(JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR),
    m_magVal(JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_LINEAR),
    m_sWrap(JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE),
    m_tWrap(JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE),
    m_textureType(GL_TEXTURE_2D),
    m_TextureTransform(new btTransform(btTransform::getIdentity())),
    m_TextureIndex(-1),
    m_Width(0),
    m_Height(0),
    m_NumberOfComponents(0),
    m_2DUniform(-1),
    m_CubeUniform(-1),
    m_is2DUniform(-1),
    m_isCubeUniform(-1),
    m_AbstractFrameBufferObject(NULL),
    m_hasOpacity(false),
    m_njliLoadGPUType(JLI_LOAD_GPU_TYPE_NONE),
    m_loadGPU_fbo(NULL),
    m_loadGPU_images(Image::createArray(NUMBER_OF_IMAGES))
    {
        enableRenderObject();
        
        char buffer[1024];
        sprintf(buffer, "%s's Image", getName());
        
        for (s32 i = 0; i < NUMBER_OF_IMAGES; ++i)
        {
            Image *img = m_loadGPU_images[i];
            img->setName(buffer);
            addChild(img);
        }
    }
    
    MaterialProperty::MaterialProperty(const MaterialProperty &copy):
    AbstractFactoryObject(this),
    m_textureID(-1),
    m_minVal(JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR),
    m_magVal(JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_LINEAR),
    m_sWrap(JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE),
    m_tWrap(JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE),
    m_textureType(GL_TEXTURE_2D),
    m_TextureTransform(new btTransform(*(copy.m_TextureTransform))),
    m_TextureIndex(-1),
    m_Width(0),
    m_Height(0),
    m_NumberOfComponents(0),
    m_2DUniform(-1),
    m_CubeUniform(-1),
    m_is2DUniform(-1),
    m_isCubeUniform(-1),
    m_AbstractFrameBufferObject(NULL),
    m_hasOpacity(false),
    m_njliLoadGPUType(JLI_LOAD_GPU_TYPE_NONE),
    m_loadGPU_fbo(NULL),
    m_loadGPU_images(Image::createArray(NUMBER_OF_IMAGES))
    {
        enableRenderObject();
        
        char buffer[1024];
        sprintf(buffer, "%s's Image", getName());
        
        for (s32 i = 0; i < NUMBER_OF_IMAGES; ++i)
        {
            Image *img = m_loadGPU_images[i];
            img->setName(buffer);
            addChild(img);
        }
    }
    
    MaterialProperty::~MaterialProperty()
    {
        delete [] m_TextureTransform;
        m_TextureTransform=NULL;
        
        unLoadGPU();
    }
    
    MaterialProperty &MaterialProperty::operator=(const MaterialProperty &rhs)
    {
        if(this != &rhs)
        {
            //TODO: Implement...
        }
        return *this;
    }
    
    s32	MaterialProperty::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void MaterialProperty::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *MaterialProperty::getClassName()const
    {
        return "MaterialProperty";
    }
    
    s32 MaterialProperty::getType()const
    {
        return MaterialProperty::type();
    }
    
    MaterialProperty::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    MaterialProperty **MaterialProperty::createArray(const u32 size)
    {
        return (MaterialProperty**)World::getInstance()->getWorldFactory()->createArray(MaterialProperty::type(), size);
    }
    
    void MaterialProperty::destroyArray(MaterialProperty **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    MaterialProperty *MaterialProperty::create()
    {
        return dynamic_cast<MaterialProperty*>(World::getInstance()->getWorldFactory()->create(MaterialProperty::type()));
    }
    
    MaterialProperty *MaterialProperty::create(const MaterialPropertyBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<MaterialProperty*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    MaterialProperty *MaterialProperty::clone(const MaterialProperty &object)
    {
        return dynamic_cast<MaterialProperty*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    MaterialProperty *MaterialProperty::copy(const MaterialProperty &object)
    {
        return dynamic_cast<MaterialProperty*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void MaterialProperty::destroy(MaterialProperty *object)
    {
        if(object)
        {
            for (s32 i = 0; i < NUMBER_OF_IMAGES; ++i)
            {
                Image *img = object->m_loadGPU_images[i];
                object->removeChild(img);
                Image::destroy(img);
            }
            Image::destroyArray(object->m_loadGPU_images);
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void MaterialProperty::load(MaterialProperty &object, lua_State *L, int index)
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
                MaterialProperty::load(object, L, -2);
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
    
    u32 MaterialProperty::type()
    {
        return JLI_OBJECT_TYPE_MaterialProperty;
    }
    
    Material *MaterialProperty::getParent()
    {
        return dynamic_cast<Material*>(AbstractDecorator::getParent());
    }
    
    const Material *MaterialProperty::getParent()const
    {
        return dynamic_cast<const Material*>(AbstractDecorator::getParent());
    }
    
    void MaterialProperty::setMinificationFilter(njliTextureMinificationValueType val)
    {
        DEBUG_ASSERT(val > JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NONE && val < JLI_TEXTURE_MINIFICATION_VALUE_TYPE_MAX);
        m_minVal = val;
    }
    
    njliTextureMinificationValueType MaterialProperty::getMinificationFilter()const
    {
        return m_minVal;
    }
    
    void MaterialProperty::setMagnificationFilter(njliTextureMagnificationValueType val)
    {
        DEBUG_ASSERT(val > JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_NONE && val < JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_MAX);
        m_magVal = val;
    }
    
    njliTextureMagnificationValueType MaterialProperty::getMagnificationFilter()const
    {
        return m_magVal;
    }
    
    void MaterialProperty::setWrapS(njliTextureWrapType val)
    {
        DEBUG_ASSERT(val > JLI_TEXTURE_WRAP_TYPE_NONE && val < JLI_TEXTURE_WRAP_TYPE_MAX);
        m_sWrap = val;
    }
    
    njliTextureWrapType MaterialProperty::getWrapS()const
    {
        return m_sWrap;
    }
    
    void MaterialProperty::setWrapT(njliTextureWrapType val)
    {
        DEBUG_ASSERT(val > JLI_TEXTURE_WRAP_TYPE_NONE && val < JLI_TEXTURE_WRAP_TYPE_MAX);
        m_tWrap = val;
    }
    
    njliTextureWrapType MaterialProperty::getWrapT()const
    {
        return m_tWrap;
    }
    
    void MaterialProperty::loadGPU()
    {
        m_njliLoadGPUType = JLI_LOAD_GPU_TYPE_2D_EMPTY;
        
        loadGPU_Internal();
    }
    void MaterialProperty::loadGPU(const Image &img)
    {
        m_njliLoadGPUType = JLI_LOAD_GPU_TYPE_2D;
        *m_loadGPU_images[0] = img;
        
        loadGPU_Internal(*m_loadGPU_images[0]);
    }
    
    void MaterialProperty::loadGPU(const Image &negativeX,
                          const Image &negativeY,
                          const Image &negativeZ,
                          const Image &positiveX,
                          const Image &positiveY,
                          const Image &positiveZ)
    {
        m_njliLoadGPUType = JLI_LOAD_GPU_TYPE_CUBE;
        *m_loadGPU_images[0] = negativeX;
        *m_loadGPU_images[1] = negativeY;
        *m_loadGPU_images[2] = negativeZ;
        *m_loadGPU_images[3] = positiveX;
        *m_loadGPU_images[4] = positiveY;
        *m_loadGPU_images[5] = positiveZ;
        
        loadGPU_Internal(*m_loadGPU_images[0],
                         *m_loadGPU_images[1],
                         *m_loadGPU_images[2],
                         *m_loadGPU_images[3],
                         *m_loadGPU_images[4],
                         *m_loadGPU_images[5]);
    }
    
    void MaterialProperty::loadGPU(AbstractFrameBufferObject *fbo)
    {
        m_njliLoadGPUType = JLI_LOAD_GPU_TYPE_FBO;
        m_loadGPU_fbo = fbo;
        
        loadGPU_Internal(m_loadGPU_fbo);
    }
    
    void MaterialProperty::unLoadGPU()
    {
        if(-1 != m_textureID)
        {
            MaterialProperty::removeReference(this);
            
            glDeleteTextures(1, &m_textureID);
        }
        m_textureID = -1;
        m_AbstractFrameBufferObject = NULL;
    }
    
    void MaterialProperty::reLoadGPU(const Image &img, const btVector2 &offset)
    {
        DEBUG_ASSERT(m_textureType == GL_TEXTURE_2D);
        
        glActiveTexture(GL_TEXTURE0 + getTextureIndex());
        
        if(m_AbstractFrameBufferObject)
        {
            glBindTexture(m_textureType, m_AbstractFrameBufferObject->getTextureID());
        }
        else
        {
            // Bind to the texture that has been loaded for this particle system
            glBindTexture(m_textureType, m_textureID);
            
            loadProperties();
            
            reLoadTexImage2DInternal(img, GL_TEXTURE_2D, offset);
        }
        m_hasOpacity = img.hasAlpha();
        
    }
    
    void MaterialProperty::reLoadGPU(const Image &img, njliTextureCubeSides cubeSide, const btVector2 &offset)
    {
        DEBUG_ASSERT(m_textureType == GL_TEXTURE_CUBE_MAP);
        
        glActiveTexture(GL_TEXTURE0 + getTextureIndex());
        
        glBindTexture(m_textureType, m_textureID);
        
        loadProperties();
        
        switch (cubeSide) {
            case JLI_TEXTURECUBE_SIDE_NEGATIVE_X:
                reLoadTexImage2DInternal(img, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, offset);
                break;
            case JLI_TEXTURECUBE_SIDE_NEGATIVE_Y:
                reLoadTexImage2DInternal(img, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, offset);
                break;
            case JLI_TEXTURECUBE_SIDE_NEGATIVE_Z:
                reLoadTexImage2DInternal(img, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, offset);
                break;
            case JLI_TEXTURECUBE_SIDE_POSITIVE_X:
                reLoadTexImage2DInternal(img, GL_TEXTURE_CUBE_MAP_POSITIVE_X, offset);
                break;
            case JLI_TEXTURECUBE_SIDE_POSITIVE_Y:
                reLoadTexImage2DInternal(img, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, offset);
                break;
            case JLI_TEXTURECUBE_SIDE_POSITIVE_Z:
                reLoadTexImage2DInternal(img, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, offset);
                break;
                
            default:
                break;
        }
        m_hasOpacity = img.hasAlpha();
    }
    
    void MaterialProperty::setTextureTransform(const btTransform &transform)
    {
        *m_TextureTransform = transform;
    }
    
    const btTransform &MaterialProperty::getTextureTransform()const
    {
        return *m_TextureTransform;
    }
    
    u32 MaterialProperty::getWidth()const
    {
        return m_Width;
    }
    
    u32 MaterialProperty::getHeight()const
    {
        return m_Height;
    }
    
    bool MaterialProperty::isTextureCube()const
    {
        return m_textureType == GL_TEXTURE_CUBE_MAP;
    }
    
    bool MaterialProperty::isTexture2D()const
    {
        return m_textureType == GL_TEXTURE_2D;
    }
    
    bool MaterialProperty::hasOpacity()const
    {
        return m_hasOpacity;
    }
    
    u8 MaterialProperty::getTextureIndex()const
    {
        return m_TextureIndex;
    }
    
    void MaterialProperty::setTextureIndex(u8 textureIndex)
    {
//        DEBUG_ASSERT(textureIndex < 8);
        
        m_TextureIndex = textureIndex;
    }
    
    
    void MaterialProperty::bind(ShaderProgram *shader, const char *propertyName)
    {//https://www.opengl.org/wiki/Texture_Combiners
        DEBUG_ASSERT(shader);
        
        
        
        if(m_TextureIndex != 255)
            glActiveTexture(GL_TEXTURE0 + m_TextureIndex);
        
        if(m_AbstractFrameBufferObject)
        {
            glBindTexture(m_textureType, m_AbstractFrameBufferObject->getTextureID());
            return;
        }
        else if(m_textureID != -1)
        {
            char buffer[256];
            char property[256];
            strcpy(property, propertyName);
            
            // Bind to the texture that has been loaded for this particle system
            glBindTexture(m_textureType, m_textureID);
            
//            loadProperties();

            property[0] = property[0] + 32;
            sprintf(buffer, "%sTexture2D", property);
            m_2DUniform = shader->getUniformIndex(buffer);
            glUniform1i(m_2DUniform, getTextureIndex());DEBUG_GL_ERROR_PRINT("glUniform1i", "%d,%hhu",m_2DUniform,getTextureIndex());
        }
    }
    
    void MaterialProperty::unBind()const
    {
        if(m_textureID != -1)
        {
            glActiveTexture(GL_TEXTURE0 + getTextureIndex());
            // Bind to the texture that has been loaded for this particle system
            glBindTexture(m_textureType, 0);
        }
    }
    
    void MaterialProperty::loadTexImage2DInternal(const Image &img, s32 target)
    {
        GLint level = 0;
        GLint internalformat = GL_RGBA;
        m_Width = img.getWidth();
        m_Height = img.getHeight();
        m_NumberOfComponents = img.getNumberOfComponents();
        GLint border = 0;
        GLenum format = GL_RGBA;
        GLenum type = GL_UNSIGNED_BYTE;
        const GLvoid* pixels = (const GLvoid*)img.getDataRaw();
        GLsizei imageSize = img.getWidth() * img.getHeight() * img.getNumberOfComponents();
        
        switch(m_NumberOfComponents)
        {
            case 1:
            {
                internalformat = GL_LUMINANCE;
                format	= GL_LUMINANCE;
            }
                break;
                
            case 2:
            {
                internalformat = GL_LUMINANCE_ALPHA;
                format	= GL_LUMINANCE_ALPHA;
            }
                break;
            case 3:
            {
                internalformat = GL_RGB;
                format	= GL_RGB;
            }
                break;
            case 4:
            {
                internalformat = GL_RGBA;
                format	= GL_RGBA;
            }
                break;
        }
        
        glTexImage2D(target, level, internalformat, m_Width, m_Height, border, format, type, pixels);DEBUG_GL_ERROR_WRITE("glTexImage2D");
        
        if(isTexture2D())
        {
            glGenerateMipmap(target);DEBUG_GL_ERROR_WRITE("glGenerateMipmap");
        }
    }
    
    void MaterialProperty::reLoadTexImage2DInternal(const Image &img,
                                                    s32 target,
                                                    const btVector2 &offset)
    {
        GLint level = 0;
        GLint internalformat = GL_RGBA;
        GLint border = 0;
        GLenum format = GL_RGBA;
        GLenum type = GL_UNSIGNED_BYTE;
        const GLvoid* pixels = (const GLvoid*)img.getDataRaw();
        GLsizei imageSize = img.getWidth() * img.getHeight() * img.getNumberOfComponents();
        
        DEBUG_ASSERT(offset.x() + img.getWidth() < getWidth());
        DEBUG_ASSERT(offset.y() + img.getHeight() < getHeight());
        DEBUG_ASSERT(img.getNumberOfComponents() == m_NumberOfComponents);
        
        switch(m_NumberOfComponents)
        {
            case 1:
            {
                internalformat = GL_LUMINANCE;
                format	= GL_LUMINANCE;
            }
                break;
                
            case 2:
            {
                internalformat = GL_LUMINANCE_ALPHA;
                format	= GL_LUMINANCE_ALPHA;
            }
                break;
            case 3:
            {
                internalformat = GL_RGB;
                format	= GL_RGB;
            }
                break;
            case 4:
            {
                internalformat = GL_RGBA;
                format	= GL_RGBA;
            }
                break;
        }
        
        glTexSubImage2D(target, level, offset.x(), offset.y(), m_Width, m_Height, format, type, pixels);DEBUG_GL_ERROR_WRITE("glTexSubImage2D");
        
        glGenerateMipmap(target);DEBUG_GL_ERROR_WRITE("glGenerateMipmap");
        
        m_hasOpacity = img.hasAlpha();
    }
    
    void MaterialProperty::loadProperties()const
    {
        DEBUG_ASSERT(m_minVal > JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NONE && m_minVal < JLI_TEXTURE_MINIFICATION_VALUE_TYPE_MAX);
        DEBUG_ASSERT(m_magVal > JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_NONE && m_magVal < JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_MAX);
        DEBUG_ASSERT(m_tWrap > JLI_TEXTURE_WRAP_TYPE_NONE && m_tWrap < JLI_TEXTURE_WRAP_TYPE_MAX);
        DEBUG_ASSERT(m_sWrap > JLI_TEXTURE_WRAP_TYPE_NONE && m_sWrap < JLI_TEXTURE_WRAP_TYPE_MAX);
        
        switch (m_minVal) {
            case JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NEAREST:
                glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            case JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR:
                glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            case JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NEAREST_MIPMAP_NEAREST:
                glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            case JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NEAREST_MIPMAP_LINEAR:
                glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            case JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR_MIPMAP_NEAREST:
                glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            case JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR_MIPMAP_LINEAR:
                glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            default:
                DEBUG_ASSERT(false);
                break;
        }
        
        switch (m_magVal)
        {
            case JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_NEAREST:
                glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            case JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_LINEAR:
                glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);DEBUG_GL_ERROR_WRITE("glTexParameteri");
                break;
            default:
                DEBUG_ASSERT(false);
                break;
        }
        
        switch (m_sWrap) {
            case JLI_TEXTURE_WRAP_TYPE_REPEAT:
                glTexParameterf(m_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);DEBUG_GL_ERROR_WRITE("glTexParameterf");
                break;
            case JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE:
                glTexParameterf(m_textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);DEBUG_GL_ERROR_WRITE("glTexParameterf");
                break;
            case JLI_TEXTURE_WRAP_TYPE_MIRRORED_REPEAT:
                glTexParameterf(m_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);DEBUG_GL_ERROR_WRITE("glTexParameterf");
                break;
            default:
                DEBUG_ASSERT(false);
                break;
        }
        
        switch (m_tWrap) {
            case JLI_TEXTURE_WRAP_TYPE_REPEAT:
                glTexParameterf(m_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);DEBUG_GL_ERROR_WRITE("glTexParameterf");
                break;
            case JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE:
                glTexParameterf(m_textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);DEBUG_GL_ERROR_WRITE("glTexParameterf");
                break;
            case JLI_TEXTURE_WRAP_TYPE_MIRRORED_REPEAT:
                glTexParameterf(m_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);DEBUG_GL_ERROR_WRITE("glTexParameterf");
                break;
            default:
                DEBUG_ASSERT(false);
                break;
        }
    }
    
    void MaterialProperty::render()
    {
        if (m_njliLoadGPUType != JLI_LOAD_GPU_TYPE_NONE)
        {
            switch (m_njliLoadGPUType)
            {
                case JLI_LOAD_GPU_TYPE_2D:
                    loadGPU_Internal(*m_loadGPU_images[0]);
                    break;
                case JLI_LOAD_GPU_TYPE_2D_EMPTY:
                    loadGPU_Internal();
                    
                    break;
                case JLI_LOAD_GPU_TYPE_CUBE:
                    loadGPU_Internal(*m_loadGPU_images[0],
                                     *m_loadGPU_images[1],
                                     *m_loadGPU_images[2],
                                     *m_loadGPU_images[3],
                                     *m_loadGPU_images[4],
                                     *m_loadGPU_images[5]);
                    break;
                case JLI_LOAD_GPU_TYPE_FBO:
                    loadGPU_Internal(m_loadGPU_fbo);
                    break;
                    
                default:
                    break;
            }
            m_njliLoadGPUType = JLI_LOAD_GPU_TYPE_NONE;
        }
    }
    
#if defined(DEBUG) || defined (_DEBUG)
    u64 MaterialProperty::s_MaxTextureUnits = 0;
    u64 MaterialProperty::s_MaxTextureSize = 0;
#endif
    std::bitset<16> MaterialProperty::s_TextureIDReferences;
    
    void MaterialProperty::initReferences()
    {
#if defined(DEBUG) || defined (_DEBUG)
        GLint maxUnits[1];
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, maxUnits);
        s_MaxTextureUnits = maxUnits[0];
        
        GLint maxSize[1];
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, maxSize);
        s_MaxTextureSize = maxSize[0];
#endif
        
        s_TextureIDReferences.reset();
        
        u32 end = s_TextureIDReferences.size();
#if defined(DEBUG) || defined (_DEBUG)
        end = s_MaxTextureUnits;
#endif
//        for (s32 i = 0; i < end; ++i)
//        {
//            MaterialProperty *m = MaterialProperty::create();
//            m->loadGPU();
//            m->unLoadGPU();
//            MaterialProperty::destroy(m);
//        }
    }
    
    void MaterialProperty::addReference(MaterialProperty *property)
    {
        bool added = false;
        u32 end = s_TextureIDReferences.size();
#if defined(DEBUG) || defined (_DEBUG)
        end = s_MaxTextureUnits;
#endif
        for (s32 i = 0; i < end && !added; ++i)
        {
            if (false == s_TextureIDReferences[i])
            {
                s_TextureIDReferences[i] = 1;
                property->setTextureIndex(i);
                added = true;
            }
        }
        
//        std::string ids = s_TextureIDReferences.to_string();
//        DEBUG_LOG_V("", "add\t%s", ids.c_str());
        DEBUG_ASSERT(added);
    }
    
    void MaterialProperty::removeReference(MaterialProperty *property)
    {
        s32 idx = property->getTextureIndex();
        
        if(hasReference(property))
            s_TextureIDReferences[idx] = 0;
        
//        std::string ids = s_TextureIDReferences.to_string();
//        DEBUG_LOG_V("", "remove\t%s", ids.c_str());
        
        property->setTextureIndex(-1);
    }
    
    bool MaterialProperty::hasReference(MaterialProperty *property)
    {
        s32 idx = property->getTextureIndex();
        return (idx != -1);
    }
    
    
    
    
    
    void MaterialProperty::loadGPU_Internal()
    {
        Image *img = Image::create();
        img->generate(2, 2, 4);
        loadGPU_Internal(*img);
        Image::destroy(img);
    }
    
    void MaterialProperty::loadGPU_Internal(const Image &img)
    {
        unLoadGPU();
        
        MaterialProperty::addReference(this);
        
        m_textureType = GL_TEXTURE_2D;
        
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
//        glActiveTexture(GL_TEXTURE0 + getTextureIndex());DEBUG_GL_ERROR_WRITE("glActiveTexture");
        
        glGenTextures ( 1, &m_textureID );DEBUG_GL_ERROR_WRITE("glGenTextures");
        
        glBindTexture(m_textureType, m_textureID);DEBUG_GL_ERROR_WRITE("glBindTexture");
        
        
        
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        loadTexImage2DInternal(img, GL_TEXTURE_2D);
        
        loadProperties();
        
        m_hasOpacity = img.hasAlpha();
    }
    
    void MaterialProperty::loadGPU_Internal(const Image &negativeX,
                                   const Image &negativeY,
                                   const Image &negativeZ,
                                   const Image &positiveX,
                                   const Image &positiveY,
                                   const Image &positiveZ)
    {
        //http://opengles-book-samples.googlecode.com/svn/trunk/LinuxX11/Chapter_9/Simple_TextureCubemap/Simple_TextureCubemap.c
        
        unLoadGPU();
        
        MaterialProperty::addReference(this);
        
        m_textureType = GL_TEXTURE_CUBE_MAP;
        
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        DEBUG_ASSERT(-1 == m_textureID);
        
        glActiveTexture(GL_TEXTURE0 + getTextureIndex());
        
        glGenTextures ( 1, &m_textureID );
        
        glBindTexture(m_textureType, m_textureID);
        
        loadTexImage2DInternal(negativeX, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        loadTexImage2DInternal(negativeY, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        loadTexImage2DInternal(negativeZ, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
        loadTexImage2DInternal(positiveX, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        loadTexImage2DInternal(positiveY, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        loadTexImage2DInternal(positiveZ, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        
        loadProperties();
        
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        
        m_hasOpacity = negativeX.hasAlpha() ||
        negativeY.hasAlpha() ||
        negativeZ.hasAlpha() ||
        positiveX.hasAlpha() ||
        positiveY.hasAlpha() ||
        positiveZ.hasAlpha();
    }
    
    void MaterialProperty::loadGPU_Internal(AbstractFrameBufferObject *fbo)
    {
        DEBUG_ASSERT(fbo);
        
        unLoadGPU();
        
        MaterialProperty::addReference(this);
        
        m_AbstractFrameBufferObject = fbo;
        
        m_textureType = GL_TEXTURE_2D;
    }
}
