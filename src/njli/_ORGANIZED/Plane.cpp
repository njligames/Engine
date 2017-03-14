//
//  Plane.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 12/26/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Plane.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PlaneBuilder.h"
#define FORMATSTRING "{\"njli::Plane\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    Plane::Plane()
    {
        
    }
    
    Plane::Plane(const AbstractBuilder &builder)
    {
        
    }
    
    Plane::Plane(const Plane &copy)
    {
        
    }
    
    Plane::~Plane()
    {
        
    }
    
    Plane &Plane::operator=(const Plane &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	Plane::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Plane::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Plane::getClassName()const
    {
        return "Plane";
    }
    
    s32 Plane::getType()const
    {
        return Plane::type();
    }
    
    Plane::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Plane **Plane::createArray(const u32 size)
    {
        return (Plane**)World::getInstance()->getWorldFactory()->createArray(Plane::type(), size);
    }
    
    void Plane::destroyArray(Plane **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Plane *Plane::create()
    {
        return dynamic_cast<Plane*>(World::getInstance()->getWorldFactory()->create(Plane::type()));
    }
    
    Plane *Plane::create(const PlaneBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Plane*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Plane *Plane::clone(const Plane &object)
    {
        return dynamic_cast<Plane*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Plane *Plane::copy(const Plane &object)
    {
        return dynamic_cast<Plane*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Plane::destroy(Plane *object)
    {
        if(object)
        {
            Geometry::destroy(object);
        }
    }
    
    void Plane::load(Plane &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
        {
            // stack now contains: -1 => value; -2 => key; -3 => table
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                Plane::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
//                    swig_lua_userdata *usr;
//                    swig_type_info *type;
//                    assert(lua_isuserdata(L,index));
//                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
//                    type = usr->type;
//                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
//                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 Plane::type()
    {
        return JLI_OBJECT_TYPE_Plane;
    }
    
    void Plane::getVertices(LevelOfDetail *geometry, btVector3 **vertices, Node*node)const
    {
    }
    
    u64 Plane::getNumberOfVertices(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Plane::getVertexColors(LevelOfDetail *geometry, btVector4 **colorVertices, Node*node)const
    {
    }
    
    u64 Plane::getNumberOfVertexColors(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Plane::getTextureCoordinates(LevelOfDetail *geometry, btVector2 **textureCoordinates, Node*node)const
    {
    }
    
    u64 Plane::getNumberOfTextureCoordinates(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Plane::setOpacity(Node *node, f32 opacity)
    {
        
    }
    
    void Plane::setHidden(Node *node, bool hidden)
    {
        
    }
    
    bool Plane::isHidden(Node *node)const
    {
        return false;
    }
    
    void Plane::transformVertices(Node *node, const btTransform &transfrom)
    {
        
    }
    
    void Plane::transformVertexColors(Node *node, const btTransform &transform)
    {
        
    }
    
    void Plane::transformTextureCoordinates(Node *node, const btTransform &transform)
    {
        
    }
    
    void Plane::applyShape(Node *node, PhysicsShape *physicsShape)
    {
        
    }
    
    void Plane::hideGeometry(Node*)
    {
        DEBUG_ASSERT(false);
    }
    
    void Plane::loadGPU()
    {
        
    }
    
    void Plane::unLoadGPU()
    {
        
    }
    
    bool Plane::isLoadedGPU()const
    {
        return false;
    }
    
   
    
    
    s32 Plane::numberOfVertices()const
    {
        return 0;
    }
    
    s32 Plane::numberOfIndices()const
    {
        return 0;
    }
    
    void Plane::swapVertexData(const size_t idx1, const size_t idx2)
    {
        
    }
    
    const void *Plane::getArrayBuffer()const
    {
        return NULL;
    }
    s64 Plane::getArrayBufferSize()const
    {
        return 0;
    }
    
    const void *Plane::getElementArrayBuffer()const
    {
        return NULL;
    }
    s64 Plane::getElementArrayBufferSize()const
    {
        return 0;
    }
    
    void Plane::setSize(Node*node, const btVector3 &position, const f32 halfSize)
    {
        //TODO: implement
    }
    
    void Plane::setColor(Node*node, const btVector4 &color)
    {
        //TODO: implement
    }
}