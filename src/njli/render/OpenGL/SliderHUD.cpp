//
//  SliderHUD.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "SliderHUD.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SliderHUDBuilder.h"
#include "GLPlatform.h"
#include "WorldHUD.h"
#include "Log.h"
#define TAG "SliderHUD.cpp"
#define FORMATSTRING "{\"njli::SliderHUD\":[]}"
#include "btPrint.h"

namespace njli
{
    SliderHUD::SliderHUD():
    AbstractFactoryObject(this),
    m_dimensions(new btVector2(170.0f, 28.0f)),
    m_position(new btVector2(100.0f, 100.0f)),
    m_knobPos(0.4f),
    m_slotHeight(4.0f),
    m_slotRadius(2.0f),
    m_slotFeather(2.0f),
    m_gradientStartColor(new btVector4(0.0f, 0.0f, 0.0f, 32.0f/255.0f)),
    m_gradientEndColor(new btVector4(0.0f, 0.0f, 0.0f, 128.0f/255.0f)),
    m_knobShadowGradientStartColor(new btVector4(0.0f, 0.0f, 0.0f, 64.0f/255.0f)),
    m_knobShadowGradientEndColor(new btVector4(0.0f, 0.0f, 0.0f, 0.0f)),
    m_knobGradientStartColor(new btVector4(1.0f, 1.0f, 1.0f, 16.0f/255.0f)),
    m_knobGradientEndColor(new btVector4(0.0f, 0.0f, 0.0f, 16.0f/255.0f)),
    m_knobColor(new btVector4(40.0f/255.0f, 43.0f/255.0f, 48.0f/255.0f, 1.0f))
    {
        
    }
    
    SliderHUD::SliderHUD(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    SliderHUD::SliderHUD(const SliderHUD &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    SliderHUD::~SliderHUD()
    {
        delete m_knobColor;m_knobColor=NULL;
        delete m_knobGradientEndColor;m_knobGradientEndColor=NULL;
        delete m_knobGradientStartColor;m_knobGradientStartColor=NULL;
        delete m_knobShadowGradientEndColor;m_knobShadowGradientEndColor=NULL;
        delete m_knobShadowGradientStartColor;m_knobShadowGradientStartColor=NULL;
        delete m_gradientEndColor;m_gradientEndColor=NULL;
        delete m_gradientStartColor;m_gradientStartColor=NULL;
        delete m_position;m_position=NULL;
        delete m_dimensions;m_dimensions=NULL;
    }
    
    SliderHUD &SliderHUD::operator=(const SliderHUD &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    void SliderHUD::renderFunction(Camera *camera)
    {
        nvgBeginFrame(World::getInstance()->getWorldHUD()->getContext(),
                      getWidth(),
                      getHeight(),
                      getAspectRatio());
        
        WorldHUD *hud = njli::World::getInstance()->getWorldHUD();
        
        //drawSlider(0.4, x,y, 170,28)
        
        f32 w = m_dimensions->x();
        f32 h = m_dimensions->y();
        f32 x = m_position->x();
        f32 y = getHeight() - m_position->y() - h;
        
//        f32 m_knobPos = 0.4f;
//        
//        f32 m_slotHeight = 4;
//        f32 m_slotRadius = 2;
//        f32 m_slotFeather = 2;
//        btVector4 *m_gradientStartColor;
//        btVector4 *m_gradientEndColor;
//        
//        btVector4 *m_knobShadowGradientStartColor;
//        btVector4 *m_knobShadowGradientEndColor;
//        
//        btVector4 *m_knobGradientStartColor;
//        btVector4 *m_knobGradientEndColor;
//        btVector4 *m_knobColor;
        
        //    function drawSlider(pos, x, y, w, h)
        //        local cy = y+(h*0.5)
        f32 cy = y+(h*0.5f);
        //        local kr = (h*0.25)
        f32 kr = h * 0.5f;
        //
        //        hud:save()
        hud->save();
        //        --	nvgClearState()
        //
        //        -- Slot
        //        local bg = hud:boxGradient(x,cy-2+1, w,4, 2,2, JLI.WorldHUD.rgba(0,0,0,32), JLI.WorldHUD.rgba(0,0,0,128))
        JLIPaint bg = hud->boxGradient(x, cy-2+1, w, m_slotHeight, m_slotRadius, m_slotFeather, *m_gradientStartColor, *m_gradientEndColor);
        //        hud:beginPath()
        hud->beginPath();
        //        hud:roundedRect(x,cy-2, w,4, 2)
        hud->roundedRect(x, cy-2, w, m_slotHeight, m_slotRadius);
        //        hud:fillPaint(bg)
        hud->fillPaint(bg);
        //        hud:fill()
        hud->fill();
        //
        //        -- Knob Shadow
        //        bg = hud:radialGradient(x+(pos*w),cy+1, kr-3,kr+3, JLI.WorldHUD.rgba(0,0,0,64), JLI.WorldHUD.rgba(0,0,0,0))
        bg = hud->radialGradient(x+(m_knobPos*w), cy+1, kr-3, kr+3, *m_knobShadowGradientStartColor, *m_knobShadowGradientEndColor);
        //        hud:beginPath()
        hud->beginPath();
        //        hud:rect(x+(pos*w)-kr-5,cy-kr-5,kr*2+5+5,kr*2+5+5+3)
        hud->rect(x+(m_knobPos*w)-kr-5, cy-kr-5, kr*2+5+5, kr*2+5+5+3);
        //        hud:circle(x+(pos*w),cy, kr)
        hud->circle(x+(m_knobPos*w), cy, kr);
        //        hud:pathWinding(JLI.JLI_HUD_SOLIDITY_HOLE)
        hud->pathWinding((njliHUDWinding)JLI_HUD_SOLIDITY_HOLE);
        //        hud:fillPaint(bg)
        hud->fillPaint(bg);
        //        hud:fill()
        hud->fill();
        //
        //        -- Knob
        //        local knob = hud:linearGradient(x,cy-kr,x,cy+kr, JLI.WorldHUD.rgba(255,255,255,16), JLI.WorldHUD.rgba(0,0,0,16))
        JLIPaint knob = hud->linearGradient(x, cy-kr, x, cy+kr, *m_knobGradientStartColor, *m_knobGradientEndColor);
        //        hud:beginPath()
        hud->beginPath();
        //        hud:circle(x+(pos*w),cy, kr-1)
        hud->circle(x+(m_knobPos*w), cy, kr-1);
        //        hud:fillColor(JLI.WorldHUD.rgba(40,43,48,255))
        hud->fillColor(*m_knobColor);
        //        hud:fill()
        hud->fill();
        //        hud:fillPaint(knob)
        hud->fillPaint(knob);
        //        hud:fill()
        hud->fill();
        //
        //        hud:beginPath()
        hud->beginPath();
        //        hud:circle(x+(pos*w),cy, kr-0.5)
        hud->circle(x+(m_knobPos*w), cy, kr-0.5);
        //        hud:strokeColor(JLI.WorldHUD.rgba(0,0,0,92))
        hud->strokeColor(btVector4(0.0f, 0.0f, 0.0f, 92.0f/255.0f));
        //        hud:stroke()
        hud->stroke();
        //
        //        hud:restore()
        hud->restore();
        //    end

        nvgEndFrame(World::getInstance()->getWorldHUD()->getContext());
    }
    
    s32	SliderHUD::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void SliderHUD::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *SliderHUD::getClassName()const
    {
        return "SliderHUD";
    }
    
    s32 SliderHUD::getType()const
    {
        return JLI_OBJECT_TYPE_SliderHUD;
    }
    
    SliderHUD::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    SliderHUD **SliderHUD::createArray(const u32 size)
    {
        return (SliderHUD**)World::getInstance()->getWorldFactory()->createArray(SliderHUD::type(), size);
    }
    
    void SliderHUD::destroyArray(SliderHUD **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SliderHUD *SliderHUD::create()
    {
        return dynamic_cast<SliderHUD*>(World::getInstance()->getWorldFactory()->create(SliderHUD::type()));
    }
    
    SliderHUD *SliderHUD::create(const SliderHUDBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<SliderHUD*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    SliderHUD *SliderHUD::clone(const SliderHUD &object)
    {
        return dynamic_cast<SliderHUD*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    SliderHUD *SliderHUD::copy(const SliderHUD &object)
    {
        return dynamic_cast<SliderHUD*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void SliderHUD::destroy(SliderHUD *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void SliderHUD::load(SliderHUD &object, lua_State *L, int index)
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
                SliderHUD::load(object, L, -2);
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
    
    u32 SliderHUD::type()
    {
        return JLI_OBJECT_TYPE_SliderHUD;
    }
    
    void SliderHUD::setValue(f32 v)
    {
        if(v < 0)
            v = 0;
        if(v > 1)
            v = 1;
        m_knobPos = v;
    }
    f32 SliderHUD::getValue()const
    {
        return m_knobPos;
    }
}
