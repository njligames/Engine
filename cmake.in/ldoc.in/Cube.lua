
----
-- @file Cube


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Cube:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:13
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function Cube:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Cube:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Cube:getType()
end

---- Brief description.
-- @author James Folk, 16-02-11 16:02:52
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param vertices <#vertices description#>
-- @param node <#node description#>
-- @return 
function Cube:getVertices(geometry, vertices, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function Cube:getNumberOfVertices(geometry, node)
end

---- Brief description.
-- @author James Folk, 16-02-11 16:02:53
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param colorVertices <#colorVertices description#>
-- @param node <#node description#>
-- @return 
function Cube:getVertexColors(geometry, colorVertices, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function Cube:getNumberOfVertexColors(geometry, node)
end

---- Brief description.
-- @author James Folk, 16-02-11 16:02:57
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param textureCoordinates <#textureCoordinates description#>
-- @param node <#node description#>
-- @return 
function Cube:getTextureCoordinates(geometry, textureCoordinates, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function Cube:getNumberOfTextureCoordinates(geometry, node)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function Cube:setOpacity(node, opacity)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transfrom <#transfrom description#> <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function Cube:setHidden(node, transfrom, node, opacity)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function Cube:isHidden(node, opacity)
end

---- Brief description.
-- @return <#return value description#>
function Cube:transformVertices()
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function Cube:transformVertexColors(node, transform)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function Cube:transformTextureCoordinates(node, transform)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Cube:numberOfVertices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Cube:numberOfIndices()
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.Cube.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.Cube.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Cube.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.Cube.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Cube.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Cube.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Cube.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.Cube.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Cube.type()
end

