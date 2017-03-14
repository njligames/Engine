//
//  AbstractBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/9/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractBuilder_h
#define JLIGameEngineTest_AbstractBuilder_h

//#include "btAlignedObjectArray.h"
#include "AbstractFactoryObject.h"
#include "Util.h"
#include "btSerializer.h"
//#include "AbstractBuilder.h"
#include <string>

namespace njli {
/// <#Description#>
class AbstractBuilder : public AbstractFactoryObject {
    friend class WorldFactory;

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
         */
    AbstractBuilder();
    /**
         *  <#Description#>
         */
    AbstractBuilder(const AbstractBuilder&);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~AbstractBuilder();
    /**
         *  <#Description#>
         *
         *  @param  <# description#>
         *
         *  @return <#return value description#>
         */
    AbstractBuilder& operator=(const AbstractBuilder&);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const = 0;
    /**
         *  <#Description#>
         *
         *  @param dataBuffer <#dataBuffer description#>
         *  @param serializer <#serializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer* serializer) const = 0;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual u32 getObjectType() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const = 0;

    //TODO: fill in specific methods for AbstractBuilder
protected:
private:
};
}

#endif
