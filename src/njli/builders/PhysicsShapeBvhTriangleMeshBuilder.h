//
//  PhysicsShapeBvhTriangleMeshBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeBvhTriangleMeshBuilder__
#define __JLIGameEngineTest__PhysicsShapeBvhTriangleMeshBuilder__

#pragma mark Header

#include "btAlignedObjectArray.h"
#include "Util.h"
#include "AbstractBuilder.h"
#include "btSerializer.h"
#include "lua.hpp"

#include "Log.h"


namespace njli
{
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeBvhTriangleMeshBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeBvhTriangleMeshBuilder();
        PhysicsShapeBvhTriangleMeshBuilder(const PhysicsShapeBvhTriangleMeshBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeBvhTriangleMeshBuilder();
        
        PhysicsShapeBvhTriangleMeshBuilder &operator=(const PhysicsShapeBvhTriangleMeshBuilder &);
        
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
        static PhysicsShapeBvhTriangleMeshBuilder **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeBvhTriangleMeshBuilder **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBvhTriangleMeshBuilder *create();
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBvhTriangleMeshBuilder *clone(const PhysicsShapeBvhTriangleMeshBuilder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeBvhTriangleMeshBuilder *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeBvhTriangleMeshBuilder &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeBvhTriangleMeshBuilder__) */
