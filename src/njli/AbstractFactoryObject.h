//
//  AbstractFactoryObject.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/9/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractFactoryObject_h
#define JLIGameEngineTest_AbstractFactoryObject_h

#include "btAlignedObjectArray.h"

#include "AbstractObject.h"
#include "Util.h"

//#include "AbstractBuilder.h"
#include "btSerializer.h"

namespace njli {
class AbstractBuilder;

class AbstractFactoryObject : public AbstractObject {
    friend class WorldFactory;

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    
    AbstractFactoryObject(const void* ptr);

    virtual ~AbstractFactoryObject();

public:
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

    virtual operator std::string() const = 0;

    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* create(const AbstractBuilder& builder) const;

    /**
         *  <#Description#>
         *
         *  @param shared <#shared description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* clone(bool shared = false) const;

    /**
         *  <#Description#>
         */
    virtual void destroy();

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
         */
    const void* getPointer() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u64 getPointerValue() const;

    /**
         *  <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    bool operator==(const AbstractFactoryObject& rhs) const;

    /**
         *  <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    bool operator<(const AbstractFactoryObject& rhs) const;

    /**
         *  <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    bool operator>(const AbstractFactoryObject& rhs) const;

    /**
         *  <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    bool operator!=(const AbstractFactoryObject& rhs) const;

    /**
         *  <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    bool operator<=(const AbstractFactoryObject& rhs) const;

    /**
         *  <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    bool operator>=(const AbstractFactoryObject& rhs) const;

    /**
         *  <#Description#>
         *
         *  @param serializer <#serializer description#>
         */
    virtual void serializeObject(class btSerializer* serializer) const;

protected:
    virtual bool canDelete() const;
    virtual void enableCanDelete(const bool enable = true);

    bool isRenderObject() const;
    void enableRenderObject(const bool enable = true);

private:
    AbstractFactoryObject();
    AbstractFactoryObject(const AbstractFactoryObject&);
    AbstractFactoryObject& operator=(const AbstractFactoryObject&);
    union {
        const void* m_pointer;
        u64 m_pointerVal;
    };
    bool m_canDelete;
    bool m_isRenderObject;
};
}

#endif
