//
//  Skinner.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Skinner__
#define __JLIGameEngineTest__Skinner__

#pragma mark Header

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

namespace njli {
class SkinnerBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Skinner : public AbstractFactoryObject
{
    friend class WorldFactory;

protected:
    Skinner();
    Skinner(const AbstractBuilder&);
    Skinner(const Skinner&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Skinner();
    Skinner& operator=(const Skinner&);

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
    static Skinner** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Skinner * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Skinner* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Skinner* create(const SkinnerBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Skinner* clone(const Skinner& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Skinner* copy(const Skinner& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Skinner * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Skinner & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for Skinner
protected:
private:
};
}

#endif /* defined(__JLIGameEngineTest__Skinner__) */
