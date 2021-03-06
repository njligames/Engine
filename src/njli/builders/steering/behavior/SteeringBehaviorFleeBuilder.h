//
//  SteeringBehaviorFleeBuilder.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehaviorFleeBuilder_hpp
#define SteeringBehaviorFleeBuilder_hpp

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
     *  Builder for <#CLASS#>
     */
    ATTRIBUTE_ALIGNED16(class) SteeringBehaviorFleeBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        SteeringBehaviorFleeBuilder();
        SteeringBehaviorFleeBuilder(const SteeringBehaviorFleeBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SteeringBehaviorFleeBuilder();
        
        SteeringBehaviorFleeBuilder &operator=(const SteeringBehaviorFleeBuilder &);
        
    public:
        /**
         *  Calculate the buffer size of this object.
         *
         *  @return The buffer size.
         */
        virtual	s32	calculateSerializeBufferSize() const;
        /**
         *  Serialize this object.
         *
         *  @param btSerializer the serializer which does the serialize.
         */
        virtual	void serialize(void*, btSerializer*) const;
        
        /**
         *  Get the type of ::jliObjectEnumType enum value, which this builder builds.
         *
         *  @return The ::jliObjectEnumType enum value.
         */
        virtual u32 getObjectType()const;
        /**
         *  The name of this class.
         *
         *  @return The name of this class.
         */
        virtual const char *getClassName()const;
        /**
         *  Get the type of ::jliObjectEnumType enum value.
         *
         *  @return The ::jliObjectEnumType enum value.
         */
        virtual s32 getType()const;
        /**
         *  The string value for this object, which can be used for debugging.
         *
         *  @return "The string value for this object.
         */
        operator std::string() const;
        
        /**
         *  Create an Array of instances of this class.
         *
         *  @param size The amount of elements in the array.
         *
         *  @return Pointer to the newly created array.
         */
        static SteeringBehaviorFleeBuilder **createArray(const u32 size);
        /**
         *  Destroy an Array of this class type.
         *
         *  @param array The Pointer to the array to delete.
         */
        static void destroyArray(SteeringBehaviorFleeBuilder **array, const u32 size = 0);
        /**
         *  Create an instance of this class.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorFleeBuilder *create();
        /**
         *  Create a clone of an instance of this class.
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorFleeBuilder *clone(const SteeringBehaviorFleeBuilder &object);
        /**
         *  Destroy an instance of this class.
         *
         *  @param object The object to destroy.
         */
        static void destroy(SteeringBehaviorFleeBuilder *object);
        /**
         *  Load a lua table representation of this class. This is used for JLIM.create(object).
         *
         *  @param object      The object to load.
         *  @param L           The current lua state.
         *  @param stack_index The stack index of the lua stack.
         */
        static void load(SteeringBehaviorFleeBuilder &object, lua_State *L, int stack_index);
        /**
         *  Get the type of ::jliObjectEnumType enum value.
         *
         *  @return The ::jliObjectEnumType enum value.
         */
        static u32 type();
    };
}



















#endif /* SteeringBehaviorFleeBuilder_hpp */
