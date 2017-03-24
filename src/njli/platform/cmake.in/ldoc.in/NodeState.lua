
----
-- @file NodeState


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NodeState:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:04
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function NodeState:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NodeState:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NodeState:getType()
end

---- Brief description.
-- @author James Folk, 16-02-11 17:02:22
-- <#Description#>
-- @param node <#node description#>
-- @return 
function NodeState:enter(node)
end

---- Brief description.
-- @author James Folk, 16-02-11 17:02:36
-- <#Description#>
-- @param node <#node description#>
-- @param timestep <#timestep description#>
-- @return 
function NodeState:update(node, timestep)
end

---- Brief description.
-- @author James Folk, 16-02-11 17:02:47
-- <#Description#>
-- @param node <#node description#>
-- @return 
function NodeState:exit(node)
end

---- Brief description.
-- <#Description#>
-- @param node <#node description#>
-- @param telegram <#telegram description#>
-- @return <#return value description#>
function NodeState:onMessage(node, telegram)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.NodeState.createArray(size)
end

---- Brief description.
-- <#Description#>
-- @param array <#array description#>
-- @return <#return value description#>
function NJLI.NodeState.destroyArray(array)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.NodeState.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.NodeState.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.NodeState.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.NodeState.copy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.NodeState.destroy(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return <#return value description#>
function NJLI.NodeState.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.NodeState.type()
end

