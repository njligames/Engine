//
//  WorldStateMachine.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldStateMachine__
#define __JLIGameEngineTest__WorldStateMachine__

#include "AbstractBuilder.h"
#include "AbstractStateMachine.h"
//#include "Input.h"
#include "lua.hpp"

namespace njli
{
    class WorldStateMachineBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) WorldStateMachine:
    public AbstractStateMachine<void>
    {
        friend class WorldFactory;
        friend class World;
        
    protected:
        WorldStateMachine();
        WorldStateMachine(const AbstractBuilder&);
        WorldStateMachine(const WorldStateMachine &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~WorldStateMachine();
        WorldStateMachine &operator=(const WorldStateMachine &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        /**
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
        virtual	void serialize(void*, btSerializer*) const;
        
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
        static WorldStateMachine **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(WorldStateMachine **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static WorldStateMachine *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static WorldStateMachine *create(const WorldStateMachineBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static WorldStateMachine *clone(const WorldStateMachine &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static WorldStateMachine *copy(const WorldStateMachine &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(WorldStateMachine *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(WorldStateMachine &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
        //TODO: fill in specific methods for WorldStateMachine
    protected:
    private:
    };
}

#endif /* defined(__JLIGameEngineTest__WorldStateMachine__) */
