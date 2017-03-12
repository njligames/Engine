//
//  TextboxHUD.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "TextboxHUD.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "TextboxHUDBuilder.h"
#include "GLPlatform.h"
#include "WorldHUD.h"
#include "Log.h"
#define TAG "TextboxHUD.cpp"
#define FORMATSTRING "{\"njli::TextboxHUD\":[]}"
#include "btPrint.h"

namespace njli
{
    TextboxHUD::TextboxHUD():
    AbstractFactoryObject(this),
    m_dimensions(new btVector2(280.0f, 28.0f)),
    m_position(new btVector2(100.0f, 100.0f)),
    m_gradientStartColor(new btVector4(1.0f, 1.0f, 1.0f,0.125490196078431f)),
    m_gradientEndColor(new btVector4(0.125490196078431f, 0.125490196078431f, 0.125490196078431f, 0.125490196078431f)),
    m_cornerRadius(3.0f),
    m_cornerFeather(4.0f),
    m_borderColor(new btVector4(0, 0, 0, 0.188235294117647)),
    m_fontSize(20.0f),
    m_fontFace("sans"),
    m_fontColor(new btVector4(1.0f, 1.0f, 1.0f, 0.250980392156863f)),
    m_align(JLI_HUD_ALIGN_LEFT | JLI_HUD_ALIGN_MIDDLE),
    m_text("EMPTY")
    {
        
    }
    
    TextboxHUD::TextboxHUD(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    TextboxHUD::TextboxHUD(const TextboxHUD &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    TextboxHUD::~TextboxHUD()
    {
        delete m_fontColor;m_fontColor=NULL;
        delete m_borderColor;m_borderColor=NULL;
        delete m_gradientEndColor;m_gradientEndColor=NULL;
        delete m_gradientStartColor;m_gradientStartColor=NULL;
        delete m_position;m_position=NULL;
        delete m_dimensions;m_dimensions=NULL;
    }
    
    TextboxHUD &TextboxHUD::operator=(const TextboxHUD &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    
    void TextboxHUD::renderFunction(Camera *camera)
    {
        nvgBeginFrame(World::getInstance()->getWorldHUD()->getContext(),
                      getWidth(),
                      getHeight(),
                      getAspectRatio());
        
        
        
        WorldHUD *hud = njli::World::getInstance()->getWorldHUD();
        
        f32 w = m_dimensions->x();
        f32 h = m_dimensions->y();
        f32 x = m_position->x();
        f32 y = getHeight() - m_position->y() - h;
        
        
//         function drawEditBoxBase(x, y, w, h)
//         -- Edit
//         local bg = hud:boxGradient(x+1,y+1+1.5, w-2,h-2, 3,4, JLI.WorldHUD.rgba(255,255,255,32), JLI.WorldHUD.rgba(32,32,32,32))
        JLIPaint bg = hud->boxGradient(x+1, y+1+1.5, w-2, h-2, m_cornerRadius, m_cornerFeather, *m_gradientStartColor, *m_gradientEndColor);
//         hud:beginPath()
        hud->beginPath();
//         hud:roundedRect(x+1,y+1, w-2,h-2, 4-1)
        hud->roundedRect(x+1, y+1, w-2, h-2, m_cornerRadius);
//         hud:fillPaint(bg)
        hud->fillPaint(bg);
//         hud:fill()
        hud->fill();
//         
//         hud:beginPath()
        hud->beginPath();
//         hud:roundedRect(x+0.5, y+0.5, w-1,h-1, 4-0.5)
        hud->roundedRect(x+0.5f, y+0.5f, w-1, h-1, m_cornerRadius + 0.5f);
//         hud:strokeColor(JLI.WorldHUD.rgba(0,0,0,48))
        hud->strokeColor(*m_borderColor);
//         hud:stroke()
        hud->stroke();
//         end
//         
//         function drawEditBox(text, x, y, w, h)
//         
//         drawEditBoxBase(x,y, w,h)
//
        
        
//         hud:fontSize(20.0)
        hud->fontSize(m_fontSize);
//         hud:fontFace("sans")
        hud->fontFace(m_fontFace.c_str());
//         hud:fillColor(JLI.WorldHUD.rgba(255,255,255,64))
        hud->fillColor(*m_fontColor);
//         local align = bit.bor(bit.tobit(JLI.JLI_HUD_ALIGN_LEFT), bit.tobit(JLI.JLI_HUD_ALIGN_MIDDLE))
        
//         hud:textAlign(align)
        hud->textAlign((njliHUDAlign)m_align);
//         hud:text(x+h*0.3, y+h*0.5, text)
        hud->text(x+h*0.3, y+h*0.5, m_text.c_str());
//         
//         end
        
        
        nvgEndFrame(World::getInstance()->getWorldHUD()->getContext());
    }
    
    s32	TextboxHUD::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void TextboxHUD::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *TextboxHUD::getClassName()const
    {
        return "TextboxHUD";
    }
    
    s32 TextboxHUD::getType()const
    {
        return JLI_OBJECT_TYPE_TextboxHUD;
    }
    
    TextboxHUD::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    TextboxHUD **TextboxHUD::createArray(const u32 size)
    {
        return (TextboxHUD**)World::getInstance()->getWorldFactory()->createArray(TextboxHUD::type(), size);
    }
    
    void TextboxHUD::destroyArray(TextboxHUD **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    TextboxHUD *TextboxHUD::create()
    {
        return dynamic_cast<TextboxHUD*>(World::getInstance()->getWorldFactory()->create(TextboxHUD::type()));
    }
    
    TextboxHUD *TextboxHUD::create(const TextboxHUDBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<TextboxHUD*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    TextboxHUD *TextboxHUD::clone(const TextboxHUD &object)
    {
        return dynamic_cast<TextboxHUD*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    TextboxHUD *TextboxHUD::copy(const TextboxHUD &object)
    {
        return dynamic_cast<TextboxHUD*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void TextboxHUD::destroy(TextboxHUD *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void TextboxHUD::load(TextboxHUD &object, lua_State *L, int index)
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
                TextboxHUD::load(object, L, -2);
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
    
    u32 TextboxHUD::type()
    {
        return JLI_OBJECT_TYPE_TextboxHUD;
    }
}
