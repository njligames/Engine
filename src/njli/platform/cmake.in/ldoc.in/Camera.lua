
----
-- @file Camera


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:17
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function Camera:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getType()
end

---- Brief description.
-- <#Description#>
-- @param val <#val description#>
-- @return <#return value description#>
function Camera:setZNear(val)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getZNear()
end

---- Brief description.
-- <#Description#>
-- @param val <#val description#>
-- @return <#return value description#>
function Camera:setZFar(val)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getZFar()
end

---- Brief description.
-- <#Description#>
-- @param val <#val description#>
-- @return <#return value description#>
function Camera:setFov(val)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getFov()
end

---- Brief description.
-- <#Description#>
-- @param enable <#enable description#>
-- @return <#return value description#>
function Camera:enableOrthographic(enable)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:isOrthographic()
end

---- Brief description.
-- <#Description#>
-- @param category <#category description#>
-- @return <#return value description#>
function Camera:setRenderCategory(category)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getRenderCategory()
end

---- Brief description.
-- <#Description#>
-- @param category <#category description#>
-- @return <#return value description#>
function Camera:addRenderCategory(category)
end

---- Brief description.
-- <#Description#>
-- @param category <#category description#>
-- @return <#return value description#>
function Camera:removeRenderCategory(category)
end

---- Brief description.
-- <#Description#>
-- @param category <#category description#>
-- @return <#return value description#>
function Camera:hasRenderCategory(category)
end

---- Brief description.
-- <#Description#>
-- @param windowPosition <#windowPosition description#>
-- @return <#return value description#>
function Camera:unProject(windowPosition)
end

---- Brief description.
-- <#Description#>
-- @param objectPosition <#objectPosition description#>
-- @return <#return value description#>
function Camera:project(objectPosition)
end

---- Brief description.
-- <#Description#>
-- @param windowPosition <#windowPosition description#>
-- @param from <#from description#>
-- @param to <#to description#>
-- @return <#return value description#>
function Camera:getTouchRay(windowPosition, from, to)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getForwardVector()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getUpVector()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getSideVector()
end

---- Brief description.
-- @author James Folk, 16-02-11 02:02:03
-- <#Description#>
-- @param pos <#pos description#>
-- @param up <#0 description#>
-- @return 
function Camera:lookAt(pos, up)
end

---- Brief description.
-- <#Description#>
-- @param screenPosition <#screenPosition description#>
-- @param rayContact <#rayContact description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function Camera:rayTestClosest(screenPosition, rayContact, collisionGroup, collisionMask)
end

---- Brief description.
-- <#Description#>
-- @param screenPosition <#screenPosition description#>
-- @param rayContacts <#rayContacts description#>
-- @param numContacts <#numContacts description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function Camera:rayTestAll(screenPosition, rayContacts, numContacts, collisionGroup, collisionMask)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getParent()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Camera:getParent()
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.Camera.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.Camera.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Camera.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.Camera.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Camera.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Camera.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Camera.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.Camera.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Camera.type()
end

