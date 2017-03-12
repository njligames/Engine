//
//  SliderHUDBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SliderHUDBuilder__
#define __JLIGameEngineTest__SliderHUDBuilder__

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
    ATTRIBUTE_ALIGNED16(class) SliderHUDBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        SliderHUDBuilder();
        SliderHUDBuilder(const SliderHUDBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SliderHUDBuilder();
        
        SliderHUDBuilder &operator=(const SliderHUDBuilder &);
        
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
        static SliderHUDBuilder **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(SliderHUDBuilder **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static SliderHUDBuilder *create();
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static SliderHUDBuilder *clone(const SliderHUDBuilder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(SliderHUDBuilder *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(SliderHUDBuilder &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    };
}

#endif /* defined(__JLIGameEngineTest__SliderHUDBuilder__) */
