//
//  NodeState.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "NodeState.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "NodeStateBuilder.h"

#define FORMATSTRING "{\"njli::NodeState\":[{\"name\":\"%s\"}]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btQuickprof.h"

namespace njli
{
    NodeState::NodeState():
    AbstractState<Node>()
//    m_Name("MyNodeState")
    {
    }
    
    NodeState::NodeState(const AbstractBuilder &builder):
    AbstractState<Node>(builder)
    {
    }
    
    NodeState::NodeState(const NodeState &copy):
    AbstractState<Node>(copy)
    {
    }
    
    NodeState::~NodeState()
    {
        
    }
    
    NodeState &NodeState::operator=(const NodeState &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	NodeState::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void NodeState::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *NodeState::getClassName()const
    {
        return "NodeState";
    }
    
    s32 NodeState::getType()const
    {
        return NodeState::type();
    }
    
    NodeState::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format(FORMATSTRING, getName()));
    }
    
    NodeState **NodeState::createArray(const u32 size)
    {
        return (NodeState**)World::getInstance()->getWorldFactory()->createArray(NodeState::type(), size);
    }
    
    void NodeState::destroyArray(NodeState **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    NodeState *NodeState::create()
    {
        return dynamic_cast<NodeState*>(World::getInstance()->getWorldFactory()->create(NodeState::type()));
    }
    
    NodeState *NodeState::create(const NodeStateBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<NodeState*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    NodeState *NodeState::clone(const NodeState &object)
    {
        NodeState *n = dynamic_cast<NodeState*>(World::getInstance()->getWorldFactory()->clone(object, false));
        return n;
    }
    
    NodeState *NodeState::copy(const NodeState &object)
    {
        return dynamic_cast<NodeState*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void NodeState::destroy(NodeState *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void NodeState::load(NodeState &object, lua_State *L, int index)
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
                NodeState::load(object, L, -2);
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
    
    u32 NodeState::type()
    {
        return JLI_OBJECT_TYPE_NodeState;
    }
    
    void NodeState::enter(Node *object)
    {
        char buffer[BUFFER_SIZE] = "__NJLINodeEnterState";
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, object);
    }
    
    void NodeState::update(Node *object, f32 timeStep)
    {
        BT_PROFILE("NodeState::update");
        char buffer[BUFFER_SIZE] = "__NJLINodeUpdateState";
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, object, timeStep);
    }
    
    void NodeState::exit(Node *object)
    {
        char buffer[BUFFER_SIZE] = "__NJLINodeExitState";
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, object);
    }
    
    bool NodeState::onMessage(Node *object, const Telegram &msg)const
    {
        bool ret;
        char buffer[BUFFER_SIZE] = "__NJLINodeOnMessage";
        
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, object, msg, ret);
        
        return ret;
    }
}
