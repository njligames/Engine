//
//  JsonJLI.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__JsonJLI__
#define __JLIGameEngineTest__JsonJLI__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

#include "json/json.h"

namespace njli {
class JsonJLIBuilder;
/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
JsonJLI : public AbstractFactoryObject
{
    friend class WorldFactory;

protected:
    JsonJLI();
    JsonJLI(const AbstractBuilder&);
    JsonJLI(const JsonJLI&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~JsonJLI();
    JsonJLI& operator=(const JsonJLI&);

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
         *  @author James Folk, 16-02-11 15:02:16
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
    static JsonJLI** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(JsonJLI * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static JsonJLI* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static JsonJLI* create(const JsonJLIBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static JsonJLI* clone(const JsonJLI& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static JsonJLI* copy(const JsonJLI& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(JsonJLI * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(JsonJLI & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for JsonJLI
    static std::string parse(const char* str, bool compact = false);

    bool parseJson(const char* str);

    void addValue(const std::string& key, const std::string& value);
    void addValue(const std::string& key, const JsonJLI& value);

    std::string getValue(const std::string& key);

    void append(const std::string& value);
    void append(const JsonJLI& value);

protected:
private:
    Json::Value m_value;
};
}

#endif /* defined(__JLIGameEngineTest__JsonJLI__) */
