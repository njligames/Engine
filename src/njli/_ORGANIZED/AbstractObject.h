//
//  AbstractObject.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/9/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractObject_h
#define JLIGameEngineTest_AbstractObject_h

#include "Util.h"
#include <string>
#include "AbstractDecorator.h"

namespace njli
{
    /// <#Description#>
    class AbstractObject :
    public AbstractDecorator
    {
    protected:
//        using AbstractDecorator::AbstractDecorator;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual ~AbstractObject(){}
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const char *getClassName()const = 0;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 getType()const = 0;
    
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual operator std::string() const = 0;
    };
}

#endif
