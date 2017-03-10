
----
-- @file PhysicsConstraintHinge


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:13
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function PhysicsConstraintHinge:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getType()
end

---- Brief description.
-- <#Description#>
-- @param nodeA <#nodeA description#>
-- @param nodeB <#nodeB description#>
-- @param pivotInA <#pivotInA description#>
-- @param pivotInB <#pivotInB description#>
-- @param axisInA <#axisInA description#>
-- @param axisInB <#axisInB description#>
-- @param useReferenceFrameA <#useReferenceFrameA description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setNodes(nodeA, nodeB, pivotInA, pivotInB, axisInA, axisInB, useReferenceFrameA)
end

---- Brief description.
-- <#Description#>
-- @param nodeA <#nodeA description#>
-- @param pivotInA <#pivotInA description#>
-- @param axisInA <#axisInA description#>
-- @param useReferenceFrameA <#useReferenceFrameA description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setNodes(nodeA, pivotInA, axisInA, useReferenceFrameA)
end

---- Brief description.
-- <#Description#>
-- @param nodeA <#nodeA description#>
-- @param nodeB <#nodeB description#>
-- @param rbAFrame <#rbAFrame description#>
-- @param rbBFrame <#rbBFrame description#>
-- @param useReferenceFrameA <#useReferenceFrameA description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setNodes(nodeA, nodeB, rbAFrame, rbBFrame, useReferenceFrameA)
end

---- Brief description.
-- <#Description#>
-- @param nodeA <#nodeA description#>
-- @param rbAFrame <#rbAFrame description#>
-- @param useReferenceFrameA <#useReferenceFrameA description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setNodes(nodeA, rbAFrame, useReferenceFrameA)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getFrameOffsetA()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getFrameOffsetB()
end

---- Brief description.
-- <#Description#>
-- @param frameA <#frameA description#>
-- @param frameB <#frameB description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setFrames(frameA, frameB)
end

---- Brief description.
-- <#Description#>
-- @param angularOnly <#angularOnly description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setAngularOnly(angularOnly)
end

---- Brief description.
-- <#Description#>
-- @param enableMotor <
-- @param targetVelocity <#targetVelocity description#>
-- @param maxMotorImpulse <#maxMotorImpulse description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:enableAngularMotor(enableMotor, targetVelocity, maxMotorImpulse)
end

---- Brief description.
-- <#Description#>
-- @param enableMotor <
-- @return <#return value description#>
function PhysicsConstraintHinge:enableMotor(enableMotor)
end

---- Brief description.
-- <#Description#>
-- @param maxMotorImpulse <#maxMotorImpulse description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setMaxMotorImpulse(maxMotorImpulse)
end

---- Brief description.
-- <#Description#>
-- @param qAinB <#qAinB description#>
-- @param dt <#dt description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setMotorTarget(qAinB, dt)
end

---- Brief description.
-- <#Description#>
-- @param targetAngle <#targetAngle description#>
-- @param dt <#dt description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setMotorTarget(targetAngle, dt)
end

---- Brief description.
-- <#Description#>
-- @param low <#low description#>
-- @param high <#high description#>
-- @param _softness <#.9f description#>
-- @param _biasFactor <#.3f description#>
-- @param _relaxationFactor <#.0f description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setLimit(low, high, _softness, _biasFactor, _relaxationFactor)
end

---- Brief description.
-- <#Description#>
-- @param axisInA <#axisInA description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:setAxis(axisInA)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getLowerLimit()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getUpperLimit()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getHingeAngle()
end

---- Brief description.
-- <#Description#>
-- @param transA <#transA description#>
-- @param transB <#transB description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getHingeAngle(transA, transB)
end

---- Brief description.
-- <#Description#>
-- @param transA <#transA description#>
-- @param transB <#transB description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:testLimit(transA, transB)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getAFrame()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getBFrame()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getAFrame()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getBFrame()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getSolveLimit()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getLimitSign()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getAngularOnly()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getEnableAngularMotor()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getMotorTargetVelocity()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintHinge:getMaxMotorImpulse()
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintHinge.type()
end

