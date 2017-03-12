//
//  AbstractState.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/10/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractState_h
#define JLIGameEngineTest_AbstractState_h

//#include "btAlignedAllocator.h"
#include "AbstractBuilder.h"
#include "Util.h"
#include "btScalar.h"
#include <stdlib.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

namespace njli {
class Telegram;

/// <#Description#>
template <class OBJECT_TYPE>
class AbstractState : public AbstractFactoryObject {
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
    AbstractState();
    /**
         *  <#Description#>
         */
    AbstractState(const AbstractBuilder& builder);
    /**
         *  <#Description#>
         */
    AbstractState(const AbstractState& copy);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~AbstractState() = 0;

    /**
         *  <#Description#>
         *
         *  @param AbstractState& <#AbstractState& description#>
         *
         *  @return <#return value description#>
         */
    AbstractState& operator=(const AbstractState&);

public:
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual bool isFinished() const;
    /**
         *  <#Description#>
         *
         *  @param bool <#bool description#>
         */
    virtual void enableFinished(const bool = true);

    /**
         *  <#Description#>
         *
         *  @param OBJECT_TYPE <#OBJECT_TYPE description#>
         */
    virtual void enter(OBJECT_TYPE*) = 0;
    /**
         *  <#Description#>
         *
         *  @param OBJECT_TYPE <#OBJECT_TYPE description#>
         *  @param f32         <#f32 description#>
         */
    virtual void update(OBJECT_TYPE*, f32) = 0;
    /**
         *  <#Description#>
         *
         *  @param OBJECT_TYPE <#OBJECT_TYPE description#>
         */
    virtual void exit(OBJECT_TYPE*) = 0;
    /**
         *  <#Description#>
         *
         *  @param OBJECT_TYPE <#OBJECT_TYPE description#>
         *  @param Telegram&   <#Telegram& description#>
         *
         *  @return <#return value description#>
         */
    virtual bool onMessage(OBJECT_TYPE*, const Telegram&) const = 0;

    virtual void enableCanDelete(const bool enable = true);

private:
    bool m_isFinished;
};

template <class OBJECT_TYPE>
AbstractState<OBJECT_TYPE>::AbstractState()
    : AbstractFactoryObject(this)
    , m_isFinished(true)
{
}

template <class OBJECT_TYPE>
AbstractState<OBJECT_TYPE>::AbstractState(const AbstractBuilder& builder)
    : AbstractFactoryObject(this)
    , m_isFinished(true)
{
}

template <class OBJECT_TYPE>
AbstractState<OBJECT_TYPE>::AbstractState(const AbstractState& copy)
    : AbstractFactoryObject(this)
    , m_isFinished(copy.m_isFinished)
{
}

template <class OBJECT_TYPE>
AbstractState<OBJECT_TYPE>::~AbstractState()
{
}

template <class OBJECT_TYPE>
AbstractState<OBJECT_TYPE>& AbstractState<OBJECT_TYPE>::operator=(const AbstractState& rhs)
{
    if (this != &rhs) {
        m_isFinished = rhs.m_isFinished;
    }
    return *this;
}

template <class OBJECT_TYPE>
bool AbstractState<OBJECT_TYPE>::isFinished() const
{
    return m_isFinished;
}

template <class OBJECT_TYPE>
void AbstractState<OBJECT_TYPE>::enableFinished(const bool finished)
{
    m_isFinished = finished;
}

template <class OBJECT_TYPE>
void AbstractState<OBJECT_TYPE>::enableCanDelete(const bool enable)
{
    AbstractFactoryObject::enableCanDelete(enable);
}

class Telegram {
public:
    //the entity that sent this telegram
    AbstractFactoryObject* Sender;

    //the entity that is to receive this telegram
    AbstractFactoryObject* Receiver;

    //the message itself. These are all enumerated in the file
    //"MessageTypes.h"
    s32 Msg;

    //messages can be dispatched immediately or delayed for a specified amount
    //of time. If a delay is necessary this field is stamped with the time
    //the message should be dispatched.
    f32 DispatchTime;

    //any additional information that may accompany the message
    void* ExtraInfo;

    Telegram()
        : Sender(NULL)
        , Receiver(NULL)
        , Msg(0)
        , DispatchTime(0) //,
    //ExtraInfo(0)
    {
    }

    Telegram(f32 time,
        AbstractFactoryObject* sender,
        AbstractFactoryObject* receiver,
        s32 msg,
        void* info = NULL)
        : Sender(sender)
        , Receiver(receiver)
        , Msg(msg)
        , DispatchTime(time)
        , ExtraInfo(info)
    {
    }
};
}

#endif
