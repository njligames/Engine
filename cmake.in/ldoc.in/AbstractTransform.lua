
----
-- @file AbstractTransform


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractTransform:AbstractTransform()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function AbstractTransform:AbstractTransform()
end

---- Brief description.
-- <#Description#>
-- @param rhs <#rhs description#>
-- @return <#return value description#>
function AbstractTransform:operator=(rhs)
end

---- Brief description.
-- The transformation is the combination of the node’s rotation, position, and scale properties. The default transformation is SCNMatrix4Identity.
-- When you set the value of this property, the node’s rotation, orientation, eulerAngles, position, and scale properties automatically change to match the new transform, and vice versa. JLIEngine can perform this conversion only if the transform you provide is a combination of rotation, translation, and scale operations. If you set the value of this property to a skew transformation or to a nonaffine transformation, the values of these properties become undefined. Setting a new value for any of these properties causes JLIEngine to compute a new transformation, discarding any skew or nonaffine operations in the original transformation.
-- @return The Transform for this instance.
function AbstractTransform:getTransform()
end

---- Brief description.
-- <#Description#>
-- @param transform <#transform description#>
-- @return The Transform for this instance.
function AbstractTransform:setTransform(transform)
end

---- Brief description.
-- The node’s position locates it within the coordinate system of its parent, as modified by the node’s pivot property. The default position is the zero vector, indicating that the node is placed at the origin of the parent node’s coordinate system.
-- @return The Origin for this instance.
function AbstractTransform:getOrigin()
end

---- Brief description.
-- <#Description#>
-- @param origin <#origin description#>
-- @return The Origin for this instance.
function AbstractTransform:setOrigin(origin)
end

---- Brief description.
-- <#Description#>
-- @param origin <#origin description#>
-- @return The Origin for this instance.
function AbstractTransform:setOrigin(origin)
end

---- Brief description.
-- The four-component rotation vector specifies the direction of the rotation axis in the first three components and the angle of rotation (in radians) in the fourth. The default rotation is the zero vector, specifying no rotation. Rotation is applied relative to the node’s pivot property.
-- The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
-- @return the Rotation for this instance.
function AbstractTransform:getRotation()
end

---- Brief description.
-- <#Description#>
-- @param rotation <#rotation description#>
-- @return the Rotation for this instance.
function AbstractTransform:setRotation(rotation)
end

---- Brief description.
-- Roll is the rotation about the node’s z-axis, yaw is the rotation about the node’s y-axis, and pitch is the rotation about the node’s x-axis. Rotation is applied relative to the node’s pivot property.
-- @return The Euler Angles for this instance.
function AbstractTransform:getEulerAngles()
end

---- Brief description.
-- <#Description#>
-- @param angles <#angles description#>
-- @return The Euler Angles for this instance.
function AbstractTransform:setEulerAngles(angles)
end

---- Brief description.
-- The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
-- @return The Orientation for this instance.
function AbstractTransform:getOrientation()
end

---- Brief description.
-- <#Description#>
-- @param orientation <#orientation description#>
-- @return The Orientation for this instance.
function AbstractTransform:setOrientation(orientation)
end

---- Brief description.
-- Each component of the scale vector multiplies the corresponding dimension of the node’s geometry. The default scale is 1.0 in all three dimensions. For example, applying a scale of (2.0, 0.5, 2.0) to a node containing a cube geometry reduces its height and increases its width and depth. Scaling is applied relative to the node’s pivot property.
-- @return The scale for this instance.
function AbstractTransform:getScale()
end

---- Brief description.
-- <#Description#>
-- @param scale <#scale description#>
-- @return The scale for this instance.
function AbstractTransform:setScale(scale)
end

---- Brief description.
-- <#Description#>
-- @param scale <#scale description#>
-- @return The scale for this instance.
function AbstractTransform:setScale(scale)
end

---- Brief description.
-- A node’s pivot is the transformation between its coordinate space and that used by its position, rotation, and scale properties. The default pivot is SCNMatrix4Identity, specifying that the node’s position locates the origin of its coordinate system, its rotation is about an axis through its center, and its scale is also relative to that center point.
-- Changing the pivot transform alters these behaviors in many useful ways. You can:
-- Offset the node’s contents relative to its position. For example, by setting the pivot to a translation transform you can position a node containing a sphere geometry relative to where the sphere would rest on a floor instead of relative to its center.
-- Move the node’s axis of rotation. For example, with a translation transform you can cause a node to revolve around a faraway point instead of rotating around its center, and with a rotation transform you can tilt the axis of rotation.
-- Adjust the center point and direction for scaling the node. For example, with a translation transform you can cause a node to grow or shrink relative to a corner instead of to its center.
-- @return The Pivot for this instance.
function AbstractTransform:getPivot()
end

---- Brief description.
-- <#Description#>
-- @param pivot <#pivot description#>
-- @return The Pivot for this instance.
function AbstractTransform:setPivot(pivot)
end

---- Brief description.
-- A world transform is the node’s coordinate space transformation relative to the scene’s coordinate space. This transformation is the concatenation of the node’s transform property with that of its parent node, the parent’s parent, and so on up to the rootNode object of the scene.
-- @return The
function AbstractTransform:getWorldTransform()
end

