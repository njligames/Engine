//
//  NodeStateMachine.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "NodeStateMachine.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "NodeStateMachineBuilder.h"
#define FORMATSTRING "{\"njli::NodeStateMachine\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    NodeStateMachine::NodeStateMachine():
    AbstractStateMachine<Node>()
    {
        
    }
    
    NodeStateMachine::NodeStateMachine(const AbstractBuilder &builder):
    AbstractStateMachine<Node>(builder)
    {
        
    }
    
    NodeStateMachine::NodeStateMachine(const NodeStateMachine &copy):
    AbstractStateMachine<Node>(copy)
    {
        
    }
    
    NodeStateMachine::~NodeStateMachine()
    {
        
    }
    
    NodeStateMachine &NodeStateMachine::operator=(const NodeStateMachine &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	NodeStateMachine::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void NodeStateMachine::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *NodeStateMachine::getClassName()const
    {
        return "NodeStateMachine";
    }
    
    s32 NodeStateMachine::getType()const
    {
        return NodeStateMachine::type();
    }
    
    NodeStateMachine::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    NodeStateMachine **NodeStateMachine::createArray(const u32 size)
    {
        return (NodeStateMachine**)World::getInstance()->getWorldFactory()->createArray(NodeStateMachine::type(), size);
    }
    
    void NodeStateMachine::destroyArray(NodeStateMachine **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    NodeStateMachine *NodeStateMachine::create()
    {
        return dynamic_cast<NodeStateMachine*>(World::getInstance()->getWorldFactory()->create(NodeStateMachine::type()));
    }
    
    NodeStateMachine *NodeStateMachine::create(const NodeStateMachineBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<NodeStateMachine*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    NodeStateMachine *NodeStateMachine::clone(const NodeStateMachine &object)
    {
        return dynamic_cast<NodeStateMachine*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    NodeStateMachine *NodeStateMachine::copy(const NodeStateMachine &object)
    {
        return dynamic_cast<NodeStateMachine*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void NodeStateMachine::destroy(NodeStateMachine *object)
    {
        if(object)
        {
            object->clear();
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void NodeStateMachine::load(NodeStateMachine &object, lua_State *L, int index)
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
                NodeStateMachine::load(object, L, -2);
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
    
    u32 NodeStateMachine::type()
    {
        return JLI_OBJECT_TYPE_NodeStateMachine;
    }
}
