
----
-- @file PhysicsShapeConvexHull


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:calculateSerializeBufferSize()
end

---- Brief description.
-- <#Description#>
-- @param btSerializer <#btSerializer description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:serialize(btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getType()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getNumVertices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getNumEdges()
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param pa <#pa description#>
-- @param pb <#pb description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getEdge(i, pa, pb)
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @param vtx <#vtx description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getVertex(i, vtx)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getNumPlanes()
end

---- Brief description.
-- <#Description#>
-- @param planeNormal <#planeNormal description#>
-- @param planeSupport <#planeSupport description#>
-- @param i <#i description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getPlane(planeNormal, planeSupport, i)
end

---- Brief description.
-- <#Description#>
-- @param pt <#pt description#>
-- @param tolerance <#tolerance description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:isInside(pt, tolerance)
end

---- Brief description.
-- <#Description#>
-- @param point <#point description#>
-- @param recalculateLocalAabb <#recalculateLocalAabb description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:addPoint(point, recalculateLocalAabb)
end

---- Brief description.
-- <#Description#>
-- @param points <#points description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getUnscaledPoints(points)
end

---- Brief description.
-- <#Description#>
-- @param i <#i description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getScaledPoint(i)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:getNumPoints()
end

---- Brief description.
-- <#Description#>
-- @param trans <#trans description#>
-- @param dir <#dir description#>
-- @param minProj <#minProj description#>
-- @param maxProj <#maxProj description#>
-- @param witnesPtMin <#witnesPtMin description#>
-- @param witnesPtMax <#witnesPtMax description#>
-- @return <#return value description#>
function PhysicsShapeConvexHull:project(trans, dir, minProj, maxProj, witnesPtMin, witnesPtMax)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.PhysicsShapeConvexHull.type()
end

