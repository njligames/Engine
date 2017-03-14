//
//  PhysicsConstraint.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/15/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraint__
#define __JLIGameEngineTest__PhysicsConstraint__

#pragma mark Header

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "Log.h"
#include "lua.hpp"

#include "btTypedConstraint.h"

namespace njli {
class PhysicsConstraintBuilder;
class Node;
    class PhysicsBody;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
PhysicsConstraint : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class PhysicsWorld;

protected:
    PhysicsConstraint();
    PhysicsConstraint(const AbstractBuilder&);
    PhysicsConstraint(const PhysicsConstraint&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsConstraint();
    PhysicsConstraint& operator=(const PhysicsConstraint&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:02
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    operator std::string() const;

    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsConstraint** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(PhysicsConstraint * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsConstraint* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsConstraint* create(const PhysicsConstraintBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsConstraint* clone(const PhysicsConstraint& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsConstraint* copy(const PhysicsConstraint& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(PhysicsConstraint * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(PhysicsConstraint & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for PhysicsConstraint
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node* getNodeA();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Node* getNodeA() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node* getNodeB();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Node* getNodeB() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getBreakingImpulseThreshold() const;
    /**
         *  <#Description#>
         *
         *  @param impulse <#impulse description#>
         */
    void setBreakingImpulseThreshold(f32 impulse);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isConstraintEnabled() const;
    /**
         *  <#Description#>
         *
         *  @param enable <#enable description#>
         */
    void enableConstraint(bool enable = true);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getJointAppliedForceA() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getJointAppliedTorqueA() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getJointAppliedForceB() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getJointAppliedTorqueB() const;
    
    
    /**
     <#Description#>

     @return <#return value description#>
     */
    PhysicsBody *getParent();
    
    /**
     <#Description#>

     @return <#return value description#>
     */
    const PhysicsBody *getParent()const;

protected:
    virtual btTypedConstraint* getConstraint() = 0;
    virtual const btTypedConstraint* getConstraint() const = 0;

    virtual void removeConstraint();
//    virtual void setNodes(Node *nodeA, Node *nodeB=NULL);

private:
};
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraint__) */
