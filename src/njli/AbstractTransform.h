//
//  AbstractTransform.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__AbstractTransform__
#define __JLIGameEngineTest__AbstractTransform__

class btTransform;
class btVector2;
class btVector3;
class btVector4;
class btQuaternion;
#include "Util.h"

namespace njli
{
    class AbstractTransform
    {
    public:
        /**
         *  <#Description#>
         */
        AbstractTransform();
        /**
         *  <#Description#>
         */
        AbstractTransform(const AbstractTransform &copy);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual ~AbstractTransform();
        
        /**
         *  <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
        AbstractTransform &operator=(const AbstractTransform &rhs);
        
        /**
         *  The transformation is the combination of the node’s rotation, position, and scale properties. The default transformation is SCNMatrix4Identity.
         
         When you set the value of this property, the node’s rotation, orientation, eulerAngles, position, and scale properties automatically change to match the new transform, and vice versa. JLIEngine can perform this conversion only if the transform you provide is a combination of rotation, translation, and scale operations. If you set the value of this property to a skew transformation or to a nonaffine transformation, the values of these properties become undefined. Setting a new value for any of these properties causes JLIEngine to compute a new transformation, discarding any skew or nonaffine operations in the original transformation.
         *
         *  @return The Transform for this instance.
         */
        btTransform &getTransform()const;
        /**
         *  <#Description#>
         *
         *  @param transform <#transform description#>
         */
        virtual void setTransform(const btTransform &transform);
        
        /**
         *  The node’s position locates it within the coordinate system of its parent, as modified by the node’s pivot property. The default position is the zero vector, indicating that the node is placed at the origin of the parent node’s coordinate system.
         *
         *  @return The Origin for this instance.
         */
        virtual btVector3 &getOrigin()const;
        /**
         *  <#Description#>
         *
         *  @param origin <#origin description#>
         */
        virtual void setOrigin(const btVector3 &origin);
        /**
         *  <#Description#>
         *
         *  @param origin <#origin description#>
         */
        virtual void setOrigin(const btVector2 &origin);
        
        /**
         *   The four-component rotation vector specifies the direction of the rotation axis in the first three components and the angle of rotation (in radians) in the fourth. The default rotation is the zero vector, specifying no rotation. Rotation is applied relative to the node’s pivot property.
         
         The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
         *
         *  @return the Rotation for this instance.
         */
        btQuaternion getRotation()const;
        /**
         *  <#Description#>
         *
         *  @param rotation <#rotation description#>
         */
        virtual void setRotation(const btQuaternion &rotation);
        
        /**
         *   Roll is the rotation about the node’s z-axis, yaw is the rotation about the node’s y-axis, and pitch is the rotation about the node’s x-axis. Rotation is applied relative to the node’s pivot property.
         *
         *  @return The Euler Angles for this instance.
         */
        btVector3 getEulerAngles()const;
        /**
         *  <#Description#>
         *
         *  @param angles <#angles description#>
         */
        virtual void setEulerAngles(const btVector3 &angles);
        
        /**
         *  The rotation, eulerAngles, and orientation properties all affect the rotational aspect of its transform property. Any change to one of these properties is reflected in the others.
         *
         *  @return The Orientation for this instance.
         */
        btQuaternion &getOrientation()const;
        /**
         *  <#Description#>
         *
         *  @param orientation <#orientation description#>
         */
        void setOrientation(const btQuaternion &orientation);
        
        /**
         *  Each component of the scale vector multiplies the corresponding dimension of the node’s geometry. The default scale is 1.0 in all three dimensions. For example, applying a scale of (2.0, 0.5, 2.0) to a node containing a cube geometry reduces its height and increases its width and depth. Scaling is applied relative to the node’s pivot property.
         *
         *  @return The scale for this instance.
         */
        btVector3 getScale()const;
        /**
         *  <#Description#>
         *
         *  @param scale <#scale description#>
         */
        virtual void setScale(const btVector3 &scale);
        
        /**
         *  <#Description#>
         *
         *  @param scale <#scale description#>
         */
        virtual void setScale(const f32 scale);
        
        /**
         *  A node’s pivot is the transformation between its coordinate space and that used by its position, rotation, and scale properties. The default pivot is SCNMatrix4Identity, specifying that the node’s position locates the origin of its coordinate system, its rotation is about an axis through its center, and its scale is also relative to that center point.
         
         Changing the pivot transform alters these behaviors in many useful ways. You can:
         
         Offset the node’s contents relative to its position. For example, by setting the pivot to a translation transform you can position a node containing a sphere geometry relative to where the sphere would rest on a floor instead of relative to its center.
         
         Move the node’s axis of rotation. For example, with a translation transform you can cause a node to revolve around a faraway point instead of rotating around its center, and with a rotation transform you can tilt the axis of rotation.
         
         Adjust the center point and direction for scaling the node. For example, with a translation transform you can cause a node to grow or shrink relative to a corner instead of to its center.
         *
         *  @return The Pivot for this instance.
         */
        btTransform &getPivot()const;
        /**
         *  <#Description#>
         *
         *  @param pivot <#pivot description#>
         */
        virtual void setPivot(const btTransform &pivot);
        
        /**
         *  A world transform is the node’s coordinate space transformation relative to the scene’s coordinate space. This transformation is the concatenation of the node’s transform property with that of its parent node, the parent’s parent, and so on up to the rootNode object of the scene.
         *
         *  @return The World Transform for this instance.
         */
        virtual btTransform getWorldTransform()const = 0;
        
    private:
        btTransform *m_WorldTransform;
        btQuaternion *m_Orientation;
        btTransform *m_Pivot;
    };

}
#endif /* defined(__JLIGameEngineTest__AbstractTransform__) */
