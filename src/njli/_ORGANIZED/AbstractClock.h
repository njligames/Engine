//
//  AbstractClock.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/6/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__AbstractClock__
#define __JLIGameEngineTest__AbstractClock__

#include "Util.h"
#include <string>


namespace njli
{
    /// <#Description#>
    class AbstractClock
    {
    public:
        /**
         *  <#Description#>
         */
        AbstractClock():m_rawtime(0){}
        /**
         *  <#Description#>
         *
         *  @param copy <#copy description#>
         *
         *  @return <#return value description#>
         */
        AbstractClock(const AbstractClock &copy):m_rawtime(copy.m_rawtime){}
        /**
         *  <#Description#>
         *
         *  @param copy <#copy description#>
         *
         *  @return <#return value description#>
         */
        AbstractClock &operator=(const AbstractClock &copy)
        {
            if (this != &copy)
            {
                m_rawtime = copy.m_rawtime;
            }
            return *this;
        }
        virtual ~AbstractClock(){}
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        operator std::string() const
        {
            char buffer[BUFFER_SIZE] = "";
            
            int milliseconds = getRawTime() % 1000;
            int seconds = ((getRawTime() / 1000)) % 60;
            int minutes = ((getRawTime() / 1000) / (60)) % 60;
            int hours   = ((getRawTime() / 1000) / (60 * 24)) % 24;
            
            sprintf(buffer, "%.2d:%.2d:%.2d.%.4d", hours, minutes, seconds, milliseconds);
            
            return std::string(buffer);
        }
        
        /**
         *  <#Description#>
         *
         *  @param milliseconds <#milliseconds description#>
         */
        void setRawTime(const s64 milliseconds)
        {
            m_rawtime = static_cast<time_t>(milliseconds);
        }
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s64 getRawTime()const
        {
            return m_rawtime;
        }
        
        /**
         *  <#Description#>
         *
         *  @param milliseconds <#milliseconds description#>
         */
        virtual void update(f64 milliseconds) = 0;
    private:
        
        time_t m_rawtime;
    };
}

#endif /* defined(__JLIGameEngineTest__AbstractClock__) */
