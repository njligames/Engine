//
//  AbstractActionable.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/6/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__AbstractActionable__
#define __JLIGameEngineTest__AbstractActionable__

#include "Util.h"

//#include <vector>
#include <string>
#include <queue>
#include <vector>

namespace njli
{
    class Action;
    
    /// <#Description#>
    class AbstractActionable
    {
    protected:
        /**
         *  <#Description#>
         */
        AbstractActionable();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual ~AbstractActionable();
    public:
        /**
         *  <#Description#>
         *
         *  @param action                 <#action description#>
         *  @param callCompletionFunction <#callCompletionFunction description#>
         */
        virtual void runAction(Action *action, bool callCompletionFunction = false);
        /**
         *  <#Description#>
         *
         *  @param action                 <#action description#>
         *  @param key                    <#key description#>
         *  @param callCompletionFunction <#callCompletionFunction description#>
         */
        virtual void runAction(Action *action, const char *key, bool callCompletionFunction = false);
        
        /**
         *  <#Description#>
         *
         *  @param key <#key description#>
         *
         *  @return <#return value description#>
         */
        Action *getAction(const char *key);
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool hasActions()const;
        
        /**
         *  <#Description#>
         *
         *  @param key <#key description#>
         *
         *  @return <#return value description#>
         */
        virtual bool removeAction(const char *key);
        
        /**
         *  <#Description#>
         */
        virtual void removeAllActions();
        
    protected:
        virtual void update(f32 timeStep);
        void getAllActionNames(std::vector<std::string> &actionNames);
    private:
        AbstractActionable(const AbstractActionable &copy);
        AbstractActionable &operator=(const AbstractActionable &rhs);
        
        struct ActionableAction
        {
            ActionableAction(){}
            bool callCompletion;
            Action *action;
            std::string key;
        };
        std::vector<ActionableAction*> m_Actions;
        std::queue<ActionableAction*> m_ActionMemoryQueue;
    };
    
}

#endif /* defined(__JLIGameEngineTest__AbstractActionable__) */
