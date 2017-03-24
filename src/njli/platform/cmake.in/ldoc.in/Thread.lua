
----
-- @file Thread


---- Brief description.
-- Calculate the buffer size of this object.
-- @return The buffer size.
function Thread:calculateSerializeBufferSize()
end

---- Brief description.
-- Serialize this object.
-- @param btSerializer the serializer which does the serialize.
-- @return The buffer size.
function Thread:serialize(btSerializer)
end

---- Brief description.
-- The name of this class.
-- @return The name of this class.
function Thread:getClassName()
end

---- Brief description.
-- Get the type of
-- @return The
function Thread:getType()
end

---- Brief description.
-- @return "The string value for this object.
function Thread:setup()
end

---- Brief description.
-- @return "The string value for this object.
function Thread:enablePause()
end

---- Brief description.
-- @return "The string value for this object.
function Thread:isPaused()
end

---- Brief description.
-- @return "The string value for this object.
function Thread:stop()
end

---- Brief description.
-- @return "The string value for this object.
function Thread:run()
end

---- Brief description.
-- Create an Array of instances of this class.
-- @param size The amount of elements in the array.
-- @return Pointer to the newly created array.
function NJLI.Thread.createArray(size)
end

---- Brief description.
-- Destroy an Array of this class type.
-- @param array The Pointer to the array to delete.
-- @return Pointer to the newly created array.
function NJLI.Thread.destroyArray(array)
end

---- Brief description.
-- Create an instance of this class.
-- @return Pointer to the newly created instance.
function NJLI.Thread.create()
end

---- Brief description.
-- Create an instance of this class using a builder.
-- @param builder The builder to use for construction
-- @return Pointer to the newly created instance.
function NJLI.Thread.create(builder)
end

---- Brief description.
-- Create a shallow copy of an instance of this class (sharing pointers).
-- @param object The object to clone.
-- @return Pointer to the newly created instance.
function NJLI.Thread.clone(object)
end

---- Brief description.
-- Create a deep copy of an instance of this class (NOT sharing pointers).
-- @param object The object to clone.
-- @return Pointer to the newly created instance.
function NJLI.Thread.copy(object)
end

---- Brief description.
-- Destroy an instance of this class.
-- @param object The object to destroy.
-- @return Pointer to the newly created instance.
function NJLI.Thread.destroy(object)
end

---- Brief description.
-- Load a lua table representation of this class. This is used for JLIM.create(object).
-- @param object The object to load.
-- @param L The current lua state.
-- @param stack_index The stack index of the lua stack.
-- @return Pointer to the newly created instance.
function NJLI.Thread.load(object, L, stack_index)
end

---- Brief description.
-- Get the type of
-- @return The
function NJLI.Thread.type()
end

