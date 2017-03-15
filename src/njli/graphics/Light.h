//
//  Light.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Light__
#define __JLIGameEngineTest__Light__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

namespace njli {
class LightBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Light : public AbstractFactoryObject
{
    friend class WorldFactory;

protected:
    Light();
    Light(const AbstractBuilder&);
    Light(const Light&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Light();
    Light& operator=(const Light&);

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
         *  @author James Folk, 16-02-11 15:02:02
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
    static Light** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Light * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Light* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Light* create(const LightBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Light* clone(const Light& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Light* copy(const Light& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Light * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Light & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

    //TODO: fill in specific methods for Light
protected:
private:
};
}

#endif /* defined(__JLIGameEngineTest__Light__) */
