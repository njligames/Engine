
----
-- @file PhysicsConstraintConeTwist


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:15
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function PhysicsConstraintConeTwist:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getType()
end

---- Brief description.
-- <#Description#>
-- @param nodeA <#nodeA description#>
-- @param rbAFrame <#rbAFrame description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setNodes(nodeA, rbAFrame)
end

---- Brief description.
-- <#Description#>
-- @param nodeA <#nodeA description#>
-- @param nodeB <#nodeB description#>
-- @param rbAFrame <#rbAFrame description#>
-- @param rbBFrame <#rbBFrame description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setNodes(nodeA, nodeB, rbAFrame, rbBFrame)
end

---- Brief description.
-- <#Description#>
-- @param angularOnly <#angularOnly description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setAngularOnly(angularOnly)
end

---- Brief description.
-- <#Description#>
-- @param limitIndex <#limitIndex description#>
-- @param limitValue <#limitValue description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setLimit(limitIndex, limitValue)
end

---- Brief description.
-- <#Description#>
-- @param _swingSpan1 <#_swingSpan1 description#>
-- @param _swingSpan2 <#_swingSpan2 description#>
-- @param _twistSpan <#_twistSpan description#>
-- @param _softness <#.f description#>
-- @param _biasFactor <#.3f description#>
-- @param _relaxationFactor <#.0f description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness, _biasFactor, _relaxationFactor)
end

---- Brief description.
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getAFrame()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getBFrame()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getSolveTwistLimit()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getSolveSwingLimit()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getTwistLimitSign()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getSwingSpan1()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getSwingSpan2()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getTwistSpan()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getTwistAngle()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:isPastSwingLimit()
end

---- Brief description.
-- <#Description#>
-- @param damping <#damping description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setDamping(damping)
end

---- Brief description.
-- <#Description#>
-- @param b <#b description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:enableMotor(b)
end

---- Brief description.
-- <#Description#>
-- @param maxMotorImpulse <#maxMotorImpulse description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setMaxMotorImpulse(maxMotorImpulse)
end

---- Brief description.
-- <#Description#>
-- @param maxMotorImpulse <#maxMotorImpulse description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setMaxMotorImpulseNormalized(maxMotorImpulse)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getFixThresh()
end

---- Brief description.
-- <#Description#>
-- @param fixThresh <#fixThresh description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setFixThresh(fixThresh)
end

---- Brief description.
-- <#Description#>
-- @param q <#q description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setMotorTarget(q)
end

---- Brief description.
-- <#Description#>
-- @param q <#q description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setMotorTargetInConstraintSpace(q)
end

---- Brief description.
-- <#Description#>
-- @param fAngleInRadians <#fAngleInRadians description#>
-- @param fLength <#fLength description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getPointForAngle(fAngleInRadians, fLength)
end

---- Brief description.
-- <#Description#>
-- @param frameA <#frameA description#>
-- @param frameB <#frameB description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:setFrames(frameA, frameB)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getFrameOffsetA()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsConstraintConeTwist:getFrameOffsetB()
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsConstraintConeTwist.type()
end

