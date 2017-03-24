
----
-- @file PhysicsWorld


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsWorld:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:19
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function PhysicsWorld:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsWorld:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsWorld:getType()
end

---- Brief description.
-- <#Description#>
-- @param timeStep <#timeStep description#>
-- @return <#return value description#>
function PhysicsWorld:update(timeStep)
end

---- Brief description.
-- <#Description#>
-- @param camera <#camera description#>
-- @return <#return value description#>
function PhysicsWorld:render(camera)
end

---- Brief description.
-- <#Description#>
-- @param gravity <#gravity description#>
-- @return <#return value description#>
function PhysicsWorld:setGravity(gravity)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsWorld:getGravity()
end

---- Brief description.
-- <#Description#>
-- @param speed <#speed description#>
-- @return <#return value description#>
function PhysicsWorld:setSimulationSpeed(speed)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsWorld:getSimulationSpeed()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsWorld:getTimeStep()
end

---- Brief description.
-- <#Description#>
-- @param callback <
-- @return <#return value description#>
function PhysicsWorld:setPreTickCallback(callback)
end

---- Brief description.
-- <#Description#>
-- @param callback <
-- @return <#return value description#>
function PhysicsWorld:setPostTickCallback(callback)
end

---- Brief description.
-- <#Description#>
-- @param rayFromWorld <#rayFromWorld description#>
-- @param rayToWorld <#rayToWorld description#>
-- @param rayContact <#rayContact description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function PhysicsWorld:rayTestClosest(rayFromWorld, rayToWorld, rayContact, collisionGroup, collisionMask)
end

---- Brief description.
-- <#Description#>
-- @param rayFromWorld <#rayFromWorld description#>
-- @param rayToWorld <#rayToWorld description#>
-- @param rayContacts <#rayContacts description#>
-- @param numContacts <#numContacts description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function PhysicsWorld:rayTestAll(rayFromWorld, rayToWorld, rayContacts, numContacts, collisionGroup, collisionMask)
end

---- Brief description.
-- @return <#return value description#>
function PhysicsWorld:enablePause()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsWorld:isPaused()
end

---- Brief description.
-- <#Description#>
-- @param body <#body description#>
-- @return <#return value description#>
function PhysicsWorld:addRigidBody(body)
end

---- Brief description.
-- <#Description#>
-- @param body <#body description#>
-- @return <#return value description#>
function PhysicsWorld:removeRigidBody(body)
end

---- Brief description.
-- <#Description#>
-- @param constraint <#constraint description#>
-- @param disableCollisionsBetweenLinkedBodies <#disableCollisionsBetweenLinkedBodies description#>
-- @return <#return value description#>
function PhysicsWorld:addConstraint(constraint, disableCollisionsBetweenLinkedBodies)
end

---- Brief description.
-- <#Description#>
-- @param constraint <#constraint description#>
-- @return <#return value description#>
function PhysicsWorld:removeConstraint(constraint)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param physics <#physics description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.clone(physics)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param physicsWorld <#physicsWorld description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.destroy(physicsWorld)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsWorld.type()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.PhysicsWorld.ghostObjectCollisionTest()
end

