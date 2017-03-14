//
//  WorldFacebook.h
//  JLIGameEngineTest
//
//  Created by James Folk on 7/6/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldFacebook__
#define __JLIGameEngineTest__WorldFacebook__

#include "AbstractObject.h"
#include <string>

namespace njli {
/// <#Description#>
class WorldFacebook : public AbstractObject {
public:
    /**
         *  <#Description#>
         */
    WorldFacebook();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~WorldFacebook();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    operator std::string() const;

    //TODO: fill in specific methods for WorldFacebook

    void login();
    void logout();

    void inviteToApp();

protected:
private:
    WorldFacebook(const WorldFacebook&);
    WorldFacebook& operator=(const WorldFacebook&);
};
}

#endif /* defined(__JLIGameEngineTest__WorldFacebook__) */
