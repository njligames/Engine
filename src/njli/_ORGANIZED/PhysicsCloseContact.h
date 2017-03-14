//
//  PhysicsCloseContact.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsCloseContact__
#define __JLIGameEngineTest__PhysicsCloseContact__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

namespace njli {
class PhysicsCloseContactBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
PhysicsCloseContact : public AbstractFactoryObject
{
    friend class WorldFactory;

protected:
    PhysicsCloseContact();
    PhysicsCloseContact(const AbstractBuilder&);
    PhysicsCloseContact(const PhysicsCloseContact&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsCloseContact();
    PhysicsCloseContact& operator=(const PhysicsCloseContact&);

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
         *  @author James Folk, 16-02-11 15:02:48
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
    static PhysicsCloseContact** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(PhysicsCloseContact * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsCloseContact* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsCloseContact* create(const PhysicsCloseContactBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsCloseContact* clone(const PhysicsCloseContact& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsCloseContact* copy(const PhysicsCloseContact& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(PhysicsCloseContact * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(PhysicsCloseContact & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for PhysicsCloseContact
protected:
private:
};
}

#endif /* defined(__JLIGameEngineTest__PhysicsCloseContact__) */
