//
//  Thread.hpp
//  JLIGameEngineTest
//
//  Created by James Folk on 10/1/15.
//  Copyright © 2015 James Folk. All rights reserved.
//

#ifndef Thread_hpp
#define Thread_hpp

#pragma mark Header

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "Log.h"
#include "lua.hpp"

extern "C" {
#include "pthread.h"
}

typedef void(JLIthreadcallback(void*));

namespace njli {
class ThreadBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Thread : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend struct wrap;
    friend class Node;

protected:
    Thread();
    Thread(const AbstractBuilder&);
    Thread(const Thread&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Thread();
    Thread& operator=(const Thread&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  Calculate the buffer size of this object.
         *
         *  @return The buffer size.
         */
    virtual s32 calculateSerializeBufferSize() const;
    /**
         *  Serialize this object.
         *
         *  @param btSerializer the serializer which does the serialize.
         */
    virtual void serialize(void*, btSerializer*) const;

    /**
         *  The name of this class.
         *
         *  @return The name of this class.
         */
    virtual const char* getClassName() const;
    /**
         *  Get the type of ::njliObjectEnumType enum value.
         *
         *  @return The ::njliObjectEnumType enum value.
         */
    virtual s32 getType() const;
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
    static Thread** createArray(const u32 size);
    /**
         *  Destroy an Array of this class type.
         *
         *  @param array The Pointer to the array to delete.
         */
    static void destroyArray(Thread * *array, const u32 size);
    /**
         *  Create an instance of this class.
         *
         *  @return Pointer to the newly created instance.
         */
    static Thread* create();
    /**
         *  Create an instance of this class using a builder.
         *
         *  @param builder The builder to use for construction
         *
         *  @return Pointer to the newly created instance.
         */
    static Thread* create(const ThreadBuilder& builder);
    /**
         *  Create a shallow copy of an instance of this class (sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
    static Thread* clone(const Thread& object);
    /**
         *  Create a deep copy of an instance of this class (NOT sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
    static Thread* copy(const Thread& object);
    /**
         *  Destroy an instance of this class.
         *
         *  @param object The object to destroy.
         */
    static void destroy(Thread * object);
    /**
         *  Load a lua table representation of this class. This is used for JLIM.create(object).
         *
         *  @param object      The object to load.
         *  @param L           The current lua state.
         *  @param stack_index The stack index of the lua stack.
         */
    static void load(Thread & object, lua_State * L, int stack_index);
    /**
         *  Get the type of ::njliObjectEnumType enum value.
         *
         *  @return The ::njliObjectEnumType enum value.
         */
    static u32 type();

public:
    //TODO: fill in specific methods for Thread

    void setup(const std::string& luaFunctionName, int _priority);

    void enablePause(bool enable = true);
    bool isPaused() const;
    void stop();
    void run();

protected:
    void setup(JLIthreadcallback * _JLIthreadcallback, void* _userdata,
        int _priority);

private:
    unsigned char m_state;

    int m_priority;

    pthread_t m_thread;
    unsigned int m_thread_hdl;

    JLIthreadcallback* m_JLIthreadcallback;

    void* m_userdata;
};

enum SIO2_THREAD_PRIORITY {
    SIO2_THREAD_PRIORITY_VERY_LOW = 15,
    SIO2_THREAD_PRIORITY_LOW = 23,
    SIO2_THREAD_PRIORITY_NORMAL = 31,
    SIO2_THREAD_PRIORITY_HIGH = 39,
    SIO2_THREAD_PRIORITY_VERY_HIGH = 47

};

enum SIO2_STATE {
    SIO2_STOP = 0,
    SIO2_PLAY,
    SIO2_PAUSE

};

struct wrap {
    //        char * msg;
    Thread ins;

    wrap(const Thread& f)
        : ins(f)
    {
    }
};
}

#endif /* Thread_hpp */
