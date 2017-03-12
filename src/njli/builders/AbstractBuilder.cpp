//
//  AbstractBuilder.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "AbstractBuilder.h"

#include "JLIFactoryTypes.h"

namespace njli
{
    AbstractBuilder::AbstractBuilder():
    AbstractFactoryObject(this)
    {
        
    }
    
    AbstractBuilder::AbstractBuilder(const AbstractBuilder &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    AbstractBuilder::~AbstractBuilder()
    {
        
    }
    
    AbstractBuilder &AbstractBuilder::operator=(const AbstractBuilder &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
}
