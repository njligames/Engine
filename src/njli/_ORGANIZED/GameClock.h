//
//  GameClock.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__GameClock__
#define __JLIGameEngineTest__GameClock__

#include <string>
#include "AbstractClock.h"

namespace njli
{
    class GameClock :
    public AbstractClock
    {
    public:
        GameClock();
        virtual ~GameClock();
        operator std::string() const;
        
        virtual void update(f64 milliseconds);
        //TODO: fill in specific methods for GameClock
    protected:
    private:
        GameClock(const GameClock &);
        GameClock &operator=(const GameClock &);
    };
}

#endif /* defined(__JLIGameEngineTest__GameClock__) */
