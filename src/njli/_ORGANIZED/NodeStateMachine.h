//
//  NodeStateMachine.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__NodeStateMachine__
#define __JLIGameEngineTest__NodeStateMachine__

#include "Node.h"
#include "AbstractBuilder.h"
#include "AbstractStateMachine.h"
#include "lua.hpp"

namespace njli
{
    class NodeStateMachineBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) NodeStateMachine:
    public AbstractStateMachine<Node>
    {
        friend class WorldFactory;
    protected:
        NodeStateMachine();
        NodeStateMachine(const AbstractBuilder&);
        NodeStateMachine(const NodeStateMachine &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~NodeStateMachine();
        NodeStateMachine &operator=(const NodeStateMachine &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:18
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
        virtual	void serialize(void*dataBuffer, btSerializer*) const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const char *getClassName()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 getType()const;
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
        static NodeStateMachine **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(NodeStateMachine **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static NodeStateMachine *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static NodeStateMachine *create(const NodeStateMachineBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static NodeStateMachine *clone(const NodeStateMachine &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static NodeStateMachine *copy(const NodeStateMachine &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(NodeStateMachine *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(NodeStateMachine &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
        //TODO: fill in specific methods for NodeStateMachine
    protected:
    private:
    };
}

#endif /* defined(__JLIGameEngineTest__NodeStateMachine__) */
