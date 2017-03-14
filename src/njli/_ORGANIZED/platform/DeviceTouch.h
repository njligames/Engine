//
//  DeviceTouch.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/8/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__DeviceTouch__
#define __JLIGameEngineTest__DeviceTouch__

#include "DeviceInputTime.h"
//#include "JLIFactoryTypes.h"
#include "btVector2.h"
#include <string>

namespace njli {
class DeviceTouch : public DeviceInputTime {
public:
    DeviceTouch()
        : m_xpos(0)
        , m_ypos(0)
        , m_prev_xpos(0)
        , m_prev_ypos(0)
        , m_address(0)
        , m_tapCount(0)
        , m_touchIndex(0)
        , m_touchTotal(0)
    , m_scale(1.0f)
    {
    }

    DeviceTouch(const DeviceTouch& rhs)
        : m_xpos(rhs.m_xpos)
        , m_ypos(rhs.m_ypos)
        , m_prev_xpos(rhs.m_prev_xpos)
        , m_prev_ypos(rhs.m_prev_ypos)
        , m_address(rhs.m_address)
        , m_tapCount(rhs.m_tapCount)
        , m_touchIndex(rhs.m_touchIndex)
    , m_touchTotal(rhs.m_touchTotal)
    , m_scale(rhs.m_scale)
    {
    }

    DeviceTouch& operator=(const DeviceTouch& rhs)
    {
        if (this != &rhs) {
            m_xpos = rhs.m_xpos;
            m_ypos = rhs.m_ypos;
            m_prev_xpos = rhs.m_prev_xpos;
            m_prev_ypos = rhs.m_prev_ypos;

            m_address = rhs.m_address;
            m_tapCount = rhs.m_tapCount;
            m_touchIndex = rhs.m_touchIndex;
            m_touchTotal = rhs.m_touchTotal;
            m_scale = rhs.m_scale;
        }
        return *this;
    }

    DeviceTouch(const void* touch, int n, int N)
    {
        set(touch, n, N);
    }

    virtual ~DeviceTouch() {}

    virtual const char* getClassName() const { return "DeviceTouch"; }
    virtual s32 getType() const { return 0; }
    operator std::string() const
    {
        char buffer[1024];

        sprintf(buffer, "\n\
                    Current Pos [%.0f, %.0f]\n\
                    Previous Pos [%.0f, %.0f]\n\
                    Frame [%f]\n\
                    Tick [%f]\n\
                    Address [%lu]\n\
                    TapCount [%lu]\n\
                    Touch %d of %d\n",
            m_xpos, m_ypos,
            m_prev_xpos, m_prev_ypos,
            //                    m_pos.x(), m_pos.y(),
            //                    m_prev_pos.x(), m_prev_pos.y(),
            getTimeStampFrame(), getTimeStampTick(),
            m_address, m_tapCount,
            m_touchIndex + 1, m_touchTotal);
        return std::string(buffer);
    }

    btVector2 getPosition() const
    {
        return btVector2(m_xpos,
                         m_ypos);
    }
    btVector2 getPreviousPosition() const
    {
        return btVector2(m_prev_xpos,
                         m_prev_ypos);
    }
    unsigned int getAddress() const { return m_address; }
    unsigned int getTapCount() const { return m_tapCount; }
    unsigned int getTouchIndex() const { return m_touchIndex; }
    unsigned int getTouchTotal() const { return m_touchTotal; }

    void set(const void* touch, int n, int N)
    {
        convert(*this, touch);

        m_touchIndex = n;
        m_touchTotal = N;
    }
    void set(u32 x, u32 y, int n, int N, float scaleFactor)
    {
        setTimeStampFrame(0);
        m_xpos = x * scaleFactor;
        m_ypos = y * scaleFactor;
        m_prev_xpos = 0;
        m_prev_ypos = 0;
        m_address = 0;
        m_tapCount = 0;
        m_scale = scaleFactor;
    }

    float getScale()const {return m_scale ;}
    
    static const u8 MAX_TOUCHES;

private:
    void convert(DeviceTouch& t, const void* touch);

    f32 m_xpos;
    f32 m_ypos;
    f32 m_prev_xpos;
    f32 m_prev_ypos;
    unsigned long m_address;
    unsigned long m_tapCount;
    u32 m_touchIndex;
    u32 m_touchTotal;
    f32 m_scale;
};
}

#endif /* defined(__JLIGameEngineTest__DeviceTouch__) */
