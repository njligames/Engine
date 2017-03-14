//
//  AbstractStateMachine.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/10/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractStateMachine_h
#define JLIGameEngineTest_AbstractStateMachine_h

#include "AbstractFactoryObject.h"
//#include "AbstractBehavior.h"
#include "AbstractState.h"

#include "btQuickprof.h"
#include <queue>

namespace njli {
/// <#Description#>
template <class OWNER_TYPE>
class AbstractStateMachine : public AbstractFactoryObject {
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
    AbstractStateMachine();
    /**
         *  <#Description#>
         */
    AbstractStateMachine(const AbstractBuilder& builder);
    /**
         *  <#Description#>
         */
    AbstractStateMachine(const AbstractStateMachine& copy);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~AbstractStateMachine();

    /**
         *  <#Description#>
         *
         *  @param AbstractStateMachine& <#AbstractStateMachine& description#>
         *
         *  @return <#return value description#>
         */
    AbstractStateMachine& operator=(const AbstractStateMachine&);

public:
    /**
         *  <#Description#>
         *
         *  @param f32 <#f32 description#>
         */
    void update(f32);

    /**
         *  <#Description#>
         *
         *  @param  <# description#>
         *
         *  @return <#return value description#>
         */
    bool handleMessage(const Telegram&);

    /**
         *  <#Description#>
         *
         *  @param AbstractState<OWNER_TYPE> <#AbstractState<OWNER_TYPE> description#>
         */
    void pushState(AbstractState<OWNER_TYPE>*);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    AbstractState<OWNER_TYPE>* const getState() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    AbstractState<OWNER_TYPE>* const getPreviousState() const;

    /**
         *  <#Description#>
         *
         *  @param callExit <#callExit description#>
         */
    void clear(bool callExit = true);

public:
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* getOwner();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const AbstractFactoryObject* getOwner() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual bool hasOwner() const;

private:
    AbstractState<OWNER_TYPE>* m_pCurrentState;
    AbstractState<OWNER_TYPE>* m_pPreviousState;

    std::queue<AbstractState<OWNER_TYPE>*> m_StateQueue;

    void setState(AbstractState<OWNER_TYPE>*);
    void changeState(AbstractState<OWNER_TYPE>*);

    //        AbstractFactoryObject *m_pOwner;
};

template <class OWNER_TYPE>
AbstractStateMachine<OWNER_TYPE>::AbstractStateMachine()
    : AbstractFactoryObject(this)
    , m_pCurrentState(NULL)
    , m_pPreviousState(NULL) //,
//    m_pOwner(NULL)
{
}

template <class OWNER_TYPE>
AbstractStateMachine<OWNER_TYPE>::AbstractStateMachine(const AbstractBuilder& builder)
    : AbstractFactoryObject(this)
    , m_pCurrentState(NULL)
    , m_pPreviousState(NULL) //,
//    m_pOwner(NULL)
{
}

template <class OWNER_TYPE>
AbstractStateMachine<OWNER_TYPE>::AbstractStateMachine(const AbstractStateMachine& copy)
    : AbstractFactoryObject(this)
    , m_pCurrentState(copy.m_pCurrentState)
    , m_pPreviousState(copy.m_pPreviousState) //,
//    m_pOwner(NULL)
{
}

template <class OWNER_TYPE>
AbstractStateMachine<OWNER_TYPE>::~AbstractStateMachine()
{
    //        clear(true);

    //        if(m_pCurrentState)
    //        {
    //            m_pCurrentState->exit(dynamic_cast<OWNER_TYPE*>(getOwner()));
    //            m_pCurrentState->enableCanDelete(true);
    //        }
    //
    //        if(m_pPreviousState)
    //        {
    //            m_pPreviousState->exit(dynamic_cast<OWNER_TYPE*>(getOwner()));
    //            m_pPreviousState->enableCanDelete(true);
    //        }
    //
    //        m_pCurrentState = NULL;
    //        m_pPreviousState = NULL;
    //
    //        AbstractState<OWNER_TYPE>* theNextState = NULL;
    //        while(!m_StateQueue.empty())
    //        {
    //            theNextState = m_StateQueue.front();
    //            theNextState->exit(dynamic_cast<OWNER_TYPE*>(getOwner()));
    //            theNextState->enableCanDelete(true);
    //            m_StateQueue.pop();
    //        }
}

template <class OWNER_TYPE>
AbstractStateMachine<OWNER_TYPE>& AbstractStateMachine<OWNER_TYPE>::operator=(const AbstractStateMachine& rhs)
{
    if (this != &rhs) {
        m_pCurrentState = rhs.m_pCurrentState;
        m_pPreviousState = rhs.m_pPreviousState;
    }
    return *this;
}

template <class OWNER_TYPE>
void AbstractStateMachine<OWNER_TYPE>::update(f32 deltaTimeStep)
{
    BT_PROFILE("AbstractStateMachine::update");
    AbstractState<OWNER_TYPE>* const theCurrentState = getState();
    bool pushNextState = false;
    u32 queueSize = m_StateQueue.size();

    if (theCurrentState && (queueSize > 0)) {
        pushNextState = theCurrentState->isFinished();
    }
    else {
        pushNextState = (queueSize > 0);
    }

    if (pushNextState) {
        AbstractState<OWNER_TYPE>* theNextState = NULL;

        if (!m_StateQueue.empty()) {
            theNextState = m_StateQueue.front();
            m_StateQueue.pop();
        }

        changeState(theNextState);
    }
    else {
        if (theCurrentState)
            theCurrentState->update(dynamic_cast<OWNER_TYPE*>(getOwner()),
                deltaTimeStep);
    }
}

template <class OWNER_TYPE>
bool AbstractStateMachine<OWNER_TYPE>::handleMessage(const Telegram& msg)
{
    const AbstractState<OWNER_TYPE>* theCurrentState = getState();

    if (theCurrentState && theCurrentState->onMessage(dynamic_cast<OWNER_TYPE*>(getOwner()), msg)) {
        return true;
    }
    return false;
}

template <class OWNER_TYPE>
void AbstractStateMachine<OWNER_TYPE>::pushState(AbstractState<OWNER_TYPE>* state)
{
    if (NULL == state) {
        AbstractState<OWNER_TYPE>* theCurrentState = getState();
        if (theCurrentState) {
            theCurrentState->exit(dynamic_cast<OWNER_TYPE*>(getOwner()));
            theCurrentState->enableCanDelete(true);
        }
    }
    else {
        state->enableCanDelete(false);
        m_StateQueue.push(state);
    }
}

template <class OWNER_TYPE>
AbstractState<OWNER_TYPE>* const AbstractStateMachine<OWNER_TYPE>::getState() const
{
    return m_pCurrentState;
}

template <class OWNER_TYPE>
AbstractState<OWNER_TYPE>* const AbstractStateMachine<OWNER_TYPE>::getPreviousState() const
{
    return m_pPreviousState;
}

template <class OWNER_TYPE>
void AbstractStateMachine<OWNER_TYPE>::clear(bool callExit)
{
    AbstractState<OWNER_TYPE>* theNextState = NULL;

    if (m_pCurrentState) {
        if (callExit)
            m_pCurrentState->exit(dynamic_cast<OWNER_TYPE*>(getOwner()));
        m_pCurrentState->enableCanDelete(true);
    }

    while (!m_StateQueue.empty()) {
        theNextState = m_StateQueue.front();
        if (theNextState) {
            if (callExit)
                theNextState->exit(dynamic_cast<OWNER_TYPE*>(getOwner()));
            theNextState->enableCanDelete(true);
        }

        m_StateQueue.pop();
    }
    m_pCurrentState = NULL;
}

template <class OWNER_TYPE>
AbstractFactoryObject* AbstractStateMachine<OWNER_TYPE>::getOwner()
{
//#if defined(DEBUG) || defined(_DEBUG)
//    return dynamic_cast<AbstractFactoryObject*>(getParent());
//#else
//    DEBUG_ASSERT(dynamic_cast<AbstractFactoryObject*>(getParent()));
    return dynamic_cast<AbstractFactoryObject*>(getParent());
//#endif
    
    
    //        return m_pOwner;
}

template <class OWNER_TYPE>
const AbstractFactoryObject* AbstractStateMachine<OWNER_TYPE>::getOwner() const
{
//#if defined(DEBUG) || defined(_DEBUG)
//    return dynamic_cast<const AbstractFactoryObject*>(getParent());
//#else
//    DEBUG_ASSERT(dynamic_cast<const AbstractFactoryObject*>(getParent()));
    return dynamic_cast<const AbstractFactoryObject*>(getParent());
//#endif
    
    
    //        return m_pOwner;
}

//    template <class OWNER_TYPE>
//    void AbstractStateMachine<OWNER_TYPE>::setOwner(AbstractFactoryObject* owner)
//    {
//        m_pOwner = owner;
//    }

template <class OWNER_TYPE>
bool AbstractStateMachine<OWNER_TYPE>::hasOwner() const
{
    return (NULL != getOwner());
}

template <class OWNER_TYPE>
void AbstractStateMachine<OWNER_TYPE>::setState(AbstractState<OWNER_TYPE>* state)
{
    m_pCurrentState = state;
}

template <class OWNER_TYPE>
void AbstractStateMachine<OWNER_TYPE>::changeState(AbstractState<OWNER_TYPE>* state)
{

    AbstractState<OWNER_TYPE>* theCurrentState = getState();

    m_pPreviousState = theCurrentState;

    if (theCurrentState) {
        theCurrentState->exit(dynamic_cast<OWNER_TYPE*>(getOwner()));
        theCurrentState->enableCanDelete(true);
        //            theCurrentState->enableFinished(false);
    }

    setState(state);

    theCurrentState = getState();
    if (theCurrentState) {
        theCurrentState->enter(dynamic_cast<OWNER_TYPE*>(getOwner()));
    }
}
}

#endif
