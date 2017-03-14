//
//  Timer.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Timer__
#define __JLIGameEngineTest__Timer__

#include "AbstractBuilder.h"
#include "AbstractClock.h"
#include "AbstractFactoryObject.h"
#include "btClock.h"
#include "lua.hpp"

namespace njli {
class TimerBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Timer : public AbstractFactoryObject
{
    friend class WorldFactory;

protected:
    Timer();
    Timer(const AbstractBuilder&);
    Timer(const Timer&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Timer();
    Timer& operator=(const Timer&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;
    /**
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void*, btSerializer*) const;

    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    operator std::string() const;

    static Timer** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Timer * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Timer* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Timer* create(const TimerBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Timer* clone(const Timer& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Timer* copy(const Timer& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Timer * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Timer & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    virtual void tick();

    //TODO: fill in specific methods for Timer

    void start(unsigned long int totalMilliseconds);
    void enablePause(bool enable = true);
    bool isPaused() const;
    bool isFinished() const;

    unsigned long int getTimeMillisecondsLeft() const;

protected:
private:
    btClock* m_Clock;
    long int m_CurrentTime;
    bool m_IsPaused;
};
}

#endif /* defined(__JLIGameEngineTest__Timer__) */
