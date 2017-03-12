//
//  WorldFactory.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/9/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_WorldFactory_h
#define JLIGameEngineTest_WorldFactory_h

#include "Util.h"

#include "btAlignedObjectArray.h"
#include "btHashMap.h"
#include "btSerializer.h"

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"

#include <map>
#include <queue>
#include <string>
#include <vector>

#include "JLIFactoryTypes.h"

namespace njli {
/// <#Description#>
class WorldFactory : public AbstractObject {

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    typedef std::vector<AbstractFactoryObject*> ObjectList;
    typedef std::vector<AbstractFactoryObject**> ObjectArrayList;
    typedef std::pair<u64, s32> ObjectDuplicatePair;
    typedef std::map<u64, s32> ObjectDuplicateMap;

public:
    friend class AbstractFactoryObject;

    friend class Action;
    friend class ActionBuilder;
    friend class ButtonHUD;
    friend class ButtonHUDBuilder;
    friend class Camera;
    friend class CameraBuilder;
    friend class CheckboxHUD;
    friend class CheckboxHUDBuilder;
    friend class Clock;
    friend class ClockBuilder;
    friend class CollisionResponse;
    friend class CollisionResponseBuilder;
    friend class Cube;
    friend class CubeBuilder;
    friend class DropdownHUD;
    friend class DropdownHUDBuilder;
    friend class Font;
    friend class FontBuilder;
    friend class Geometry;
    friend class Image;
    friend class ImageBuilder;
    friend class JsonJLI;
    friend class JsonJLIBuilder;
    friend class LabelHUD;
    friend class LabelHUDBuilder;
    friend class Light;
    friend class LightBuilder;
    friend class LevelOfDetail;
    friend class LevelOfDetailBuilder;
    friend class Lua;
    friend class LuaBuilder;
    friend class Material;
    friend class MaterialBuilder;
    friend class MaterialProperty;
    friend class MaterialPropertyBuilder;
    friend class Node;
    friend class NodeBuilder;
    friend class NodeState;
    friend class NodeStateBuilder;
    friend class NodeStateMachine;
    friend class NodeStateMachineBuilder;
    friend class ParticleEmitter;
    friend class ParticleEmitterBuilder;
    friend class PhysicsBody;
    friend class PhysicsBodyGhost;
    friend class PhysicsBodyGhostBuilder;
    friend class PhysicsBodyRigid;
    friend class PhysicsBodyRigidBuilder;
    friend class PhysicsBodySoft;
    friend class PhysicsBodySoftBuilder;
    friend class PhysicsCloseContact;
    friend class PhysicsCloseContactBuilder;
    friend class PhysicsConstraint;
    friend class PhysicsConstraintBuilder;
    friend class PhysicsConstraintHinge;
    friend class PhysicsConstraintHingeBuilder;
    friend class PhysicsConstraintPointToPoint;
    friend class PhysicsConstraintPointToPointBuilder;

    friend class PhysicsConstraintSlider;
    friend class PhysicsConstraintSliderBuilder;
    friend class PhysicsConstraintConeTwist;
    friend class PhysicsConstraintConeTwistBuilder;
    friend class PhysicsConstraintFixed;
    friend class PhysicsConstraintFixedBuilder;
    friend class PhysicsConstraintGeneric6Dof;
    friend class PhysicsConstraintGeneric6DofBuilder;
    friend class PhysicsConstraintGeneric6DofSpring;
    friend class PhysicsConstraintGeneric6DofSpringBuilder;

    friend class PhysicsContact;
    friend class PhysicsContactBuilder;
    friend class PhysicsField;
    friend class PhysicsFieldBuilder;
    friend class PhysicsRayContact;
    friend class PhysicsRayContactBuilder;
    friend class PhysicsShape;
    friend class PhysicsShapeBox;
    friend class PhysicsShapeBoxBuilder;
    friend class PhysicsShapeBox2D;
    friend class PhysicsShapeBox2DBuilder;

    friend class PhysicsShapeSphere;
    friend class PhysicsShapeSphereBuilder;
    friend class PhysicsShapeCylinder;
    friend class PhysicsShapeCylinderBuilder;
    friend class PhysicsShapeCapsule;
    friend class PhysicsShapeCapsuleBuilder;
    friend class PhysicsShapeCone;
    friend class PhysicsShapeConeBuilder;
    friend class PhysicsShapeMultiSphere;
    friend class PhysicsShapeMultiSphereBuilder;
    friend class PhysicsShapeConvexHull;
    friend class PhysicsShapeConvexHullBuilder;
    friend class PhysicsShapeConvexTriangleMesh;
    friend class PhysicsShapeConvexTriangleMeshBuilder;
    friend class PhysicsShapeBvhTriangleMesh;
    friend class PhysicsShapeBvhTriangleMeshBuilder;
    friend class PhysicsShapeHeightfieldTerrain;
    friend class PhysicsShapeHeightfieldTerrainBuilder;
    friend class PhysicsShapeStaticPlane;
    friend class PhysicsShapeStaticPlaneBuilder;

    friend class PhysicsWorld;
    friend class PhysicsWorldBuilder;
    friend class Plane;
    friend class PlaneBuilder;
    friend class Scene;
    friend class SceneBuilder;
    friend class SceneState;
    friend class SceneStateBuilder;
    friend class SceneStateMachine;
    friend class SceneStateMachineBuilder;
    friend class ShaderProgram;
    friend class ShaderProgramBuilder;
    friend class Skinner;
    friend class SkinnerBuilder;
    friend class SliderHUD;
    friend class SliderHUDBuilder;
    friend class Sound;
    friend class SoundBuilder;
    friend class Sprite2D;
    friend class Sprite2DBuilder;
    friend class SpriteFrameAtlas;
    friend class SpriteFrameAtlasBuilder;
    
    friend class SteeringBehavior;
    friend class SteeringBehaviorBuilder;
    
    friend class SteeringBehaviorAlignment;
    friend class SteeringBehaviorAlignmentBuilder;
    friend class SteeringBehaviorArrive;
    friend class SteeringBehaviorArriveBuilder;
    friend class SteeringBehaviorCohesion;
    friend class SteeringBehaviorCohesionBuilder;
    friend class SteeringBehaviorEvade;
    friend class SteeringBehaviorEvadeBuilder;
    friend class SteeringBehaviorFlee;
    friend class SteeringBehaviorFleeBuilder;
    friend class SteeringBehaviorFollowPath;
    friend class SteeringBehaviorFollowPathBuilder;
    friend class SteeringBehaviorHide;
    friend class SteeringBehaviorHideBuilder;
    friend class SteeringBehaviorInterpose;
    friend class SteeringBehaviorInterposeBuilder;
    
    friend class SteeringBehaviorMachine;
    friend class SteeringBehaviorMachineBuilder;
    friend class SteeringBehaviorMachineDithered;
    friend class SteeringBehaviorMachineDitheredBuilder;
    friend class SteeringBehaviorMachinePrioritized;
    friend class SteeringBehaviorMachinePrioritizedBuilder;
    friend class SteeringBehaviorMachineWeighted;
    friend class SteeringBehaviorMachineWeightedBuilder;
    
    friend class SteeringBehaviorObstacleAvoidance;
    friend class SteeringBehaviorObstacleAvoidanceBuilder;
    friend class SteeringBehaviorOffsetPursuit;
    friend class SteeringBehaviorOffsetPursuitBuilder;
    friend class SteeringBehaviorPursuit;
    friend class SteeringBehaviorPursuitBuilder;
    friend class SteeringBehaviorSeek;
    friend class SteeringBehaviorSeekBuilder;
    friend class SteeringBehaviorSeparation;
    friend class SteeringBehaviorSeparationBuilder;
    friend class SteeringBehaviorWallAvoidance;
    friend class SteeringBehaviorWallAvoidanceBuilder;
    friend class SteeringBehaviorWander;
    friend class SteeringBehaviorWanderBuilder;
    
    friend class StopWatch;
    friend class StopWatchBuilder;
    friend class TextboxHUD;
    friend class TextboxHUDBuilder;
    friend class Timer;
    friend class TimerBuilder;
    friend class Thread;
    friend class ThreadBuilder;
    friend class WorldState;
    friend class WorldStateBuilder;
    friend class WorldStateMachine;
    friend class WorldStateMachineBuilder;
    friend class Xml;
    friend class XmlBuilder;
    friend class World;

protected:
    /**
         *  <#Description#>
         *
         *  @param type <#type description#>
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject** createArray(const u32 type, const u32 size);
    /**
         *  <#Description#>
         *
         *  @param type <#type description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* create(const u32 type);
    /**
         *  <#Description#>
         *
         *  @param  <# description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* create(const AbstractBuilder&);
    /**
         *  <#Description#>
         *
         *  @param      <# description#>
         *  @param bool <#bool description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* clone(const AbstractFactoryObject&, bool = false);

public:
    /**
         *  @author James Folk, 16-02-11 17:02:52
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    virtual bool has(AbstractFactoryObject* object) const;

protected:
    /**
         *  <#Description#>
         *
         *  @param AbstractFactoryObject <#AbstractFactoryObject description#>
         *  @param array                 <#array description#>
         */
    virtual void destroy(AbstractFactoryObject*, bool array = false);
    /**
         *  <#Description#>
         *
         *  @param AbstractFactoryObject <#AbstractFactoryObject description#>
         */
    virtual void destroyArray(AbstractFactoryObject**, const u32, bool isRenderObject = false);

public:
    /**
         *  <#Description#>
         */
    virtual void destroyAll();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 size();

    /**
         *  @author James Folk, 16-02-11 17:02:05
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 numberOfReferences(AbstractFactoryObject* object);

    /**
         *  <#Description#>
         *
         *  @param u32 <#u32 description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* get(const u32) const;

    /**
         *  @author James Folk, 16-02-11 17:02:19
         *
         *  @brief <#Description#>
         *
         *  @param objects <#objects description#>
         */
    virtual void getAll(std::vector<AbstractFactoryObject*>& objects) const;

    /**
         *  @author James Folk, 16-02-11 17:02:32
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 index(AbstractFactoryObject* object) const;

    /**
         *  <#Description#>
         *
         *  @param serializer <#serializer description#>
         */
    virtual void serialize(btSerializer* serializer);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const;

    /**
         *  <#Description#>
         *
         *  @param u32 <#u32 description#>
         *
         *  @return <#return value description#>
         */
    bool isBuilder(u32);

protected:
    /**
         *  <#Description#>
         */
    WorldFactory();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~WorldFactory();

    /**
         *  @author James Folk, 16-02-11 18:02:34
         *
         *  @brief <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* ctor(const u32& size);

    /**
         *  @author James Folk, 16-02-11 18:02:59
         *
         *  @brief <#Description#>
         *
         *  @param idx  <#idx description#>
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject** ctor(const u32& idx, u32 size);

    /**
         *  @author James Folk, 16-02-11 17:02:49
         *
         *  @brief <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* ctor(const njli::AbstractBuilder& rhs);

    /**
         *  @author James Folk, 16-02-11 17:02:05
         *
         *  @brief <#Description#>
         *
         *  @param rhs <#rhs description#>
         *
         *  @return <#return value description#>
         */
    virtual AbstractFactoryObject* ctor(const AbstractFactoryObject& rhs);

    /**
         *  <#Description#>
         *
         *  @param u32 <#u32 description#>
         *
         *  @return <#return value description#>
         */
    AbstractFactoryObject* create_Internal(const u32);
    /**
         *  <#Description#>
         *
         *  @param  <# description#>
         *
         *  @return <#return value description#>
         */
    AbstractFactoryObject* create_Internal(const AbstractBuilder&);
    /**
         *  <#Description#>
         *
         *  @param      <# description#>
         *  @param bool <#bool description#>
         *
         *  @return <#return value description#>
         */
    AbstractFactoryObject* clone_Internal(const AbstractFactoryObject&, bool);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    s32 numberOfObjects_Internal() const;
    /**
         *  <#Description#>
         *
         *  @param AbstractFactoryObject <#AbstractFactoryObject description#>
         */
    bool removeObject_Internal(AbstractFactoryObject*);
    /**
         *  <#Description#>
         *
         *  @param AbstractFactoryObject <#AbstractFactoryObject description#>
         */
    void addObject_Internal(AbstractFactoryObject*);

    s32 numberOfArrayObjects_Internal() const;
    /**
         *  <#Description#>
         *
         *  @param AbstractFactoryObject <#AbstractFactoryObject description#>
         */
    void removeArrayObject_Internal(AbstractFactoryObject**);
    /**
         *  <#Description#>
         *
         *  @param AbstractFactoryObject <#AbstractFactoryObject description#>
         */
    void addArrayObject_Internal(AbstractFactoryObject**);

    /**
         *  <#Description#>
         *
         *  @param AbstractFactoryObject <#AbstractFactoryObject description#>
         *
         *  @return <#return value description#>
         */
    s32 numberOfReferences_Internal(AbstractFactoryObject*);

    /**
         *  remove an instance from the object duplication map
         *
         *  @param AbstractFactoryObject the object
         *
         *  @return returns true if the instance shoudl be removed from rhe ObjecdtArrayList
         */
    bool removeReference_Internal(AbstractFactoryObject*);

    /**
         *  add an instance to the object duplication map
         *
         *  @param AbstractFactoryObject the object
         *
         *  @return returns true if the instance shoudl be added to the ObjecdtArrayList;
         */
    bool addReference_Internal(AbstractFactoryObject*);
public:
    void collectGarbage();
    s64 collectGarbageSize() const;
    void collectGarbage_GPU();
    s64 collectGarbage_GPUSize() const;

private:
    ObjectList m_ObjectList;
    ObjectArrayList m_ObjectArrayList;
    ObjectDuplicateMap m_ObjectDuplicateMap;

    std::vector<AbstractFactoryObject*> m_ObjectsToDelete;
    std::vector<AbstractFactoryObject**> m_ArrayObjectsToDelete;

    std::vector<AbstractFactoryObject*> m_ObjectsToDelete_GPU;
    std::vector<AbstractFactoryObject**> m_ArrayObjectsToDelete_GPU;
};
}

#endif
