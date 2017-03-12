//
//  Scene.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Scene.h"
#include "JLIFactoryTypes.h"
#include "World.h"

#include "SceneBuilder.h"

#include "btTransform.h"

#include "Node.h"
#include "Camera.h"
#include "Light.h"
#include "SceneStateMachine.h"
#include "ParticleEmitter.h"
#include "Material.h"

#include "PhysicsWorld.h"
#include "PhysicsBody.h"
#include "PhysicsRayContact.h"
#include "Clock.h"
#include "Geometry.h"
#define FORMATSTRING "{\"njli::Scene\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "NodeStateMachine.h"

#include "btQuickprof.h"

#include "SceneState.h"

#define TAG "Scene.cpp"

namespace njli
{
    Scene::Scene():
    AbstractFactoryObject(this),
//    m_Name("MyScene"),
    m_RootNode(NULL),
    m_SceneStateMachine(SceneStateMachine::create()),
    m_BackgroundMaterial(Material::create()),
    m_PhysicsWorld(NULL),
//    m_isPaused(false),
    m_ActiveCameras(new btAlignedObjectArray<Camera*>()),
    m_ActiveNodes(new btAlignedObjectArray<Node*>()),
    m_ActiveParticleEmitters(new btAlignedObjectArray<ParticleEmitter*>()),
    m_ActiveClocks(new btAlignedObjectArray<Clock*>()),
    m_ActiveGeometry(new btAlignedObjectArray<Geometry*>()),
    m_TouchCamera(NULL)
    {
        addChild(m_SceneStateMachine);
        addChild(m_BackgroundMaterial);
    }
    
    Scene::Scene(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
//    m_Name("MyScene"),
    m_RootNode(NULL),
    m_SceneStateMachine(SceneStateMachine::create()),
    m_BackgroundMaterial(Material::create()),
    m_PhysicsWorld(NULL),
//    m_isPaused(false),
    m_ActiveCameras(new btAlignedObjectArray<Camera*>()),
    m_ActiveNodes(new btAlignedObjectArray<Node*>()),
    m_ActiveParticleEmitters(new btAlignedObjectArray<ParticleEmitter*>()),
    m_ActiveClocks(new btAlignedObjectArray<Clock*>()),
    m_ActiveGeometry(new btAlignedObjectArray<Geometry*>()),
    m_TouchCamera(NULL)
    {
        addChild(m_SceneStateMachine);
        addChild(m_BackgroundMaterial);
    }
    
    Scene::Scene(const Scene &copy):
    AbstractFactoryObject(this),
//    m_Name("MyScene"),
    m_RootNode(NULL),
    m_SceneStateMachine(SceneStateMachine::create()),
    m_BackgroundMaterial(Material::create()),
    m_PhysicsWorld(NULL),
//    m_isPaused(false),
    m_ActiveCameras(new btAlignedObjectArray<Camera*>()),
    m_ActiveNodes(new btAlignedObjectArray<Node*>()),
    m_ActiveParticleEmitters(new btAlignedObjectArray<ParticleEmitter*>()),
    m_ActiveClocks(new btAlignedObjectArray<Clock*>()),
    m_ActiveGeometry(new btAlignedObjectArray<Geometry*>()),
    m_TouchCamera(NULL)
    {
        addChild(m_SceneStateMachine);
        addChild(m_BackgroundMaterial);
    }
    
    Scene::~Scene()
    {
        delete m_ActiveGeometry;m_ActiveGeometry=NULL;
        delete m_ActiveClocks;m_ActiveClocks=NULL;
        delete m_ActiveParticleEmitters;m_ActiveParticleEmitters=NULL;
        delete m_ActiveNodes;m_ActiveNodes=NULL;
        delete m_ActiveCameras;m_ActiveCameras=NULL;
    }
    
    Scene &Scene::operator=(const Scene &rhs)
    {
        if(this != &rhs)
        {
            //TODO:implement...
        }
        return *this;
    }
    
    s32	Scene::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Scene::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Scene::getClassName()const
    {
        return "Scene";
    }
    
    s32 Scene::getType()const
    {
        return Scene::type();
    }
    
    Scene::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Scene **Scene::createArray(const u32 size)
    {
        return (Scene**)World::getInstance()->getWorldFactory()->createArray(Scene::type(), size);
    }
    
    void Scene::destroyArray(Scene **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Scene *Scene::create()
    {
        return dynamic_cast<Scene*>(World::getInstance()->getWorldFactory()->create(Scene::type()));
    }
    
    Scene *Scene::create(const SceneBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Scene*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Scene *Scene::clone(const Scene &object)
    {
        return dynamic_cast<Scene*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Scene *Scene::copy(const Scene &object)
    {
        return dynamic_cast<Scene*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Scene::destroy(Scene *object)
    {
        if(object)
        {
            Material *m = object->getBackground();
            if(World::getInstance()->getWorldFactory()->has(m))
                Material::destroy(m);
            object->removeBackground();
            
            SceneStateMachine *sm = object->getStateMachine();
            if(World::getInstance()->getWorldFactory()->has(sm))
                SceneStateMachine::destroy(sm);
            object->removeStateMachine();
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Scene::load(Scene &object, lua_State *L, int index)
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
                Scene::load(object, L, -2);
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
    
    u32 Scene::type()
    {
        return JLI_OBJECT_TYPE_Scene;
    }

    void Scene::update(f32 timeStep, const u32 numSubSteps)
    {
        BT_PROFILE("Scene::update");
        
        if(getPhysicsWorld())
            getPhysicsWorld()->update(timeStep);
        
        m_ActiveGeometries.clear();
        
        for (s32 i = 0; i < (*m_ActiveNodes).size(); ++i)
        {
            Node *node = (*m_ActiveNodes).at(i);
            const u64 geometryIndex = node->getGeometryIndex();
            
            node->update(timeStep);
            
            Geometry *geometry = node->getGeometry();
            if(geometry)
            {
                PhysicsBody *physicsBody = node->getPhysicsBody();
                
                if(physicsBody && geometry->shouldApplyShape(node))
                    geometry->applyShape(node, physicsBody->getPhysicsShape());
                
                geometry->setTransform(geometryIndex, node->getWorldTransform());
                
                geometry->setColorTransform(geometryIndex, node->getColorTransform());
            }
        }
        
            for (s32 i = 0; i < (*m_ActiveNodes).size(); ++i)
        {
            s32 idx = i % (*m_ActiveNodes).size();
            
            Node *node = (*m_ActiveNodes).at(idx);
            Geometry *geometry = node->getGeometry();
            if(geometry)
                geometry->setTransform(node->getGeometryIndex(), node->getWorldTransform());
        }
        
        for (s32 i = 0; i < (*m_ActiveParticleEmitters).size(); ++i)
        {
            (*m_ActiveParticleEmitters).at(i)->update(timeStep);
        }
        
        for (s32 i = 0; i < (*m_ActiveClocks).size(); ++i)
        {
            (*m_ActiveClocks).at(i)->update(timeStep);
        }
        
        SceneStateMachine *sm = getStateMachine();
        if(sm)
            sm->update(timeStep);
        
        
    }

    void Scene::render()
    {
        
//        for (s32 j = 0; j < m_ActiveGeometries.size(); ++j)
//        {
//            Geometry *geometry = m_ActiveGeometries.at(j);
//            geometry->getMaterial()->render();
//        }
//        struct myclass {
//            Camera *camera;
//            bool operator() (Geometry *i,Geometry *j)
//            {
//                Node *i_node = i->getParent();
//                Node *j_node = j->getParent();
//                
//                btScalar distance_i = i_node->getOrigin().distance(camera->getParent()->getOrigin());
//                btScalar distance_j = j_node->getOrigin().distance(camera->getParent()->getOrigin());
//                
//                return (distance_i > distance_j);
//            }
//        } myobject;
        
        for (s32 i = 0; i < (*m_ActiveCameras).size(); ++i)
        {
            Camera *camera = (*m_ActiveCameras).at(i);
            btVector3 cameraOrigin(camera->getParent()->getWorldTransform().getOrigin());
            
            m_ActiveGeometries.clear();
            
            for (s32 k = 0; k < (*m_ActiveNodes).size(); ++k)
            {
                Node *node = (*m_ActiveNodes).at(k);
                
                Geometry *geometry = node->getGeometry();
                if (geometry)
                    geometry->setHidden(node, node->isHidden(camera));
                
                if(m_ActiveGeometries.end() == std::find(m_ActiveGeometries.begin(), m_ActiveGeometries.end(), geometry))
                    m_ActiveGeometries.push_back(geometry);
                
            }
            
            for (s32 j = 0; j < m_ActiveGeometries.size(); ++j)
            {
                Geometry *geometry = m_ActiveGeometries.at(j);
                
                if(geometry && !geometry->isHidden(camera))
                {
//                    geometry->sort(cameraOrigin);
                    geometry->render(camera);
                }
            }
            
//            for (s32 j = 0; j < (*m_ActiveParticleEmitters).size(); ++j)
//            {
//                (*m_ActiveParticleEmitters).at(j)->render((*m_ActiveCameras).at(i));
//            }
        }
        
//        m_BackgroundMaterial->render();
    }
    
    void Scene::setRootNode(Node *node)
    {
        DEBUG_ASSERT(node != NULL);
        
        if(getRootNode())
            removeChild(getRootNode());
        
        m_RootNode = node;
        
        addChild(m_RootNode);
        
        addActiveNode(m_RootNode);
    }
    
    void Scene::removeRootNode()
    {
        Node *root = getRootNode();
        
        if(root != NULL)
        {
            removeActiveNode(root);
            removeChild(root);
        }
        
        m_RootNode = NULL;
    }
    
    Node *Scene::getRootNode()
    {
        s32 idx = getChildIndex(m_RootNode);
        if(idx != -1)
            return dynamic_cast<Node*>(getChild(idx));
        return NULL;
    }
    
    const Node *Scene::getRootNode()const
    {
        s32 idx = getChildIndex(m_RootNode);
        if(idx != -1)
            return dynamic_cast<const Node*>(getChild(idx));
        return NULL;
    }
    
    SceneStateMachine *Scene::getStateMachine()
    {
        s32 idx = getChildIndex(m_SceneStateMachine);
        if(idx != -1)
            return dynamic_cast<SceneStateMachine*>(getChild(idx));
        return NULL;
    }
    
    const SceneStateMachine *Scene::getStateMachine()const
    {
        s32 idx = getChildIndex(m_SceneStateMachine);
        if(idx != -1)
            return dynamic_cast<const SceneStateMachine*>(getChild(idx));
        return NULL;
    }
    
    void Scene::removeStateMachine()
    {
        SceneStateMachine *sm = getStateMachine();
        if (sm != NULL)
        {
            removeChild(sm);
            m_SceneStateMachine = NULL;
        }
    }
    
//    s32 Scene::addParticleEmitter(ParticleEmitter *particleEmitter)
//    {
//        DEBUG_ASSERT(NULL != particleEmitter);
//        
//        std::vector<ParticleEmitter*>::const_iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), particleEmitter);
//        
//        if(iter == m_ParticleEmitterList.end())
//        {
//            std::vector<ParticleEmitter*>::iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), particleEmitter);
//            
//            if(iter != m_ParticleEmitterList.end())
//                removeChild(particleEmitter);
//            
//            m_ParticleEmitterList.push_back(particleEmitter);
//            
//            addChild(particleEmitter);
//            addActiveParticleEmitter(particleEmitter);
//        }
//        return getParticleEmitterIndex(particleEmitter);
//    }
//    
//    bool Scene::removeParticleEmitter(ParticleEmitter *particleEmitter)
//    {DEBUG_ASSERT(NULL != particleEmitter);
//        
//        std::vector<ParticleEmitter*>::iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), particleEmitter);
//        
//        if(iter != m_ParticleEmitterList.end())
//        {
//            removeChild(*iter);
//            removeActiveParticleEmitter(*iter);
//            
//            m_ParticleEmitterList.erase(iter);
//            return true;
//        }
//        return false;
//    }
//    
//    void Scene::removeAllParticleEmitters()
//    {
//        for(std::vector<ParticleEmitter*>::iterator iter = m_ParticleEmitterList.begin();
//            iter != m_ParticleEmitterList.end();
//            ++iter)
//        {
//            removeChild(*iter);
//            removeActiveParticleEmitter(*iter);
//        }
//        m_ParticleEmitterList.clear();
//    }
//    
//    void Scene::getParticleEmitters(std::vector<ParticleEmitter*> &particleEmitters)const
//    {
//        for(std::vector<ParticleEmitter*>::const_iterator iter = m_ParticleEmitterList.begin();
//            iter != m_ParticleEmitterList.end();
//            ++iter)
//        {
//            if(getChildIndex(*iter) != -1)
//                particleEmitters.push_back(*iter);
//        }
//    }
//    
//    s32 Scene::getParticleEmitterIndex(ParticleEmitter *particleEmitter)const
//    {
//        std::vector<ParticleEmitter*>::const_iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), particleEmitter);
//        
//        if (iter != m_ParticleEmitterList.end())
//        {
//            return std::distance(m_ParticleEmitterList.begin(), iter);
//        }
//        return -1;
//    }
//    
//    ParticleEmitter *Scene::getParticleEmitter(const u32 index)
//    {
//        if (index < m_ParticleEmitterList.size())
//        {
//            s32 idx = getChildIndex(m_ParticleEmitterList.at(index));
//            if(idx != -1)
//                return dynamic_cast<ParticleEmitter*>(getChild(idx));
//        }
//        return NULL;
//    }
//    
//    const ParticleEmitter *Scene::getParticleEmitter(const u32 index)const
//    {
//        if (index < m_ParticleEmitterList.size())
//        {
//            s32 idx = getChildIndex(m_ParticleEmitterList.at(index));
//            if(idx != -1)
//                return dynamic_cast<const ParticleEmitter*>(getChild(idx));
//        }
//        return NULL;
//    }
    
    void Scene::addBackground(Material *background)
    {
        DEBUG_ASSERT(background != NULL);
        
        if(getBackground())
            removeChild(getBackground());
        
        m_BackgroundMaterial = background;
        
        addChild(m_BackgroundMaterial);
    }
    
    void Scene::removeBackground()
    {
        if(getBackground())
            removeChild(getBackground());
        
        m_BackgroundMaterial = NULL;
    }
    
    Material *Scene::getBackground()
    {
        s32 idx = getChildIndex(m_BackgroundMaterial);
        if(idx != -1)
            return dynamic_cast<Material*>(getChild(idx));
        return NULL;
    }
    
    const Material *Scene::getBackground()const
    {
        s32 idx = getChildIndex(m_BackgroundMaterial);
        if(idx != -1)
            return dynamic_cast<const Material*>(getChild(idx));
        return NULL;
    }
    
    void Scene::setPhysicsWorld(PhysicsWorld *world)
    {
        DEBUG_ASSERT(world != NULL);
        
        if(getPhysicsWorld())
            removeChild(getPhysicsWorld());
        
        m_PhysicsWorld = world;
        
        addChild(m_PhysicsWorld);
        
//        m_isPaused = getPhysicsWorld()->isPaused();
    }
    
    void Scene::removePhysicsWorld()
    {
        if(getPhysicsWorld())
        {
            removeChild(getPhysicsWorld());
        }
        
        m_PhysicsWorld = NULL;
    }
    
    PhysicsWorld *Scene::getPhysicsWorld()
    {
        s32 idx = getChildIndex(m_PhysicsWorld);
        if(idx != -1)
//#if defined(DEBUG) || defined(_DEBUG)
//        {
//            return dynamic_cast<PhysicsWorld*>(getChild(idx));
//        }
//#else
        {
//            DEBUG_ASSERT(dynamic_cast<PhysicsWorld*>(getChild(idx)));
            return dynamic_cast<PhysicsWorld*>(getChild(idx));
        }
//#endif
        
        return NULL;
    }
    
    const PhysicsWorld *Scene::getPhysicsWorld()const
    {
        s32 idx = getChildIndex(m_PhysicsWorld);
        if(idx != -1)
//#if defined(DEBUG) || defined(_DEBUG)
//        {
//            return dynamic_cast<const PhysicsWorld*>(getChild(idx));
//        }
//#else
        {
//            DEBUG_ASSERT(dynamic_cast<const PhysicsWorld*>(getChild(idx)));
            return dynamic_cast<const PhysicsWorld*>(getChild(idx));
        }
//#endif
        
        
        return NULL;
    }
    
    s32 Scene::addClock(Clock *clock)
    {
        DEBUG_ASSERT(NULL != clock);
        
        std::vector<Clock*>::const_iterator iter = std::find(m_ClockList.begin(), m_ClockList.end(), clock);
        
        if(iter == m_ClockList.end())
        {
            std::vector<Clock*>::iterator iter = std::find(m_ClockList.begin(), m_ClockList.end(), clock);

            if(iter != m_ClockList.end())
                removeChild(clock);
            
            m_ClockList.push_back(clock);
            
            addChild(clock);
            addActiveClock(clock);
        }
        
        return getClockIndex(clock);
    }
    
    bool Scene::removeClock(Clock *clock)
    {
        DEBUG_ASSERT(NULL != clock);
        
        std::vector<Clock*>::iterator iter = std::find(m_ClockList.begin(), m_ClockList.end(), clock);
        
        if(iter != m_ClockList.end())
        {
            removeChild(*iter);
            removeActiveClock(*iter);
            
            m_ClockList.erase(iter);
            return true;
        }
        return false;
    }
    
    void Scene::removeAllClocks()
    {
        for(std::vector<Clock*>::iterator iter = m_ClockList.begin();
            iter != m_ClockList.end();
            ++iter)
        {
            removeChild(*iter);
        }
        m_ClockList.clear();
    }
    
    void Scene::getClocks(std::vector<Clock*> &clocks)const
    {
        for(std::vector<Clock*>::const_iterator iter = m_ClockList.begin();
            iter != m_ClockList.end();
            ++iter)
        {
            if(getChildIndex(*iter) != -1)
                clocks.push_back(*iter);
        }
    }
    
    s32 Scene::getClockIndex(Clock *clock)const
    {
        std::vector<Clock*>::const_iterator iter = std::find(m_ClockList.begin(), m_ClockList.end(), clock);
        
        if (iter != m_ClockList.end())
        {
            return std::distance(m_ClockList.begin(), iter);
        }
        return -1;
    }
    
    Clock *Scene::getClock(const u32 index)
    {
        if (index < m_ClockList.size())
        {
            s32 idx = getChildIndex(m_ClockList.at(index));
            if(idx != -1)
                return dynamic_cast<Clock*>(getChild(idx));
        }
        return NULL;
    }
    
    const Clock *Scene::getClock(const u32 index)const
    {
        if (index < m_ClockList.size())
        {
            s32 idx = getChildIndex(m_ClockList.at(index));
            if(idx != -1)
                return dynamic_cast<const Clock*>(getChild(idx));
        }
        return NULL;
    }
    
    
    
    
    
    void Scene::touchDown(DeviceTouch **m_CurrentTouches)
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->touchDown(this, m_CurrentTouches);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::touchUp(DeviceTouch **m_CurrentTouches)
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->touchUp(this, m_CurrentTouches);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::touchMove(DeviceTouch **m_CurrentTouches)
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->touchMove(this, m_CurrentTouches);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::touchCancelled(DeviceTouch **m_CurrentTouches)
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->touchCancelled(this, m_CurrentTouches);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::keyboardShow()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->keyboardShow(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::keyboardCancel()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->keyboardCancel(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::keyboardReturn(const char* text)
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->keyboardReturn(this, text);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::renderHUD()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->renderHUD(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::pauseGame()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->pauseGame(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::unPauseGame()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->unPauseGame(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::willResignActive()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->willResignActive(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::didBecomeActive()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->didBecomeActive(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::didEnterBackground()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->didEnterBackground(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::willEnterForeground()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->willEnterForeground(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::willTerminate()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->willTerminate(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::interrupt()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->interrupt(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::resumeInterrupt()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->resumeInterrupt(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::receivedMemoryWarning()
    {
        SceneState *currentState = dynamic_cast<SceneState*>(m_SceneStateMachine->getState());
        
        if(currentState)
        {
            currentState->receivedMemoryWarning(this);
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "There is no SceneState\n");
        }
    }
    
    void Scene::updateViewSize()
    {
        for (s32 i = 0; i < (*m_ActiveCameras).size(); ++i)
        {
            Camera *camera = (*m_ActiveCameras).at(i);
            camera->updateViewSize();
        }
    }
    
    void Scene::addCameraNode(Node *cameraNode, bool touchCamera)
    {
        getRootNode()->addChildNode(cameraNode);
        if(touchCamera)
        {
            Camera *camera = cameraNode->getCamera();
            if(camera)
            {
                if(camera->isOrthographic())
                {
                    setTouchCamera(camera);
                }
                else
                {
                    DEBUG_WARN(TAG, "The camera must be orthographic\n");
                }
            }
            else
            {
                DEBUG_WARN(TAG, "There must be a camera set to the node\n");
            }
        }
    }
    
    /**
     *  <#Description#>
     *
     *  @param camera <#camera description#>
     */
    void Scene::setTouchCamera(Camera* camera)
    {
        m_TouchCamera = camera;
    }
    
    Camera* Scene::getTouchCamera()
    {
        return m_TouchCamera;
    }
    
    const Camera* Scene::getTouchCamera() const
    {
        return m_TouchCamera;
    }
    
    
    
    
    
//    void Scene::pause()
//    {
//        if(getPhysicsWorld())
//            getPhysicsWorld()->pause();
//        else
//            m_isPaused = true;
//    }
//    void Scene::unPause()
//    {
//        if(getPhysicsWorld())
//            getPhysicsWorld()->unPause();
//        else
//            m_isPaused = false;
//    }
//    bool Scene::isPaused()const
//    {
//        if(getPhysicsWorld())
//            return getPhysicsWorld()->isPaused();
//        return m_isPaused;
//    }
    
    void Scene::addActiveCamera(Camera *camera)
    {
        DEBUG_ASSERT(NULL != camera);
        
        if((*m_ActiveCameras).size() == (*m_ActiveCameras).findLinearSearch(camera))
            (*m_ActiveCameras).push_back(camera);
    }
    void Scene::removeActiveCamera(Camera *camera)
    {
        DEBUG_ASSERT(NULL != camera);
        
        (*m_ActiveCameras).remove(camera);
    }
    void Scene::addActiveNode(Node *node)
    {
        DEBUG_ASSERT(NULL != node);
        
        if((*m_ActiveNodes).size() == (*m_ActiveNodes).findLinearSearch(node))
        {
            (*m_ActiveNodes).push_back(node);
            node->setCurrentScene(this);
            addChild(node);
        }
        for (unsigned int i = 0; i < node->numberOfChildrenNodes(); i++)
            this->addActiveNode(node->getChildNode(i));
    }
    void Scene::removeActiveNode(Node *node)
    {
        DEBUG_ASSERT(NULL != node);
        
        (*m_ActiveNodes).remove(node);
        node->removeCurrentScene();
        removeChild(node);
        
        for (unsigned int i = 0; i < node->numberOfChildrenNodes(); i++)
            this->removeActiveNode(node->getChildNode(i));
    }
    void Scene::getActiveNodes(btAlignedObjectArray<Node*> &activeNodes)const
    {
        for (unsigned int i = 0; i < m_ActiveNodes->size(); i++)
        {
            Node *n = (*m_ActiveNodes)[i];
            activeNodes.push_back(n);
        }
    }
    void Scene::addActiveParticleEmitter(ParticleEmitter *particleEmitter)
    {
        DEBUG_ASSERT(NULL != particleEmitter);
        
//        particleEmitter->addReference();
        
        if((*m_ActiveParticleEmitters).size() == (*m_ActiveParticleEmitters).findLinearSearch(particleEmitter))
            (*m_ActiveParticleEmitters).push_back(particleEmitter);
    }
    void Scene::removeActiveParticleEmitter(ParticleEmitter *particleEmitter)
    {
        DEBUG_ASSERT(NULL != particleEmitter);
        
//        particleEmitter->removeReference();
        
        (*m_ActiveParticleEmitters).remove(particleEmitter);
    }
    void Scene::addActiveClock(Clock *clock)
    {
        DEBUG_ASSERT(NULL != clock);
        
        if((*m_ActiveClocks).size() == (*m_ActiveClocks).findLinearSearch(clock))
            (*m_ActiveClocks).push_back(clock);
    }
    void Scene::removeActiveClock(Clock *clock)
    {
        DEBUG_ASSERT(NULL != clock);
        
        (*m_ActiveClocks).remove(clock);
    }
    void Scene::addActiveGeometry(Geometry *geometry)
    {
        DEBUG_ASSERT(NULL != geometry);
        
        if((*m_ActiveGeometry).size() == (*m_ActiveGeometry).findLinearSearch(geometry))
            (*m_ActiveGeometry).push_back(geometry);
    }
    void Scene::removeActiveGeometry(Geometry *geometry)
    {
        DEBUG_ASSERT(NULL != geometry);
        
        (*m_ActiveGeometry).remove(geometry);
    }
    
    void Scene::clearNodeTouches()
    {
        for (s32 i = 0; i < (*m_ActiveNodes).size(); ++i)
        {
            (*m_ActiveNodes).at(i)->enableTouched(false);
        }
    }
    
    void Scene::clearAllStates()
    {
        
        SceneStateMachine *sm = getStateMachine();
        if (sm)
            sm->clear();
        for (s32 i = 0; i < (*m_ActiveNodes).size(); ++i)
        {
            Node *node = (*m_ActiveNodes).at(i);
            if (node)
            {
                NodeStateMachine *nsm = node->getStateMachine();
                if(nsm)
                    nsm->clear();
            }
        }
    }

}
