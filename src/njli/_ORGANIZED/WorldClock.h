//
//  WorldClock.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldClock__
#define __JLIGameEngineTest__WorldClock__

#include "AbstractClock.h"
#include "AbstractObject.h"
#include "btClock.h"
#include <string>

namespace njli {
/// <#Description#>
class WorldClock : public AbstractClock,
                   public AbstractObject,
                   public btClock {
public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    /**
         *  <#Description#>
         */
    WorldClock();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~WorldClock();

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

public:
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f64 totalMilliseconds() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 timeStep() const;

    /**
         *  <#Description#>
         *
         *  @param milliseconds <#milliseconds description#>
         */
    virtual void update(f64 milliseconds);
    //TODO: fill in specific methods for WorldClock

protected:
private:
    WorldClock(const WorldClock&);
    WorldClock& operator=(const WorldClock&);

    f32 m_TimeStep;
    f64 m_TotalMilliseconds;
};
}

#endif /* defined(__JLIGameEngineTest__WorldClock__) */
