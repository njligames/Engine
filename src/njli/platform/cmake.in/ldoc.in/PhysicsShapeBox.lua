
----
-- @file PhysicsShapeBox


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:calculateSerializeBufferSize()
end

---- Brief description.
-- <#Description#>
-- @param btSerializer <#btSerializer description#>
-- @return <#return value description#>
function PhysicsShapeBox:serialize(btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:getType()
end

---- Brief description.
-- <#Description#>
-- @param extends <#extends description#>
-- @return <#return value description#>
function PhysicsShapeBox:setHalfExtends(extends)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:getHalfExtentsWithMargin()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:getHalfExtentsWithoutMargin()
end

---- Brief description.
-- <#Description#>
-- @param vec <#vec description#>
-- @return <#return value description#>
function PhysicsShapeBox:localGetSupportingVertex(vec)
end

---- Brief description.
-- <#Description#>
-- @param vec <#vec description#>
-- @return <#return value description#>
function PhysicsShapeBox:localGetSupportingVertexWithoutMargin(vec)
end

---- Brief description.
-- <#Description#>
-- @param vectors <#vectors description#>
-- @param supportVerticesOut <#supportVerticesOut description#>
-- @param numVectors <#numVectors description#>
-- @return <#return value description#>
function PhysicsShapeBox:batchedUnitVectorGetSupportingVertexWithoutMargin(vectors, supportVerticesOut, numVectors)
end

---- Brief description.
-- <#Description#>
-- @param collisionMargin <#collisionMargin description#>
-- @return <#return value description#>
function PhysicsShapeBox:setMargin(collisionMargin)
end

---- Brief description.
-- <#Description#>
-- @param mass <#mass description#>
-- @param inertia <#inertia description#>
-- @return <#return value description#>
function PhysicsShapeBox:calculateLocalInertia(mass, inertia)
end

---- Brief description.
-- <#Description#>
-- @param planeNormal <#planeNormal description#>
-- @param planeSupport <#planeSupport description#>
-- @param i <#i description#>
-- @return <#return value description#>
function PhysicsShapeBox:getPlane(planeNormal, planeSupport, i)
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @return <#return value description#>
function PhysicsShapeBox:getPlane(i)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:getNumPlanes()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:getNumVertices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeBox:getNumEdges()
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param vtx <#vtx description#>
-- @return <#return value description#>
function PhysicsShapeBox:getVertex(i, vtx)
end

---- Brief description.
-- <#Description#>
-- @param plane <#plane description#>
-- @param i <#i description#>
-- @return <#return value description#>
function PhysicsShapeBox:getPlaneEquation(plane, i)
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param pa <#pa description#>
-- @param pb <#pb description#>
-- @return <#return value description#>
function PhysicsShapeBox:getEdge(i, pa, pb)
end

---- Brief description.
-- <#Description#>
-- @param pt <#pt description#>
-- @param tolerance <#tolerance description#>
-- @return <#return value description#>
function PhysicsShapeBox:isInside(pt, tolerance)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeBox.type()
end

