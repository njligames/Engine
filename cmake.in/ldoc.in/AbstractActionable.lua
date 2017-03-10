
----
-- @file AbstractActionable


---- Brief description.
-- <#Description#>
-- @param action <#action description#>
-- @param callCompletionFunction <#callCompletionFunction description#>
-- @return 
function AbstractActionable:runAction(action, callCompletionFunction)
end

---- Brief description.
-- <#Description#>
-- @param action <#action description#>
-- @param key <#key description#>
-- @param callCompletionFunction <#callCompletionFunction description#>
-- @return 
function AbstractActionable:runAction(action, key, callCompletionFunction)
end

---- Brief description.
-- <#Description#>
-- @param key <#key description#>
-- @return <#return value description#>
function AbstractActionable:getAction(key)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractActionable:hasActions()
end

---- Brief description.
-- <#Description#>
-- @param key <#key description#>
-- @return <#return value description#>
function AbstractActionable:removeAction(key)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractActionable:removeAllActions()
end

---- Brief description.
-- @return <#return value description#>
function AbstractActionable:AbstractActionable()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractActionable:operator=()
end

