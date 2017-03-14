//
//  btClock.hpp
//  JLIGameEngineTest
//
//  Created by James Folk on 10/1/15.
//  Copyright © 2015 James Folk. All rights reserved.
//

#ifndef btClock_hpp
#define btClock_hpp

///The btClock is a portable basic clock that measures accurate time in seconds, use for profiling.
class btClock
{
public:
    btClock();
    
    btClock(const btClock& other);
    btClock& operator=(const btClock& other);
    
    ~btClock();
    
    /// Resets the initial reference time.
    void reset();
    
    /// Returns the time in ms since the last call to reset or since
    /// the btClock was created.
    unsigned long int getTimeMilliseconds();
    
    /// Returns the time in us since the last call to reset or since
    /// the Clock was created.
    unsigned long int getTimeMicroseconds();
private:
    struct btClockData* m_data;
};

#endif /* btClock_hpp */
