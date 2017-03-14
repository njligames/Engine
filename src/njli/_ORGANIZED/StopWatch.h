//
//  StopWatch.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__StopWatch__
#define __JLIGameEngineTest__StopWatch__

#include "AbstractBuilder.h"
#include "AbstractClock.h"
#include "AbstractFactoryObject.h"
#include "btClock.h"
#include "lua.hpp"

namespace njli {
class StopWatchBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
StopWatch : public AbstractFactoryObject,
            public AbstractClock
{
    friend class WorldFactory;

protected:
    StopWatch();
    StopWatch(const AbstractBuilder&);
    StopWatch(const StopWatch&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~StopWatch();
    StopWatch& operator=(const StopWatch&);

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

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
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

    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    static StopWatch** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(StopWatch * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static StopWatch* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static StopWatch* create(const StopWatchBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static StopWatch* clone(const StopWatch& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static StopWatch* copy(const StopWatch& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(StopWatch * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(StopWatch & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

    /**
         *  <#Description#>
         *
         *  @param milliseconds <#milliseconds description#>
         */
    virtual void update(f64 milliseconds);

public:
    //TODO: fill in specific methods for StopWatch

    //Start or continue the current lap.
    void start();

    unsigned long int getMilliseconds(s32 index = -1);

    //stop the current lap
    void stop();

    bool isStopped() const;

    //stop the current lap and start a new lap.
    bool lap();

    void clearLaps();

    //return the current number of laps.
    u64 numberOfLaps();

protected:
private:
    std::vector<unsigned long int> m_Laps;
    btClock* m_CurrentClock;
    bool m_IsStopped;
    unsigned long int m_StoppedMilliseconds;
};
}

#endif /* defined(__JLIGameEngineTest__StopWatch__) */
