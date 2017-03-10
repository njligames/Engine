
----
-- @file AbstractState


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractState:AbstractState()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractState:AbstractState()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractState:AbstractState()
end

---- Brief description.
-- <#Description#>
-- @param AbstractState& <
-- @return <#return value description#>
function AbstractState:operator=(AbstractState&)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractState:isFinished()
end

---- Brief description.
-- <#Description#>
-- @param bool <#bool description#>
-- @return <#return value description#>
function AbstractState:enableFinished(bool)
end

---- Brief description.
-- <#Description#>
-- @param OBJECT_TYPE <#OBJECT_TYPE description#>
-- @return <#return value description#>
function AbstractState:enter(OBJECT_TYPE)
end

---- Brief description.
-- <#Description#>
-- @param OBJECT_TYPE <#OBJECT_TYPE description#>
-- @param f32 <
-- @return <#return value description#>
function AbstractState:update(OBJECT_TYPE, f32)
end

---- Brief description.
-- <#Description#>
-- @param OBJECT_TYPE <#OBJECT_TYPE description#>
-- @return <#return value description#>
function AbstractState:exit(OBJECT_TYPE)
end

---- Brief description.
-- <#Description#>
-- @param OBJECT_TYPE <#OBJECT_TYPE description#>
-- @param Telegram& <#Telegram& description#>
-- @return <#return value description#>
function AbstractState:onMessage(OBJECT_TYPE, Telegram&)
end

---- Brief description.
-- @return <#return value description#>
function AbstractState:enableCanDelete()
end

