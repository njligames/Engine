//
//  LevelOfDetailBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/26/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__LevelOfDetailBuilder__
#define __JLIGameEngineTest__LevelOfDetailBuilder__

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
    ATTRIBUTE_ALIGNED16(class) LevelOfDetailBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        LevelOfDetailBuilder();
        LevelOfDetailBuilder(const LevelOfDetailBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~LevelOfDetailBuilder();
        
        LevelOfDetailBuilder &operator=(const LevelOfDetailBuilder &);
        
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:55
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
        static LevelOfDetailBuilder **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(LevelOfDetailBuilder **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static LevelOfDetailBuilder *create();
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static LevelOfDetailBuilder *clone(const LevelOfDetailBuilder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(LevelOfDetailBuilder *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(LevelOfDetailBuilder &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    };
}

#endif /* defined(__JLIGameEngineTest__LevelOfDetailBuilder__) */
