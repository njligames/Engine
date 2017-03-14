//
//  NodeState.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__NodeState__
#define __JLIGameEngineTest__NodeState__

#include "AbstractBuilder.h"
#include "AbstractState.h"
#include "Node.h"
#include "lua.hpp"

namespace njli {
class NodeStateBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
NodeState : public AbstractState<Node>
{
    friend class WorldFactory;

protected:
    NodeState();
    NodeState(const AbstractBuilder&);
    NodeState(const NodeState&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~NodeState();
    NodeState& operator=(const NodeState&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;
    using AbstractState::isFinished;
    using AbstractState::enableFinished;
    using AbstractState::enableCanDelete;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:04
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    operator std::string() const;

    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    static NodeState** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(NodeState * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static NodeState* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static NodeState* create(const NodeStateBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static NodeState* clone(const NodeState& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static NodeState* copy(const NodeState& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(NodeState * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(NodeState & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    /**
         *  @author James Folk, 16-02-11 17:02:22
         *
         *  @brief <#Description#>
         *
         *  @param node <#node description#>
         */
    virtual void enter(Node * node);

    /**
         *  @author James Folk, 16-02-11 17:02:36
         *
         *  @brief <#Description#>
         *
         *  @param node     <#node description#>
         *  @param timestep <#timestep description#>
         */
    virtual void update(Node * node, f32 timestep);

    /**
         *  @author James Folk, 16-02-11 17:02:47
         *
         *  @brief <#Description#>
         *
         *  @param node <#node description#>
         */
    virtual void exit(Node * node);

    /**
         *  @author James Folk, 16-02-11 17:02:03
         *
         *  @brief <#Description#>
         *
         *  @param node     <#node description#>
         *  @param telegram <#telegram description#>
         *
         *  @return <#return value description#>
         */
    virtual bool onMessage(Node * node, const Telegram& telegram) const;

protected:
private:
    //        std::string m_Name;
};
}

#endif /* defined(__JLIGameEngineTest__NodeState__) */
