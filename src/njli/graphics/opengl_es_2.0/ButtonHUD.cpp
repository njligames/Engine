//
//  ButtonHUD.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "ButtonHUD.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "ButtonHUDBuilder.h"
#include "GLPlatform.h"
#include "WorldHUD.h"
#include "Log.h"
#define TAG "ButtonHUD.cpp"
#include "SpriteFrameAtlas.h"

#define FORMATSTRING "{\"njli::ButtonHUD\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    ButtonHUD::ButtonHUD():
    AbstractFactoryObject(this),
    m_fontSize(20*3),
    m_fontFace("sans-jp"),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_position(new btVector2(0.0f, 0)),
    m_dimensions(new btVector2(140*3, 28*3)),
    m_text("私はガラスを食べられます。それは私を傷つけません。"),
    m_fillColor(new btVector4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_borderColor(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    m_textColor(new btVector4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_textShadowColor(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    m_gradientStartColor(new btVector4(1.0f, 1.0f, 1.0f, 32.0/255.0)),
    m_gradientEndColor(new btVector4(0.0f, 0.0f, 0.0f, 32.0/255.0)),
    m_cornerRadius(4.0f*3)
    {
        
    }
    
    ButtonHUD::ButtonHUD(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_fontSize(20),
    m_fontFace("sans"),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_position(new btVector2(0.0f, 0)),
    m_dimensions(new btVector2(140, 28)),
    m_text("EMPTY"),
    m_fillColor(new btVector4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_borderColor(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    m_textColor(new btVector4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_textShadowColor(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    m_gradientStartColor(new btVector4(1.0f, 1.0f, 1.0f, 32.0/255.0)),
    m_gradientEndColor(new btVector4(0.0f, 0.0f, 0.0f, 32.0/255.0)),
    m_cornerRadius(4.0f)
    {
        
    }
    
    ButtonHUD::ButtonHUD(const ButtonHUD &copy):
    AbstractFactoryObject(this),
    m_fontSize(20),
    m_fontFace("sans"),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_position(new btVector2(0.0f, 0)),
    m_dimensions(new btVector2(140, 28)),
    m_text("EMPTY"),
    m_fillColor(new btVector4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_borderColor(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    m_textColor(new btVector4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_textShadowColor(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    m_gradientStartColor(new btVector4(1.0f, 1.0f, 1.0f, 32.0/255.0)),
    m_gradientEndColor(new btVector4(0.0f, 0.0f, 0.0f, 32.0/255.0)),
    m_cornerRadius(4.0f)
    {
        
    }
    
    ButtonHUD::~ButtonHUD()
    {
        delete m_gradientEndColor;m_gradientEndColor=NULL;
        delete m_gradientStartColor;m_gradientStartColor=NULL;
        delete m_textShadowColor;m_textShadowColor=NULL;
        delete m_textColor;m_textColor=NULL;
        delete m_borderColor;m_borderColor=NULL;
        delete m_fillColor;m_fillColor=NULL;
        delete m_dimensions;m_dimensions=NULL;
        delete m_position;m_position=NULL;
    }
    
    ButtonHUD &ButtonHUD::operator=(const ButtonHUD &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    void ButtonHUD::renderFunction(Camera *camera)
    {
        nvgBeginFrame(World::getInstance()->getWorldHUD()->getContext(),
                      getWidth(),
                      getHeight(),
                      getAspectRatio());
        
        WorldHUD *hud = njli::World::getInstance()->getWorldHUD();
        
        f32 w = m_dimensions->x();
        f32 h = m_dimensions->y();
        f32 tw = 0;
        f32 iw = 0;
        f32 x = m_position->x();
        f32 y = getHeight() - m_position->y() - h;
        
        JLIPaint bg = hud->linearGradient(x, y, x, y+h, *m_gradientStartColor, *m_gradientEndColor);
//        JLIPaint bg = hud->radialGradient(x + (w*.5), y + (h*.5), 0, w, *m_gradientStartColor, *m_gradientEndColor);
//        JLIPaint bg = hud->boxGradient(x, y, w, h, m_cornerRadius, 100, *m_gradientStartColor, *m_gradientEndColor);
        hud->beginPath();
        hud->roundedRect(x+1, y+1, w-2, h-2, m_cornerRadius - 1);
        hud->fillColor(*m_fillColor);
        hud->fill();
        hud->fillPaint(bg);
        hud->fill();
        
        hud->beginPath();
        hud->roundedRect(x + 0.5f, y + 0.5f, w-1, h-1, m_cornerRadius-0.5f);
        hud->strokeColor(*m_borderColor);
        hud->stroke();
        
        Rect rect;
        njli::World::getInstance()->getWorldHUD()->fontSize(m_fontSize);
        njli::World::getInstance()->getWorldHUD()->fontFace(m_fontFace.c_str());
        tw = hud->textBounds(0, 0, rect, m_text.c_str());
        
        njli::World::getInstance()->getWorldHUD()->textAlign((njli::njliHUDAlign)m_align);
        hud->fillColor(*m_textShadowColor);
        hud->text(x+w*0.5-tw*0.5+iw*0.25, y+h*0.5-1,m_text.c_str());
        hud->fillColor(*m_textColor);
        hud->text(x+w*0.5-tw*0.5+iw*0.25, y+h*0.5, m_text.c_str());
        
        nvgEndFrame(World::getInstance()->getWorldHUD()->getContext());
    }
    
    s32	ButtonHUD::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void ButtonHUD::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *ButtonHUD::getClassName()const
    {
        return "ButtonHUD";
    }
    
    s32 ButtonHUD::getType()const
    {
        return JLI_OBJECT_TYPE_ButtonHUD;
    }
    
    ButtonHUD::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    ButtonHUD **ButtonHUD::createArray(const u32 size)
    {
        return (ButtonHUD**)World::getInstance()->getWorldFactory()->createArray(ButtonHUD::type(), size);
    }
    
    void ButtonHUD::destroyArray(ButtonHUD **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    ButtonHUD *ButtonHUD::create()
    {
        return dynamic_cast<ButtonHUD*>(World::getInstance()->getWorldFactory()->create(ButtonHUD::type()));
    }
    
    ButtonHUD *ButtonHUD::create(const ButtonHUDBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<ButtonHUD*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    ButtonHUD *ButtonHUD::clone(const ButtonHUD &object)
    {
        return dynamic_cast<ButtonHUD*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    ButtonHUD *ButtonHUD::copy(const ButtonHUD &object)
    {
        return dynamic_cast<ButtonHUD*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void ButtonHUD::destroy(ButtonHUD *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void ButtonHUD::load(ButtonHUD &object, lua_State *L, int index)
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
                ButtonHUD::load(object, L, -2);
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
    
    u32 ButtonHUD::type()
    {
        return JLI_OBJECT_TYPE_ButtonHUD;
    }
    
    void ButtonHUD::setFontSize(f32 size)
    {
        m_fontSize = size;
    }
    
    void ButtonHUD::setFontFace(const char *face)
    {
        m_fontFace = face;
    }
    
    void ButtonHUD::setPosition(const btVector2 &pos)
    {
        *m_position = pos;
    }
    
    void ButtonHUD::setDimensions(const btVector2 &dim)
    {
        *m_dimensions = dim;
    }
    
    void ButtonHUD::setText(const char *text)
    {
        m_text = text;
    }
    
    void ButtonHUD::setFillColor(const btVector4 &color)
    {
        *m_fillColor = color;
    }
    
    void ButtonHUD::setBorderColor(const btVector4 &color)
    {
        *m_borderColor = color;
    }
    
    void ButtonHUD::setTextColor(const btVector4 &color)
    {
        *m_textColor = color;
    }
    
    void ButtonHUD::setTextShadowColor(const btVector4 &color)
    {
        *m_textShadowColor = color;
    }
    
    void ButtonHUD::setGradientStartColor(const btVector4 &start)
    {
        *m_gradientStartColor = start;
    }
    
    void ButtonHUD::setGradientEndColor(const btVector4 &end)
    {
        *m_gradientEndColor = end;
    }
    
    void ButtonHUD::setCornerRadius(f32 radius)
    {
        m_cornerRadius = radius;
    }
    
    
    f32 ButtonHUD::getFontSize(f32 size)
    {
        return m_fontSize;
    }
    
    const char *ButtonHUD::getFontFace()const
    {
        return m_fontFace.c_str();
    }
    
    const btVector2 &ButtonHUD::getPosition()const
    {
        return *m_position;
    }
    
    const btVector2 &ButtonHUD::getDimensions()const
    {
        return *m_dimensions;
    }
    
    const char *ButtonHUD::getText()const
    {
        return m_text.c_str();
    }
    
    const btVector4 &ButtonHUD::getFillColor()const
    {
        return *m_fillColor;
    }
    
    const btVector4 &ButtonHUD::getBorderColor()const
    {
        return *m_borderColor;
    }
    
    const btVector4 &ButtonHUD::getTextColor()const
    {
        return *m_textColor;
    }
    
    const btVector4 &ButtonHUD::getTextShadowColor()const
    {
        return *m_textShadowColor;
    }
    
    const btVector4 &ButtonHUD::getGradientStartColor()const
    {
        return *m_gradientStartColor;
    }
    
    const btVector4 &ButtonHUD::getGradientEndColor()const
    {
        return *m_gradientEndColor;
    }
    
    f32 ButtonHUD::getCornerRadius()const
    {
        return m_cornerRadius;
    }
    
}
