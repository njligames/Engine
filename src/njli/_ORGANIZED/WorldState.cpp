//
//  WorldState.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "WorldState.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "WorldStateBuilder.h"
#include "Scene.h"
#include "SceneState.h"
#include "SceneStateMachine.h"
#include "PhysicsRayContact.h"
#include "PhysicsWorld.h"
#include "Log.h"
#define TAG "WorldState.cpp"
#define FORMATSTRING "{\"njli::WorldState\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#define MAX_CONTACTS (100)

static btVector3	getRayTo(int x,int y,btVector3 cameraUp)
{
    float m_screenHeight = njli::World::getInstance()->getViewportDimensions().y();
    float m_screenWidth = njli::World::getInstance()->getViewportDimensions().x();
    
    float cameraDistance = m_screenHeight/2.f;//m_screenWidth/2;//1.f;
    btVector3 cameraTargetPosition(0,0,0);
//    btVector3 cameraUp(0,-1,0);
    
    if (1)//_ortho)
    {
        
        btScalar aspect;
        btVector3 extents;
        if (m_screenWidth> m_screenHeight)
        {
            
            aspect = m_screenWidth / (btScalar)m_screenHeight;
            extents.setValue(aspect * 1.0f, 1.0f,0);
        } else
        {
            cameraDistance = m_screenWidth/2.f;
            aspect = m_screenHeight / (btScalar)m_screenWidth;
            extents.setValue(1.0f, aspect*1.f,0);
        }
        
        
        
        extents *= cameraDistance;
        btVector3 lower = cameraTargetPosition - extents;
        btVector3 upper = cameraTargetPosition + extents;
        
        btScalar u = x / btScalar(m_screenWidth);
        btScalar v = (m_screenHeight - y) / btScalar(m_screenHeight);
        
        btVector3	p(0,0,0);
        p.setValue(
                   (1.0f - u) * lower.getX() + u * upper.getX(),
                   -((1.0f - v) * lower.getY() + v * upper.getY()),
                   cameraTargetPosition.getZ());
        return p;
    }
    
    float top = 1.f;
    float bottom = -1.f;
    float nearPlane = 1.f;
    float tanFov = (top-bottom)*0.5f / nearPlane;
    float fov = 2 * atanf (tanFov);
    
    btVector3 cameraPosition(0,0,-100);
    btVector3	rayFrom = cameraPosition;
    btVector3 rayForward = (cameraTargetPosition-cameraPosition);
    rayForward.normalize();
    float farPlane = 10000.f;
    rayForward*= farPlane;
    
    btVector3 rightOffset;
    btVector3 vertical = cameraUp;
    
    btVector3 hor;
    hor = rayForward.cross(vertical);
    hor.normalize();
    vertical = hor.cross(rayForward);
    vertical.normalize();
    
    float tanfov = tanf(0.5f*fov);
    
    
    hor *= 2.f * farPlane * tanfov;
    vertical *= 2.f * farPlane * tanfov;
    
    btScalar aspect;
    
    if (m_screenWidth > m_screenHeight)
    {
        aspect = m_screenWidth / (btScalar)m_screenHeight;
        
        hor*=aspect;
    } else
    {
        aspect = m_screenHeight / (btScalar)m_screenWidth;
        vertical*=aspect;
    }
    
    
    btVector3 rayToCenter = rayFrom + rayForward;
    btVector3 dHor = hor * 1.f/float(m_screenWidth);
    btVector3 dVert = vertical * 1.f/float(m_screenHeight);
    
    
    btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * vertical;
    rayTo += btScalar(x) * dHor;
    rayTo -= btScalar(y) * dVert;
    //rayTo += y * dVert;
    
    return rayTo;
}

namespace njli
{
    WorldState::WorldState():
    AbstractState<void>()
    {
        char buffer[1024];
        sprintf(buffer, "%s's PhysicsRayContact", getName());
        
        for (s32 i = 0; i < MAX_CONTACTS; ++i) {
            PhysicsRayContact *contact = PhysicsRayContact::create();
            contact->setName(buffer);
            
            addChild(contact);
            
            m_RayContacts.push_back(contact);
        }
    }
    
    WorldState::WorldState(const AbstractBuilder &builder):
    AbstractState<void>(builder)
    {
        char buffer[1024];
        sprintf(buffer, "%s's PhysicsRayContact", getName());
        
        for (s32 i = 0; i < MAX_CONTACTS; ++i) {
            PhysicsRayContact *contact = PhysicsRayContact::create();
            addChild(contact);
            
            m_RayContacts.push_back(contact);
        }
    }
    
    WorldState::WorldState(const WorldState &copy):
    AbstractState<void>(copy)
    {
        char buffer[1024];
        sprintf(buffer, "%s's PhysicsRayContact", getName());
        
        for (s32 i = 0; i < MAX_CONTACTS; ++i) {
            PhysicsRayContact *contact = PhysicsRayContact::create();
            addChild(contact);
            
            m_RayContacts.push_back(contact);
        }
    }
    
    WorldState::~WorldState()
    {
    }
    
    WorldState &WorldState::operator=(const WorldState &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	WorldState::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void WorldState::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *WorldState::getClassName()const
    {
        return "WorldState";
    }
    
    s32 WorldState::getType()const
    {
        return WorldState::type();
    }
    
    WorldState::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    WorldState **WorldState::createArray(const u32 size)
    {
        return (WorldState**)World::getInstance()->getWorldFactory()->createArray(WorldState::type(), size);
    }
    
    void WorldState::destroyArray(WorldState **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    WorldState *WorldState::create()
    {
        return dynamic_cast<WorldState*>(World::getInstance()->getWorldFactory()->create(WorldState::type()));
    }
    
    WorldState *WorldState::create(const WorldStateBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<WorldState*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    WorldState *WorldState::clone(const WorldState &object)
    {
        return dynamic_cast<WorldState*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    WorldState *WorldState::copy(const WorldState &object)
    {
        return dynamic_cast<WorldState*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void WorldState::destroy(WorldState *object)
    {
        if(object)
        {
            for (s32 i = 0; i < MAX_CONTACTS; ++i) {
                
                PhysicsRayContact *c = object->m_RayContacts.at(i);
                if(World::getInstance()->getWorldFactory()->has(c))
                    PhysicsRayContact::destroy(c);
                object->removeChild(c);
            }
            object->m_RayContacts.clear();
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void WorldState::load(WorldState &object, lua_State *L, int index)
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
                WorldState::load(object, L, -2);
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
    
    u32 WorldState::type()
    {
        return JLI_OBJECT_TYPE_WorldState;
    }
    
    void WorldState::enter(void *object)
    {
        char buffer[BUFFER_SIZE] = "__NJLIWorldEnterState";
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    }
    
    void WorldState::update(void *object, f32 timeStep)
    {
        BT_PROFILE("WorldState::update");
        char buffer[BUFFER_SIZE] = "__NJLIWorldUpdateState";
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, timeStep);
    }
    
    void WorldState::exit(void *object)
    {
        Scene *scene = World::getInstance()->getScene();
        if(scene)
        {
            scene->clearAllStates();
        }
        
        char buffer[BUFFER_SIZE] = "__NJLIWorldExitState";
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
    }
    
    bool WorldState::onMessage(void *object, const Telegram &msg)const
    {
        bool ret;
        char buffer[BUFFER_SIZE] = "__NJLIWorldOnMessage";
        
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, msg, ret);
        
        return ret;
    }
    
    void WorldState::checkRayCollision(DeviceTouch **m_CurrentTouches, const char *code, bool disableNodeTouched)
    {
        Scene *scene = njli::World::getInstance()->getScene();
        
        if(scene)
        {
            Camera *camera = scene->getTouchCamera();
            if(NULL != camera)
            {
                PhysicsWorld *physicsWorld = scene->getPhysicsWorld();
                if(physicsWorld)
                {
                    btAlignedObjectArray<Node*> untouchedNodes;
                    untouchedNodes.clear();
                    
                    scene->getActiveNodes(untouchedNodes);
                    
                    bool touched = false;
                    for (s32 i = 0; i < DeviceTouch::MAX_TOUCHES; ++i)
                    {
                        if(m_CurrentTouches[i])
                        {
                            btVector2 touchPosition = m_CurrentTouches[i]->getPosition();
                            btVector3 from, to;
                            camera->getTouchRay(touchPosition, from, to);
                            
                            s32 numContacts = 0;
                            if (physicsWorld->rayTestAll(from, to, m_RayContacts, numContacts))
                            {
                                for (s32 i = 0; i < numContacts; ++i)
                                {
                                    PhysicsRayContact *contact = m_RayContacts.at(i);
                                    
                                    if (disableNodeTouched)
                                    {
                                        contact->getHitNode()->enableTouched(false);
                                        
                                    }
                                    untouchedNodes.remove(contact->getHitNode());
                                    contact->screenPosition(btVector2(from.x(), from.y()));
                                    char buffer[BUFFER_SIZE];
                                    sprintf(buffer, "%s%s", "__NJLINodeRay", code);
                                    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, *contact);
                                    touched = true;
                                    
                                }
                            }
                            //                        if(physicsWorld->rayTestClosest(from, to, *m_RayContact))
                            //                        {
                            //                            if (disableNodeTouched)
                            //                            {
                            //                                m_RayContact->getHitNode()->enableTouched(false);
                            //                            }
                            //                            m_RayContact->screenPosition(btVector2(from.x(), from.y()));
                            //                            char buffer[BUFFER_SIZE];
                            //                            sprintf(buffer, "%s%s", code, "Ray");
                            //                            njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, *m_RayContact);
                            //                            touched = true;
                            //                        }
                        }
                    }
                    
                    for(unsigned int i = 0; i < untouchedNodes.size(); i++)
                    {
                        Node *n = untouchedNodes[i];
                        
                        char buffer[BUFFER_SIZE];
                        sprintf(buffer, "%s", "__NJLINodeRayTouchMissed");
                        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, n);
                    }
                    //                if (!touched)
                    //                {
                    //                    char buffer[BUFFER_SIZE];
                    //                    sprintf(buffer, "%s%s", code, "RayMissed");
                    //                    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
                    //                }
                }
            }
            else
            {
                DEBUG_WARN(TAG, "setTouchCamera() must be called on the scene\n");
            }
            
        }
    }
    
    void WorldState::touchDown(DeviceTouch **m_CurrentTouches)
    {
//        DEBUG_LOG_WRITE_D(TAG, "WorldState::touchDown\n");
        
        char action[BUFFER_SIZE] = "Down";
        char buffer[BUFFER_SIZE] = "";
        
        sprintf(buffer, "__NJLIWorldTouch%s", action);
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, m_CurrentTouches);
        
//        sprintf(buffer, "WorldTouch%s", action);
        sprintf(buffer, "Touch%s", action);
        checkRayCollision(m_CurrentTouches, buffer);
    }
    
    void WorldState::touchUp(DeviceTouch **m_CurrentTouches)
    {
        char action[BUFFER_SIZE] = "Up";
        char buffer[BUFFER_SIZE] = "";
        
        sprintf(buffer, "__NJLIWorldTouch%s", action);
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, m_CurrentTouches);
        
//        sprintf(buffer, "WorldTouch%s", action);
        sprintf(buffer, "Touch%s", action);
        checkRayCollision(m_CurrentTouches, buffer, true);
        
    }
    
    void WorldState::touchMove(DeviceTouch **m_CurrentTouches)
    {
        char action[BUFFER_SIZE] = "Move";
        char buffer[BUFFER_SIZE] = "";
        
        sprintf(buffer, "__NJLIWorldTouch%s", action);
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, m_CurrentTouches);
        
//        sprintf(buffer, "WorldTouch%s", action);
        sprintf(buffer, "Touch%s", action);
        checkRayCollision(m_CurrentTouches, buffer);
    }
    
    void WorldState::touchCancelled(DeviceTouch **m_CurrentTouches)
    {
        char action[BUFFER_SIZE] = "Cancelled";
        char buffer[BUFFER_SIZE] = "";
        
        sprintf(buffer, "__NJLIWorldTouch%s", action);
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, m_CurrentTouches);
        
//        sprintf(buffer, "WorldTouch%s", action);
        sprintf(buffer, "Touch%s", action);
        checkRayCollision(m_CurrentTouches, buffer);
    }
    
//    void WorldState::enableRayTestClosest(bool enable)
//    {
//        m_EnableRayTestClosest = enable;
//    }
//    
//    bool WorldState::isRayTestClosestEnabled()const
//    {
//        return m_EnableRayTestClosest;
//    }
//    
//    void WorldState::enableRayTestAll(bool enable)
//    {
//        m_EnableRayTestAll = enable;
//    }
//    
//    bool WorldState::isRayTestAllEnabled()const
//    {
//        return m_EnableRayTestAll;
//    }
}
