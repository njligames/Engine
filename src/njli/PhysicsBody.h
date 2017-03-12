//
//  PhysicsBody.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__AbstractPhysicsBody__
#define __JLIGameEngineTest__AbstractPhysicsBody__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "JLIFactoryTypes.h"
#include "btTransform.h"
#include "lua.hpp"

class btManifoldPoint;
struct btDispatcherInfo;
class btCollisionObject;
class btVector3;
class btTransform;

namespace njli {
class PhysicsWorld;
class Node;
class PhysicsShape;
class PhysicsConstraint;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
PhysicsBody : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class PhysicsWorld;
    friend class Node;
    friend class PhysicsShapeBox2D;
    friend class PhysicsShapeBox;
    friend class PhysicsConstraintPointToPoint;
    friend class PhysicsConstraintHinge;
    friend class PhysicsConstraintConeTwist;
    friend class PhysicsConstraintFixed;
    friend class PhysicsConstraintGeneric6Dof;
    friend class PhysicsConstraintGeneric6DofSpring;
    friend class PhysicsConstraintSlider;

    friend class PhysicsConstraint;

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    PhysicsBody();
    PhysicsBody(const AbstractBuilder&);
    PhysicsBody(const PhysicsBody&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsBody();
    PhysicsBody& operator=(const PhysicsBody&);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const = 0;

    /**
         *  @author James Folk, 16-02-11 15:02:51
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const = 0;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const = 0;

    /**
         *  <#Description#>
         *
         *  @param type <#type description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsBody* create(u32 type);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(PhysicsBody * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(PhysicsBody & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for PhysicsBody
    /**
         *  <#Description#>
         *
         *  @param body               <#body description#>
         *  @param btManifoldPoint&pt <#btManifoldPoint&pt description#>
         */
    void handleCollide(PhysicsBody * body, const btManifoldPoint& pt);
    /**
         *  <#Description#>
         *
         *  @param body         <#body description#>
         *  @param dispatchInfo <#dispatchInfo description#>
         */
    void handleCollisionNear(PhysicsBody * body, const btDispatcherInfo& dispatchInfo);

    /**
         *  <#Description#>
         *
         *  @param shape <#shape description#>
         */
    virtual void setPhysicsShape(PhysicsShape * shape);
    /**
         *  <#Description#>
         */
    void removePhysicsShape();
    PhysicsShape* getPhysicsShape();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const PhysicsShape* getPhysicsShape() const;

    /**
         *  <#Description#>
         *
         *  @param transform <#transform description#>
         */
    virtual void setWorldTransform(const btTransform& transform) = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual btTransform getWorldTransform() const;

    /**
         *  <#Description#>
         *
         *  @param friction <#friction description#>
         */
    virtual void setFriction(f32 friction);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual f32 getFriction() const;

    /**
         *  <#Description#>
         *
         *  @param friction <#friction description#>
         */
    virtual void setAngularFriction(f32 friction);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual f32 getAngularFriction() const;

    /**
         *  <#Description#>
         *
         *  @param restitution <#restitution description#>
         */
    virtual void setRestitution(f32 restitution);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual f32 getRestitution() const;

    /**
         *  <#Description#>
         *
         *  @param type <#type description#>
         */
    virtual void setPhysicsType(njliPhysicsType type);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual njliPhysicsType getPhysicsType() const;

    /**
         *  <#Description#>
         *
         *  @param categoryBitMask <#categoryBitMask description#>
         */
    virtual void setCollisionGroup(njliBitCategories categoryBitMask);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual njliBitCategories getCollisionGroup() const;

    /**
         *  <#Description#>
         *
         *  @param categoryBitMask <#categoryBitMask description#>
         */
    virtual void setCollisionMask(njliBitCategories categoryBitMask);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual njliBitCategories getCollisionMask() const;

    /**
         *  <#Description#>
         */
    virtual void setStaticPhysics();
    /**
         *  <#Description#>
         */
    virtual void setKinematicPhysics();
    /**
         *  <#Description#>
         */
    virtual void setDynamicPhysics();
    /**
         *  <#Description#>
         *
         *  @param enable <#enable description#>
         */
    virtual void enableContactResponse(bool enable = true);
    /**
         *  <#Description#>
         *
         *  @param enable <#enable description#>
         */
    virtual void enableHandleCollideCallback(bool enable = true);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isStaticPhysics() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isKinematicPhysics() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isDynamicPhysics() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual bool isResting() const;
    /**
         *  <#Description#>
         *
         *  @param enable <#enable description#>
         */
    virtual void enableResting(bool enable = true);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const btVector3& getVelocity() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const btVector3& getAngularVelocity() const = 0;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual bool isInWorld() const = 0;
    
    virtual void setMass(f32 mass) = 0;
    virtual f32 getMass()const = 0;

protected:
    virtual const btCollisionObject* getCollisionObject() const = 0;
    virtual btCollisionObject* getCollisionObject() = 0;
    virtual void setCollisionObject(const btCollisionObject& obj, PhysicsShape* shape) = 0;

    virtual bool setTransform(const btTransform& transform = btTransform::getIdentity()) = 0;
    virtual bool removePhysicsBody() = 0;
    //        virtual void enablePropertyChange(bool enable = true);
    //        virtual bool isPropertyChanged()const;

    /**
         *  <#Description#>
         *
         *  @param constraint <#constraint description#>
         *
         *  @return <#return value description#>
         */
    s32 setPhysicsConstraint(PhysicsConstraint * constraint);

    /**
         *  <#Description#>
         *
         *  @param constraint <#constraint description#>
         *
         *  @return <#return value description#>
         */
    bool removePhysicsConstraint(PhysicsConstraint * constraint);

    /**
         *  <#Description#>
         */
    void removeAllPhysicsConstraints();

public:
    /**
         *  <#Description#>
         *
         *  @param physicsConstraints <#physicsConstraints description#>
         */
    void getPhysicsConstraints(std::vector<PhysicsConstraint*> & physicsConstraints) const;
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    s32 getPhysicsConstraintIndex(PhysicsConstraint * object) const;
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    PhysicsConstraint* getPhysicsConstraint(const u32 index);
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    const PhysicsConstraint* getPhysicsConstraint(const u32 index) const;

    bool hasPhysicsConstraint() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node* getParent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Node* getParent() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    s32 getCollisionFlags() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    s32 getActivationState() const;

private:
    std::vector<PhysicsConstraint*> m_PhysicsConstraintList;
    //        PhysicsWorld *m_PhysicsWorld;

    PhysicsShape* m_PhysicsShape;
    njliBitCategories m_CategoryBitMask;
    njliBitCategories m_CollisionBitMask;

    bool m_RestingAllowed;
    bool m_IsResting;
    //        bool m_PropertyChanged;

    s32 m_CollisionFlags;
    s32 m_ActivationState;
};
}

#endif /* defined(__JLIGameEngineTest__AbstractPhysicsBody__) */
