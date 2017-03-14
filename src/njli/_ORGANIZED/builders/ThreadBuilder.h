//
//  ThreadBuilder.hpp
//  JLIGameEngineTest
//
//  Created by James Folk on 10/1/15.
//  Copyright © 2015 James Folk. All rights reserved.
//

#ifndef ThreadBuilder_hpp
#define ThreadBuilder_hpp

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
     *  Builder for Thread
     */
    ATTRIBUTE_ALIGNED16(class) ThreadBuilder :
    public AbstractBuilder
    {
        friend class WorldFactory;
    protected:
        ThreadBuilder();
        ThreadBuilder(const ThreadBuilder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~ThreadBuilder();
        
        ThreadBuilder &operator=(const ThreadBuilder &);
        
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
         *  Get the type of ::njliObjectEnumType enum value, which this builder builds.
         *
         *  @return The ::njliObjectEnumType enum value.
         */
        virtual u32 getObjectType()const;
        /**
         *  The name of this class.
         *
         *  @return The name of this class.
         */
        virtual const char *getClassName()const;
        /**
         *  Get the type of ::njliObjectEnumType enum value.
         *
         *  @return The ::njliObjectEnumType enum value.
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
        static ThreadBuilder **createArray(const u32 size);
        /**
         *  Destroy an Array of this class type.
         *
         *  @param array The Pointer to the array to delete.
         */
        static void destroyArray(ThreadBuilder **array, const u32 size);
        /**
         *  Create an instance of this class.
         *
         *  @return Pointer to the newly created instance.
         */
        static ThreadBuilder *create();
        /**
         *  Create a clone of an instance of this class.
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
        static ThreadBuilder *clone(const ThreadBuilder &object);
        /**
         *  Destroy an instance of this class.
         *
         *  @param object The object to destroy.
         */
        static void destroy(ThreadBuilder *object);
        /**
         *  Load a lua table representation of this class. This is used for JLIM.create(object).
         *
         *  @param object      The object to load.
         *  @param L           The current lua state.
         *  @param stack_index The stack index of the lua stack.
         */
        static void load(ThreadBuilder &object, lua_State *L, int stack_index);
        /**
         *  Get the type of ::njliObjectEnumType enum value.
         *
         *  @return The ::njliObjectEnumType enum value.
         */
        static u32 type();
    };
}



















#endif /* ThreadBuilder_hpp */
