
----
-- @file ThreadBuilder


---- Brief description.
-- Calculate the buffer size of this object.
-- @return The buffer size.
function ThreadBuilder:calculateSerializeBufferSize()
end

---- Brief description.
-- Serialize this object.
-- @param btSerializer the serializer which does the serialize.
-- @return The buffer size.
function ThreadBuilder:serialize(btSerializer)
end

---- Brief description.
-- Get the type of
-- @return The
function ThreadBuilder:getObjectType()
end

---- Brief description.
-- The name of this class.
-- @return The name of this class.
function ThreadBuilder:getClassName()
end

---- Brief description.
-- Get the type of
-- @return The
function ThreadBuilder:getType()
end

---- Brief description.
-- Create an Array of instances of this class.
-- @param size The amount of elements in the array.
-- @return Pointer to the newly created array.
function NJLI.ThreadBuilder.createArray(size)
end

---- Brief description.
-- Destroy an Array of this class type.
-- @param array The Pointer to the array to delete.
-- @return Pointer to the newly created array.
function NJLI.ThreadBuilder.destroyArray(array)
end

---- Brief description.
-- Create an instance of this class.
-- @return Pointer to the newly created instance.
function NJLI.ThreadBuilder.create()
end

---- Brief description.
-- Create a clone of an instance of this class.
-- @param object The object to clone.
-- @return Pointer to the newly created instance.
function NJLI.ThreadBuilder.clone(object)
end

---- Brief description.
-- Destroy an instance of this class.
-- @param object The object to destroy.
-- @return Pointer to the newly created instance.
function NJLI.ThreadBuilder.destroy(object)
end

---- Brief description.
-- Load a lua table representation of this class. This is used for JLIM.create(object).
-- @param object The object to load.
-- @param L The current lua state.
-- @param stack_index The stack index of the lua stack.
-- @return Pointer to the newly created instance.
function NJLI.ThreadBuilder.load(object, L, stack_index)
end

---- Brief description.
-- Get the type of
-- @return The
function NJLI.ThreadBuilder.type()
end

