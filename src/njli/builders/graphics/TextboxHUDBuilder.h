//
//  TextboxHUDBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__TextboxHUDBuilder__
#define __JLIGameEngineTest__TextboxHUDBuilder__

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
    ATTRIBUTE_ALIGNED16(class) TextboxHUDBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        TextboxHUDBuilder();
        TextboxHUDBuilder(const TextboxHUDBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~TextboxHUDBuilder();
        
        TextboxHUDBuilder &operator=(const TextboxHUDBuilder &);
        
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
        static TextboxHUDBuilder **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(TextboxHUDBuilder **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static TextboxHUDBuilder *create();
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static TextboxHUDBuilder *clone(const TextboxHUDBuilder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(TextboxHUDBuilder *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(TextboxHUDBuilder &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    };
}

#endif /* defined(__JLIGameEngineTest__TextboxHUDBuilder__) */
