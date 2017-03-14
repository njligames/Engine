//
//  SceneStateMachine.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SceneStateMachine__
#define __JLIGameEngineTest__SceneStateMachine__

#include "Scene.h"
#include "AbstractBuilder.h"
#include "AbstractStateMachine.h"
#include "lua.hpp"

namespace njli
{
    class SceneStateMachineBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) SceneStateMachine:
    public AbstractStateMachine<Scene>
    {
        friend class WorldFactory;
    protected:
        SceneStateMachine();
        SceneStateMachine(const AbstractBuilder&);
        SceneStateMachine(const SceneStateMachine &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SceneStateMachine();
        SceneStateMachine &operator=(const SceneStateMachine &);
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
        static SceneStateMachine **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(SceneStateMachine **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static SceneStateMachine *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static SceneStateMachine *create(const SceneStateMachineBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static SceneStateMachine *clone(const SceneStateMachine &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static SceneStateMachine *copy(const SceneStateMachine &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(SceneStateMachine *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(SceneStateMachine &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
        //TODO: fill in specific methods for SceneStateMachine
    protected:
    private:
    };
}

#endif /* defined(__JLIGameEngineTest__SceneStateMachine__) */
