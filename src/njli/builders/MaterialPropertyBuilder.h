//
//  MaterialPropertyBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__MaterialPropertyBuilder__
#define __JLIGameEngineTest__MaterialPropertyBuilder__

#include "btAlignedObjectArray.h"
#include "Util.h"
#include "AbstractBuilder.h"
#include "btSerializer.h"
#include "lua.hpp"

namespace njli
{
    ATTRIBUTE_ALIGNED16(class) MaterialPropertyBuilder :
//    class MaterialPropertyBuilder:
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        MaterialPropertyBuilder();
        MaterialPropertyBuilder(const MaterialPropertyBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~MaterialPropertyBuilder();
        
        MaterialPropertyBuilder &operator=(const MaterialPropertyBuilder &);
        
    public:
        /**
         *  @author James Folk, 16-02-11 15:02:01
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:04
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
        virtual	void serialize(void*dataBuffer, btSerializer*) const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:06
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual u32 getObjectType()const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:10
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const char *getClassName()const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:13
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 getType()const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:16
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
        operator std::string() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:18
         *
         *  @brief <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
        static MaterialPropertyBuilder **createArray(const u32 size);
        
        /**
         *  @author James Folk, 16-02-11 15:02:21
         *
         *  @brief <#Description#>
         *
         *  @param array <#array description#>
         *  @param size  <#size description#>
         */
        static void destroyArray(MaterialPropertyBuilder **array, const u32 size = 0);
        
        /**
         *  @author James Folk, 16-02-11 15:02:23
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
        static MaterialPropertyBuilder *create();
        
        /**
         *  @author James Folk, 16-02-11 15:02:25
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static MaterialPropertyBuilder *clone(const MaterialPropertyBuilder &object);
        
        /**
         *  @author James Folk, 16-02-11 15:02:28
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(MaterialPropertyBuilder *object);
        
        /**
         *  @author James Folk, 16-02-11 15:02:31
         *
         *  @brief <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(MaterialPropertyBuilder &object, lua_State *L, int stack_index);
        
        /**
         *  @author James Folk, 16-02-11 15:02:34
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    };
}

#endif /* defined(__JLIGameEngineTest__MaterialPropertyBuilder__) */
