//
//  DeviceInputTime.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/8/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__DeviceInputTime__
#define __JLIGameEngineTest__DeviceInputTime__

#include "Util.h"
//#include "AbstractObject.h"

namespace njli {
class DeviceInputTime // : public AbstractObject
    {
public:
    virtual const char* getClassName() const { return "DeviceInputTime"; }
    virtual s32 getType() const = 0;

    void setTimeStampFrame(const f64 timeStamp) { m_timestamp_frame = timeStamp; }
    void setTimeStampTick(const f64 timeStamp) { m_timestamp_soundtick = timeStamp; }
    f64 getTimeStampFrame() const { return m_timestamp_frame; }
    f64 getTimeStampTick() const { return m_timestamp_soundtick; }

protected:
    DeviceInputTime()
        : m_timestamp_frame(0)
        , m_timestamp_soundtick(0)
    {
    }
    DeviceInputTime(const DeviceInputTime& rhs)
        : m_timestamp_frame(rhs.m_timestamp_frame)
        , m_timestamp_soundtick(rhs.m_timestamp_soundtick)
    {
    }
    DeviceInputTime& operator=(const DeviceInputTime& rhs)
    {
        if (this != &rhs) {
            m_timestamp_frame = rhs.m_timestamp_frame;
            m_timestamp_soundtick = rhs.m_timestamp_soundtick;
        }
        return *this;
    }
    ~DeviceInputTime() {}

private:
    f64 m_timestamp_frame;
    f64 m_timestamp_soundtick;
};
}

#endif /* defined(__JLIGameEngineTest__DeviceInputTime__) */
