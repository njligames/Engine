//
//  JsonJLI.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "JsonJLI.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "JsonJLIBuilder.h"


#define FORMATSTRING "{\"njli::JsonJLI\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    JsonJLI::JsonJLI():
    AbstractFactoryObject(this)
    {
        
    }
    
    JsonJLI::JsonJLI(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    JsonJLI::JsonJLI(const JsonJLI &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    JsonJLI::~JsonJLI()
    {
        
    }
    
    JsonJLI &JsonJLI::operator=(const JsonJLI &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	JsonJLI::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void JsonJLI::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *JsonJLI::getClassName()const
    {
        return "JsonJLI";
    }
    
    s32 JsonJLI::getType()const
    {
        return JsonJLI::type();
    }
    
    JsonJLI::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    JsonJLI **JsonJLI::createArray(const u32 size)
    {
        return (JsonJLI**)World::getInstance()->getWorldFactory()->createArray(JsonJLI::type(), size);
    }
    
    void JsonJLI::destroyArray(JsonJLI **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    JsonJLI *JsonJLI::create()
    {
        return dynamic_cast<JsonJLI*>(World::getInstance()->getWorldFactory()->create(JsonJLI::type()));
    }
    
    JsonJLI *JsonJLI::create(const JsonJLIBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<JsonJLI*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    JsonJLI *JsonJLI::clone(const JsonJLI &object)
    {
        return dynamic_cast<JsonJLI*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    JsonJLI *JsonJLI::copy(const JsonJLI &object)
    {
        return dynamic_cast<JsonJLI*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void JsonJLI::destroy(JsonJLI *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void JsonJLI::load(JsonJLI &object, lua_State *L, int index)
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
                JsonJLI::load(object, L, -2);
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
    
    u32 JsonJLI::type()
    {
        return JLI_OBJECT_TYPE_JsonJLI;
    }
    
    std::string JsonJLI::parse(const char *jsonMessage, bool compact)
    {
        Json::Value parsedFromString;
        Json::Reader reader;
        if(reader.parse(jsonMessage, parsedFromString))
        {
            if(compact)
            {
                Json::FastWriter fastWriter;
                return fastWriter.write(parsedFromString);
            }
            Json::StyledWriter styledWriter;
            return styledWriter.write(parsedFromString);
        }
        return "";
        
    }
    
    bool JsonJLI::parseJson(const char *jsonMessage)
    {
        Json::Reader reader;
        return reader.parse(jsonMessage, m_value);
    }
    
    void JsonJLI::addValue(const std::string &key, const std::string &value)
    {
        m_value[key.c_str()] = value;
    }
    
    void JsonJLI::addValue(const std::string &key, const JsonJLI &value)
    {
        m_value[key.c_str()] = value.m_value;
    }
    
    std::string JsonJLI::getValue(const std::string &key)
    {
        Json::Value v = m_value.get(key.c_str(), "");
        if(v.isString())
        {
            return v.asString();
        }
        return "";
    }
    
    void JsonJLI::append(const std::string &value)
    {
        m_value.append(value.c_str());
    }
    
    void JsonJLI::append(const JsonJLI &value)
    {
        m_value.append(value.m_value);
    }
}
