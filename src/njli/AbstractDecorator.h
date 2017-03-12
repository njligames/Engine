//
//  AbstractDecorator.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/15/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractDecorator_h
#define JLIGameEngineTest_AbstractDecorator_h

#include "Util.h"
#include <vector>
#include <string>

namespace njli
{
    class AbstractDecorator
    {
    protected:
        AbstractDecorator();
        virtual ~AbstractDecorator();

        AbstractDecorator *getParent();
        const AbstractDecorator *getParent() const;
        bool hasParent()const;
        virtual void setParent(AbstractDecorator *parent);
        void removeParent();
        bool removeFromParent();
        
        AbstractDecorator *findChild(const char *name);
        const AbstractDecorator *findChild(const char *name) const;
        AbstractDecorator* getChild(const u32 index);
        const AbstractDecorator *getChild(const u32 index) const;
        void getChildren(std::vector<AbstractDecorator*> &children)const;
        s32 getChildIndex(AbstractDecorator *object)const;
        s32 getChildIndex(const AbstractDecorator *object)const;
        bool hasChild(AbstractDecorator *object)const;
        bool hasChildren()const;
        void addChild(AbstractDecorator *object);
        void removeChild(const u32 index);
        void removeChild(AbstractDecorator *object);
        void removeChildren();
        s64 numberOfChildren()const;
        void replaceChild(AbstractDecorator *oldChild, AbstractDecorator *newChild);
    public:
        /**
         *  <#Description#>
         *
         *  @param name <#name description#>
         */
        void setName(const char *name);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const char *getName()const;
    private:
        AbstractDecorator(const AbstractDecorator &);
        AbstractDecorator &operator=(const AbstractDecorator &rhs);
    
        std::vector<AbstractDecorator*> m_Children;
        AbstractDecorator *m_pParent;
        
        std::string m_Name;
};
}

#endif
