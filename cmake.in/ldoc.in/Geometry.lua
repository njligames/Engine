
----
-- @file Geometry


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:57
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function Geometry:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getType()
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @return <#return value description#>
function Geometry:addLevelOfDetail(geometry)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @return <#return value description#>
function Geometry:removeLevelOfDetail(geometry)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:removeAllLevelOfDetails()
end

---- Brief description.
-- <#Description#>
-- @param geometries <#geometries description#>
-- @return <#return value description#>
function Geometry:getLevelOfDetails(geometries)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Geometry:getLevelOfDetail(index)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Geometry:getLevelOfDetail(index)
end

---- Brief description.
-- <#Description#>
-- @param material <#material description#>
-- @return <#return value description#>
function Geometry:addMaterial(material)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:removeMaterial()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getMaterial()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getMaterial()
end

---- Brief description.
-- <#Description#>
-- @param shader <#shader description#>
-- @return <#return value description#>
function Geometry:addShaderProgram(shader)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:removeShaderProgram()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getShaderProgram()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getShaderProgram()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getMaxMeshes()
end

---- Brief description.
-- @author James Folk, 16-02-11 17:02:44
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param vertices <#vertices description#>
-- @param node <#node description#>
-- @return 
function Geometry:getVertices(geometry, vertices, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function Geometry:getNumberOfVertices(geometry, node)
end

---- Brief description.
-- @author James Folk, 16-02-11 17:02:56
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param colorVertices <#colorVertices description#>
-- @param node <#node description#>
-- @return 
function Geometry:getVertexColors(geometry, colorVertices, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function Geometry:getNumberOfVertexColors(geometry, node)
end

---- Brief description.
-- @author James Folk, 16-02-11 17:02:14
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param textureCoordinates <#textureCoordinates description#>
-- @param node <#node description#>
-- @return 
function Geometry:getTextureCoordinates(geometry, textureCoordinates, node)
end

---- Brief description.
-- <#Description#>
-- @param geometry <#geometry description#>
-- @param node <#node description#>
-- @return <#return value description#>
function Geometry:getNumberOfTextureCoordinates(geometry, node)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function Geometry:setOpacity(node, opacity)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transfrom <#transfrom description#> <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function Geometry:setHidden(node, transfrom, node, opacity)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param opacity <#opacity description#>
-- @return <#return value description#>
function Geometry:isHidden(node, opacity)
end

---- Brief description.
-- @return <#return value description#>
function Geometry:transformVertices()
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function Geometry:transformVertexColors(node, transform)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function Geometry:transformTextureCoordinates(node, transform)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param physicsShape <#physicsShape description#>
-- @return <#return value description#>
function Geometry:applyShape(node, physicsShape)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:numberOfVertices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:numberOfIndices()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getArrayBuffer()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getArrayBufferSize()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getElementArrayBuffer()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:getElementArrayBufferSize()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:setSize()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:setColor()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:setBlendSource()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:setBlendDestination()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:setupOpacity()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:loadGPU()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:unLoadGPU()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Geometry:isLoadedGPU()
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @param transform <#transform description#>
-- @return <#return value description#>
function Geometry:setTransform(index, transform)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Geometry:getTransform(index)
end

---- Brief description.
-- @return <#return value description#>
function Geometry:getAabb()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:enableBlend()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:enableDepthTest()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:enableStencilTest()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:numberOfReferences()
end

---- Brief description.
-- @return <#return value description#>
function Geometry:sort()
end

---- Brief description.
-- <#Description#>
-- @param type <
-- @return <#return value description#>
function NJLI.Geometry.create(type)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Geometry.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.Geometry.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Geometry.type()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.setPointSize()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.getPointSize()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.setLineWidth()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.getLineWidth()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.quickSort()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.swapTransformData()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.lessThan()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.greaterThan()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.swapVertexData()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.bindTransform()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.loadGPU_Internal()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.setupOpacity_Internal()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.unLoadGPU_Internal()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Geometry.setupShader_Internal()
end

