
----
-- @file PhysicsBody


---- Brief description.
-- @return <#return value description#>
function PhysicsBody:PhysicsBody()
end

---- Brief description.
-- @return <#return value description#>
function PhysicsBody:PhysicsBody()
end

---- Brief description.
-- @return <#return value description#>
function PhysicsBody:PhysicsBody()
end

---- Brief description.
-- @return <#return value description#>
function PhysicsBody:BT_DECLARE_ALIGNED_ALLOCATOR()
end

---- Brief description.
-- @return <#return value description#>
function PhysicsBody:operator=()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:51
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function PhysicsBody:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getType()
end

---- Brief description.
-- <#Description#>
-- @param body <#body description#>
-- @param btManifoldPoint&pt <#btManifoldPoint&pt description#>
-- @return <#return value description#>
function PhysicsBody:handleCollide(body, btManifoldPoint&pt)
end

---- Brief description.
-- <#Description#>
-- @param body <#body description#>
-- @param dispatchInfo <#dispatchInfo description#>
-- @return <#return value description#>
function PhysicsBody:handleCollisionNear(body, dispatchInfo)
end

---- Brief description.
-- <#Description#>
-- @param shape <#shape description#>
-- @return <#return value description#>
function PhysicsBody:addPhysicsShape(shape)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:removePhysicsShape()
end

---- Brief description.
-- @return <#return value description#>
function PhysicsBody:getPhysicsShape()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getPhysicsShape()
end

---- Brief description.
-- <#Description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function PhysicsBody:setWorldTransform(transform)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getWorldTransform()
end

---- Brief description.
-- <#Description#>
-- @param friction <#friction description#>
-- @return <#return value description#>
function PhysicsBody:setFriction(friction)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getFriction()
end

---- Brief description.
-- <#Description#>
-- @param friction <#friction description#>
-- @return <#return value description#>
function PhysicsBody:setAngularFriction(friction)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getAngularFriction()
end

---- Brief description.
-- <#Description#>
-- @param restitution <#restitution description#>
-- @return <#return value description#>
function PhysicsBody:setRestitution(restitution)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getRestitution()
end

---- Brief description.
-- <#Description#>
-- @param type <
-- @return <#return value description#>
function PhysicsBody:setPhysicsType(type)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getPhysicsType()
end

---- Brief description.
-- <#Description#>
-- @param categoryBitMask <#categoryBitMask description#>
-- @return <#return value description#>
function PhysicsBody:setCollisionGroup(categoryBitMask)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getCollisionGroup()
end

---- Brief description.
-- <#Description#>
-- @param categoryBitMask <#categoryBitMask description#>
-- @return <#return value description#>
function PhysicsBody:setCollisionMask(categoryBitMask)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getCollisionMask()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:setStaticPhysics()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:setKinematicPhysics()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:setDynamicPhysics()
end

---- Brief description.
-- <#Description#>
-- @param enable <#enable description#>
-- @return <#return value description#>
function PhysicsBody:enableContactResponse(enable)
end

---- Brief description.
-- <#Description#>
-- @param enable <#enable description#>
-- @return <#return value description#>
function PhysicsBody:enableHandleCollideCallback(enable)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:isStaticPhysics()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:isKinematicPhysics()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:isDynamicPhysics()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:isResting()
end

---- Brief description.
-- <#Description#>
-- @param enable <#enable description#>
-- @return <#return value description#>
function PhysicsBody:enableResting(enable)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getVelocity()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getAngularVelocity()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:isInWorld()
end

---- Brief description.
-- <#Description#>
-- @param physicsConstraints <#physicsConstraints description#>
-- @return <#return value description#>
function PhysicsBody:getPhysicsConstraints(physicsConstraints)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function PhysicsBody:getPhysicsConstraintIndex(object)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function PhysicsBody:getPhysicsConstraint(index)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function PhysicsBody:getPhysicsConstraint(index)
end

---- Brief description.
-- @return <#return value description#>
function PhysicsBody:hasPhysicsConstraint()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getParent()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getParent()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getCollisionFlags()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsBody:getActivationState()
end

---- Brief description.
-- <#Description#>
-- @param type <
-- @return <#return value description#>
function NJLI.PhysicsBody.create(type)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsBody.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsBody.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsBody.type()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.PhysicsBody.getCollisionObject()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.PhysicsBody.getCollisionObject()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.PhysicsBody.setCollisionObject()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.PhysicsBody.addPhysicsBody()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.PhysicsBody.removePhysicsBody()
end

---- Brief description.
-- <#Description#>
-- !!TODO: !!TODO: scene->addActivePhysicsConstraint(constraint);
-- @param constraint <#constraint description#>
-- @return <#return value description#>
function NJLI.PhysicsBody.addPhysicsConstraint(constraint)
end

---- Brief description.
-- <#Description#>
-- !!TODO: scene->removeActivePhysicsConstraint(*iter);
-- @param constraint <#constraint description#>
-- @return <#return value description#>
function NJLI.PhysicsBody.removePhysicsConstraint(constraint)
end

---- Brief description.
-- <#Description#>
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsBody.removeAllPhysicsConstraints()
end

