//
//  DropdownHUD.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__DropdownHUD__
#define __JLIGameEngineTest__DropdownHUD__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "lua.hpp"

namespace njli {
class DropdownHUDBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
DropdownHUD : public AbstractFactoryObject,
              public AbstractFrameBufferObject
{
    friend class WorldFactory;

protected:
    DropdownHUD();
    DropdownHUD(const AbstractBuilder&);
    DropdownHUD(const DropdownHUD&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~DropdownHUD();
    DropdownHUD& operator=(const DropdownHUD&);
    virtual void renderFunction(Camera * camera);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;
    using AbstractFrameBufferObject::isHidden;
    using AbstractFrameBufferObject::hide;
    using AbstractFrameBufferObject::show;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:28
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
    static DropdownHUD** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(DropdownHUD * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static DropdownHUD* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static DropdownHUD* create(const DropdownHUDBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static DropdownHUD* clone(const DropdownHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static DropdownHUD* copy(const DropdownHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(DropdownHUD * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(DropdownHUD & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for DropdownHUD
protected:
private:
};
}

#endif /* defined(__JLIGameEngineTest__DropdownHUD__) */
