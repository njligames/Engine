//
//  LabelHUD.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "LabelHUD.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "LabelHUDBuilder.h"
#include "GLPlatform.h"
#include "WorldHUD.h"
#include "Log.h"
#define TAG "LabelHUD.cpp"
#include "btVector2.h"
#include "btVector3.h"
#include "SpriteFrameAtlas.h"
#define FORMATSTRING "{\"njli::LabelHUD\":[]}"
#include "btPrint.h"

namespace njli
{
    LabelHUD::LabelHUD():
    AbstractFactoryObject(this),
    m_fontSize(48),
    m_fontFace("sans"),
    m_fillColor(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_position(new btVector2(0.0f, getHeight())),
    m_dimensions(new btVector2(280.0f, 20.0f)),
    m_text("I love my wife. She is the bomb digaty")
    {
//        m_FBO = njli::World::getInstance()->getWorldHUD()->createFBO(512, 512, NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
    }
    
    LabelHUD::LabelHUD(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_fontSize(128),
    m_fontFace("sans"),
    m_fillColor(new btVector4(1.0f, 0.0f, 0.0f, 1.0f)),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_position(new btVector2(0.0f, getHeight())),
    m_dimensions(new btVector2(280.0f, 20.0f)),
    m_text("EMPTY")
    {
//        m_FBO = njli::World::getInstance()->getWorldHUD()->createFBO(512, 512, NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
    }
    
    LabelHUD::LabelHUD(const LabelHUD &copy):
    AbstractFactoryObject(this),
    m_fontSize(128),
    m_fontFace("sans"),
    m_fillColor(new btVector4(1.0f, 0.0f, 0.0f, 1.0f)),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_position(new btVector2(0.0f, getHeight())),
    m_dimensions(new btVector2(280.0f, 20.0f)),
    m_text("EMPTY")
    {
//        m_FBO = njli::World::getInstance()->getWorldHUD()->createFBO(512, 512, NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
    }
    
    LabelHUD::~LabelHUD()
    {
//        njli::World::getInstance()->getWorldHUD()->destroyFBO(m_FBO);
        delete m_dimensions;m_dimensions=NULL;
        delete m_position;m_position=NULL;
        delete m_fillColor;m_fillColor=NULL;
    }
    
    LabelHUD &LabelHUD::operator=(const LabelHUD &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    void LabelHUD::renderFunction(Camera *camera)
    {   
        nvgBeginFrame(World::getInstance()->getWorldHUD()->getContext(),
                      getWidth(),
                      getHeight(),
                      getAspectRatio());
        
        f32 w = m_dimensions->x();
        f32 h = m_dimensions->y();
        f32 x = m_position->x();
        f32 y = getHeight() - m_position->y() - h;
        
        njli::World::getInstance()->getWorldHUD()->fontSize(m_fontSize);
        njli::World::getInstance()->getWorldHUD()->fontFace(m_fontFace.c_str());
        njli::World::getInstance()->getWorldHUD()->fillColor(*m_fillColor);
        njli::World::getInstance()->getWorldHUD()->textAlign((njli::njliHUDAlign)m_align);
        njli::World::getInstance()->getWorldHUD()->text(x, y, m_text.c_str());
        
        nvgEndFrame(World::getInstance()->getWorldHUD()->getContext());
        
    }
    
    s32	LabelHUD::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void LabelHUD::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *LabelHUD::getClassName()const
    {
        return "LabelHUD";
    }
    
    s32 LabelHUD::getType()const
    {
        return JLI_OBJECT_TYPE_LabelHUD;
    }
    
    LabelHUD::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    LabelHUD **LabelHUD::createArray(const u32 size)
    {
        return (LabelHUD**)World::getInstance()->getWorldFactory()->createArray(LabelHUD::type(), size);
    }
    
    void LabelHUD::destroyArray(LabelHUD **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    LabelHUD *LabelHUD::create()
    {
        return dynamic_cast<LabelHUD*>(World::getInstance()->getWorldFactory()->create(LabelHUD::type()));
    }
    
    LabelHUD *LabelHUD::create(const LabelHUDBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<LabelHUD*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    LabelHUD *LabelHUD::clone(const LabelHUD &object)
    {
        return dynamic_cast<LabelHUD*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    LabelHUD *LabelHUD::copy(const LabelHUD &object)
    {
        return dynamic_cast<LabelHUD*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void LabelHUD::destroy(LabelHUD *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void LabelHUD::load(LabelHUD &object, lua_State *L, int index)
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
                LabelHUD::load(object, L, -2);
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
    
    u32 LabelHUD::type()
    {
        return JLI_OBJECT_TYPE_LabelHUD;
    }
    
    void LabelHUD::setFontSize(f32 size)
    {
        m_fontSize = size;
    }
    
    f32 LabelHUD::getFontSize()const
    {
        return m_fontSize;
    }
    
    void LabelHUD::setFontFace(const char *fontFace)
    {
        m_fontFace = fontFace;
    }
    
    const char *LabelHUD::getFontFace()const
    {
        return m_fontFace.c_str();
    }
    
    void LabelHUD::setFillColor(const btVector4 &color)
    {
        *m_fillColor = color;
    }
    
    const btVector4 &LabelHUD::getFillColor()const
    {
        return *m_fillColor;
    }
    
    void LabelHUD::setAlign(s32 align)
    {
        m_align = align;
    }
    
    s32 LabelHUD::getAlign()const
    {
        return m_align;
    }
    
    void LabelHUD::setPosition(const btVector2 &pos)
    {
        *m_position = pos;
    }
    
    const btVector2 &LabelHUD::getPosition()const
    {
        return *m_position;
    }
    
    void LabelHUD::setText(const char *text)
    {
        m_text = text;
    }
    
    const char *LabelHUD::getText()const
    {
        return m_text.c_str();
    }
}
