//
//  AbstractFactoryObject.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "AbstractFactoryObject.h"

#include "AbstractBuilder.h"

#include "World.h"
#include "JLIFactoryTypes.h"

namespace njli
{
    
    AbstractFactoryObject::AbstractFactoryObject(const void* ptr):
    m_pointer(ptr),m_canDelete(true),m_isRenderObject(false){}
    
    AbstractFactoryObject::~AbstractFactoryObject()
    {
        DEBUG_ASSERT(m_canDelete);
    }
    
//    const char *AbstractFactoryObject::getClassName()const
//    {
//        return "AbstractFactoryObject";
//    }
//    
//    s32 AbstractFactoryObject::getType()const
//    {
//        return JLI_OBJECT_TYPE_None;
//    }
    
    AbstractFactoryObject *AbstractFactoryObject::create(const AbstractBuilder &builder)const
    {
        return World::getInstance()->getWorldFactory()->create(builder);
    }
    
    AbstractFactoryObject *AbstractFactoryObject::clone(bool shared)const
    {
        return World::getInstance()->getWorldFactory()->clone(*this, shared);
    }
    
    void AbstractFactoryObject::destroy()
    {
        World::getInstance()->getWorldFactory()->destroy(this);
    }
    
    const void*	AbstractFactoryObject::getPointer() const
    {
        return m_pointer;
    }
    
    u64 AbstractFactoryObject::getPointerValue() const
    {
        return m_pointerVal;
    }
    
    bool AbstractFactoryObject::operator==(const AbstractFactoryObject &rhs)const
    {
        return getPointer() == rhs.getPointer();
    }
    
    bool AbstractFactoryObject::operator<(const AbstractFactoryObject &rhs)const
    {
        return getPointer() < rhs.getPointer();
    }
    
    bool AbstractFactoryObject::operator>(const AbstractFactoryObject &rhs)const
    {
        return getPointer() > rhs.getPointer();
    }
    
    bool AbstractFactoryObject::operator!=(const AbstractFactoryObject &rhs)const
    {
        return !(*this == rhs);
    }
    
    bool AbstractFactoryObject::operator<=(const AbstractFactoryObject &rhs)const
    {
        return (*this < rhs) || (*this == rhs);
    }
    
    bool AbstractFactoryObject::operator>=(const AbstractFactoryObject &rhs)const
    {
        return (*this > rhs) || (*this == rhs);
    }
    
    void AbstractFactoryObject::serializeObject(class btSerializer* serializer) const
    {
        s32 len = calculateSerializeBufferSize();
        btChunk* chunk = serializer->allocate(len,1);
        serialize(chunk->m_oldPtr, serializer);
        serializer->finalizeChunk(chunk,getClassName(),getType(),(void*)this);
    }
    
    bool AbstractFactoryObject::canDelete()const
    {
        bool can = !hasChildren();
        return m_canDelete && can;
    }
    void AbstractFactoryObject::enableCanDelete(const bool enable)
    {
        m_canDelete = enable;
    }
    
    bool AbstractFactoryObject::isRenderObject()const
    {
        return m_isRenderObject;
    }
    
    void AbstractFactoryObject::enableRenderObject(const bool enable)
    {
        m_isRenderObject = enable;
    }
}
