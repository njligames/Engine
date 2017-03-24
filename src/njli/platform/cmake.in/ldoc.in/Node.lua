
----
-- @file Node


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:calculateSerializeBufferSize()
end

---- Brief description.
-- @author James Folk, 16-02-11 15:02:45
-- <#Description#>
-- @param dataBuffer <#dataBuffer description#>
-- @param btSerializer <#btSerializer description#>
-- @return 
function Node:serialize(dataBuffer, btSerializer)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getType()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getWorldTransform()
end

---- Brief description.
-- The transformation is the combination of the node’s rotation, position, and scale properties. The default transformation is SCNMatrix4Identity.
-- When you set the value of this property, the node’s rotation, orientation, eulerAngles, position, and scale properties automatically change to match the new transform, and vice versa. JLIEngine can perform this conversion only if the transform you provide is a combination of rotation, translation, and scale operations. If you set the value of this property to a skew transformation or to a nonaffine transformation, the values of these properties become undefined. Setting a new value for any of these properties causes JLIEngine to compute a new transformation, discarding any skew or nonaffine operations in the original transformation.
-- @return The Transform for this instance.
function Node:getTransform()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:36
-- <#Description#>
-- @param transform <#transform description#>
-- @return 
function Node:setTransform(transform)
end

---- Brief description.
-- The node’s position locates it within the coordinate system of its parent, as modified by the node’s pivot property. The default position is the zero vector, indicating that the node is placed at the origin of the parent node’s coordinate system.
-- @return The Origin for this instance.
function Node:getOrigin()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:56
-- <#Description#>
-- @param origin <#origin description#>
-- @return 
function Node:setOrigin(origin)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:02
-- <#Description#>
-- @param origin <#origin description#>
-- @return 
function Node:setOrigin(origin)
end

---- Brief description.
-- The four-component rotation vector specifies the direction of the rotation axis in the first three components and the angle of rotation (in radians) in the fourth. The default rotation is the zero vector, specifying no rotation. Rotation is applied relative to the node’s pivot property.
-- The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
-- @return the Rotation for this instance.
function Node:getRotation()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:22
-- <#Description#>
-- @param rotation <#rotation description#>
-- @return 
function Node:setRotation(rotation)
end

---- Brief description.
-- Roll is the rotation about the node’s z-axis, yaw is the rotation about the node’s y-axis, and pitch is the rotation about the node’s x-axis. Rotation is applied relative to the node’s pivot property.
-- @return The Euler Angles for this instance.
function Node:getEulerAngles()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:44
-- <#Description#>
-- @param angles <#angles description#>
-- @return 
function Node:setEulerAngles(angles)
end

---- Brief description.
-- The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
-- @return The Orientation for this instance.
function Node:getOrientation()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:04
-- <#Description#>
-- @param orientation <#orientation description#>
-- @return 
function Node:setOrientation(orientation)
end

---- Brief description.
-- Each component of the scale vector multiplies the corresponding dimension of the node’s geometry. The default scale is 1.0 in all three dimensions. For example, applying a scale of (2.0, 0.5, 2.0) to a node containing a cube geometry reduces its height and increases its width and depth. Scaling is applied relative to the node’s pivot property.
-- @return The scale for this instance.
function Node:getScale()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:21
-- <#Description#>
-- @param scale <#scale description#>
-- @return 
function Node:setScale(scale)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:30
-- <#Description#>
-- @param scale <#scale description#>
-- @return 
function Node:setScale(scale)
end

---- Brief description.
-- A node’s pivot is the transformation between its coordinate space and that used by its position, rotation, and scale properties. The default pivot is SCNMatrix4Identity, specifying that the node’s position locates the origin of its coordinate system, its rotation is about an axis through its center, and its scale is also relative to that center point.
-- Changing the pivot transform alters these behaviors in many useful ways. You can:
-- Offset the node’s contents relative to its position. For example, by setting the pivot to a translation transform you can position a node containing a sphere geometry relative to where the sphere would rest on a floor instead of relative to its center.
-- Move the node’s axis of rotation. For example, with a translation transform you can cause a node to revolve around a faraway point instead of rotating around its center, and with a rotation transform you can tilt the axis of rotation.
-- Adjust the center point and direction for scaling the node. For example, with a translation transform you can cause a node to grow or shrink relative to a corner instead of to its center.
-- @return The Pivot for this instance.
function Node:getPivot()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:55
-- <#Description#>
-- @param pivot <#pivot description#>
-- @return 
function Node:setPivot(pivot)
end

---- Brief description.
-- <#Description#>
-- @param emitter <#emitter description#>
-- @return <#return value description#>
function Node:addParticleEmitter(emitter)
end

---- Brief description.
-- <#Description#>
-- @param emitter <#emitter description#>
-- @return <#return value description#>
function Node:removeParticleEmitter(emitter)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:09
-- <#Description#>
-- @return 
function Node:removeAllParticleEmitters()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:numberOfParticleEmitters()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:19
-- <#Description#>
-- @param particleEmitters <#particleEmitters description#>
-- @return 
function Node:getParticleEmitters(particleEmitters)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function Node:getParticleEmitterIndex(object)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Node:getParticleEmitter(index)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Node:getParticleEmitter(index)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:34
-- <#Description#>
-- @param body <#body description#>
-- @return 
function Node:addPhysicsBody(body)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:38
-- <#Description#>
-- @return 
function Node:removePhysicsBody()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getPhysicsBody()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getPhysicsBody()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:56
-- <#Description#>
-- @param body <#body description#>
-- @return 
function Node:addLight(body)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:03
-- <#Description#>
-- @return 
function Node:removeLight()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getLight()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getLight()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:17
-- <#Description#>
-- @param body <#body description#>
-- @return 
function Node:addCamera(body)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:21
-- <#Description#>
-- @return 
function Node:removeCamera()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getCamera()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getCamera()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:33
-- <#Description#>
-- @param body <#body description#>
-- @return 
function Node:addGeometry(body)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:36
-- <#Description#>
-- @return 
function Node:removeGeometry()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getGeometry()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getGeometry()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:48
-- <#Description#>
-- @param body <#body description#>
-- @return 
function Node:addPhysicsField(body)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:52
-- <#Description#>
-- @return 
function Node:removePhysicsField()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getPhysicsField()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getPhysicsField()
end

---- Brief description.
-- <#Description#>
-- @param sound <#sound description#>
-- @return <#return value description#>
function Node:addSound(sound)
end

---- Brief description.
-- <#Description#>
-- @param sound <#sound description#>
-- @return <#return value description#>
function Node:removeSound(sound)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:13
-- <#Description#>
-- @return 
function Node:removeAllSounds()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:17
-- <#Description#>
-- @param sounds <#sounds description#>
-- @return 
function Node:getSounds(sounds)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function Node:getSoundIndex(object)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Node:getSound(index)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Node:getSound(index)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:36
-- <#Description#>
-- @param opacity <#opacity description#>
-- @return 
function Node:setOpacity(opacity)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:54
-- <#Description#>
-- @param transfrom <#transfrom description#>
-- @return 
function Node:transformVertices(transfrom)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:57
-- <#Description#>
-- @param transform <#transform description#>
-- @return 
function Node:transformVertexColors(transform)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:03
-- <#Description#>
-- @param transform <#transform description#>
-- @return 
function Node:transformTextureCoordinates(transform)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getOpacity()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:hasOpacity()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:17
-- <#Description#>
-- @param camera <#camera description#>
-- @return 
function Node:hide(camera)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:11
-- <#Description#>
-- @param camera <#camera description#>
-- @return 
function Node:show(camera)
end

---- Brief description.
-- <#Description#>
-- @param camera <#camera description#>
-- @return <#return value description#>
function Node:isHidden(camera)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:17
-- <#Description#>
-- @param node <#node description#>
-- @return 
function Node:setRenderCategory(node)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getStateMachine()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getStateMachine()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:27
-- <#Description#>
-- @return 
function Node:removeStateMachine()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:isTouched()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:34
-- <#Description#>
-- @param enable <#enable description#>
-- @return 
function Node:enableTouched(enable)
end

---- Brief description.
-- <#Description#>
-- @param from <#from description#>
-- @param to <#to description#>
-- @param rayContact <#rayContact description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function Node:rayTestClosest(from, to, rayContact, collisionGroup, collisionMask)
end

---- Brief description.
-- <#Description#>
-- @param from <#from description#>
-- @param to <#to description#>
-- @param rayContacts <#rayContacts description#>
-- @param numContacts <#numContacts description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function Node:rayTestAll(from, to, rayContacts, numContacts, collisionGroup, collisionMask)
end

---- Brief description.
-- <#Description#>
-- @param screenPosition <#screenPosition description#>
-- @param rayContact <#rayContact description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function Node:rayTestClosest(screenPosition, rayContact, collisionGroup, collisionMask)
end

---- Brief description.
-- <#Description#>
-- @param screenPosition <#screenPosition description#>
-- @param rayContacts <#rayContacts description#>
-- @param numContacts <#numContacts description#>
-- @param collisionGroup <#collisionGroup description#>
-- @param collisionMask <#collisionMask description#>
-- @return <#return value description#>
function Node:rayTestAll(screenPosition, rayContacts, numContacts, collisionGroup, collisionMask)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:57
-- <#Description#>
-- @param action <#action description#>
-- @param callCompletionFunction <#callCompletionFunction description#>
-- @return 
function Node:runAction(action, callCompletionFunction)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:02
-- <#Description#>
-- @param action <#action description#>
-- @param key <#key description#>
-- @param callCompletionFunction <#callCompletionFunction description#>
-- @return 
function Node:runAction(action, key, callCompletionFunction)
end

---- Brief description.
-- <#Description#>
-- @param key <#key description#>
-- @return <#return value description#>
function Node:removeAction(key)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:08
-- <#Description#>
-- @return 
function Node:removeAllActions()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:12
-- <#Description#>
-- @param aabbMin <#aabbMin description#>
-- @param aabbMax <#aabbMax description#>
-- @return 
function Node:getAabb(aabbMin, aabbMax)
end

---- Brief description.
-- <#Description#>
-- <#Description#>
-- <#Description#>
-- <#Description#>
-- <#Description#>
-- @return <#return value description#>
function Node:getParentNode()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:getParentNode()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:hasParentNode()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:30
-- <#Description#>
-- @param parent <#parent description#>
-- @return 
function Node:setParentNode(parent)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:40
-- <#Description#>
-- @return 
function Node:removeParentNode()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:removeFromParentNode()
end

---- Brief description.
-- <#Description#>
-- @param name <#name description#>
-- @return <#return value description#>
function Node:findChildNode(name)
end

---- Brief description.
-- <#Description#>
-- @param name <#name description#>
-- @return <#return value description#>
function Node:findChildNode(name)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Node:getChildNode(index)
end

---- Brief description.
-- <#Description#>
-- @param index <#index description#>
-- @return <#return value description#>
function Node:getChildNode(index)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:08
-- <#Description#>
-- @param children <#children description#>
-- @return 
function Node:getChildrenNodes(children)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function Node:getChildNodeIndex(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function Node:hasChildNode(object)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:hasChildrenNodes()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:29
-- <#Description#>
-- @param object <#object description#>
-- @return 
function Node:addChildNode(object)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:34
-- <#Description#>
-- @param index <#index description#>
-- @return 
function Node:removeChildNode(index)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:38
-- <#Description#>
-- @param object <#object description#>
-- @return 
function Node:removeChildNode(object)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:43
-- <#Description#>
-- @return 
function Node:removeChildrenNodes()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function Node:numberOfChildrenNodes()
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:50
-- <#Description#>
-- @param oldChild <#oldChild description#>
-- @param newChild <#newChild description#>
-- @return 
function Node:replaceChildNode(oldChild, newChild)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function NJLI.Node.createArray(size)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:13
-- <#Description#>
-- @param array <#array description#>
-- @param size <#size description#>
-- @return 
function NJLI.Node.destroyArray(array, size)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Node.create()
end

---- Brief description.
-- <#Description#>
-- @param builder <#builder description#>
-- @return <#return value description#>
function NJLI.Node.create(builder)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Node.clone(object)
end

---- Brief description.
-- <#Description#>
-- @param object <#object description#>
-- @return <#return value description#>
function NJLI.Node.copy(object)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:41
-- <#Description#>
-- @param object <#object description#>
-- @param destroyChildrenNodes <#destroyChildrenNodes description#>
-- @return 
function NJLI.Node.destroy(object, destroyChildrenNodes)
end

---- Brief description.
-- @author James Folk, 16-02-10 21:02:46
-- <#Description#>
-- @param object <#object description#>
-- @param L <#L description#>
-- @param stack_index <#stack_index description#>
-- @return 
function NJLI.Node.load(object, L, stack_index)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function NJLI.Node.type()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.Node.updateActions()
end

