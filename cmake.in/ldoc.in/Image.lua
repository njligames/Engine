
----
-- @file Image


---- Brief description.
-- <#Description#>
-- @param  description#>
-- @return <#return value description#>
function Image:operator=(param1)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:03
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function Image:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getType()
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param color <#color description#>
-- @return <#return value description#>
function Image:setPixel(position, color)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param imageSource <#imageSource description#>
-- @return <#return value description#>
function Image:setPixel(position, imageSource)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param pixel <#pixel description#>
-- @return <#return value description#>
function Image:getPixel(position, pixel)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param dimensions <#dimensions description#>
-- @param color <#color description#>
-- @return <#return value description#>
function Image:setPixels(position, dimensions, color)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param dimensions <#dimensions description#>
-- @param sourceImage <#sourceImage description#>
-- @param 0 <#0 description#>
-- @param 0 <#0 description#>
-- @return <#return value description#>
function Image:setPixels(position, dimensions, sourceImage, 0, 0)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param dimension <#dimension description#>
-- @param destinationImage <#destinationImage description#>
-- @param 0 <#0 description#>
-- @param 0 <#0 description#>
-- @return <#return value description#>
function Image:getPixels(position, dimension, destinationImage, 0, 0)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getNumberOfComponents()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getWidth()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getHeight()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getFilename()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getBytesPerPixel()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getDataRaw()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getDataRaw()
end

---- Brief description.
-- <#Description#>
-- @param width <#width description#>
-- @param height <#height description#>
-- @param numberOfComponents <#numberOfComponents description#>
-- @param const <#const description#>
-- @param 1.0f <#1.0f description#>
-- @param 1.0f <#1.0f description#>
-- @param 1.0f <#1.0f description#>
-- @param 0.0f <#0.0f description#>
-- @return <#return value description#>
function Image:setDataRaw(width, height, numberOfComponents, const, 1.0f, 1.0f, 1.0f, 0.0f)
end

---- Brief description.
-- <#Description#>
-- @param width <#width description#>
-- @param height <#height description#>
-- @param numberOfComponents <#numberOfComponents description#>
-- @param 1.0f <#1.0f description#>
-- @param 1.0f <#1.0f description#>
-- @param 1.0f <#1.0f description#>
-- @param 1.0f <#1.0f description#>
-- @return <#return value description#>
function Image:generate(width, height, numberOfComponents, 1.0f, 1.0f, 1.0f, 1.0f)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:getDataRawLength()
end

---- Brief description.
-- <#Description#>
-- @param from <#from description#>
-- @param to <#to description#>
-- @param color <#color description#>
-- @return <#return value description#>
function Image:drawLine(from, to, color)
end

---- Brief description.
-- <#Description#>
-- @param from <#from description#>
-- @param to <#to description#>
-- @param imageSource <#imageSource description#>
-- @return <#return value description#>
function Image:drawLine(from, to, imageSource)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:blur()
end

---- Brief description.
-- <#Description#>
-- @param image <#image description#>
-- @return <#return value description#>
function Image:setAlpha(image)
end

---- Brief description.
-- <#Description#>
-- @param alpha <#alpha description#>
-- @return <#return value description#>
function Image:setAlpha(alpha)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:hasAlpha()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:preMultiplyAlpha()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Image:flip()
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.Image.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.Image.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Image.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.Image.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Image.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Image.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Image.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.Image.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Image.type()
end

---- Brief description.
-- <#Description#>
-- @param imageSource <#imageSource description#>
-- @param position <#position description#>
-- @param dimensions <#dimensions description#>
-- @return <#return value description#>
function NJLI.Image.createSubImage(imageSource, position, dimensions)
end

