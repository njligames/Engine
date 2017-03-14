//
//  CheckboxHUD.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "CheckboxHUD.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "CheckboxHUDBuilder.h"
#include "GLPlatform.h"
#include "WorldHUD.h"
#include "Log.h"
#define TAG "CheckboxHUD.cpp"

#define ICON_CHECK 0x2713
#define SCALE (3)

#define FORMATSTRING "{\"njli::CheckboxHUD\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    CheckboxHUD::CheckboxHUD():
    AbstractFactoryObject(this),
    m_dimensions(new btVector2(140*SCALE, 28*SCALE)),
    m_position(new btVector2(0,0)),
    m_fontSize(18*SCALE),
    m_fontFace("sans"),
    m_fillColor(new btVector4(1.0,1.0,1.0, 160.0/255.0)),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_cornerRadius(3*SCALE),
    m_feather(3*SCALE),
    m_gradientStartColor(new btVector4(0.0f, 0.0f, 0.0f, 32.0f/255.0f)),
    m_gradientEndColor(new btVector4(0.0f, 0.0f, 0.0f, 92.0f/255.0f)),
    m_iconFontSize(40*SCALE),
    m_iconFontFace("icons"),
    m_iconFillColor(new btVector4(1.0f, 1.0f, 1.0f, 128.0f/255.0f)),
    m_iconText(njli::World::getInstance()->getWorldHUD()->cpToUTF8(ICON_CHECK)),
    m_text("CHECKBOX"),
    m_checkboxDimension(new btVector2(18*SCALE, 18*SCALE)),
    m_isChecked(true)
    {
        
    }
    
    CheckboxHUD::CheckboxHUD(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    CheckboxHUD::CheckboxHUD(const CheckboxHUD &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    CheckboxHUD::~CheckboxHUD()
    {
        delete m_checkboxDimension;m_checkboxDimension=NULL;
        delete m_iconFillColor;m_iconFillColor=NULL;
        delete m_gradientEndColor;m_gradientEndColor=NULL;
        delete m_gradientStartColor;m_gradientStartColor=NULL;
        delete m_fillColor;m_fillColor=NULL;
        delete m_position;m_position=NULL;
        delete m_dimensions;m_dimensions=NULL;
    }
    
    CheckboxHUD &CheckboxHUD::operator=(const CheckboxHUD &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    
    void CheckboxHUD::renderFunction(Camera *camera)
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
        
        hud->fontSize(m_fontSize);
        hud->fontFace(m_fontFace.c_str());
        hud->fillColor(*m_fillColor);
        
        hud->textAlign((njliHUDAlign)m_align);
        hud->text(x+m_checkboxDimension->x() + 10, y+h*0.5, m_text.c_str());
        
        JLIPaint bg = hud->boxGradient(x+1, y+(h*0.5)-(m_checkboxDimension->y()*0.5f)+1, m_checkboxDimension->x(), m_checkboxDimension->y(), m_cornerRadius, m_feather, *m_gradientStartColor, *m_gradientEndColor);
        hud->beginPath();
        hud->roundedRect(x+1, y+(h*0.5)-(m_checkboxDimension->y()*0.5f), m_checkboxDimension->x(), m_checkboxDimension->y(), m_cornerRadius);
        hud->fillPaint(bg);
        hud->fill();
        
        hud->fontSize(m_iconFontSize);
        hud->fontFace(m_iconFontFace.c_str());
        hud->fillColor(*m_iconFillColor);
        
        if(m_isChecked)
        {
            hud->textAlign((njliHUDAlign)m_align);
            hud->text(x+(m_checkboxDimension->x()*0.3f), y+(h*0.4f), m_iconText.c_str());
        }

        
        nvgEndFrame(World::getInstance()->getWorldHUD()->getContext());
    }
    
    s32	CheckboxHUD::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void CheckboxHUD::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *CheckboxHUD::getClassName()const
    {
        return "CheckboxHUD";
    }
    
    s32 CheckboxHUD::getType()const
    {
        return JLI_OBJECT_TYPE_CheckboxHUD;
    }
    
    CheckboxHUD::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    CheckboxHUD **CheckboxHUD::createArray(const u32 size)
    {
        return (CheckboxHUD**)World::getInstance()->getWorldFactory()->createArray(CheckboxHUD::type(), size);
    }
    
    void CheckboxHUD::destroyArray(CheckboxHUD **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    CheckboxHUD *CheckboxHUD::create()
    {
        return dynamic_cast<CheckboxHUD*>(World::getInstance()->getWorldFactory()->create(CheckboxHUD::type()));
    }
    
    CheckboxHUD *CheckboxHUD::create(const CheckboxHUDBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<CheckboxHUD*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    CheckboxHUD *CheckboxHUD::clone(const CheckboxHUD &object)
    {
        return dynamic_cast<CheckboxHUD*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    CheckboxHUD *CheckboxHUD::copy(const CheckboxHUD &object)
    {
        return dynamic_cast<CheckboxHUD*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void CheckboxHUD::destroy(CheckboxHUD *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void CheckboxHUD::load(CheckboxHUD &object, lua_State *L, int index)
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
                CheckboxHUD::load(object, L, -2);
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
    
    u32 CheckboxHUD::type()
    {
        return JLI_OBJECT_TYPE_CheckboxHUD;
    }
    
    void CheckboxHUD::setDimensions(const btVector2 &dim)
    {
        *m_dimensions = dim;
    }
    
    void CheckboxHUD::setPosition(const btVector2 &pos)
    {
        *m_position = pos;
    }
    
    void CheckboxHUD::setFontSize(f32 fontSize)
    {
        m_fontSize = fontSize;
    }
    
    void CheckboxHUD::setFontFace(const char *fontFace)
    {
        m_fontFace = fontFace;
    }
    
    void CheckboxHUD::setFontColor(const btVector4 &color)
    {
        *m_fillColor = color;
    }
    
    void CheckboxHUD::setText(const char *text)
    {
        m_text = text;
    }
    
    void CheckboxHUD::setFontAlign(njliHUDAlign align)
    {
        m_align = align;
    }
    
    void CheckboxHUD::setCheckboxRadius(f32 radius)
    {
        m_cornerRadius = radius;
    }
    
    void CheckboxHUD::setCheckboxFeather(f32 feather)
    {
        m_feather = feather;
    }
    
    void CheckboxHUD::setCheckboxGradientStartColor(const btVector4 &start)
    {
        *m_gradientStartColor = start;
    }
    
    void CheckboxHUD::setCheckboxGradientEndColor(const btVector4 &end)
    {
        *m_gradientEndColor = end;
    }
    
    void CheckboxHUD::setCheckboxDimensions(const btVector2 &dim)
    {
        *m_checkboxDimension = dim;
    }
    
    void CheckboxHUD::setFontSizeIcon(f32 size)
    {
        m_iconFontSize = size;
    }
    
    void CheckboxHUD::setFontFaceIcon(const char *fontFace)
    {
        m_iconFontFace = fontFace;
    }
    
    void CheckboxHUD::setFontColorIcon(const btVector4 &color)
    {
        *m_iconFillColor = color;
    }
    
    void CheckboxHUD::setTextIcon(const char *text)
    {
        m_iconText = text; 
    }
    
    
    const btVector2 &CheckboxHUD::getDimensions()const
    {
        return *m_dimensions;
    }
    
    const btVector2 &CheckboxHUD::getPosition(const btVector2 &pos)const
    {
        return *m_position;
    }
    
    f32 CheckboxHUD::getFontSize()const
    {
        return m_fontSize;
    }
    
    const char *CheckboxHUD::getFontFace()const
    {
        return m_fontFace.c_str();
    }
    
    const btVector4 &CheckboxHUD::getFontColor()const
    {
        return *m_fillColor;
    }
    
    const char *CheckboxHUD::getText()const
    {
        return m_text.c_str();
    }
    
    njliHUDAlign CheckboxHUD::getFontAlign()const
    {
        return (njliHUDAlign)m_align;
    }
    
    f32 CheckboxHUD::getCheckboxRadius()const
    {
        return m_cornerRadius;
    }
    
    f32 CheckboxHUD::getCheckboxFeather()const
    {
        return m_feather;
    }
    
    const btVector4 &CheckboxHUD::getCheckboxGradientStartColor()const
    {
        return *m_gradientStartColor;
    }
    
    const btVector4 &CheckboxHUD::getCheckboxGradientEndColor()const
    {
        return *m_gradientEndColor;
    }
    
    const btVector2 &CheckboxHUD::getCheckboxDimensions()const
    {
        return *m_checkboxDimension;
    }
    
    f32 CheckboxHUD::getFontSizeIcon()const
    {
        return m_iconFontSize;
    }
    
    const char *CheckboxHUD::getFontFaceIcon()const
    {
        return m_iconFontFace.c_str();
    }
    
    const btVector4 &CheckboxHUD::getFontColorIcon()const
    {
        return *m_iconFillColor;
    }
    
    const char *CheckboxHUD::getTextIcon()const
    {
        return m_iconText.c_str();
    }
    
    void CheckboxHUD::check()
    {
        m_isChecked = true;
    }
    
    void CheckboxHUD::unCheck()
    {
        m_isChecked = false;
    }
    
    bool CheckboxHUD::isChecked()const
    {
        return m_isChecked;
    }
    
}
