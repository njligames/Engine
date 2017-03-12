//
//  DropdownHUD.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "DropdownHUD.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "DropdownHUDBuilder.h"
#include "GLPlatform.h"
#include "WorldHUD.h"
#include "Log.h"
#define TAG "DropdownHUD.cpp"
#define FORMATSTRING "{\"njli::DropdownHUD\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    DropdownHUD::DropdownHUD():
    AbstractFactoryObject(this)
    {
        
    }
    
    DropdownHUD::DropdownHUD(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    DropdownHUD::DropdownHUD(const DropdownHUD &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    DropdownHUD::~DropdownHUD()
    {
        
    }
    
    DropdownHUD &DropdownHUD::operator=(const DropdownHUD &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    void DropdownHUD::renderFunction(Camera *camera)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        
        nvgBeginFrame(World::getInstance()->getWorldHUD()->getContext(),
                      njli::World::getInstance()->getViewportDimensions().x(),
                      njli::World::getInstance()->getViewportDimensions().y(),
                      njli::World::getInstance()->getAspectRatio());
        
        
        nvgEndFrame(World::getInstance()->getWorldHUD()->getContext());
    }
    
    s32	DropdownHUD::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void DropdownHUD::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *DropdownHUD::getClassName()const
    {
        return "DropdownHUD";
    }
    
    s32 DropdownHUD::getType()const
    {
        return JLI_OBJECT_TYPE_DropdownHUD;
    }
    
    DropdownHUD::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    DropdownHUD **DropdownHUD::createArray(const u32 size)
    {
        return (DropdownHUD**)World::getInstance()->getWorldFactory()->createArray(DropdownHUD::type(), size);
    }
    
    void DropdownHUD::destroyArray(DropdownHUD **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    DropdownHUD *DropdownHUD::create()
    {
        return dynamic_cast<DropdownHUD*>(World::getInstance()->getWorldFactory()->create(DropdownHUD::type()));
    }
    
    DropdownHUD *DropdownHUD::create(const DropdownHUDBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<DropdownHUD*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    DropdownHUD *DropdownHUD::clone(const DropdownHUD &object)
    {
        return dynamic_cast<DropdownHUD*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    DropdownHUD *DropdownHUD::copy(const DropdownHUD &object)
    {
        return dynamic_cast<DropdownHUD*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void DropdownHUD::destroy(DropdownHUD *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void DropdownHUD::load(DropdownHUD &object, lua_State *L, int index)
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
                DropdownHUD::load(object, L, -2);
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
    
    u32 DropdownHUD::type()
    {
        return JLI_OBJECT_TYPE_DropdownHUD;
    }
}
