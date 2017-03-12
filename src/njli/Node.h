//
//  Node.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Node__
#define __JLIGameEngineTest__Node__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
//#include "AbstractTransform.h"
#include "AbstractActionable.h"
#include "JLIFactoryTypes.h"
#include "btVector2.h"
#include "lua.hpp"
#include <string>

#include "btTransform.h"
#include "PhysicsBody.h"

class btQuaternion;
class btTransform;

namespace njli {
class NodeBuilder;
class NodeStateMachine;
class ParticleEmitter;
class NodeStateMachine;
class Camera;
class Light;
class Geometry;
//class PhysicsBody;
class PhysicsField;
class PhysicsWorld;
class Scene;
class NodeState;
class PhysicsRayContact;
class Sound;
class PhysicsConstraint;
class Thread;
    class SteeringBehaviorMachine;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Node : public AbstractFactoryObject,
       //    public AbstractTransform,
       public AbstractActionable
{
    friend class WorldFactory;
    friend class World;
    friend class Scene;
    friend class Geometry;
    friend class Sprite2D;
    friend class PhysicsConstraintPointToPoint;
    friend class PhysicsBody;
    friend class PhysicsShape;
    friend class PhysicsConstraintHinge;
    friend class PhysicsConstraintConeTwist;
    friend class PhysicsConstraintFixed;
    friend class PhysicsConstraintGeneric6Dof;
    friend class PhysicsConstraintGeneric6DofSpring;
    friend class PhysicsConstraintSlider;
    friend class PhysicsBodyRigid;
    
    friend class PhysicsConstraint;

protected:
    Node();
    Node(const AbstractBuilder&);
    Node(const Node&);
    BT_DECLARE_ALIGNED_ALLOCATOR();

    virtual ~Node();
    Node& operator=(const Node&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

//    using AbstractActionable::runAction;
    using AbstractActionable::getAction;
    using AbstractActionable::hasActions;
    using AbstractActionable::removeAction;
    using AbstractActionable::removeAllActions;

    /**
         *  @author James Folk, 16-02-10 21:02:39
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:45
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

    /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual const char* getClassName() const;

    /**
         *  @author James Folk, 16-02-10 21:02:54
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual s32 getType() const;

    /**
         *  @author James Folk, 16-02-10 21:02:59
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    operator std::string() const;

    /**
         *  @author James Folk, 16-02-10 21:02:09
         *
         *  @brief <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static Node** createArray(const u32 size);

    /**
         *  @author James Folk, 16-02-10 21:02:13
         *
         *  @brief <#Description#>
         *
         *  @param array <#array description#>
         *  @param size  <#size description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static void destroyArray(Node * *array, const u32 size = 0);

    /**
         *  @author James Folk, 16-02-10 21:02:21
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static Node* create();

    /**
         *  @author James Folk, 16-02-10 21:02:23
         *
         *  @brief <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static Node* create(const NodeBuilder& builder);

    /**
         *  @author James Folk, 16-02-10 21:02:31
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static Node* clone(const Node& object);

    /**
         *  @author James Folk, 16-02-10 21:02:36
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static Node* copy(const Node& object);

    /**
         *  @author James Folk, 16-02-10 21:02:41
         *
         *  @brief <#Description#>
         *
         *  @param object               <#object description#>
         *  @param destroyChildrenNodes <#destroyChildrenNodes description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static void destroy(Node * object, bool destroyChildrenNodes = false);

    /**
         *  @author James Folk, 16-02-10 21:02:46
         *
         *  @brief <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static void load(Node & object, lua_State * L, int stack_index);

    /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    static u32 type();

    /**
         *  @author James Folk, 16-02-10 21:02:55
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    inline btTransform getWorldTransform() const
    {
        const PhysicsBody *physicsBody = getPhysicsBody();
        
        if(physicsBody)
        {
            btTransform transform(physicsBody->getWorldTransform());
            
            transform.setBasis(transform.getBasis().scaled(getScale()));
            
            if(getParentNode())
            {
                return (transform * getParentNode()->getWorldTransform());
            }
            return (transform);
        }
        
        btTransform transform(getTransform());
        
        transform.setBasis(transform.getBasis().scaled(getScale()));
        
        if(getParentNode())
        {
            return (transform * getParentNode()->getWorldTransform());
        }
        return (transform);
    }
    
    
    const btTransform& getColorTransform() const;
    void setColorTransform(const btTransform& transform);

public:
    //TODO: fill in specific methods for Node

    /**
         *  @author James Folk, 16-02-10 21:02:05
         *
         *  @brief The transformation is the combination of the node’s rotation, position, and scale properties. The default transformation is SCNMatrix4Identity.
         
         When you set the value of this property, the node’s rotation, orientation, eulerAngles, position, and scale properties automatically change to match the new transform, and vice versa. JLIEngine can perform this conversion only if the transform you provide is a combination of rotation, translation, and scale operations. If you set the value of this property to a skew transformation or to a nonaffine transformation, the values of these properties become undefined. Setting a new value for any of these properties causes JLIEngine to compute a new transformation, discarding any skew or nonaffine operations in the original transformation.
         *
         *  @return The Transform for this instance.
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const btTransform& getTransform() const;

    /**
         *  @author James Folk, 16-02-10 21:02:36
         *
         *  @brief <#Description#>
         *
         *  @param transform <#transform description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setTransform(const btTransform& transform);

    /**
         *  @author James Folk, 16-02-10 21:02:39
         *
         *  @brief The node’s position locates it within the coordinate system of its parent, as modified by the node’s pivot property. The default position is the zero vector, indicating that the node is placed at the origin of the parent node’s coordinate system.
         *
         *  @return The Origin for this instance.
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    btVector3 getOrigin() const;

    /**
         *  @author James Folk, 16-02-10 21:02:56
         *
         *  @brief <#Description#>
         *
         *  @param origin <#origin description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setOrigin(const btVector3& origin);

    /**
         *  @author James Folk, 16-02-10 21:02:02
         *
         *  @brief <#Description#>
         *
         *  @param origin <#origin description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setOrigin(const btVector2& origin);

    /**
         *  @author James Folk, 16-02-10 21:02:05
         *
         *  @brief The four-component rotation vector specifies the direction of the rotation axis in the first three components and the angle of rotation (in radians) in the fourth. The default rotation is the zero vector, specifying no rotation. Rotation is applied relative to the node’s pivot property.
         
         The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
         *
         *  @return the Rotation for this instance.
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    btQuaternion getRotation() const;

    /**
         *  @author James Folk, 16-02-10 21:02:22
         *
         *  @brief <#Description#>
         *
         *  @param rotation <#rotation description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setRotation(const btQuaternion& rotation);

    /**
         *  @author James Folk, 16-02-10 21:02:26
         *
         *  @brief Roll is the rotation about the node’s z-axis, yaw is the rotation about the node’s y-axis, and pitch is the rotation about the node’s x-axis. Rotation is applied relative to the node’s pivot property.
         *
         *  @return The Euler Angles for this instance.
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    btVector3 getEulerAngles() const;

    /**
         *  @author James Folk, 16-02-10 21:02:44
         *
         *  @brief <#Description#>
         *
         *  @param angles <#angles description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setEulerAngles(const btVector3& angles);

    /**
         *  @author James Folk, 16-02-10 21:02:47
         *
         *  @brief The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
         *
         *  @return The Orientation for this instance.
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const btQuaternion& getOrientation() const;

    /**
         *  @author James Folk, 16-02-10 21:02:04
         *
         *  @brief <#Description#>
         *
         *  @param orientation <#orientation description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setOrientation(const btQuaternion& orientation);

    /**
         *  @author James Folk, 16-02-10 21:02:08
         *
         *  @brief Each component of the scale vector multiplies the corresponding dimension of the node’s geometry. The default scale is 1.0 in all three dimensions. For example, applying a scale of (2.0, 0.5, 2.0) to a node containing a cube geometry reduces its height and increases its width and depth. Scaling is applied relative to the node’s pivot property.
         *
         *  @return The scale for this instance.
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const btVector3& getScale() const;
    /**
         *  @author James Folk, 16-02-10 21:02:21
         *
         *  @brief <#Description#>
         *
         *  @param scale <#scale description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setScale(const btVector3& scale);

    /**
         *  @author James Folk, 16-02-10 21:02:30
         *
         *  @brief <#Description#>
         *
         *  @param scale <#scale description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setScale(const f32 scale);

    /**
         *  @author James Folk, 16-02-10 21:02:33
         *
         *  @brief A node’s pivot is the transformation between its coordinate space and that used by its position, rotation, and scale properties. The default pivot is SCNMatrix4Identity, specifying that the node’s position locates the origin of its coordinate system, its rotation is about an axis through its center, and its scale is also relative to that center point.
         
         Changing the pivot transform alters these behaviors in many useful ways. You can:
         
         Offset the node’s contents relative to its position. For example, by setting the pivot to a translation transform you can position a node containing a sphere geometry relative to where the sphere would rest on a floor instead of relative to its center.
         
         Move the node’s axis of rotation. For example, with a translation transform you can cause a node to revolve around a faraway point instead of rotating around its center, and with a rotation transform you can tilt the axis of rotation.
         
         Adjust the center point and direction for scaling the node. For example, with a translation transform you can cause a node to grow or shrink relative to a corner instead of to its center.
         *
         *  @return The Pivot for this instance.
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    btTransform& getPivot() const;

    /**
         *  @author James Folk, 16-02-10 21:02:55
         *
         *  @brief <#Description#>
         *
         *  @param pivot <#pivot description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setPivot(const btTransform& pivot);

    /**
     <#Description#>

     @param sb <#sb description#>
     */
    void setSteeringBehaviorMachine(SteeringBehaviorMachine *sb);
    
    
    /**
     <#Description#>
     */
    void removeSteeringBehaviorMachine();
    
    
    /**
     <#Description#>

     @return <#return value description#>
     */
    SteeringBehaviorMachine *getSteeringBehaviorMachine();
    
    
    /**
     <#Description#>

     @return <#return value description#>
     */
    const SteeringBehaviorMachine *getSteeringBehaviorMachine()const;
    
    /**
         *  @author James Folk, 16-02-10 21:02:01
         *
         *  @brief <#Description#>
         *
         *  @param emitter <#emitter description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    s32 addParticleEmitter(ParticleEmitter * emitter);

    /**
         *  @author James Folk, 16-02-10 21:02:05
         *
         *  @brief <#Description#>
         *
         *  @param emitter <#emitter description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool removeParticleEmitter(ParticleEmitter * emitter);

    /**
         *  @author James Folk, 16-02-10 21:02:09
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeAllParticleEmitters();

    /**
         *  @author James Folk, 16-02-10 21:02:14
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    s32 numberOfParticleEmitters() const;

    /**
         *  @author James Folk, 16-02-10 21:02:19
         *
         *  @brief <#Description#>
         *
         *  @param particleEmitters <#particleEmitters description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void getParticleEmitters(std::vector<ParticleEmitter*> & particleEmitters) const;

    /**
         *  @author James Folk, 16-02-10 21:02:22
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    s32 getParticleEmitterIndex(ParticleEmitter * object) const;

    /**
         *  @author James Folk, 16-02-10 21:02:27
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    ParticleEmitter* getParticleEmitter(const u32 index);

    /**
         *  @author James Folk, 16-02-10 21:02:30
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const ParticleEmitter* getParticleEmitter(const u32 index) const;

    /**
         *  @author James Folk, 16-02-10 21:02:34
         *
         *  @brief <#Description#>
         *
         *  @param body <#body description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setPhysicsBody(PhysicsBody * body);

    /**
         *  @author James Folk, 16-02-10 21:02:38
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removePhysicsBody();

    /**
         *  @author James Folk, 16-02-10 21:02:43
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    PhysicsBody* getPhysicsBody();

    /**
         *  @author James Folk, 16-02-10 21:02:51
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const PhysicsBody* getPhysicsBody() const;

    /**
         *  @author James Folk, 16-02-10 21:02:56
         *
         *  @brief <#Description#>
         *
         *  @param body <#body description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setLight(Light * body);

    /**
         *  @author James Folk, 16-02-10 21:02:03
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeLight();

    /**
         *  @author James Folk, 16-02-10 21:02:08
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    Light* getLight();

    /**
         *  @author James Folk, 16-02-10 21:02:13
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const Light* getLight() const;

    /**
         *  @author James Folk, 16-02-10 21:02:17
         *
         *  @brief <#Description#>
         *
         *  @param body <#body description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setCamera(Camera * body);

    /**
         *  @author James Folk, 16-02-10 21:02:21
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeCamera();

    /**
         *  @author James Folk, 16-02-10 21:02:26
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    Camera* getCamera();

    /**
         *  @author James Folk, 16-02-10 21:02:29
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const Camera* getCamera() const;

    /**
         *  @author James Folk, 16-02-10 21:02:33
         *
         *  @brief <#Description#>
         *
         *  @param body <#body description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setGeometry(Geometry * body);

    /**
         *  @author James Folk, 16-02-10 21:02:36
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeGeometry();

    /**
         *  @author James Folk, 16-02-10 21:02:41
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    Geometry* getGeometry();

    /**
         *  @author James Folk, 16-02-10 21:02:44
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const Geometry* getGeometry() const;

    /**
         *  @author James Folk, 16-02-10 21:02:48
         *
         *  @brief <#Description#>
         *
         *  @param body <#body description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setPhysicsField(PhysicsField * body);

    /**
         *  @author James Folk, 16-02-10 21:02:52
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removePhysicsField();

    /**
         *  @author James Folk, 16-02-10 21:02:55
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    PhysicsField* getPhysicsField();

    /**
         *  @author James Folk, 16-02-10 21:02:00
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const PhysicsField* getPhysicsField() const;

    /**
         *  @author James Folk, 16-02-10 21:02:04
         *
         *  @brief <#Description#>
         *
         *  @param sound <#sound description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    s32 addSound(Sound * sound);

    /**
         *  @author James Folk, 16-02-10 21:02:09
         *
         *  @brief <#Description#>
         *
         *  @param sound <#sound description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool removeSound(Sound * sound);

    /**
         *  @author James Folk, 16-02-10 21:02:13
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeAllSounds();

    /**
         *  @author James Folk, 16-02-10 21:02:17
         *
         *  @brief <#Description#>
         *
         *  @param sounds <#sounds description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void getSounds(std::vector<Sound*> & sounds) const;

    /**
         *  @author James Folk, 16-02-10 21:02:21
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    s32 getSoundIndex(Sound * object) const;

    /**
         *  @author James Folk, 16-02-10 21:02:25
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    Sound* getSound(const u32 index);

    /**
         *  @author James Folk, 16-02-10 21:02:30
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const Sound* getSound(const u32 index) const;

    /**
         *  @author James Folk, 16-02-10 21:02:36
         *
         *  @brief <#Description#>
         *
         *  @param opacity <#opacity description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setOpacity(f32 opacity);

    /**
         *  @author James Folk, 16-02-10 21:02:54
         *
         *  @brief <#Description#>
         *
         *  @param transfrom <#transfrom description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void transformVertices(const btTransform& transfrom);

    /**
         *  @author James Folk, 16-02-10 21:02:57
         *
         *  @brief <#Description#>
         *
         *  @param transform <#transform description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void transformVertexColors(const btTransform& transform);

    /**
         *  @author James Folk, 16-02-10 21:02:03
         *
         *  @brief <#Description#>
         *
         *  @param transform <#transform description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void transformTextureCoordinates(const btTransform& transform);

    /**
         *  @author James Folk, 16-02-10 21:02:10
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    f32 getOpacity() const;

    /**
         *  @author James Folk, 16-02-10 21:02:13
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool hasOpacity() const;

    /**
         *  @author James Folk, 16-02-10 21:02:17
         *
         *  @brief <#Description#>
         *
         *  @param camera <#camera description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void hide(Camera* camera = NULL);

    /**
         *  @author James Folk, 16-02-10 21:02:11
         *
         *  @brief <#Description#>
         *
         *  @param camera <#camera description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void show(Camera * camera);

    /**
         *  @author James Folk, 16-02-10 21:02:14
         *
         *  @brief <#Description#>
         *
         *  @param camera <#camera description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool isHidden(Camera * camera) const;

    /**
         *  @author James Folk, 16-02-10 21:02:17
         *
         *  @brief <#Description#>
         *
         *  @param node <#node description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setRenderCategory(Node * node);

    /**
         *  @author James Folk, 16-02-10 21:02:20
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    NodeStateMachine* getStateMachine();

    /**
         *  @author James Folk, 16-02-10 21:02:24
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const NodeStateMachine* getStateMachine() const;

    /**
         *  @author James Folk, 16-02-10 21:02:27
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeStateMachine();

    /**
         *  @author James Folk, 16-02-10 21:02:30
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool isTouched() const;

    /**
         *  @author James Folk, 16-02-10 21:02:34
         *
         *  @brief <#Description#>
         *
         *  @param enable <#enable description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void enableTouched(bool enable = true);

    /**
         *  @author James Folk, 16-02-10 21:02:39
         *
         *  @brief <#Description#>
         *
         *  @param from           <#from description#>
         *  @param to             <#to description#>
         *  @param rayContact     <#rayContact description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool rayTestClosest(const btVector3& from, const btVector3& to,
        PhysicsRayContact& rayContact,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;

    /**
         *  @author James Folk, 16-02-10 21:02:44
         *
         *  @brief <#Description#>
         *
         *  @param from           <#from description#>
         *  @param to             <#to description#>
         *  @param rayContacts    <#rayContacts description#>
         *  @param numContacts    <#numContacts description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool rayTestAll(const btVector3& from, const btVector3& to,
        btAlignedObjectArray<PhysicsRayContact*>& rayContacts,
        s32& numContacts,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;

    /**
         *  @author James Folk, 16-02-10 21:02:49
         *
         *  @brief <#Description#>
         *
         *  @param screenPosition <#screenPosition description#>
         *  @param rayContact     <#rayContact description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool rayTestClosest(const btVector2& screenPosition,
        PhysicsRayContact& rayContact,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;

    /**
         *  @author James Folk, 16-02-10 21:02:53
         *
         *  @brief <#Description#>
         *
         *  @param screenPosition <#screenPosition description#>
         *  @param rayContacts    <#rayContacts description#>
         *  @param numContacts    <#numContacts description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool rayTestAll(const btVector2& screenPosition,
        btAlignedObjectArray<PhysicsRayContact*>& rayContacts,
        s32& numContacts,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;
    /**
         *  @author James Folk, 16-02-10 21:02:57
         *
         *  @brief <#Description#>
         *
         *  @param action                 <#action description#>
         *  @param callCompletionFunction <#callCompletionFunction description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual void runAction(Action * action, bool callCompletionFunction = false);

    /**
         *  @author James Folk, 16-02-10 21:02:02
         *
         *  @brief <#Description#>
         *
         *  @param action                 <#action description#>
         *  @param key                    <#key description#>
         *  @param callCompletionFunction <#callCompletionFunction description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual void runAction(Action * action, const char* key, bool callCompletionFunction = false);

    /**
         *  @author James Folk, 16-02-10 21:02:06
         *
         *  @brief <#Description#>
         *
         *  @param key <#key description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual bool removeAction(const char* key);

    /**
         *  @author James Folk, 16-02-10 21:02:08
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual void removeAllActions();

    /**
         *  @author James Folk, 16-02-10 21:02:12
         *
         *  @brief <#Description#>
         *
         *  @param aabbMin <#aabbMin description#>
         *  @param aabbMax <#aabbMax description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    virtual void getAabb(btVector3 & aabbMin, btVector3 & aabbMax) const;

protected:
    /**
         *  <#Description#>
         */
    //        void applyPhysicsShape();

public:
    /**
         *  @author James Folk, 16-02-10 21:02:18
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    Node* getParentNode();

    /**
         *  @author James Folk, 16-02-10 21:02:22
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const Node* getParentNode() const;

    /**
         *  @author James Folk, 16-02-10 21:02:26
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool hasParentNode() const;

    /**
         *  @author James Folk, 16-02-10 21:02:30
         *
         *  @brief <#Description#>
         *
         *  @param parent <#parent description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void setParentNode(Node * parent);

    /**
         *  @author James Folk, 16-02-10 21:02:40
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeParentNode();

    /**
         *  @author James Folk, 16-02-10 21:02:44
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool removeFromParentNode();

    /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @param name <#name description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    Node* findChildNode(const char* name);

    /**
         *  @author James Folk, 16-02-10 21:02:54
         *
         *  @brief <#Description#>
         *
         *  @param name <#name description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const Node* findChildNode(const char* name) const;

    /**
         *  @author James Folk, 16-02-10 21:02:58
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    Node* getChildNode(const u32 index);

    /**
         *  @author James Folk, 16-02-10 21:02:04
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    const Node* getChildNode(const u32 index) const;

    /**
         *  @author James Folk, 16-02-10 21:02:08
         *
         *  @brief <#Description#>
         *
         *  @param children <#children description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void getChildrenNodes(std::vector<Node*> & children) const;

    /**
         *  @author James Folk, 16-02-10 21:02:14
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    s32 getChildNodeIndex(Node * object) const;

    /**
         *  @author James Folk, 16-02-10 21:02:18
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool hasChildNode(Node * object) const;

    /**
         *  @author James Folk, 16-02-10 21:02:22
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    bool hasChildrenNodes() const;

    /**
         *  @author James Folk, 16-02-10 21:02:29
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void addChildNode(Node * object);

    /**
         *  @author James Folk, 16-02-10 21:02:34
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeChildNode(const u32 index);

    /**
         *  @author James Folk, 16-02-10 21:02:38
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeChildNode(Node * object);

    /**
         *  @author James Folk, 16-02-10 21:02:43
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void removeChildrenNodes();

    /**
         *  @author James Folk, 16-02-10 21:02:47
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    u32 numberOfChildrenNodes() const;

    /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @param oldChild <#oldChild description#>
         *  @param newChild <#newChild description#>
         *
         *  @section ex1 Lua example
         *  @snippet Node.lua Node_calculateSerializeBufferSize_
         */
    void replaceChildNode(Node * oldChild, Node * newChild);

    void setCurrentScene(Node *node);
protected:
    void updateActions();
    virtual bool canDelete() const;

    friend class SceneRenderer;
    void update(f32 timeStep);
    //        void render(Camera *camera);
    void applyPhysicsBodyTransform(const btTransform& transform);

    void setGeometryIndex(s64 index);
    size_t getGeometryIndex() const;
    void clearGeometryIndex();
    
    Scene *getCurrentScene();
    const Scene *getCurrentScene()const;
    void setCurrentScene(Scene *scene);
    
    void removeCurrentScene();

private:
    std::vector<PhysicsConstraint*> m_PhysicsConstraintList;
    std::vector<ParticleEmitter*> m_ParticleEmitterList;
    std::vector<Sound*> m_SoundList;
    PhysicsBody* m_PhysicsBody;
    Light* m_Light;
    Camera* m_Camera;
    Geometry* m_Geometry;
    PhysicsField* m_PhysicsField;

    f32 m_Opacity;
    njliBitCategories m_RenderCategory;
    NodeStateMachine* m_NodeStateMachine;

    std::vector<Node*> m_Children;
    Node* m_pParent;

    size_t m_GeometryIndex;
    bool m_isTouchedByRay;

//    bool m_ApplyPhysicsShape;

    //        Thread *m_ActionThread;

    static void updateActions(void* _ptr);

    btTransform* m_Transform;
    btTransform* m_ColorTransform;
    btQuaternion* m_Orientation;
    btVector3* m_Scale;
    btTransform* m_Pivot;
    
    SteeringBehaviorMachine *m_SteeringBehaviorMachine;
    
    Scene *m_CurrentScene;
};
}

#endif /* defined(__JLIGameEngineTest__Node__) */
