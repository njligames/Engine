
----
-- @file WorldDebugDrawer


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:WorldDebugDrawer()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:BT_DECLARE_ALIGNED_ALLOCATOR()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:getType()
end

---- Brief description.
-- <#Description#>
-- @param from <#from description#>
-- @param to <#to description#>
-- @param color <#color description#>
-- @return <#return value description#>
function WorldDebugDrawer:drawLine(from, to, color)
end

---- Brief description.
-- <#Description#>
-- @param PointOnB <#PointOnB description#>
-- @param normalOnB <#normalOnB description#>
-- @param distance <#distance description#>
-- @param lifeTime <#lifeTime description#>
-- @param color <#color description#>
-- @return <#return value description#>
function WorldDebugDrawer:drawContactPoint(PointOnB, normalOnB, distance, lifeTime, color)
end

---- Brief description.
-- <#Description#>
-- @param warningString <#warningString description#>
-- @return <#return value description#>
function WorldDebugDrawer:reportErrorWarning(warningString)
end

---- Brief description.
-- <#Description#>
-- @param location <#location description#>
-- @param textString <#textString description#>
-- @return <#return value description#>
function WorldDebugDrawer:draw3dText(location, textString)
end

---- Brief description.
-- <#Description#>
-- @param debugMode <#debugMode description#>
-- @return <#return value description#>
function WorldDebugDrawer:setDebugMode(debugMode)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:getDebugMode()
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param vertices <#vertices description#>
-- @param node <#node description#>
-- @return <#return value description#>
function WorldDebugDrawer:getVertices(geometry, vertices, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function WorldDebugDrawer:getNumberOfVertices(geometry, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param colorVertices <#colorVertices description#>
-- @param node <#node description#>
-- @return <#return value description#>
function WorldDebugDrawer:getVertexColors(geometry, colorVertices, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function WorldDebugDrawer:getNumberOfVertexColors(geometry, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param textureCoordinates <#textureCoordinates description#>
-- @param node <#node description#>
-- @return <#return value description#>
function WorldDebugDrawer:getTextureCoordinates(geometry, textureCoordinates, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function WorldDebugDrawer:getNumberOfTextureCoordinates(geometry, node)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function WorldDebugDrawer:setOpacity(node, opacity)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function WorldDebugDrawer:setHidden(node, opacity)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function WorldDebugDrawer:isHidden(node, opacity)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transfrom <#transfrom description#>
-- @return <#return value description#>
function WorldDebugDrawer:transformVertices(node, transfrom)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function WorldDebugDrawer:transformVertexColors(node, transform)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function WorldDebugDrawer:transformTextureCoordinates(node, transform)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:numberOfVertices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:numberOfIndices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:getArrayBuffer()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:getArrayBufferSize()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:getElementArrayBuffer()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldDebugDrawer:getElementArrayBufferSize()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:setSize()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:setColor()
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param physicsShape <#physicsShape description#>
-- @return <#return value description#>
function WorldDebugDrawer:applyShape(node, physicsShape)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @return <#return value description#>
function WorldDebugDrawer:hideGeometry(node)
end

---- Brief description.
-- <#Description#>
-- @param camera <#camera description#>
-- @return <#return value description#>
function WorldDebugDrawer:render(camera)
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:swapVertexData()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:setVertexPositions()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:getVertexPositions()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:setVertexTextureCoordinates()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:getVertexTextureCoordinates()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:setVertexColors()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:getVertexColors()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:load()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:unLoad()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:WorldDebugDrawer()
end

---- Brief description.
-- @return <#return value description#>
function WorldDebugDrawer:operator=()
end

