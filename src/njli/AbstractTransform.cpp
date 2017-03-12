//
//  AbstractTransform.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 12/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "AbstractTransform.h"

#include "btTransform.h"
#include "btQuaternion.h"
#include "btVector3.h"
#include "btVector2.h"
#include "Util.h"

namespace njli
{
    AbstractTransform::AbstractTransform():
    m_WorldTransform(new btTransform(btTransform::getIdentity())),
    m_Orientation(new btQuaternion(btQuaternion::getIdentity())),
    m_Pivot(new btTransform(btTransform::getIdentity()))
    {
    }

    AbstractTransform::AbstractTransform(const AbstractTransform &copy):
    m_WorldTransform(new btTransform(*copy.m_WorldTransform)),
    m_Orientation(new btQuaternion(*copy.m_Orientation)),
    m_Pivot(new btTransform(*copy.m_Pivot))
    {
    }

    AbstractTransform::~AbstractTransform()
    {
        delete m_Pivot;m_Pivot = NULL;
        delete m_Orientation;m_Orientation = NULL;
        delete m_WorldTransform;m_WorldTransform = NULL;
    }

    AbstractTransform &AbstractTransform::operator=(const AbstractTransform &rhs)
    {
        if (this != &rhs)
        {
            *m_WorldTransform = *rhs.m_WorldTransform;
        }
        return *this;
    }

    btTransform &AbstractTransform::getTransform()const
    {
        return *m_WorldTransform;
    }

    void AbstractTransform::setTransform(const btTransform &transform)
    {
        *m_WorldTransform = transform;
    }

    btVector3 &AbstractTransform::getOrigin()const
    {
        return m_WorldTransform->getOrigin();
    }

    void AbstractTransform::setOrigin(const btVector3 &origin)
    {
        m_WorldTransform->setOrigin(origin);
    }
    
    void AbstractTransform::setOrigin(const btVector2 &origin)
    {
        btVector3 v = getOrigin();
        setOrigin(btVector3(origin.x(), origin.y(), v.z()));
    }

    btQuaternion AbstractTransform::getRotation()const
    {
        return m_WorldTransform->getRotation();
    }

    void AbstractTransform::setRotation(const btQuaternion &rotation)
    {
        m_WorldTransform->setRotation(rotation);
    }

    btVector3 AbstractTransform::getEulerAngles()const
    {
        f32 x, y, z;
        
        m_WorldTransform->getBasis().getEulerYPR(x, y, z);

        btVector3 v(x,y,z);
        return v;
    }

    void AbstractTransform::setEulerAngles(const btVector3 &angles)
    {
        m_WorldTransform->getBasis().setEulerYPR(angles.x(), angles.y(), angles.z());
    }

    btQuaternion &AbstractTransform::getOrientation()const
    {
        return *m_Orientation;
    }

    void AbstractTransform::setOrientation(const btQuaternion &orientation)
    {
        *m_Orientation = orientation;
    }

    btVector3 AbstractTransform::getScale()const
    {
        btTransform trans(getWorldTransform());
        btVector3 t(trans.getBasis().getColumn(0).length(),
                    trans.getBasis().getColumn(0).length(),
                    trans.getBasis().getColumn(0).length());
        return t;
    }

    void AbstractTransform::setScale(const btVector3 &scale)
    {
        getTransform().setBasis(getTransform().getBasis().scaled(scale));
    }
    
    void AbstractTransform::setScale(const f32 scale)
    {
        setScale(btVector3(scale, scale, scale));
    }

    btTransform &AbstractTransform::getPivot()const
    {
        return *m_Pivot;
    }

    void AbstractTransform::setPivot(const btTransform &pivot)
    {
        *m_Pivot = pivot;
    }
}
