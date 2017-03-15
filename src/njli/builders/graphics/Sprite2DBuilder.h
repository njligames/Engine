//
//  Sprite2DBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/15/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Sprite2DBuilder__
#define __JLIGameEngineTest__Sprite2DBuilder__

#pragma mark Header

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
    ATTRIBUTE_ALIGNED16(class) Sprite2DBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        Sprite2DBuilder();
        Sprite2DBuilder(const Sprite2DBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~Sprite2DBuilder();
        
        Sprite2DBuilder &operator=(const Sprite2DBuilder &);
        
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
        static Sprite2DBuilder **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(Sprite2DBuilder **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static Sprite2DBuilder *create();
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static Sprite2DBuilder *clone(const Sprite2DBuilder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(Sprite2DBuilder *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(Sprite2DBuilder &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    };
}

#endif /* defined(__JLIGameEngineTest__Sprite2DBuilder__) */
