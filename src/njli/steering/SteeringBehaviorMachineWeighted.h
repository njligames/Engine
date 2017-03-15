//
//  SteeringBehaviorMachineWeighted.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehaviorMachineWeighted_hpp
#define SteeringBehaviorMachineWeighted_hpp

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "btVector3.h"

#include "SteeringBehaviorMachine.h"

namespace njli
{
    class SteeringBehaviorMachineWeightedBuilder;
    class Node;
    class SteeringBehavior;
    
    
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) SteeringBehaviorMachineWeighted:
    public SteeringBehaviorMachine
    {
        friend class WorldFactory;
    protected:
        SteeringBehaviorMachineWeighted();
        SteeringBehaviorMachineWeighted(const AbstractBuilder&);
        SteeringBehaviorMachineWeighted(const SteeringBehaviorMachineWeighted &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SteeringBehaviorMachineWeighted();
        SteeringBehaviorMachineWeighted &operator=(const SteeringBehaviorMachineWeighted &);
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
        static SteeringBehaviorMachineWeighted **createArray(const u32 size);
        /**
         *  Destroy an Array of this class type.
         *
         *  @param array The Pointer to the array to delete.
         */
        static void destroyArray(SteeringBehaviorMachineWeighted **array, const u32 size = 0);
        /**
         *  Create an instance of this class.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachineWeighted *create();
        /**
         *  Create an instance of this class using a builder.
         *
         *  @param builder The builder to use for construction
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachineWeighted *create(const SteeringBehaviorMachineWeightedBuilder &builder);
        /**
         *  Create a shallow copy of an instance of this class (sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachineWeighted *clone(const SteeringBehaviorMachineWeighted &object);
        /**
         *  Create a deep copy of an instance of this class (NOT sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachineWeighted *copy(const SteeringBehaviorMachineWeighted &object);
        /**
         *  Destroy an instance of this class.
         *
         *  @param object The object to destroy.
         */
        static void destroy(SteeringBehaviorMachineWeighted *object);
        /**
         *  Load a lua table representation of this class. This is used for JLIM.create(object).
         *
         *  @param object      The object to load.
         *  @param L           The current lua state.
         *  @param stack_index The stack index of the lua stack.
         */
        static void load(SteeringBehaviorMachineWeighted &object, lua_State *L, int stack_index);
        /**
         *  Get the type of ::jliObjectEnumType enum value.
         *
         *  @return The ::jliObjectEnumType enum value.
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for SteeringBehaviorMachineDithered
        
        virtual const btVector3 &calculateSteeringForce();
    protected:
    private:
        
    };
}

#endif /* SteeringBehaviorMachineWeighted_hpp */
