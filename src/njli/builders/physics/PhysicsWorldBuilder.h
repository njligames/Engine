//
//  PhysicsWorldBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsWorldBuilder__
#define __JLIGameEngineTest__PhysicsWorldBuilder__

#include "btAlignedObjectArray.h"
#include "Util.h"
#include "AbstractBuilder.h"
#include "btSerializer.h"
#include "lua.hpp"

namespace njli
{
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsWorldBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        PhysicsWorldBuilder();
        PhysicsWorldBuilder(const PhysicsWorldBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsWorldBuilder();
        
        PhysicsWorldBuilder &operator=(const PhysicsWorldBuilder &);
        
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
        virtual u32 getObjectType()const;
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
        static PhysicsWorldBuilder **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsWorldBuilder **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsWorldBuilder *create();
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsWorldBuilder *clone(const PhysicsWorldBuilder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsWorldBuilder *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsWorldBuilder &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsWorldBuilder__) */
