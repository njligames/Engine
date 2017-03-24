
----
-- @file PhysicsConstraintGeneric6Dof


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:41
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function PhysicsConstraintGeneric6Dof:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getType()
end

---- Brief description.
-- <#Description#>
-- @param nodeA <#nodeA description#>
-- @param nodeB <#nodeB description#>
-- @param frameInA <#frameInA description#>
-- @param frameInB <#frameInB description#>
-- @param useLinearReferenceFrameA <#useLinearReferenceFrameA description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setNodes(nodeA, nodeB, frameInA, frameInB, useLinearReferenceFrameA)
end

---- Brief description.
-- <#Description#>
-- @param nodeB <#nodeB description#>
-- @param frameInB <#frameInB description#>
-- @param useLinearReferenceFrameB <#useLinearReferenceFrameB description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setNodes(nodeB, frameInB, useLinearReferenceFrameB)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:calculateTransforms()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getCalculatedTransformA()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getCalculatedTransformB()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getFrameOffsetA()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getFrameOffsetB()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getFrameOffsetA()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getFrameOffsetB()
end

---- Brief description.
-- <#Description#>
-- @param axis_index <#axis_index description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getAxis(axis_index)
end

---- Brief description.
-- <#Description#>
-- @param axis_index <#axis_index description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getAngle(axis_index)
end

---- Brief description.
-- <#Description#>
-- @param axis_index <#axis_index description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getRelativePivotPosition(axis_index)
end

---- Brief description.
-- <#Description#>
-- @param frameA <#frameA description#>
-- @param frameB <#frameB description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setFrames(frameA, frameB)
end

---- Brief description.
-- <#Description#>
-- @param axis_index <#axis_index description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:testAngularLimitMotor(axis_index)
end

---- Brief description.
-- <#Description#>
-- @param linearLower <#linearLower description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setLinearLowerLimit(linearLower)
end

---- Brief description.
-- <#Description#>
-- @param linearLower <#linearLower description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getLinearLowerLimit(linearLower)
end

---- Brief description.
-- <#Description#>
-- @param linearUpper <#linearUpper description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setLinearUpperLimit(linearUpper)
end

---- Brief description.
-- <#Description#>
-- @param linearUpper <#linearUpper description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getLinearUpperLimit(linearUpper)
end

---- Brief description.
-- <#Description#>
-- @param angularLower <#angularLower description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setAngularLowerLimit(angularLower)
end

---- Brief description.
-- <#Description#>
-- @param angularLower <#angularLower description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getAngularLowerLimit(angularLower)
end

---- Brief description.
-- <#Description#>
-- @param angularUpper <#angularUpper description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setAngularUpperLimit(angularUpper)
end

---- Brief description.
-- <#Description#>
-- @param angularUpper <#angularUpper description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getAngularUpperLimit(angularUpper)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getRotationalLimitMotor(index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getTranslationalLimitMotor()
end

---- Brief description.
-- <#Description#>
-- @param axis <#axis description#>
-- @param lo <#lo description#>
-- @param hi <#hi description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setLimit(axis, lo, hi)
end

---- Brief description.
-- <#Description#>
-- @param limitIndex <#limitIndex description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:isLimited(limitIndex)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:getUseFrameOffset()
end

---- Brief description.
-- <#Description#>
-- @param frameOffsetOnOff <#frameOffsetOnOff description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setUseFrameOffset(frameOffsetOnOff)
end

---- Brief description.
-- <#Description#>
-- @param axis1 <#axis1 description#>
-- @param axis2 <#axis2 description#>
-- @return <#return value description#>
function PhysicsConstraintGeneric6Dof:setAxis(axis1, axis2)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintGeneric6Dof.type()
end

