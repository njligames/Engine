
//
//  Node.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Node.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "btTransform.h"

#include "NodeBuilder.h"
#include "NodeStateMachine.h"
#include "ParticleEmitter.h"
#include "NodeStateMachine.h"
#include "Camera.h"
#include "Light.h"
#include "Geometry.h"
#include "PhysicsBody.h"
#include "PhysicsField.h"
#include "PhysicsWorld.h"
#include "Scene.h"
#include "Sound.h"
#include "Log.h"
#define TAG "Node.cpp"
#include "Material.h"
#include "PhysicsConstraint.h"
#include "PhysicsShape.h"
#define FORMATSTRING "{\"njli::Node\":[{\"name\":\"%s\"}]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btQuickprof.h"
#include "Thread.h"
#include "SteeringBehaviorMachine.h"




namespace njli
{
    void  Node::updateActions( void *_ptr )
    {
        njli::Node *node = static_cast<njli::Node*>(_ptr);
        node->updateActions();
    }

    
    Node::Node():
    AbstractFactoryObject(this),
    m_PhysicsBody(NULL),
    m_Light(NULL),
    m_Camera(NULL),
    m_Geometry(NULL),
    m_PhysicsField(NULL),
    m_Opacity(1.0f),
    m_RenderCategory(JLI_BIT_CATEGORY_NONE),
    m_NodeStateMachine(NodeStateMachine::create()),
    m_pParent(NULL),
    m_GeometryIndex(-1),
    m_isTouchedByRay(false),
//    m_ApplyPhysicsShape(false),
    m_Transform(new btTransform(btTransform::getIdentity())),
    m_ColorTransform(new btTransform(btTransform::getIdentity())),
    m_Orientation(new btQuaternion(btQuaternion::getIdentity())),
    m_Scale(new btVector3(1,1,1)),
    m_Pivot(new btTransform(btTransform::getIdentity())),
    m_SteeringBehaviorMachine(NULL),
    m_CurrentScene(NULL)//,
//    m_ActionThread(Thread::create())
    {
        addChild(m_NodeStateMachine);
        
        
//        m_ActionThread->enablePause(false);
    }
    
    Node::Node(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_PhysicsBody(NULL),
    m_Light(NULL),
    m_Camera(NULL),
    m_Geometry(NULL),
    m_PhysicsField(NULL),
    m_Opacity(1.0f),
    m_RenderCategory(JLI_BIT_CATEGORY_NONE),
    m_NodeStateMachine(NodeStateMachine::create()),
    m_pParent(NULL),
    m_GeometryIndex(-1),
    m_isTouchedByRay(false),
//    m_ApplyPhysicsShape(false),
    m_Transform(new btTransform(btTransform::getIdentity())),
    m_ColorTransform(new btTransform(btTransform::getIdentity())),
    m_Orientation(new btQuaternion(btQuaternion::getIdentity())),
    m_Scale(new btVector3(1,1,1)),
    m_Pivot(new btTransform(btTransform::getIdentity())),
    m_SteeringBehaviorMachine(NULL),
    m_CurrentScene(NULL)//,
//    m_ActionThread(Thread::create())
    {
        addChild(m_NodeStateMachine);
        
//        m_ActionThread->enablePause(false);
    }
    
    Node::Node(const Node &copy):
    AbstractFactoryObject(this),
    m_PhysicsBody(NULL),
    m_Light(NULL),
    m_Camera(NULL),
    m_Geometry(NULL),
    m_PhysicsField(NULL),
    m_Opacity(1.0f),
    m_RenderCategory(JLI_BIT_CATEGORY_NONE),
    m_NodeStateMachine(NodeStateMachine::create()),
    m_pParent(NULL),
    m_GeometryIndex(-1),
    m_isTouchedByRay(false),
//    m_ApplyPhysicsShape(false),
    m_Transform(new btTransform(btTransform::getIdentity())),
    m_ColorTransform(new btTransform(btTransform::getIdentity())),
    m_Orientation(new btQuaternion(btQuaternion::getIdentity())),
    m_Scale(new btVector3(1,1,1)),
    m_Pivot(new btTransform(btTransform::getIdentity())),
    m_SteeringBehaviorMachine(NULL),
    m_CurrentScene(NULL)//,
//    m_ActionThread(Thread::create())
    {
        addChild(m_NodeStateMachine);
        
//        m_ActionThread->enablePause(false);
    }
    
    Node::~Node()
    {
        delete m_Pivot;
        m_Pivot = NULL;
        
        delete m_Scale;
        m_Scale = NULL;
        
        delete m_Orientation;
        m_Orientation = NULL;
        
        delete m_Transform;
        m_Transform = NULL;
        
        delete m_ColorTransform;
        m_ColorTransform = NULL;
        
        removeFromParentNode();
        
    }
    
    Node &Node::operator=(const Node &rhs)
    {
        if(this != &rhs)
        {
            //TODO: Implement....
        }
        return *this;
    }
    
    s32	Node::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Node::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Node::getClassName()const
    {
        return "Node";
    }
    
    s32 Node::getType()const
    {
        return Node::type();
    }
    
    Node::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format(FORMATSTRING, getName()));
    }
    
    Node **Node::createArray(const u32 size)
    {
        return (Node**)World::getInstance()->getWorldFactory()->createArray(Node::type(), size);
    }
    
    void Node::destroyArray(Node **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Node *Node::create()
    {
        return dynamic_cast<Node*>(World::getInstance()->getWorldFactory()->create(Node::type()));
    }
    
    Node *Node::create(const NodeBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Node*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Node *Node::clone(const Node &object)
    {
        return dynamic_cast<Node*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Node *Node::copy(const Node &object)
    {
        return dynamic_cast<Node*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Node::destroy(Node *object, bool destroyChildrenNodes)
    {
        if(object)
        {
            if (destroyChildrenNodes)
            {
                for (std::vector<Node*>::iterator iter = object->m_Children.begin();
                     iter != object->m_Children.end(); ++iter)
                {
                    Node::destroy(*iter, true);
                }
            }
            
            object->removeAllActions();
            object->removeAllParticleEmitters();
            object->removePhysicsBody();
            object->removeLight();
            object->removeCamera();
            object->removeGeometry();
            object->removePhysicsField();
            object->removeAllSounds();
            
            NodeStateMachine *sm = object->getStateMachine();
            if(World::getInstance()->getWorldFactory()->has(sm))
                NodeStateMachine::destroy(sm);
            object->removeStateMachine();
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Node::load(Node &object, lua_State *L, int index)
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
                Node::load(object, L, -2);
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
    
    u32 Node::type()
    {
        return JLI_OBJECT_TYPE_Node;
    }
    
//    btTransform Node::getWorldTransform()const
//    {
//        const PhysicsBody *physicsBody = getPhysicsBody();
//        
//        if(physicsBody)
//        {
//            btTransform transform(physicsBody->getWorldTransform());
//            
//            transform.setBasis(transform.getBasis().scaled(getScale()));
//            
//            if(getParentNode())
//            {
//                return (transform * getParentNode()->getWorldTransform());
//            }
//            return (transform);
//        }
//        
//        btTransform transform(getTransform());
//        
//        transform.setBasis(transform.getBasis().scaled(getScale()));
//        
//        if(getParentNode())
//        {
//            return (transform * getParentNode()->getWorldTransform());
//        }
//        return (transform);
//    }
    
    const btTransform& Node::getColorTransform() const
    {
        return *m_ColorTransform;
    }
    
    void Node::setColorTransform(const btTransform& transform)
    {
        *m_ColorTransform = transform;
    }
    
    const btTransform &Node::getTransform()const
    {
        return *m_Transform;
    }
    
    void Node::setTransform(const btTransform &transform)
    {
        *m_Transform = transform;

        applyPhysicsBodyTransform(transform);
        
//        PhysicsBody *physicsBody = getPhysicsBody();
//        
//        if(physicsBody)// && physicsBody->getCollisionObject() && !physicsBody->isDynamicPhysics())
//        {
//            physicsBody->setWorldTransform(getTransform());
//        }
    }
    
    btVector3 Node::getOrigin()const
    {
        return getWorldTransform().getOrigin();
    }
    
    void Node::setOrigin(const btVector3 &origin)
    {
        btTransform t(getTransform());
        t.setOrigin(origin);
        setTransform(t);
    }
    
    void Node::setOrigin(const btVector2 &origin)
    {
        btVector3 _origin(origin.x(), origin.y(), 0);
        Node::setOrigin(_origin);
    }
    
    btQuaternion Node::getRotation()const
    {
        return getWorldTransform().getRotation();
    }
    
    void Node::setRotation(const btQuaternion &rotation)
    {
        btTransform t(getTransform());
        t.setRotation(rotation);
        setTransform(t);
    }
    
    btVector3 Node::getEulerAngles()const
    {
        f32 x, y, z;
        
        m_Transform->getBasis().getEulerYPR(x, y, z);
        
        btVector3 v(x,y,z);
        return v;
    }
    
    void Node::setEulerAngles(const btVector3 &angles)
    {
        btTransform t(getTransform());
        btMatrix3x3 m(t.getBasis());
        m.setEulerYPR(angles.x(), angles.y(), angles.z());
        t.setBasis(m);
        setTransform(t);
    }
    
    const btQuaternion &Node::getOrientation()const
    {
        return *m_Orientation;
    }
    
    void Node::setOrientation(const btQuaternion &orientation)
    {
        *m_Orientation = orientation;
    }
    
    const btVector3 &Node::getScale()const
    {
        return *m_Scale;
    }
    
    void Node::setScale(const btVector3 &scale)
    {
        *m_Scale = scale;
    }
    
    void Node::setScale(const f32 scale)
    {
        btVector3 _scale(scale,scale,scale);
        Node::setScale(_scale);
    }
    
    btTransform &Node::getPivot()const
    {
        return *m_Pivot;
    }
    
    void Node::setPivot(const btTransform &pivot)
    {
        *m_Pivot = pivot;
    }
    
    void Node::setSteeringBehaviorMachine(SteeringBehaviorMachine *steeringBehaviorMachine)
    {
        DEBUG_ASSERT(steeringBehaviorMachine != NULL);
        
        removeSteeringBehaviorMachine();
        
        m_SteeringBehaviorMachine = steeringBehaviorMachine;
        
        addChild(m_SteeringBehaviorMachine);
    }
    
    void Node::removeSteeringBehaviorMachine()
    {
        if(getSteeringBehaviorMachine())
        {
            removeChild(getSteeringBehaviorMachine());
        }
        
        m_SteeringBehaviorMachine = NULL;
    }
    
    SteeringBehaviorMachine *Node::getSteeringBehaviorMachine()
    {
        s32 idx = getChildIndex(m_SteeringBehaviorMachine);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<SteeringBehaviorMachine*>(getChild(idx)));
            return dynamic_cast<SteeringBehaviorMachine*>(getChild(idx));
        }
        return NULL;
    }
    
    const SteeringBehaviorMachine *Node::getSteeringBehaviorMachine()const
    {
        s32 idx = getChildIndex(m_SteeringBehaviorMachine);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const SteeringBehaviorMachine*>(getChild(idx)));
            return dynamic_cast<const SteeringBehaviorMachine*>(getChild(idx));
        }
        return NULL;
    }
    
    s32 Node::addParticleEmitter(ParticleEmitter *emitter)
    {
        DEBUG_ASSERT(NULL != emitter);
        
        Scene *scene = this->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        std::vector<ParticleEmitter*>::const_iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), emitter);
        
        if(iter == m_ParticleEmitterList.end())
        {
            std::vector<ParticleEmitter*>::iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), emitter);
            
            if(iter != m_ParticleEmitterList.end())
                removeParticleEmitter(emitter);
            
            m_ParticleEmitterList.push_back(emitter);
            
            addChild(emitter);
            scene->addActiveParticleEmitter(emitter);
        }
        
        return getParticleEmitterIndex(emitter);
    }
    
    bool Node::removeParticleEmitter(ParticleEmitter *emitter)
    {
        DEBUG_ASSERT(NULL != emitter);
        
        Scene *scene = this->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        std::vector<ParticleEmitter*>::iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), emitter);
        
        if(iter != m_ParticleEmitterList.end())
        {
            removeChild(*iter);
            scene->removeActiveParticleEmitter(*iter);
            
            m_ParticleEmitterList.erase(iter);
            return true;
        }
        return false;
    }
    
    void Node::removeAllParticleEmitters()
    {
        for(std::vector<ParticleEmitter*>::iterator iter = m_ParticleEmitterList.begin();
            iter != m_ParticleEmitterList.end();
            ++iter)
        {
            removeChild(*iter);
        }
        m_ParticleEmitterList.clear();
    }
    
    s32 Node::numberOfParticleEmitters()const
    {
        return m_ParticleEmitterList.size();
    }
    
    void Node::getParticleEmitters(std::vector<ParticleEmitter*> &particleEmitters)const
    {
        for(std::vector<ParticleEmitter*>::const_iterator iter = m_ParticleEmitterList.begin();
            iter != m_ParticleEmitterList.end();
            ++iter)
        {
            if(getChildIndex(*iter) != -1)
                particleEmitters.push_back(*iter);
        }
    }
    
    s32 Node::getParticleEmitterIndex(ParticleEmitter *emitter)const
    {
        std::vector<ParticleEmitter*>::const_iterator iter = std::find(m_ParticleEmitterList.begin(), m_ParticleEmitterList.end(), emitter);
        
        if (iter != m_ParticleEmitterList.end())
        {
            return std::distance(m_ParticleEmitterList.begin(), iter);
        }
        return -1;
    }
    
    ParticleEmitter *Node::getParticleEmitter(const u32 index)
    {
        if (index < m_ParticleEmitterList.size())
        {
            s32 idx = getChildIndex(m_ParticleEmitterList.at(index));
            if(idx != -1)
                return dynamic_cast<ParticleEmitter*>(getChild(idx));
        }
        return NULL;
    }
    
    const ParticleEmitter *Node::getParticleEmitter(const u32 index)const
    {
        if (index < m_ParticleEmitterList.size())
        {
            s32 idx = getChildIndex(m_ParticleEmitterList.at(index));
            if(idx != -1)
                return dynamic_cast<const ParticleEmitter*>(getChild(idx));
        }
        return NULL;
    }
    
    void Node::setPhysicsBody(PhysicsBody *body)
    {
        DEBUG_ASSERT(body != NULL);
        
        removePhysicsBody();
        
        m_PhysicsBody = body;
        
        addChild(m_PhysicsBody);
        
        getPhysicsBody()->setTransform(getTransform());
        
//        m_ApplyPhysicsShape = true;
    }
    
    void Node::removePhysicsBody()
    {
        PhysicsBody *physicsBody = getPhysicsBody();
        
        if(physicsBody)
        {
            removeChild(getPhysicsBody());
            
            physicsBody->removePhysicsBody();
        }
        
        m_PhysicsBody = NULL;
    }
    
    PhysicsBody *Node::getPhysicsBody()
    {
        s32 idx = getChildIndex(m_PhysicsBody);
        if(idx != -1)
//#if defined(DEBUG) || defined(_DEBUG)
//        {
//            return dynamic_cast<PhysicsBody*>(getChild(idx));
//        }
//#else
        {
//            DEBUG_ASSERT(dynamic_cast<PhysicsBody*>(getChild(idx)));
            return dynamic_cast<PhysicsBody*>(getChild(idx));
        }
//#endif
        
        return NULL;
    }
    
    const PhysicsBody *Node::getPhysicsBody()const
    {
        s32 idx = getChildIndex(m_PhysicsBody);
        if(idx != -1)
//#if defined(DEBUG) || defined(_DEBUG)
//        {
//            return dynamic_cast<const PhysicsBody*>(getChild(idx));
//        }
//#else
        {
//            DEBUG_ASSERT(dynamic_cast<const PhysicsBody*>(getChild(idx)));
            return dynamic_cast<const PhysicsBody*>(getChild(idx));
        }
//#endif
        
        return NULL;
    }
    
    void Node::setLight(Light *light)
    {
        DEBUG_ASSERT(light != NULL);
        
        removeLight();
        
        m_Light = light;
        
        addChild(m_Light);
    }
    
    void Node::removeLight()
    {
        if(getLight())
        {
            removeChild(getLight());
        }
        
        m_Light = NULL;
    }
    
    Light *Node::getLight()
    {
        s32 idx = getChildIndex(m_Light);
        if(idx != -1)
            return dynamic_cast<Light*>(getChild(idx));
        return NULL;
    }
    
    const Light *Node::getLight()const
    {
        s32 idx = getChildIndex(m_Light);
        if(idx != -1)
            return dynamic_cast<const Light*>(getChild(idx));
        return NULL;
    }
    
    void Node::setCamera(Camera *camera)
    {
        DEBUG_ASSERT(camera != NULL);
        
        removeCamera();
        m_Camera = camera;
        addChild(m_Camera);
        
//        Scene *scene = this->getCurrentScene();
//        
//        if(scene)
//        {
//            
//            scene->addActiveCamera(m_Camera);
//        }
//        else
//        {
//            DEBUG_LOG_WRITE_W(TAG, "Unable to set the Camera, the scene is NULL\n");
//        }

        
//        Scene *scene = this->getCurrentScene();
//        DEBUG_ASSERT(NULL != scene);
//        
//        removeCamera();
//        
//        m_Camera = camera;
//        
//        addChild(m_Camera);
////        scene->addActiveCamera(m_Camera);
    }
    
    void Node::removeCamera()
    {
        if(getCamera())
        {
            Scene *scene = this->getCurrentScene();
            DEBUG_ASSERT(NULL != scene);
            
            Camera *camera = getCamera();
            removeChild(camera);
            scene->removeActiveCamera(camera);
        }
        
        m_Camera = NULL;
    }
    
    Camera *Node::getCamera()
    {
        s32 idx = getChildIndex(m_Camera);
        if(idx != -1)
            return dynamic_cast<Camera*>(getChild(idx));
        return NULL;
    }
    
    const Camera *Node::getCamera()const
    {
        s32 idx = getChildIndex(m_Camera);
        if(idx != -1)
            return dynamic_cast<const Camera*>(getChild(idx));
        return NULL;
    }
    
    void Node::setGeometry(Geometry *geometry)
    {
        DEBUG_ASSERT(geometry != NULL);
        
        removeGeometry();
        
        m_Geometry = geometry;
        
        addChild(m_Geometry);
        
        m_Geometry->addReference(this);
        
//        m_ApplyPhysicsShape = true;
        
        Scene *scene = this->getCurrentScene();
//        DEBUG_ASSERT(NULL != scene);
        if(scene)
        {
            scene->addActiveGeometry(m_Geometry);
        }
        else
        {
            DEBUG_LOG_WRITE_W(TAG, "Unable to set the Geometry, the scene is NULL\n");
        }
    }
    
    void Node::removeGeometry()
    {
        Geometry *geometry = getGeometry();
        if(geometry)
        {
            Scene *scene = this->getCurrentScene();
            DEBUG_ASSERT(NULL != scene);
            
            geometry->removeReference(this);
            
            removeChild(geometry);
            
            scene->removeActiveGeometry(geometry);
        }
        
        m_Geometry = NULL;
    }
    
    Geometry *Node::getGeometry()
    {
        if(m_Geometry)
        {
            s32 idx = getChildIndex(m_Geometry);
            if(idx != -1)
            {
//                DEBUG_ASSERT(dynamic_cast<Geometry*>(getChild(idx)));
                return dynamic_cast<Geometry*>(getChild(idx));
            }
//                return dynamic_cast<Geometry*>(getChild(idx));
        }
        return NULL;
    }
    
    const Geometry *Node::getGeometry()const
    {
        if(m_Geometry)
        {
            s32 idx = getChildIndex(m_Geometry);
            if(idx != -1)
                return dynamic_cast<const Geometry*>(getChild(idx));
        }
        return NULL;
    }
    
    void Node::setPhysicsField(PhysicsField *field)
    {
        DEBUG_ASSERT(field != NULL);
        
        removePhysicsField();
        
        m_PhysicsField = field;
        
        addChild(m_PhysicsField);
    }
    
    void Node::removePhysicsField()
    {
        if(getPhysicsField())
        {
            removeChild(getPhysicsField());
        }
        
        m_PhysicsField = NULL;
    }
    
    PhysicsField *Node::getPhysicsField()
    {
        s32 idx = getChildIndex(m_PhysicsField);
        if(idx != -1)
            return dynamic_cast<PhysicsField*>(getChild(idx));
        return NULL;
    }
    
    const PhysicsField *Node::getPhysicsField()const
    {
        s32 idx = getChildIndex(m_PhysicsField);
        if(idx != -1)
            return dynamic_cast<const PhysicsField*>(getChild(idx));
        return NULL;
    }
    
    s32 Node::addSound(Sound *sound)
    {
        DEBUG_ASSERT(NULL != sound);
        
        std::vector<Sound*>::const_iterator iter = std::find(m_SoundList.begin(), m_SoundList.end(), sound);
        
        if(iter == m_SoundList.end())
        {
            std::vector<Sound*>::iterator iter = std::find(m_SoundList.begin(), m_SoundList.end(), sound);
            
            if(iter != m_SoundList.end())
                removeSound(sound);
            
            m_SoundList.push_back(sound);
            
            sound->setTransform(btTransform::getIdentity());
            
            addChild(sound);
        }
        
        return getSoundIndex(sound);
    }
    
    bool Node::removeSound(Sound *sound)
    {DEBUG_ASSERT(NULL != sound);
        
        std::vector<Sound*>::iterator iter = std::find(m_SoundList.begin(), m_SoundList.end(), sound);
        
        if(iter != m_SoundList.end())
        {
            removeChild(*iter);
            m_SoundList.erase(iter);
            return true;
        }
        return false;
    }
    
    void Node::removeAllSounds()
    {
        for(std::vector<Sound*>::iterator iter = m_SoundList.begin();
            iter != m_SoundList.end();
            ++iter)
        {
            removeChild(*iter);
        }
        m_SoundList.clear();
    }
    
    void Node::getSounds(std::vector<Sound*> &particleEmitters)const
    {
        for(std::vector<Sound*>::const_iterator iter = m_SoundList.begin();
            iter != m_SoundList.end();
            ++iter)
        {
            if(getChildIndex(*iter) != -1)
                particleEmitters.push_back(*iter);
        }
    }
    
    s32 Node::getSoundIndex(Sound *sound)const
    {
        std::vector<Sound*>::const_iterator iter = std::find(m_SoundList.begin(), m_SoundList.end(), sound);
        
        if (iter != m_SoundList.end())
        {
            return std::distance(m_SoundList.begin(), iter);
        }
        return -1;
    }
    
    Sound *Node::getSound(const u32 index)
    {
        if (index < m_SoundList.size())
        {
            s32 idx = getChildIndex(m_SoundList.at(index));
            if(idx != -1)
                return dynamic_cast<Sound*>(getChild(idx));
        }
        return NULL;
    }
    
    const Sound *Node::getSound(const u32 index)const
    {
        if (index < m_SoundList.size())
        {
            s32 idx = getChildIndex(m_SoundList.at(index));
            if(idx != -1)
                return dynamic_cast<const Sound*>(getChild(idx));
        }
        return NULL;
    }
    
    void Node::setOpacity(f32 opacity)
    {
        m_Opacity = (opacity > 1.0f)?1.0f:((opacity<0.0f)?0.0f:opacity);
        
        Geometry *g = getGeometry();
        if (g)
        {
            g->setOpacity(this, m_Opacity);
        }
    }
    
    void Node::transformVertices(const btTransform &transfrom)
    {
        Geometry *g = getGeometry();
        if (g)
        {
            g->transformVertices(this, transfrom);
        }
    }
    
    void Node::transformVertexColors(const btTransform &transform)
    {
        Geometry *g = getGeometry();
        if (g)
        {
            g->transformVertexColors(this, transform);
        }
    }
    
    void Node::transformTextureCoordinates(const btTransform &transform)
    {
        Geometry *g = getGeometry();
        if (g)
        {
            g->transformTextureCoordinates(this, transform);
        }
        
    }
    
    f32 Node::getOpacity()const
    {
        return m_Opacity;
    }
    
    bool Node::hasOpacity()const
    {
        const Geometry *geometry = getGeometry();
        if (geometry)
        {
            const Material *material = geometry->getMaterial();
            
            if(material)
            {
                return (material->hasOpacity() ||
                        (material->getTransparency() != 1.0) ||
                        (m_Opacity != 1.0f));
            }
        }
        return m_Opacity != 1.0f;
    }
    
    void Node::hide(Camera *camera)
    {
        if (NULL == camera)
        {
            m_RenderCategory = (njliBitCategories)Off(m_RenderCategory, JLI_BIT_CATEGORY_ALL);
        }
        else
        {
            m_RenderCategory = (njliBitCategories)Off(m_RenderCategory, camera->getRenderCategory());
        }
        
        for (std::vector<Node*>::const_iterator iter = m_Children.begin();
             iter != m_Children.end();
             ++iter)
        {
            Node *n = (*iter);
            if(NULL != n)
            {
                n->hide(camera);
            }
        }
        for (int i = 0; i < numberOfParticleEmitters(); ++i)
        {
            ParticleEmitter *pe = getParticleEmitter(i);
            pe->setRenderCategory(this);
        }
    }
    
    void Node::show(Camera *camera)
    {
        m_RenderCategory = (njliBitCategories)On(m_RenderCategory, camera->getRenderCategory());
        for (std::vector<Node*>::const_iterator iter = m_Children.begin();
             iter != m_Children.end();
             ++iter)
        {
            Node *n = (*iter);
            if(NULL != n)
            {
                n->show(camera);
            }
        }
        for (int i = 0; i < numberOfParticleEmitters(); ++i)
        {
            ParticleEmitter *pe = getParticleEmitter(i);
            pe->setRenderCategory(this);
        }
        
    }
    
    bool Node::isHidden(Camera *camera)const
    {
        return !camera->hasRenderCategory(m_RenderCategory);
    }
    
    void Node::setRenderCategory(Node *node)
    {
        if(node)
        {
            m_RenderCategory = node->m_RenderCategory;
            
            
            for (std::vector<Node*>::const_iterator iter = m_Children.begin();
                 iter != m_Children.end();
                 ++iter)
            {
                Node *n = (*iter);
                if(NULL != n)
                {
                    n->setRenderCategory(node);
                }
            }
            for (int i = 0; i < numberOfParticleEmitters(); ++i)
            {
                ParticleEmitter *pe = getParticleEmitter(i);
                pe->setRenderCategory(node);
            }
        }
    }
    
    NodeStateMachine *Node::getStateMachine()
    {
        s32 idx = getChildIndex(m_NodeStateMachine);
        if(idx != -1)
//#if defined(DEBUG) || defined(_DEBUG)
//        {
//            return dynamic_cast<NodeStateMachine*>(getChild(idx));
//        }
//#else
        {
//            DEBUG_ASSERT(dynamic_cast<NodeStateMachine*>(getChild(idx)));
            return dynamic_cast<NodeStateMachine*>(getChild(idx));
        }
//#endif
        
        return NULL;
    }
    
    const NodeStateMachine *Node::getStateMachine() const
    {
        s32 idx = getChildIndex(m_NodeStateMachine);
        
        if(idx != -1)
//#if defined(DEBUG) || defined(_DEBUG)
//        {
//            return dynamic_cast<const NodeStateMachine*>(getChild(idx));
//        }
//#else
        {
//            DEBUG_ASSERT(dynamic_cast<const NodeStateMachine*>(getChild(idx)));
            return dynamic_cast<const NodeStateMachine*>(getChild(idx));
        }
//#endif
        
        return NULL;
    }
    
    void Node::removeStateMachine()
    {
        NodeStateMachine *sm = getStateMachine();
        if (sm != NULL)
        {
            removeChild(sm);
            m_NodeStateMachine = NULL;
        }
    }
    
    bool Node::isTouched()const
    {
        return m_isTouchedByRay;
    }
    
    void Node::enableTouched(bool enable)
    {
        m_isTouchedByRay = enable;
    }
    
    bool Node::rayTestClosest(const btVector3 &from, const btVector3 &to,
                            PhysicsRayContact &rayContact,
                            njliBitCategories collisionGroup,
                            njliBitCategories collisionMask)const
    {
        const Scene *scene = this->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        if(scene)
            return scene->getPhysicsWorld()->rayTestClosest(from,
                                                            to,
                                                            rayContact,
                                                            collisionGroup,
                                                            collisionMask);
        return false;
    }
    
    bool Node::rayTestAll(const btVector3 &from, const btVector3 &to,
                          btAlignedObjectArray<PhysicsRayContact*> &rayContacts,
                          s32 &numContacts,
                          njliBitCategories collisionGroup,
                          njliBitCategories collisionMask)const
    {
        const Scene *scene = this->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        if(scene)
            return scene->getPhysicsWorld()->rayTestAll(from, to, rayContacts, numContacts, collisionGroup, collisionMask);
        return false;
    }
    
    bool Node::rayTestClosest(const btVector2 &screenPosition,
                               PhysicsRayContact &rayContact,
                               njliBitCategories collisionGroup,
                               njliBitCategories collisionMask)const
    {
        const Scene *scene = this->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        if(scene && scene->getPhysicsWorld() && getCamera())
        {
            btVector3 from = getCamera()->unProject(screenPosition);
            btVector3 near = from * getCamera()->getZNear();
            from += near;
            btVector3 to = from * getCamera()->getZFar();
            
            return rayTestClosest(from, to, rayContact, collisionGroup, collisionMask);
        }
        return false;
    }
    
    bool Node::rayTestAll(const btVector2 &screenPosition,
                          btAlignedObjectArray<PhysicsRayContact*> &rayContacts,
                          s32 &numContacts,
                          njliBitCategories collisionGroup,
                          njliBitCategories collisionMask)const
    {
        const Scene *scene = this->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        if(scene && scene->getPhysicsWorld() && getCamera())
        {
            btVector3 from = getCamera()->unProject(screenPosition);
            btVector3 near = from * getCamera()->getZNear();
            from += near;
            btVector3 to = from * getCamera()->getZFar();
            
            return rayTestAll(from, to, rayContacts, numContacts, collisionGroup, collisionMask);
        }
        
        return false;
    }
    
    void Node::runAction(Action *action, bool callCompletionFunction)
    {
        addChild(action);
        AbstractActionable::runAction(action, callCompletionFunction);
    }
    
    void Node::runAction(Action *action, const char *key, bool callCompletionFunction)
    {
        addChild(action);
        AbstractActionable::runAction(action, key, callCompletionFunction);
    }
    
    bool Node::removeAction(const char *key)
    {
        Action *a = AbstractActionable::getAction(key);
        if(a)
        {
            removeChild(a);
            return AbstractActionable::removeAction(key);
        }
        return false;
    }
    
    void Node::removeAllActions()
    {
        std::vector<std::string> actionNames;
        
        AbstractActionable::getAllActionNames(actionNames);
        
        for (s32 i = 0; i < actionNames.size(); ++i)
        {
            Node::removeAction(actionNames[i].c_str());
        }
    }
    
    void Node::getAabb(btVector3& aabbMin,btVector3& aabbMax) const
    {
        btTransform transform(getWorldTransform());
        aabbMin = btVector3(0,0,0);
        aabbMax = btVector3(0,0,0);
        transform.setOrigin(aabbMin);
        
        const PhysicsBody * body = getPhysicsBody();
        if (body)
        {
            const PhysicsShape *shape = body->getPhysicsShape();
            if(shape)
            {
                shape->getAabb(transform, aabbMin, aabbMax);
            }
        }
        
    }
    
//    void Node::applyPhysicsShape()
//    {
//        BT_PROFILE("Node::applyPhysicsShape");
//        Geometry *geometry = getGeometry();
//        if(geometry)
//        {
//            geometry->setTransform(this->getGeometryIndex(), getWorldTransform());
//            PhysicsBody *physicsBody = getPhysicsBody();
//            if(physicsBody)
//                geometry->applyShape(this, physicsBody->getPhysicsShape());
//        }
//    }
    
    Node *Node::getParentNode()
    {
        return m_pParent;
    }
    
    const Node *Node::getParentNode() const
    {
        return m_pParent;
    }
    
    bool Node::hasParentNode()const
    {
        return (NULL != m_pParent);
    }
    
    void Node::setParentNode(Node *parent)
    {
        DEBUG_ASSERT_WRITE(parent, "object is null");
        
        m_pParent = parent;
    }
    
    void Node::removeParentNode()
    {
        m_pParent = NULL;
    }
    
    bool Node::removeFromParentNode()
    {
        Node *parent = dynamic_cast<Node*>(getParentNode());
        
        if(parent && parent->hasChildNode(this))
        {
            parent->removeChildNode(this);
            return true;
        }
        return false;
    }
    
    Node *Node::findChildNode(const char *name)
    {
        if(strcmp(getName(), name) == 0)
        {
            return this;
        }
        else
        {
            for (std::vector<Node*>::const_iterator iter = m_Children.begin();
                 iter != m_Children.end();
                 ++iter)
            {
                Node *n = (*iter)->findChildNode(name);
                if(NULL != n)
                {
                    return n;
                }
            }
        }
        return NULL;
    }
    
    const Node *Node::findChildNode(const char *name) const
    {
        if(strcmp(getName(), name) == 0)
        {
            return this;
        }
        else
        {
            for (std::vector<Node*>::const_iterator iter = m_Children.begin();
                 iter != m_Children.end();
                 ++iter)
            {
                Node *n = (*iter)->findChildNode(name);
                if(NULL != n)
                {
                    return n;
                }
            }
        }
        return NULL;
    }
    
    Node*	Node::getChildNode(const u32 index)
    {
        DEBUG_ASSERT_WRITE(index < numberOfChildrenNodes(), "index must be smaller than the size of the array");
        return m_Children.at(index);
    }
    
    const Node*	Node::getChildNode(const u32 index)const
    {
        DEBUG_ASSERT_WRITE(index < numberOfChildrenNodes(), "index must be smaller than the size of the array");
        return m_Children.at(index);
    }
    
    void Node::getChildrenNodes(std::vector<Node*> &children)const
    {
        children = m_Children;
    }
    
    s32 Node::getChildNodeIndex(Node *object)const
    {
        std::vector<Node*>::const_iterator iter = std::find(m_Children.begin(), m_Children.end(), object);
        
        if (iter != m_Children.end())
        {
            return std::distance(m_Children.begin(), iter);
        }
        return -1;
    }
    
    bool Node::hasChildNode(Node *object)const
    {
        DEBUG_ASSERT_WRITE(object, "object is null");
        
        std::vector<Node*>::const_iterator iter = std::find(m_Children.begin(), m_Children.end(), object);
        
        if(m_Children.end() != iter)
            return true;
        
        for (iter = m_Children.begin(); iter != m_Children.end(); ++iter)
        {
            if((*iter)->hasChildNode(object))
            {
                return true;
            }
        }
        return false;
    }
    
    bool Node::hasChildrenNodes()const
    {
        return (numberOfChildrenNodes() > 0);
    }
    
    void Node::addChildNode(Node *object)
    {
        DEBUG_ASSERT_WRITE(this != object, "cannot decorate self with self");
        DEBUG_ASSERT_WRITE(!hasChildNode(object), "already has the decorator");
        
        object->setParentNode(this);
        m_Children.push_back(object);
        
        Scene *scene = this->getCurrentScene();
        if(NULL != scene)
            scene->addActiveNode(object);
    }
    
    void Node::removeChildNode(const u32 index)
    {
        DEBUG_ASSERT_WRITE(index < numberOfChildrenNodes(), "index must be smaller than the size of the array");
        removeChildNode(getChildNode(index));
    }
    
    void Node::removeChildNode(Node *object)
    {
        const Scene *scene = this->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        DEBUG_ASSERT_WRITE(object, "object is null");
        
        std::vector<Node*>::iterator iter = std::find(m_Children.begin(), m_Children.end(), object);
        
        if(iter != m_Children.end())
        {
            (*iter)->removeParentNode();
            m_Children.erase(iter);
            
            Scene *scene = this->getCurrentScene();
            if(NULL != scene)
                scene->removeActiveNode(object);
            
            scene->removeActiveNode(object);
        }
    }
    
    void Node::removeChildrenNodes()
    {
        for (s32 i = 0; i < m_Children.size(); ++i)
        {
            removeChildNode(m_Children.at(i));
        }
        m_Children.clear();
    }
    
    u32 Node::numberOfChildrenNodes()const
    {
        return m_Children.size();
    }
    
    void Node::replaceChildNode(Node *oldChild, Node *newChild)
    {
        Node *parent = dynamic_cast<Node*>(oldChild->getParentNode());
        
        parent->removeChildNode(oldChild);
        parent->addChildNode(newChild);
    }
    
    void Node::update(f32 timeStep)
    {
        BT_PROFILE("Node::update");

        SteeringBehaviorMachine *steeringMachine = getSteeringBehaviorMachine();
        if(steeringMachine)
        {
            steeringMachine->calculate(timeStep);
        }
        
//        if(m_ActionThread->isPaused())
//        {
//            m_ActionThread->setup(&Node::updateActions, this, SIO2_THREAD_PRIORITY_NORMAL);
//            m_ActionThread->enablePause(false);
//        }
        AbstractActionable::update(timeStep);
        
        NodeStateMachine *sm = getStateMachine();
        if(sm != NULL)
            sm->update(timeStep);
        
//        Node *parent = getParentNode();
//        //        if(m_ApplyPhysicsShape || (parent && parent->m_ApplyPhysicsShape))
//        {
//            applyPhysicsShape();
//            m_ApplyPhysicsShape = false;
//        }
    }
    
//    void Node::render(Camera *camera)
//    {
//        if(!isHidden(camera))
//        {
//            Geometry *geometry = getGeometry();
//            if(geometry != NULL)
//                geometry->render(camera);
//        }
//    }
    
    void Node::applyPhysicsBodyTransform(const btTransform &transform)
    {
        PhysicsBody *physicsBody = getPhysicsBody();
        
        if(physicsBody)
            physicsBody->setTransform(transform);
    }
    
    void Node::setGeometryIndex(s64 index)
    {
        DEBUG_ASSERT(index >= 0 && index < NUMBER_OF_MESHES);
        m_GeometryIndex = index;
//        m_ApplyPhysicsShape = true;
    }
    size_t Node::getGeometryIndex()const
    {
        return m_GeometryIndex;
    }
    void Node::clearGeometryIndex()
    {
        m_GeometryIndex = -1;
    }
    
    Scene *Node::getCurrentScene()
    {
        if(m_CurrentScene == NULL)
            m_CurrentScene = njli::World::getInstance()->getScene();
        return m_CurrentScene;
    }
    
    const Scene *Node::getCurrentScene()const
    {
        return m_CurrentScene;
    }
    
    void Node::setCurrentScene(Scene *scene)
    {
        m_CurrentScene = scene;
        
        if(NULL != m_Geometry)
        {
            if(m_CurrentScene)
                m_CurrentScene->addActiveGeometry(m_Geometry);
        }
        
        if(NULL != m_Camera)
        {
            if(m_CurrentScene)
                m_CurrentScene->addActiveCamera(m_Camera);
        }
    }
    
    void Node::setCurrentScene(Node *node)
    {
        setCurrentScene(node->getCurrentScene());
    }
    void Node::removeCurrentScene()
    {
        m_CurrentScene = NULL;
    }
    
    void Node::updateActions()
    {
        AbstractActionable::update(World::getInstance()->getWorldClock()->timeStep());
    }
    
    bool Node::canDelete()const
    {
        bool can = AbstractFactoryObject::canDelete();
        can = can && !hasChildrenNodes();
        return can;
    }
}
