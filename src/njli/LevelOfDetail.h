//
//  LevelOfDetail.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/26/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__LevelOfDetail__
#define __JLIGameEngineTest__LevelOfDetail__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

namespace njli {
class LevelOfDetailBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
LevelOfDetail : public AbstractFactoryObject
{
    friend class WorldFactory;

protected:
    LevelOfDetail();
    LevelOfDetail(const AbstractBuilder&);
    LevelOfDetail(const LevelOfDetail&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~LevelOfDetail();
    LevelOfDetail& operator=(const LevelOfDetail&);

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
    static LevelOfDetail** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(LevelOfDetail * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static LevelOfDetail* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static LevelOfDetail* create(const LevelOfDetailBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static LevelOfDetail* clone(const LevelOfDetail& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static LevelOfDetail* copy(const LevelOfDetail& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(LevelOfDetail * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(LevelOfDetail & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for LevelOfDetail
protected:
private:
};
}

#endif /* defined(__JLIGameEngineTest__LevelOfDetail__) */
