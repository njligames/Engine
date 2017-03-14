//
//  WorldFacebook.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 7/6/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldFacebook.h"
#include "JLIFactoryTypes.h"

namespace njli
{
    
    WorldFacebook::WorldFacebook()
    {
        
    }

    WorldFacebook::~WorldFacebook()
    {
        
    }
    
    const char *WorldFacebook::getClassName()const
    {
        return "WorldFacebook";
    }
    
    s32 WorldFacebook::getType()const
    {
        return JLI_OBJECT_TYPE_WorldFacebook;
    }
    
    WorldFacebook::operator std::string() const
    {
        return "TODO";
    }
}
