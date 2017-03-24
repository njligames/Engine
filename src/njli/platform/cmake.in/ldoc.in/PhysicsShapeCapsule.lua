
----
-- @file PhysicsShapeCapsule


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:calculateSerializeBufferSize()
end

---- Brief description.
-- <#Description#>
-- @param btSerializer <#btSerializer description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:serialize(btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getType()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getNumVertices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getNumEdges()
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param pa <#pa description#>
-- @param pb <#pb description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getEdge(i, pa, pb)
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param vtx <#vtx description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getVertex(i, vtx)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getNumPlanes()
end

---- Brief description.
-- <#Description#>
-- @param planeNormal <#planeNormal description#>
-- @param planeSupport <#planeSupport description#>
-- @param i <#i description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getPlane(planeNormal, planeSupport, i)
end

---- Brief description.
-- <#Description#>
-- @param pt <#pt description#>
-- @param tolerance <#tolerance description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:isInside(pt, tolerance)
end

---- Brief description.
-- <#Description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setRadiusX(radius)
end

---- Brief description.
-- <#Description#>
-- @param height <#height description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setHeightX(height)
end

---- Brief description.
-- <#Description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setRadiusY(radius)
end

---- Brief description.
-- <#Description#>
-- @param height <#height description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setHeightY(height)
end

---- Brief description.
-- <#Description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setRadiusZ(radius)
end

---- Brief description.
-- <#Description#>
-- @param height <#height description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setHeightZ(height)
end

---- Brief description.
-- <#Description#>
-- @param mass <#mass description#>
-- @param inertia <#inertia description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:calculateLocalInertia(mass, inertia)
end

---- Brief description.
-- <#Description#>
-- @param collisionMargin <#collisionMargin description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setMargin(collisionMargin)
end

---- Brief description.
-- <#Description#>
-- @param t <#t description#>
-- @param aabbMin <#aabbMin description#>
-- @param aabbMax <#aabbMax description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getAabb(t, aabbMin, aabbMax)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getUpAxis()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getRadius()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getHalfHeight()
end

---- Brief description.
-- <#Description#>
-- @param scaling <#scaling description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:setLocalScaling(scaling)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeCapsule:getAnisotropicRollingFrictionDirection()
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeCapsule.type()
end

