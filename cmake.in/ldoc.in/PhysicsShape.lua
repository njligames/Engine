
----
-- @file PhysicsShape


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShape:calculateSerializeBufferSize()
end

---- Brief description.
-- <#Description#>
-- @param btSerializer <#btSerializer description#>
-- @return <#return value description#>
function PhysicsShape:serialize(btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShape:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShape:getType()
end

---- Brief description.
-- <#Description#>
-- @param mass <#mass description#>
-- @param motionState <#motionState description#>
-- @param localInertia <#0 description#>
-- @return <#return value description#>
function PhysicsShape:createRigidBodyWithShape(mass, motionState, localInertia)
end

---- Brief description.
-- <#Description#>
-- @param mass <#mass description#>
-- @return <#return value description#>
function PhysicsShape:calculateLocalInertia(mass)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShape:getNumVertices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShape:getNumEdges()
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param pa <#pa description#>
-- @param pb <#pb description#>
-- @return <#return value description#>
function PhysicsShape:getEdge(i, pa, pb)
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param vtx <#vtx description#>
-- @return <#return value description#>
function PhysicsShape:getVertex(i, vtx)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShape:getNumPlanes()
end

---- Brief description.
-- <#Description#>
-- @param planeNormal <#planeNormal description#>
-- @param planeSupport <#planeSupport description#>
-- @param i <#i description#>
-- @return <#return value description#>
function PhysicsShape:getPlane(planeNormal, planeSupport, i)
end

---- Brief description.
-- <#Description#>
-- @param pt <#pt description#>
-- @param tolerance <#tolerance description#>
-- @return <#return value description#>
function PhysicsShape:isInside(pt, tolerance)
end

---- Brief description.
-- <#Description#>
-- @param scaling <#scaling description#>
-- @return <#return value description#>
function PhysicsShape:setLocalScaling(scaling)
end

---- Brief description.
-- <#Description#>
-- @param t <#t description#>
-- @param aabbMin <#aabbMin description#>
-- @param aabbMax <#aabbMax description#>
-- @return <#return value description#>
function PhysicsShape:getAabb(t, aabbMin, aabbMax)
end

---- Brief description.
-- <#Description#>
-- @param type <
-- @return <#return value description#>
function NJLI.PhysicsShape.create(type)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShape.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsShape.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsShape.type()
end

