//
//  Clock.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Clock__
#define __JLIGameEngineTest__Clock__

#include "AbstractBuilder.h"
#include "AbstractClock.h"
#include "AbstractFactoryObject.h"
#include "btClock.h"
#include "lua.hpp"

namespace njli {
class ClockBuilder;
/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Clock : public AbstractFactoryObject,
        public AbstractClock
{
    friend class WorldFactory;
    friend class World;

protected:
    Clock();
    Clock(const AbstractBuilder&);
    Clock(const Clock&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Clock();
    Clock& operator=(const Clock&);

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
         *  @author James Folk, 16-02-11 15:02:44
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

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
    static Clock** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Clock * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Clock* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Clock* create(const ClockBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Clock* clone(const Clock& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Clock* copy(const Clock& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Clock * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Clock & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

    //TODO: fill in specific methods for Clock

    virtual void update(f64 milliseconds);

    /// Resets the initial reference time.
    void reset();

    /// Returns the time in ms since the last call to reset or since
    /// the btClock was created.
    unsigned long int getTimeMilliseconds();

    /// Returns the time in us since the last call to reset or since
    /// the Clock was created.
    unsigned long int getTimeMicroseconds();

protected:
private:
    btClock* m_btClock;
};
}

#endif /* defined(__JLIGameEngineTest__Clock__) */
