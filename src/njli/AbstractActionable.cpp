//
//  AbstractActionable.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/6/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "AbstractActionable.h"
#include "Action.h"
#include "World.h"
#include "WorldLuaVirtualMachine.h"
#include "Log.h"
#define TAG "AbstractActionable.cpp"
#define FORMATSTRING "{\"njli::AbstractActionable\":[]}";

namespace njli
{
    AbstractActionable::AbstractActionable()
    {
        for (s32 i = 0; i < 100; ++i)
        {
            m_ActionMemoryQueue.push(new ActionableAction());
        }
        m_Actions.clear();
    }
    AbstractActionable::~AbstractActionable()
    {
        while (!m_ActionMemoryQueue.empty())
        {
            ActionableAction *actionable = m_ActionMemoryQueue.front();
            delete actionable;
            actionable = NULL;
            m_ActionMemoryQueue.pop();
        }
        
        for (std::vector<ActionableAction*>::iterator iter = m_Actions.begin(); iter != m_Actions.end(); )
        {
            ActionableAction *actionable = *iter;
            delete actionable;
            actionable = NULL;
            iter = m_Actions.erase(iter);
        }
    }
    
    void AbstractActionable::runAction(Action *action, bool callCompletionFunction)
    {
        AbstractActionable::runAction(action, "key", callCompletionFunction);
    }
    
    void AbstractActionable::runAction(Action *action, const char *key, bool callCompletionFunction)
    {
        if(m_ActionMemoryQueue.empty())
        {
            DEBUG_LOG_WRITE_W(TAG, "memory is running out");
            return;
        }
        
        ActionableAction *actionable = m_ActionMemoryQueue.front();
        m_ActionMemoryQueue.pop();
        
        actionable->action = action;
        actionable->callCompletion = callCompletionFunction;
        actionable->key = key;
        
        m_Actions.push_back(actionable);
    }
    
    Action *AbstractActionable::getAction(const char *key)
    {
        for (std::vector<ActionableAction*>::iterator iter = m_Actions.begin();
             iter != m_Actions.end();++iter)
        {
            ActionableAction *actionable = *iter;
            if(actionable->key == std::string(key))
            {
                return actionable->action;
            }
        }
        return NULL;
    }
    
    bool AbstractActionable::hasActions()const
    {
        return m_Actions.size() != 0;
    }
    
    bool AbstractActionable::removeAction(const char *key)
    {
        for (std::vector<ActionableAction*>::iterator iter = m_Actions.begin();
             iter != m_Actions.end();++iter)
        {
            ActionableAction *actionable = *iter;
            if(actionable->key == std::string(key))
            {
                m_ActionMemoryQueue.push(*iter);
                iter = m_Actions.erase(iter);
                return true;
            }
        }
        return false;
    }
    
    void AbstractActionable::removeAllActions()
    {
        for (s32 i = 0; i < m_Actions.size(); ++i)
        {
            removeAction(m_Actions[i]->key.c_str());
        }
    }
    
    void AbstractActionable::update(f32 timeStep)
    {
        if(!World::getInstance()->isAnimationPaused())
        {
            for (std::vector<ActionableAction*>::iterator iter = m_Actions.begin(); iter != m_Actions.end();)
            {
                ActionableAction *actionable = *iter;
                Action *currentAction = actionable->action;
                
                currentAction->update(timeStep);
                
                if(currentAction->isFinishedRepeating() && currentAction->isFinished() && currentAction->isChildrenFinished())
                {
                    m_ActionMemoryQueue.push(actionable);
                    
                    iter = m_Actions.erase(iter);
                    
                    if(actionable->callCompletion)
                    {
                        char buffer[BUFFER_SIZE] = "__NJLINodeActionComplete";
                        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, currentAction);
                    }
                }
                else
                {
                    ++iter;
                }
            }
        }
    }
    
    void AbstractActionable::getAllActionNames(std::vector<std::string> &actionNames)
    {
        for (s32 i = 0; i < m_Actions.size(); ++i)
        {
            actionNames.push_back(m_Actions[i]->key);
        }
    }
}