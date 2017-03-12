
//
//  WorldFactory.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "WorldFactory.h"

#include "World.h"
#include "JLIFactoryTypes.h"
//#include "JLITransform.h"
#include "PhysicsBody.h"
#include "PhysicsShape.h"
#include "Geometry.h"
#include "PhysicsConstraint.h"

#include "Log.h"
#define TAG "WorldFactory.cpp"
#define FORMATSTRING "{\"njli::WorldFactory\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#pragma mark Start AbstractFactoryObjects includes

#include "Action.h"
#include "ActionBuilder.h"
#include "ButtonHUD.h"
#include "ButtonHUDBuilder.h"
#include "Camera.h"
#include "CameraBuilder.h"
#include "CheckboxHUD.h"
#include "CheckboxHUDBuilder.h"
#include "Clock.h"
#include "ClockBuilder.h"
#include "CollisionResponse.h"
#include "CollisionResponseBuilder.h"
#include "Cube.h"
#include "CubeBuilder.h"
#include "DropdownHUD.h"
#include "DropdownHUDBuilder.h"
#include "Font.h"
#include "FontBuilder.h"
#include "Image.h"
#include "ImageBuilder.h"
#include "JsonJLI.h"
#include "JsonJLIBuilder.h"
#include "LabelHUD.h"
#include "LabelHUDBuilder.h"
#include "Light.h"
#include "LightBuilder.h"
#include "LevelOfDetail.h"
#include "LevelOfDetailBuilder.h"
#include "Lua.h"
//#include "LuaBuilder.h"
#include "Material.h"
#include "MaterialBuilder.h"
#include "MaterialProperty.h"
#include "MaterialPropertyBuilder.h"
#include "Node.h"
#include "NodeBuilder.h"
#include "NodeState.h"
#include "NodeStateBuilder.h"
#include "NodeStateMachine.h"
#include "NodeStateMachineBuilder.h"
#include "ParticleEmitter.h"
#include "ParticleEmitterBuilder.h"
#include "PhysicsBodyGhost.h"
#include "PhysicsBodyGhostBuilder.h"
#include "PhysicsBodyRigid.h"
#include "PhysicsBodyRigidBuilder.h"
#include "PhysicsBodySoft.h"
#include "PhysicsBodySoftBuilder.h"
#include "PhysicsCloseContact.h"
#include "PhysicsCloseContactBuilder.h"
#include "PhysicsConstraintBuilder.h"
#include "PhysicsConstraintHinge.h"
#include "PhysicsConstraintHingeBuilder.h"
#include "PhysicsConstraintPointToPoint.h"
#include "PhysicsConstraintPointToPointBuilder.h"

#include "PhysicsConstraintSlider.h"
#include "PhysicsConstraintSliderBuilder.h"
#include "PhysicsConstraintConeTwist.h"
#include "PhysicsConstraintConeTwistBuilder.h"
#include "PhysicsConstraintFixed.h"
#include "PhysicsConstraintFixedBuilder.h"
#include "PhysicsConstraintGeneric6Dof.h"
#include "PhysicsConstraintGeneric6DofBuilder.h"
#include "PhysicsConstraintGeneric6DofSpring.h"
#include "PhysicsConstraintGeneric6DofSpringBuilder.h"

#include "PhysicsContact.h"
#include "PhysicsContactBuilder.h"
#include "PhysicsField.h"
#include "PhysicsFieldBuilder.h"
#include "PhysicsRayContact.h"
#include "PhysicsRayContactBuilder.h"
#include "PhysicsShapeBox.h"
#include "PhysicsShapeBoxBuilder.h"
#include "PhysicsShapeBox2D.h"
#include "PhysicsShapeBox2DBuilder.h"

#include "PhysicsShapeSphere.h"
#include "PhysicsShapeSphereBuilder.h"
#include "PhysicsShapeCylinder.h"
#include "PhysicsShapeCylinderBuilder.h"
#include "PhysicsShapeCapsule.h"
#include "PhysicsShapeCapsuleBuilder.h"
#include "PhysicsShapeCone.h"
#include "PhysicsShapeConeBuilder.h"
#include "PhysicsShapeMultiSphere.h"
#include "PhysicsShapeMultiSphereBuilder.h"
#include "PhysicsShapeConvexHull.h"
#include "PhysicsShapeConvexHullBuilder.h"
#include "PhysicsShapeConvexTriangleMesh.h"
#include "PhysicsShapeConvexTriangleMeshBuilder.h"
#include "PhysicsShapeBvhTriangleMesh.h"
#include "PhysicsShapeBvhTriangleMeshBuilder.h"
#include "PhysicsShapeHeightfieldTerrain.h"
#include "PhysicsShapeHeightfieldTerrainBuilder.h"
#include "PhysicsShapeStaticPlane.h"
#include "PhysicsShapeStaticPlaneBuilder.h"

#include "PhysicsWorld.h"
#include "PhysicsWorldBuilder.h"
#include "Plane.h"
#include "PlaneBuilder.h"
#include "Scene.h"
#include "SceneBuilder.h"
#include "SceneState.h"
#include "SceneStateBuilder.h"
#include "SceneStateMachine.h"
#include "SceneStateMachineBuilder.h"
#include "ShaderProgram.h"
#include "ShaderProgramBuilder.h"
#include "Skinner.h"
#include "SkinnerBuilder.h"
#include "SliderHUD.h"
#include "SliderHUDBuilder.h"
#include "Sound.h"
#include "SoundBuilder.h"
#include "Sprite2D.h"
#include "Sprite2DBuilder.h"
#include "SpriteFrameAtlas.h"
#include "SpriteFrameAtlasBuilder.h"





#include "SteeringBehavior.h"
#include "SteeringBehaviorBuilder.h"
#include "SteeringBehaviorAlignment.h"
#include "SteeringBehaviorAlignmentBuilder.h"
#include "SteeringBehaviorArrive.h"
#include "SteeringBehaviorArriveBuilder.h"
#include "SteeringBehaviorCohesion.h"
#include "SteeringBehaviorCohesionBuilder.h"
#include "SteeringBehaviorEvade.h"
#include "SteeringBehaviorEvadeBuilder.h"
#include "SteeringBehaviorFlee.h"
#include "SteeringBehaviorFleeBuilder.h"
#include "SteeringBehaviorFollowPath.h"
#include "SteeringBehaviorFollowPathBuilder.h"
#include "SteeringBehaviorHide.h"
#include "SteeringBehaviorHideBuilder.h"
#include "SteeringBehaviorInterpose.h"
#include "SteeringBehaviorInterposeBuilder.h"
#include "SteeringBehaviorMachine.h"
#include "SteeringBehaviorMachineBuilder.h"
#include "SteeringBehaviorMachineDithered.h"
#include "SteeringBehaviorMachineDitheredBuilder.h"
#include "SteeringBehaviorMachinePrioritized.h"
#include "SteeringBehaviorMachinePrioritizedBuilder.h"
#include "SteeringBehaviorMachineWeighted.h"
#include "SteeringBehaviorMachineWeightedBuilder.h"
#include "SteeringBehaviorObstacleAvoidance.h"
#include "SteeringBehaviorObstacleAvoidanceBuilder.h"
#include "SteeringBehaviorOffsetPursuit.h"
#include "SteeringBehaviorOffsetPursuitBuilder.h"
#include "SteeringBehaviorPursuit.h"
#include "SteeringBehaviorPursuitBuilder.h"
#include "SteeringBehaviorSeek.h"
#include "SteeringBehaviorSeekBuilder.h"
#include "SteeringBehaviorSeparation.h"
#include "SteeringBehaviorSeparationBuilder.h"
#include "SteeringBehaviorWallAvoidance.h"
#include "SteeringBehaviorWallAvoidanceBuilder.h"
#include "SteeringBehaviorWander.h"
#include "SteeringBehaviorWanderBuilder.h"






#include "StopWatch.h"
#include "StopWatchBuilder.h"
#include "TextboxHUD.h"
#include "TextboxHUDBuilder.h"
#include "Timer.h"
#include "TimerBuilder.h"
#include "Thread.h"
#include "ThreadBuilder.h"
#include "WorldState.h"
#include "WorldStateBuilder.h"
#include "WorldStateMachine.h"
#include "WorldStateMachineBuilder.h"
#include "Xml.h"
#include "XmlBuilder.h"

#pragma mark End AbstractFactoryObjects includes

namespace njli
{
    AbstractFactoryObject **WorldFactory::createArray(const u32 type, const u32 size)
    {
        AbstractFactoryObject **object = ctor(type, size);
        addArrayObject_Internal(object);
        return object;
    }
    
    AbstractFactoryObject *WorldFactory::create(const u32 type)
    {
        return create_Internal(type);
    }
    AbstractFactoryObject *WorldFactory::create(const AbstractBuilder &builder)
    {
        return create_Internal(builder);
    }
    
    AbstractFactoryObject *WorldFactory::clone(const AbstractFactoryObject &object, bool share)
    {
        return clone_Internal(object, share);
    }
    
    bool WorldFactory::has(AbstractFactoryObject *object)const
    {
        return (m_ObjectList.size() != index(object));
    }
    
    /*
     std::vector<AbstractFactoryObject*> m_ObjectsToDelete;
     std::vector<AbstractFactoryObject**> m_ArrayObjectsToDelete;
     */
    void WorldFactory::destroy(AbstractFactoryObject *object, bool array)
    {
        if(object)
        {
            if (object->isRenderObject())
                m_ObjectsToDelete_GPU.push_back(object);
            else
                m_ObjectsToDelete.push_back(object);
        }
        
    }
    
    void WorldFactory::destroyArray(AbstractFactoryObject **object, const u32 size, bool isRenderObject)
    {
        for (s32 i = 0; i < size; ++i)
        {
            destroy(object[i]);
        }
        if (isRenderObject)
            m_ArrayObjectsToDelete_GPU.push_back(object);
        else
            m_ArrayObjectsToDelete.push_back(object);
        
    }
    void WorldFactory::destroyAll()
    {
//        m_ObjectDuplicateMap.clear();
//        
        while (m_ObjectList.size() > 0)
        {
            destroy(m_ObjectList.back());
            m_ObjectList.pop_back();
        }
        m_ObjectList.clear();
        
        collectGarbage();
        collectGarbage_GPU();
        
        
//        size = m_ObjectArrayList.size();
//        while (m_ObjectArrayList.size() > 0)
//        {
//            destroyArray(m_ObjectArrayList.at(0));
//        }
//        m_ObjectArrayList.clear();
//        
////        World::getInstance()->removeAllNodes();
////        World::getInstance()->removeAllCameras();
//        World::getInstance()->getWorldResourceLoader()->unLoadAll();
    }
    
    s32 WorldFactory::size()
    {
        return m_ObjectList.size();
    }
    
    s32 WorldFactory::numberOfReferences(AbstractFactoryObject *object)
    {
        return numberOfReferences_Internal(object);
    }
    
    AbstractFactoryObject *WorldFactory::get(const u32 index)const
    {
        DEBUG_ASSERT_WRITE(index < m_ObjectList.size(), "index must be smaller than the size of the array");
        
        return m_ObjectList.at(index);
    }
    
    void WorldFactory::getAll(std::vector<AbstractFactoryObject*> &objects)const
    {
        objects = m_ObjectList;
    }
    
    s32 WorldFactory::index(AbstractFactoryObject *object)const
    {
        DEBUG_ASSERT_WRITE(object, "object is null");
        
        ObjectList::const_iterator iter = std::find(m_ObjectList.begin(), m_ObjectList.end(), object);
        if (iter != m_ObjectList.end())
        {
            return std::distance(m_ObjectList.begin(), iter);
        }
        return -1;
    }
    
    void WorldFactory::serialize(btSerializer* serializer)
    {
        for (s32 i = 0; i < m_ObjectList.size(); i++)
        {
            m_ObjectList[i]->serializeObject(serializer);
        }
    }
    
    const char *WorldFactory::getClassName()const
    {
        return "WorldFactory";
    }
    
    s32 WorldFactory::getType()const
    {
        return JLI_OBJECT_TYPE_WorldFactory;
    }
    
    WorldFactory::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    bool WorldFactory::isBuilder(u32 type)
    {
        switch (type)
        {
            case JLI_OBJECT_TYPE_ActionBuilder:
            case JLI_OBJECT_TYPE_CameraBuilder:
            case JLI_OBJECT_TYPE_ClockBuilder:
            case JLI_OBJECT_TYPE_CollisionResponseBuilder:
            case JLI_OBJECT_TYPE_CubeBuilder:
            case JLI_OBJECT_TYPE_FontBuilder:
            case JLI_OBJECT_TYPE_ImageBuilder:
            case JLI_OBJECT_TYPE_JsonJLIBuilder:
            case JLI_OBJECT_TYPE_LightBuilder:
            case JLI_OBJECT_TYPE_LevelOfDetailBuilder:
//            case JLI_OBJECT_TYPE_LuaBuilder:
            case JLI_OBJECT_TYPE_MaterialBuilder:
            case JLI_OBJECT_TYPE_MaterialPropertyBuilder:
            case JLI_OBJECT_TYPE_NodeBuilder:
            case JLI_OBJECT_TYPE_NodeStateBuilder:
            case JLI_OBJECT_TYPE_NodeStateMachineBuilder:
            case JLI_OBJECT_TYPE_ParticleEmitterBuilder:
            case JLI_OBJECT_TYPE_PhysicsBodyGhostBuilder:
            case JLI_OBJECT_TYPE_PhysicsBodyRigidBuilder:
            case JLI_OBJECT_TYPE_PhysicsBodySoftBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintHingeBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPointBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintSliderBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintConeTwistBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintFixedBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofBuilder:
            case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpringBuilder:
            case JLI_OBJECT_TYPE_PhysicsContactBuilder:
            case JLI_OBJECT_TYPE_PhysicsCloseContactBuilder:
            case JLI_OBJECT_TYPE_PhysicsFieldBuilder:
            case JLI_OBJECT_TYPE_PhysicsRayContactBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeBoxBuilder:
                case JLI_OBJECT_TYPE_PhysicsShapeBox2DBuilder:
                
            case JLI_OBJECT_TYPE_PhysicsShapeSphereBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeCylinderBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeCapsuleBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeConeBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeMultiSphereBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeConvexHullBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMeshBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMeshBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrainBuilder:
            case JLI_OBJECT_TYPE_PhysicsShapeStaticPlaneBuilder:

                
                
            case JLI_OBJECT_TYPE_PhysicsWorldBuilder:
            case JLI_OBJECT_TYPE_PlaneBuilder:
            case JLI_OBJECT_TYPE_SceneBuilder:
            case JLI_OBJECT_TYPE_SceneStateBuilder:
            case JLI_OBJECT_TYPE_SceneStateMachineBuilder:
            case JLI_OBJECT_TYPE_ShaderProgramBuilder:
            case JLI_OBJECT_TYPE_SkinnerBuilder:
            case JLI_OBJECT_TYPE_SoundBuilder:
            case JLI_OBJECT_TYPE_Sprite2DBuilder:
            case JLI_OBJECT_TYPE_SpriteFrameAtlasBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorAlignmentBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorArriveBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorCohesionBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorFleeBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorFollowPathBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorHideBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineDitheredBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritizedBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeightedBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidanceBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuitBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorPursuitBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorSeekBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorSeparationBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidanceBuilder:
            case JLI_OBJECT_TYPE_SteeringBehaviorWanderBuilder:
            case JLI_OBJECT_TYPE_StopWatchBuilder:
            case JLI_OBJECT_TYPE_TimerBuilder:
            case JLI_OBJECT_TYPE_ThreadBuilder:
            case JLI_OBJECT_TYPE_WorldStateBuilder:
            case JLI_OBJECT_TYPE_WorldStateMachineBuilder:
            case JLI_OBJECT_TYPE_XmlBuilder:
            case JLI_OBJECT_TYPE_ButtonHUDBuilder:
            case JLI_OBJECT_TYPE_CheckboxHUDBuilder:
            case JLI_OBJECT_TYPE_DropdownHUDBuilder:
            case JLI_OBJECT_TYPE_LabelHUDBuilder:
            case JLI_OBJECT_TYPE_SliderHUDBuilder:
            case JLI_OBJECT_TYPE_TextboxHUDBuilder:
                return true;
        }
        
        return false;
    }
    
    WorldFactory::WorldFactory()
    {

    }
    
    WorldFactory::~WorldFactory()
    {
        DEBUG_ASSERT_WRITE(size() == 0, "WorldFactory is not empty.");
    }
    
    AbstractFactoryObject **WorldFactory::ctor(const u32 &type, u32 size)
    {
        AbstractFactoryObject **obj = NULL;
        
        switch (type)
        {
            case JLI_OBJECT_TYPE_Action:
            {
                Action **_obj = new Action*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Action::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ActionBuilder:
            {
                ActionBuilder **_obj = new ActionBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ActionBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ButtonHUD:
            {
                ButtonHUD **_obj = new ButtonHUD*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ButtonHUD::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ButtonHUDBuilder:
            {
                ButtonHUDBuilder **_obj = new ButtonHUDBuilder*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ButtonHUDBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Camera:
            {
                Camera **_obj = new Camera*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Camera::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_CameraBuilder:
            {
                CameraBuilder **_obj = new CameraBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = CameraBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_CheckboxHUD:
            {
                CheckboxHUD **_obj = new CheckboxHUD*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = CheckboxHUD::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_CheckboxHUDBuilder:
            {
                CheckboxHUDBuilder **_obj = new CheckboxHUDBuilder*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = CheckboxHUDBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Clock:
            {
                Clock **_obj = new Clock*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Clock::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ClockBuilder:
            {
                ClockBuilder **_obj = new ClockBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ClockBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_CollisionResponse:
            {
                CollisionResponse **_obj = new CollisionResponse*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = CollisionResponse::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_CollisionResponseBuilder:
            {
                CollisionResponseBuilder **_obj = new CollisionResponseBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = CollisionResponseBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Cube:
            {
                Cube **_obj = new Cube*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Cube::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_CubeBuilder:
            {
                CubeBuilder **_obj = new CubeBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = CubeBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_DropdownHUD:
            {
                DropdownHUD **_obj = new DropdownHUD*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = DropdownHUD::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_DropdownHUDBuilder:
            {
                DropdownHUDBuilder **_obj = new DropdownHUDBuilder*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = DropdownHUDBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Font:
            {
                Font **_obj = new Font*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Font::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_FontBuilder:
            {
                FontBuilder **_obj = new FontBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = FontBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Image:
            {
                Image **_obj = new Image*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Image::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ImageBuilder:
            {
                ImageBuilder **_obj = new ImageBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ImageBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_JsonJLI:
            {
                JsonJLI **_obj = new JsonJLI*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = JsonJLI::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_JsonJLIBuilder:
            {
                JsonJLIBuilder **_obj = new JsonJLIBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = JsonJLIBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_LabelHUD:
            {
                LabelHUD **_obj = new LabelHUD*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = LabelHUD::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_LabelHUDBuilder:
            {
                LabelHUDBuilder **_obj = new LabelHUDBuilder*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = LabelHUDBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Light:
            {
                Light **_obj = new Light*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Light::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_LightBuilder:
            {
                LightBuilder **_obj = new LightBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = LightBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_LevelOfDetail:
            {
                LevelOfDetail **_obj = new LevelOfDetail*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = LevelOfDetail::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_LevelOfDetailBuilder:
            {
                LevelOfDetailBuilder **_obj = new LevelOfDetailBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = LevelOfDetailBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
//            case JLI_OBJECT_TYPE_Lua:
//            {
//                Lua **_obj = new Lua*[size];
//                for (s32 i = 0; i < size; ++i)
//                {
//                    _obj[i] = Lua::create();
//                }
//                obj = (AbstractFactoryObject**)_obj;
//            }
//                break;
//            case JLI_OBJECT_TYPE_LuaBuilder:
//            {
//                LuaBuilder **_obj = new LuaBuilder*[size];
//                for (s32 i = 0; i < size; ++i)
//                {
//                    _obj[i] = LuaBuilder::create();
//                }
//                obj = (AbstractFactoryObject**)_obj;
//            }
//                break;
            case JLI_OBJECT_TYPE_Material:
            {
                Material **_obj = new Material*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Material::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_MaterialBuilder:
            {
                MaterialBuilder **_obj = new MaterialBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = MaterialBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_MaterialProperty:
            {
                MaterialProperty **_obj = new MaterialProperty*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = MaterialProperty::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_MaterialPropertyBuilder:
            {
                MaterialPropertyBuilder **_obj = new MaterialPropertyBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = MaterialPropertyBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Node:
            {
                Node **_obj = new Node*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Node::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_NodeBuilder:
            {
                NodeBuilder **_obj = new NodeBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = NodeBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_NodeState:
            {
                NodeState **_obj = new NodeState*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = NodeState::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_NodeStateBuilder:
            {
                NodeStateBuilder **_obj = new NodeStateBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = NodeStateBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_NodeStateMachine:
            {
                NodeStateMachine **_obj = new NodeStateMachine*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = NodeStateMachine::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_NodeStateMachineBuilder:
            {
                NodeStateMachineBuilder **_obj = new NodeStateMachineBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = NodeStateMachineBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ParticleEmitter:
            {
                ParticleEmitter **_obj = new ParticleEmitter*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ParticleEmitter::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ParticleEmitterBuilder:
            {
                ParticleEmitterBuilder **_obj = new ParticleEmitterBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ParticleEmitterBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyGhost:
            {
                PhysicsBodyGhost **_obj = new PhysicsBodyGhost*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsBodyGhost::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyGhostBuilder:
            {
                PhysicsBodyGhostBuilder **_obj = new PhysicsBodyGhostBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsBodyGhostBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyRigid:
            {
                PhysicsBodyRigid **_obj = new PhysicsBodyRigid*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsBodyRigid::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyRigidBuilder:
            {
                PhysicsBodyRigidBuilder **_obj = new PhysicsBodyRigidBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsBodyRigidBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsBodySoft:
            {
                PhysicsBodySoft **_obj = new PhysicsBodySoft*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsBodySoft::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsBodySoftBuilder:
            {
                PhysicsBodySoftBuilder **_obj = new PhysicsBodySoftBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsBodySoftBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraint:
            {
                PhysicsConstraint **_obj = new PhysicsConstraint*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraint::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintBuilder:
            {
                PhysicsConstraintBuilder **_obj = new PhysicsConstraintBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintHinge:
            {
                PhysicsConstraintHinge **_obj = new PhysicsConstraintHinge*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintHinge::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintHingeBuilder:
            {
                PhysicsConstraintHingeBuilder **_obj = new PhysicsConstraintHingeBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintHingeBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint:
            {
                PhysicsConstraintPointToPoint **_obj = new PhysicsConstraintPointToPoint*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintPointToPoint::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPointBuilder:
            {
                PhysicsConstraintPointToPointBuilder **_obj = new PhysicsConstraintPointToPointBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintPointToPointBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
                
                
            case JLI_OBJECT_TYPE_PhysicsConstraintSlider:
            {
                PhysicsConstraintSlider **_obj = new PhysicsConstraintSlider*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintSlider::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintSliderBuilder:
            {
                PhysicsConstraintSliderBuilder **_obj = new PhysicsConstraintSliderBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintSliderBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintConeTwist:
            {
                PhysicsConstraintConeTwist **_obj = new PhysicsConstraintConeTwist*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintConeTwist::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintConeTwistBuilder:
            {
                PhysicsConstraintConeTwistBuilder **_obj = new PhysicsConstraintConeTwistBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintConeTwistBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintFixed:
            {
                PhysicsConstraintFixed **_obj = new PhysicsConstraintFixed*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintFixed::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintFixedBuilder:
            {
                PhysicsConstraintFixedBuilder **_obj = new PhysicsConstraintFixedBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintFixedBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6Dof:
            {
                PhysicsConstraintGeneric6Dof **_obj = new PhysicsConstraintGeneric6Dof*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintGeneric6Dof::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofBuilder:
            {
                PhysicsConstraintGeneric6DofBuilder **_obj = new PhysicsConstraintGeneric6DofBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintGeneric6DofBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpring:
            {
                PhysicsConstraintGeneric6DofSpring **_obj = new PhysicsConstraintGeneric6DofSpring*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintGeneric6DofSpring::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpringBuilder:
            {
                PhysicsConstraintGeneric6DofSpringBuilder **_obj = new PhysicsConstraintGeneric6DofSpringBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsConstraintGeneric6DofSpringBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsContact:
            {
                PhysicsContact **_obj = new PhysicsContact*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsContact::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsContactBuilder:
            {
                PhysicsContactBuilder **_obj = new PhysicsContactBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsContactBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsCloseContact:
            {
                PhysicsCloseContact **_obj = new PhysicsCloseContact*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsCloseContact::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsCloseContactBuilder:
            {
                PhysicsCloseContactBuilder **_obj = new PhysicsCloseContactBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsCloseContactBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsField:
            {
                PhysicsField **_obj = new PhysicsField*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsField::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsFieldBuilder:
            {
                PhysicsFieldBuilder **_obj = new PhysicsFieldBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsFieldBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsRayContact:
            {
                PhysicsRayContact **_obj = new PhysicsRayContact*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsRayContact::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsRayContactBuilder:
            {
                PhysicsRayContactBuilder **_obj = new PhysicsRayContactBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsRayContactBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox:
            {
                PhysicsShapeBox **_obj = new PhysicsShapeBox*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsShapeBox::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBoxBuilder:
            {
                PhysicsShapeBoxBuilder **_obj = new PhysicsShapeBoxBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsShapeBoxBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox2D:
            {
                PhysicsShapeBox2D **_obj = new PhysicsShapeBox2D*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsShapeBox2D::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox2DBuilder:
            {
                PhysicsShapeBox2DBuilder **_obj = new PhysicsShapeBox2DBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsShapeBox2DBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
	    case JLI_OBJECT_TYPE_PhysicsShapeSphere:
		{
			PhysicsShapeSphere **_obj = new PhysicsShapeSphere*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeSphere::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeSphereBuilder:
		{
			PhysicsShapeSphereBuilder **_obj = new PhysicsShapeSphereBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeSphereBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCylinder:
		{
			PhysicsShapeCylinder **_obj = new PhysicsShapeCylinder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeCylinder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCylinderBuilder:
		{
			PhysicsShapeCylinderBuilder **_obj = new PhysicsShapeCylinderBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeCylinderBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCapsule:
		{
			PhysicsShapeCapsule **_obj = new PhysicsShapeCapsule*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeCapsule::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCapsuleBuilder:
		{
			PhysicsShapeCapsuleBuilder **_obj = new PhysicsShapeCapsuleBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeCapsuleBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCone:
		{
			PhysicsShapeCone **_obj = new PhysicsShapeCone*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeCone::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConeBuilder:
		{
			PhysicsShapeConeBuilder **_obj = new PhysicsShapeConeBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeConeBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeMultiSphere:
		{
			PhysicsShapeMultiSphere **_obj = new PhysicsShapeMultiSphere*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeMultiSphere::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeMultiSphereBuilder:
		{
			PhysicsShapeMultiSphereBuilder **_obj = new PhysicsShapeMultiSphereBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeMultiSphereBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexHull:
		{
			PhysicsShapeConvexHull **_obj = new PhysicsShapeConvexHull*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeConvexHull::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexHullBuilder:
		{
			PhysicsShapeConvexHullBuilder **_obj = new PhysicsShapeConvexHullBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeConvexHullBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMesh:
		{
			PhysicsShapeConvexTriangleMesh **_obj = new PhysicsShapeConvexTriangleMesh*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeConvexTriangleMesh::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMeshBuilder:
		{
			PhysicsShapeConvexTriangleMeshBuilder **_obj = new PhysicsShapeConvexTriangleMeshBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeConvexTriangleMeshBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMesh:
		{
			PhysicsShapeBvhTriangleMesh **_obj = new PhysicsShapeBvhTriangleMesh*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeBvhTriangleMesh::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMeshBuilder:
		{
			PhysicsShapeBvhTriangleMeshBuilder **_obj = new PhysicsShapeBvhTriangleMeshBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeBvhTriangleMeshBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrain:
		{
			PhysicsShapeHeightfieldTerrain **_obj = new PhysicsShapeHeightfieldTerrain*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeHeightfieldTerrain::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrainBuilder:
		{
			PhysicsShapeHeightfieldTerrainBuilder **_obj = new PhysicsShapeHeightfieldTerrainBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeHeightfieldTerrainBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeStaticPlane:
		{
			PhysicsShapeStaticPlane **_obj = new PhysicsShapeStaticPlane*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeStaticPlane::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeStaticPlaneBuilder:
		{
			PhysicsShapeStaticPlaneBuilder **_obj = new PhysicsShapeStaticPlaneBuilder*[size];
			for(s32 i = 0; i < size; ++i)
			{
                _obj[i] = PhysicsShapeStaticPlaneBuilder::create();
			}
			obj = (AbstractFactoryObject**)_obj;
		}
		break;  
            case JLI_OBJECT_TYPE_PhysicsWorld:
            {
                PhysicsWorld **_obj = new PhysicsWorld*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsWorld::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PhysicsWorldBuilder:
            {
                PhysicsWorldBuilder **_obj = new PhysicsWorldBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PhysicsWorldBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Plane:
            {
                Plane **_obj = new Plane*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Plane::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_PlaneBuilder:
            {
                PlaneBuilder **_obj = new PlaneBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = PlaneBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Scene:
            {
                Scene **_obj = new Scene*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Scene::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SceneBuilder:
            {
                SceneBuilder **_obj = new SceneBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SceneBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SceneState:
            {
                SceneState **_obj = new SceneState*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SceneState::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SceneStateBuilder:
            {
                SceneStateBuilder **_obj = new SceneStateBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SceneStateBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SceneStateMachine:
            {
                SceneStateMachine **_obj = new SceneStateMachine*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SceneStateMachine::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SceneStateMachineBuilder:
            {
                SceneStateMachineBuilder **_obj = new SceneStateMachineBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SceneStateMachineBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ShaderProgram:
            {
                ShaderProgram **_obj = new ShaderProgram*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ShaderProgram::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ShaderProgramBuilder:
            {
                ShaderProgramBuilder **_obj = new ShaderProgramBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ShaderProgramBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Skinner:
            {
                Skinner **_obj = new Skinner*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Skinner::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SkinnerBuilder:
            {
                SkinnerBuilder **_obj = new SkinnerBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SkinnerBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SliderHUD:
            {
                SliderHUD **_obj = new SliderHUD*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SliderHUD::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SliderHUDBuilder:
            {
                SliderHUDBuilder **_obj = new SliderHUDBuilder*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SliderHUDBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Sound:
            {
                Sound **_obj = new Sound*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Sound::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SoundBuilder:
            {
                SoundBuilder **_obj = new SoundBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SoundBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Sprite2D:
            {
                Sprite2D **_obj = new Sprite2D*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Sprite2D::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Sprite2DBuilder:
            {
                Sprite2DBuilder **_obj = new Sprite2DBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Sprite2DBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SpriteFrameAtlas:
            {
                SpriteFrameAtlas **_obj = new SpriteFrameAtlas*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SpriteFrameAtlas::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SpriteFrameAtlasBuilder:
            {
                SpriteFrameAtlasBuilder **_obj = new SpriteFrameAtlasBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SpriteFrameAtlasBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_SteeringBehavior:
                {
                SteeringBehavior **_obj = new SteeringBehavior*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehavior::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorBuilder:
                {
                SteeringBehaviorBuilder **_obj = new SteeringBehaviorBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorAlignment:
                {
                SteeringBehaviorAlignment **_obj = new SteeringBehaviorAlignment*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorAlignment::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorAlignmentBuilder:
                {
                SteeringBehaviorAlignmentBuilder **_obj = new SteeringBehaviorAlignmentBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorAlignmentBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorArrive:
                {
                SteeringBehaviorArrive **_obj = new SteeringBehaviorArrive*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorArrive::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorArriveBuilder:
                {
                SteeringBehaviorArriveBuilder **_obj = new SteeringBehaviorArriveBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorArriveBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorCohesion:
                {
                SteeringBehaviorCohesion **_obj = new SteeringBehaviorCohesion*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorCohesion::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorCohesionBuilder:
                {
                SteeringBehaviorCohesionBuilder **_obj = new SteeringBehaviorCohesionBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorCohesionBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorEvade:
                {
                SteeringBehaviorEvade **_obj = new SteeringBehaviorEvade*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorEvade::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder:
                {
                SteeringBehaviorEvadeBuilder **_obj = new SteeringBehaviorEvadeBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorEvadeBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorFlee:
                {
                SteeringBehaviorFlee **_obj = new SteeringBehaviorFlee*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorFlee::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorFleeBuilder:
                {
                SteeringBehaviorFleeBuilder **_obj = new SteeringBehaviorFleeBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorFleeBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorFollowPath:
                {
                SteeringBehaviorFollowPath **_obj = new SteeringBehaviorFollowPath*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorFollowPath::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorFollowPathBuilder:
                {
                SteeringBehaviorFollowPathBuilder **_obj = new SteeringBehaviorFollowPathBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorFollowPathBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorHide:
                {
                SteeringBehaviorHide **_obj = new SteeringBehaviorHide*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorHide::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorHideBuilder:
                {
                SteeringBehaviorHideBuilder **_obj = new SteeringBehaviorHideBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorHideBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorInterpose:
                {
                SteeringBehaviorInterpose **_obj = new SteeringBehaviorInterpose*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorInterpose::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder:
                {
                SteeringBehaviorInterposeBuilder **_obj = new SteeringBehaviorInterposeBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorInterposeBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachine:
                {
                SteeringBehaviorMachine **_obj = new SteeringBehaviorMachine*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachine::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineBuilder:
                {
                SteeringBehaviorMachineBuilder **_obj = new SteeringBehaviorMachineBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachineBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineDithered:
                {
                SteeringBehaviorMachineDithered **_obj = new SteeringBehaviorMachineDithered*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachineDithered::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineDitheredBuilder:
                {
                SteeringBehaviorMachineDitheredBuilder **_obj = new SteeringBehaviorMachineDitheredBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachineDitheredBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritized:
                {
                SteeringBehaviorMachinePrioritized **_obj = new SteeringBehaviorMachinePrioritized*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachinePrioritized::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritizedBuilder:
                {
                SteeringBehaviorMachinePrioritizedBuilder **_obj = new SteeringBehaviorMachinePrioritizedBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachinePrioritizedBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeighted:
                {
                SteeringBehaviorMachineWeighted **_obj = new SteeringBehaviorMachineWeighted*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachineWeighted::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeightedBuilder:
                {
                SteeringBehaviorMachineWeightedBuilder **_obj = new SteeringBehaviorMachineWeightedBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorMachineWeightedBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidance:
                {
                SteeringBehaviorObstacleAvoidance **_obj = new SteeringBehaviorObstacleAvoidance*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorObstacleAvoidance::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidanceBuilder:
                {
                SteeringBehaviorObstacleAvoidanceBuilder **_obj = new SteeringBehaviorObstacleAvoidanceBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorObstacleAvoidanceBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuit:
                {
                SteeringBehaviorOffsetPursuit **_obj = new SteeringBehaviorOffsetPursuit*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorOffsetPursuit::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuitBuilder:
                {
                SteeringBehaviorOffsetPursuitBuilder **_obj = new SteeringBehaviorOffsetPursuitBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorOffsetPursuitBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorPursuit:
                {
                SteeringBehaviorPursuit **_obj = new SteeringBehaviorPursuit*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorPursuit::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorPursuitBuilder:
                {
                SteeringBehaviorPursuitBuilder **_obj = new SteeringBehaviorPursuitBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorPursuitBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorSeek:
                {
                SteeringBehaviorSeek **_obj = new SteeringBehaviorSeek*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorSeek::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorSeekBuilder:
                {
                SteeringBehaviorSeekBuilder **_obj = new SteeringBehaviorSeekBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorSeekBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorSeparation:
                {
                SteeringBehaviorSeparation **_obj = new SteeringBehaviorSeparation*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorSeparation::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorSeparationBuilder:
                {
                SteeringBehaviorSeparationBuilder **_obj = new SteeringBehaviorSeparationBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorSeparationBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidance:
                {
                SteeringBehaviorWallAvoidance **_obj = new SteeringBehaviorWallAvoidance*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorWallAvoidance::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidanceBuilder:
                {
                SteeringBehaviorWallAvoidanceBuilder **_obj = new SteeringBehaviorWallAvoidanceBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorWallAvoidanceBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorWander:
                {
                SteeringBehaviorWander **_obj = new SteeringBehaviorWander*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorWander::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_SteeringBehaviorWanderBuilder:
                {
                SteeringBehaviorWanderBuilder **_obj = new SteeringBehaviorWanderBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = SteeringBehaviorWanderBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
                }
                break;
            case JLI_OBJECT_TYPE_StopWatch:
            {
                StopWatch **_obj = new StopWatch*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = StopWatch::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_StopWatchBuilder:
            {
                StopWatchBuilder **_obj = new StopWatchBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = StopWatchBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_TextboxHUD:
            {
                TextboxHUD **_obj = new TextboxHUD*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = TextboxHUD::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_TextboxHUDBuilder:
            {
                TextboxHUDBuilder **_obj = new TextboxHUDBuilder*[size];
                for(s32 i = 0; i < size; ++i)
                {
                    _obj[i] = TextboxHUDBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Timer:
            {
                Timer **_obj = new Timer*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Timer::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_TimerBuilder:
            {
                TimerBuilder **_obj = new TimerBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = TimerBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Thread:
            {
                Thread **_obj = new Thread*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Thread::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_ThreadBuilder:
            {
                ThreadBuilder **_obj = new ThreadBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = ThreadBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_WorldState:
            {
                WorldState **_obj = new WorldState*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = WorldState::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_WorldStateBuilder:
            {
                WorldStateBuilder **_obj = new WorldStateBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = WorldStateBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_WorldStateMachine:
            {
                WorldStateMachine **_obj = new WorldStateMachine*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = WorldStateMachine::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_WorldStateMachineBuilder:
            {
                WorldStateMachineBuilder **_obj = new WorldStateMachineBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = WorldStateMachineBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_Xml:
            {
                Xml **_obj = new Xml*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = Xml::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            case JLI_OBJECT_TYPE_XmlBuilder:
            {
                XmlBuilder **_obj = new XmlBuilder*[size];
                for (s32 i = 0; i < size; ++i)
                {
                    _obj[i] = XmlBuilder::create();
                }
                obj = (AbstractFactoryObject**)_obj;
            }
                break;
            default:
                obj = NULL;
                break;
        }
        
        return obj;
    }
    
    AbstractFactoryObject *WorldFactory::ctor(const u32 &type)
    {
        AbstractFactoryObject *obj = NULL;
        
        switch (type)
        {
            case JLI_OBJECT_TYPE_Action:
                    obj = new Action();
                break;
            case JLI_OBJECT_TYPE_ActionBuilder:
                    obj = new ActionBuilder();
                break;
            case JLI_OBJECT_TYPE_ButtonHUD:
                obj = new ButtonHUD();
                break;
            case JLI_OBJECT_TYPE_ButtonHUDBuilder:
                obj = new ButtonHUDBuilder();
                break;
            case JLI_OBJECT_TYPE_Camera:
                    obj = new Camera();
                break;
            case JLI_OBJECT_TYPE_CameraBuilder:
                    obj = new CameraBuilder();
                break;
            case JLI_OBJECT_TYPE_CheckboxHUD:
                obj = new CheckboxHUD();
                break;
            case JLI_OBJECT_TYPE_CheckboxHUDBuilder:
                obj = new CheckboxHUDBuilder();
                break;
            case JLI_OBJECT_TYPE_Clock:
                    obj = new Clock();
                break;
            case JLI_OBJECT_TYPE_ClockBuilder:
                    obj = new ClockBuilder();
                break;
            case JLI_OBJECT_TYPE_CollisionResponse:
                    obj = new CollisionResponse();
                break;
            case JLI_OBJECT_TYPE_CollisionResponseBuilder:
                    obj = new CollisionResponseBuilder();
                break;
            case JLI_OBJECT_TYPE_Cube:
                    obj = new Cube();
                break;
            case JLI_OBJECT_TYPE_CubeBuilder:
                    obj = new CubeBuilder();
                break;
            case JLI_OBJECT_TYPE_DropdownHUD:
                obj = new DropdownHUD();
                break;
            case JLI_OBJECT_TYPE_DropdownHUDBuilder:
                obj = new DropdownHUDBuilder();
                break;
            case JLI_OBJECT_TYPE_Font:
                    obj = new Font();
                break;
            case JLI_OBJECT_TYPE_FontBuilder:
                    obj = new FontBuilder();
                break;
            case JLI_OBJECT_TYPE_Image:
                    obj = new Image();
                break;
            case JLI_OBJECT_TYPE_ImageBuilder:
                    obj = new ImageBuilder();
                break;
            case JLI_OBJECT_TYPE_JsonJLI:
                    obj = new JsonJLI();
                break;
            case JLI_OBJECT_TYPE_JsonJLIBuilder:
                    obj = new JsonJLIBuilder();
                break;
            case JLI_OBJECT_TYPE_LabelHUD:
                obj = new LabelHUD();
                break;
            case JLI_OBJECT_TYPE_LabelHUDBuilder:
                obj = new LabelHUDBuilder();
                break;
            case JLI_OBJECT_TYPE_Light:
                    obj = new Light();
                break;
            case JLI_OBJECT_TYPE_LightBuilder:
                    obj = new LightBuilder();
                break;
            case JLI_OBJECT_TYPE_LevelOfDetail:
                    obj = new LevelOfDetail();
                break;
            case JLI_OBJECT_TYPE_LevelOfDetailBuilder:
                    obj = new LevelOfDetailBuilder();
                break;
//            case JLI_OBJECT_TYPE_Lua:
//                    obj = new Lua();
//                break;
//            case JLI_OBJECT_TYPE_LuaBuilder:
//                    obj = new LuaBuilder();
//                break;
            case JLI_OBJECT_TYPE_Material:
                    obj = new Material();
                break;
            case JLI_OBJECT_TYPE_MaterialBuilder:
                    obj = new MaterialBuilder();
                break;
            case JLI_OBJECT_TYPE_MaterialProperty:
                    obj = new MaterialProperty();
                break;
            case JLI_OBJECT_TYPE_MaterialPropertyBuilder:
                    obj = new MaterialPropertyBuilder();
                break;
            case JLI_OBJECT_TYPE_Node:
                    obj = new Node();
                break;
            case JLI_OBJECT_TYPE_NodeBuilder:
                    obj = new NodeBuilder();
                break;
            case JLI_OBJECT_TYPE_NodeState:
                    obj = new NodeState();
                break;
            case JLI_OBJECT_TYPE_NodeStateBuilder:
                    obj = new NodeStateBuilder();
                break;
            case JLI_OBJECT_TYPE_NodeStateMachine:
                    obj = new NodeStateMachine();
                break;
            case JLI_OBJECT_TYPE_NodeStateMachineBuilder:
                    obj = new NodeStateMachineBuilder();
                break;
            case JLI_OBJECT_TYPE_ParticleEmitter:
                    obj = new ParticleEmitter();
                break;
            case JLI_OBJECT_TYPE_ParticleEmitterBuilder:
                    obj = new ParticleEmitterBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyGhost:
                    obj = new PhysicsBodyGhost();
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyGhostBuilder:
                    obj = new PhysicsBodyGhostBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyRigid:
                    obj = new PhysicsBodyRigid();
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyRigidBuilder:
                    obj = new PhysicsBodyRigidBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsBodySoft:
                    obj = new PhysicsBodySoft();
                break;
            case JLI_OBJECT_TYPE_PhysicsBodySoftBuilder:
                    obj = new PhysicsBodySoftBuilder();
                break;
//            case JLI_OBJECT_TYPE_PhysicsConstraint:
//                obj = new PhysicsConstraint();
//                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintBuilder:
                obj = new PhysicsConstraintBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintHinge:
                obj = new PhysicsConstraintHinge();
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintHingeBuilder:
                obj = new PhysicsConstraintHingeBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint:
                obj = new PhysicsConstraintPointToPoint();
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPointBuilder:
                obj = new PhysicsConstraintPointToPointBuilder();
                break;
                
                
	    case JLI_OBJECT_TYPE_PhysicsConstraintSlider:
		obj = new PhysicsConstraintSlider();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintSliderBuilder:
		obj = new PhysicsConstraintSliderBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintConeTwist:
		obj = new PhysicsConstraintConeTwist();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintConeTwistBuilder:
		obj = new PhysicsConstraintConeTwistBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintFixed:
		obj = new PhysicsConstraintFixed();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintFixedBuilder:
		obj = new PhysicsConstraintFixedBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6Dof:
		obj = new PhysicsConstraintGeneric6Dof();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofBuilder:
		obj = new PhysicsConstraintGeneric6DofBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpring:
		obj = new PhysicsConstraintGeneric6DofSpring();
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpringBuilder:
		obj = new PhysicsConstraintGeneric6DofSpringBuilder();
		break;

            case JLI_OBJECT_TYPE_PhysicsCloseContact:
                    obj = new PhysicsCloseContact();
                break;
            case JLI_OBJECT_TYPE_PhysicsCloseContactBuilder:
                    obj = new PhysicsCloseContactBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsContact:
                    obj = new PhysicsContact();
                break;
            case JLI_OBJECT_TYPE_PhysicsContactBuilder:
                    obj = new PhysicsContactBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsField:
                    obj = new PhysicsField();
                break;
            case JLI_OBJECT_TYPE_PhysicsFieldBuilder:
                    obj = new PhysicsFieldBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsRayContact:
                    obj = new PhysicsRayContact();
                break;
            case JLI_OBJECT_TYPE_PhysicsRayContactBuilder:
                    obj = new PhysicsRayContactBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox:
                    obj = new PhysicsShapeBox();
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBoxBuilder:
                    obj = new PhysicsShapeBoxBuilder();
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox2D:
                obj = new PhysicsShapeBox2D();
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox2DBuilder:
                obj = new PhysicsShapeBox2DBuilder();
                break;
                
	    case JLI_OBJECT_TYPE_PhysicsShapeSphere:
		obj = new PhysicsShapeSphere();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeSphereBuilder:
		obj = new PhysicsShapeSphereBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCylinder:
		obj = new PhysicsShapeCylinder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCylinderBuilder:
		obj = new PhysicsShapeCylinderBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCapsule:
		obj = new PhysicsShapeCapsule();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCapsuleBuilder:
		obj = new PhysicsShapeCapsuleBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCone:
		obj = new PhysicsShapeCone();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConeBuilder:
		obj = new PhysicsShapeConeBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeMultiSphere:
		obj = new PhysicsShapeMultiSphere();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeMultiSphereBuilder:
		obj = new PhysicsShapeMultiSphereBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexHull:
		obj = new PhysicsShapeConvexHull();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexHullBuilder:
		obj = new PhysicsShapeConvexHullBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMesh:
		obj = new PhysicsShapeConvexTriangleMesh();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMeshBuilder:
		obj = new PhysicsShapeConvexTriangleMeshBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMesh:
		obj = new PhysicsShapeBvhTriangleMesh();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMeshBuilder:
		obj = new PhysicsShapeBvhTriangleMeshBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrain:
		obj = new PhysicsShapeHeightfieldTerrain();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrainBuilder:
		obj = new PhysicsShapeHeightfieldTerrainBuilder();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeStaticPlane:
		obj = new PhysicsShapeStaticPlane();
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeStaticPlaneBuilder:
		obj = new PhysicsShapeStaticPlaneBuilder();
		break;

                
                
            case JLI_OBJECT_TYPE_PhysicsWorld:
                    obj = new PhysicsWorld();
                break;
            case JLI_OBJECT_TYPE_PhysicsWorldBuilder:
                    obj = new PhysicsWorldBuilder();
                break;
            case JLI_OBJECT_TYPE_Plane:
                    obj = new Plane();
                break;
            case JLI_OBJECT_TYPE_PlaneBuilder:
                    obj = new PlaneBuilder();
                break;
            case JLI_OBJECT_TYPE_Scene:
                    obj = new Scene();
                break;
            case JLI_OBJECT_TYPE_SceneBuilder:
                    obj = new SceneBuilder();
                break;
            case JLI_OBJECT_TYPE_SceneState:
                    obj = new SceneState();
                break;
            case JLI_OBJECT_TYPE_SceneStateBuilder:
                    obj = new SceneStateBuilder();
                break;
            case JLI_OBJECT_TYPE_SceneStateMachine:
                    obj = new SceneStateMachine();
                break;
            case JLI_OBJECT_TYPE_SceneStateMachineBuilder:
                    obj = new SceneStateMachineBuilder();
                break;
            case JLI_OBJECT_TYPE_ShaderProgram:
                    obj = new ShaderProgram();
                break;
            case JLI_OBJECT_TYPE_ShaderProgramBuilder:
                    obj = new ShaderProgramBuilder();
                break;
            case JLI_OBJECT_TYPE_Skinner:
                    obj = new Skinner();
                break;
                case JLI_OBJECT_TYPE_SkinnerBuilder:
                    obj = new SkinnerBuilder();
                break;
            case JLI_OBJECT_TYPE_SliderHUD:
                obj = new SliderHUD();
                break;
            case JLI_OBJECT_TYPE_SliderHUDBuilder:
                obj = new SliderHUDBuilder();
                break;
            case JLI_OBJECT_TYPE_Sound:
                    obj = new Sound();
                break;
            case JLI_OBJECT_TYPE_SoundBuilder:
                    obj = new SoundBuilder();
                break;
            case JLI_OBJECT_TYPE_Sprite2D:
                    obj = new Sprite2D();
                break;
            case JLI_OBJECT_TYPE_Sprite2DBuilder:
                    obj = new Sprite2DBuilder();
                break;
            case JLI_OBJECT_TYPE_SpriteFrameAtlas:
                    obj = new SpriteFrameAtlas();
                break;
            case JLI_OBJECT_TYPE_SpriteFrameAtlasBuilder:
                    obj = new SpriteFrameAtlasBuilder();
                break;
//                case JLI_OBJECT_TYPE_SteeringBehavior:
//                obj = new SteeringBehavior();
//                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorBuilder:
                obj = new SteeringBehaviorBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorAlignment:
                obj = new SteeringBehaviorAlignment();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorAlignmentBuilder:
                obj = new SteeringBehaviorAlignmentBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorArrive:
                obj = new SteeringBehaviorArrive();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorArriveBuilder:
                obj = new SteeringBehaviorArriveBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorCohesion:
                obj = new SteeringBehaviorCohesion();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorCohesionBuilder:
                obj = new SteeringBehaviorCohesionBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorEvade:
                obj = new SteeringBehaviorEvade();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder:
                obj = new SteeringBehaviorEvadeBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFlee:
                obj = new SteeringBehaviorFlee();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFleeBuilder:
                obj = new SteeringBehaviorFleeBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFollowPath:
                obj = new SteeringBehaviorFollowPath();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFollowPathBuilder:
                obj = new SteeringBehaviorFollowPathBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorHide:
                obj = new SteeringBehaviorHide();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorHideBuilder:
                obj = new SteeringBehaviorHideBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorInterpose:
                obj = new SteeringBehaviorInterpose();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder:
                obj = new SteeringBehaviorInterposeBuilder();
                break;
//                case JLI_OBJECT_TYPE_SteeringBehaviorMachine:
//                obj = new SteeringBehaviorMachine();
//                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineBuilder:
                obj = new SteeringBehaviorMachineBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineDithered:
                obj = new SteeringBehaviorMachineDithered();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineDitheredBuilder:
                obj = new SteeringBehaviorMachineDitheredBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritized:
                obj = new SteeringBehaviorMachinePrioritized();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritizedBuilder:
                obj = new SteeringBehaviorMachinePrioritizedBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeighted:
                obj = new SteeringBehaviorMachineWeighted();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeightedBuilder:
                obj = new SteeringBehaviorMachineWeightedBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidance:
                obj = new SteeringBehaviorObstacleAvoidance();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidanceBuilder:
                obj = new SteeringBehaviorObstacleAvoidanceBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuit:
                obj = new SteeringBehaviorOffsetPursuit();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuitBuilder:
                obj = new SteeringBehaviorOffsetPursuitBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorPursuit:
                obj = new SteeringBehaviorPursuit();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorPursuitBuilder:
                obj = new SteeringBehaviorPursuitBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeek:
                obj = new SteeringBehaviorSeek();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeekBuilder:
                obj = new SteeringBehaviorSeekBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeparation:
                obj = new SteeringBehaviorSeparation();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeparationBuilder:
                obj = new SteeringBehaviorSeparationBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidance:
                obj = new SteeringBehaviorWallAvoidance();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidanceBuilder:
                obj = new SteeringBehaviorWallAvoidanceBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWander:
                obj = new SteeringBehaviorWander();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWanderBuilder:
                obj = new SteeringBehaviorWanderBuilder();
                break;
            case JLI_OBJECT_TYPE_StopWatch:
                    obj = new StopWatch();
                break;
            case JLI_OBJECT_TYPE_StopWatchBuilder:
                    obj = new StopWatchBuilder();
                break;
            case JLI_OBJECT_TYPE_TextboxHUD:
                obj = new TextboxHUD();
                break;
            case JLI_OBJECT_TYPE_TextboxHUDBuilder:
                obj = new TextboxHUDBuilder();
                break;
            case JLI_OBJECT_TYPE_Timer:
                    obj = new Timer();
                break;
            case JLI_OBJECT_TYPE_TimerBuilder:
                    obj = new TimerBuilder();
                break;
            case JLI_OBJECT_TYPE_Thread:
                obj = new Thread();
                break;
            case JLI_OBJECT_TYPE_ThreadBuilder:
                obj = new ThreadBuilder();
                break;
            case JLI_OBJECT_TYPE_WorldState:
                    obj = new WorldState();
                break;
            case JLI_OBJECT_TYPE_WorldStateBuilder:
                    obj = new WorldStateBuilder();
                break;
            case JLI_OBJECT_TYPE_WorldStateMachine:
                    obj = new WorldStateMachine();
                break;
            case JLI_OBJECT_TYPE_WorldStateMachineBuilder:
                    obj = new WorldStateMachineBuilder();
                break;
            case JLI_OBJECT_TYPE_Xml:
                    obj = new Xml();
                break;
            case JLI_OBJECT_TYPE_XmlBuilder:
                    obj = new XmlBuilder();
                break;
            default:
                obj = NULL;
                break;
        }
        return obj;
    }
    
    AbstractFactoryObject *WorldFactory::ctor(const AbstractBuilder &builder)
    {
        AbstractFactoryObject *obj = NULL;
        
        switch (builder.getObjectType())
        {
            case JLI_OBJECT_TYPE_Action:
                obj = new Action(builder);
                break;
            case JLI_OBJECT_TYPE_ButtonHUD:
                obj = new ButtonHUD(builder);
                break;
            case JLI_OBJECT_TYPE_CheckboxHUD:
                obj = new CheckboxHUD(builder);
                break;
            case JLI_OBJECT_TYPE_Camera:
                obj = new Camera(builder);
                break;
            case JLI_OBJECT_TYPE_Clock:
                obj = new Clock(builder);
                break;
            case JLI_OBJECT_TYPE_CollisionResponse:
                obj = new CollisionResponse(builder);
                break;
            case JLI_OBJECT_TYPE_Cube:
                obj = new Cube(builder);
                break;
            case JLI_OBJECT_TYPE_DropdownHUD:
                obj = new DropdownHUD(builder);
                break;
            case JLI_OBJECT_TYPE_Font:
                obj = new Font(builder);
                break;
            case JLI_OBJECT_TYPE_Image:
                obj = new Image(builder);
                break;
            case JLI_OBJECT_TYPE_JsonJLI:
                obj = new JsonJLI(builder);
                break;
            case JLI_OBJECT_TYPE_LabelHUD:
                obj = new LabelHUD(builder);
                break;
            case JLI_OBJECT_TYPE_Light:
                obj = new Light(builder);
                break;
            case JLI_OBJECT_TYPE_LevelOfDetail:
                obj = new LevelOfDetail(builder);
                break;
//            case JLI_OBJECT_TYPE_Lua:
//                obj = new Lua(builder);
//                break;
            case JLI_OBJECT_TYPE_Material:
                obj = new Material(builder);
                break;
            case JLI_OBJECT_TYPE_MaterialProperty:
                obj = new MaterialProperty(builder);
                break;
            case JLI_OBJECT_TYPE_Node:
                obj = new Node(builder);
                break;
            case JLI_OBJECT_TYPE_NodeState:
                obj = new NodeState(builder);
                break;
            case JLI_OBJECT_TYPE_NodeStateMachine:
                obj = new NodeStateMachine(builder);
                break;
            case JLI_OBJECT_TYPE_ParticleEmitter:
                obj = new ParticleEmitter(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyGhost:
                obj = new PhysicsBodyGhost(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyRigid:
                obj = new PhysicsBodyRigid(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsBodySoft:
                obj = new PhysicsBodySoft(builder);
                break;
//            case JLI_OBJECT_TYPE_PhysicsConstraint:
//                obj = new PhysicsConstraint(builder);
//                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintHinge:
                obj = new PhysicsConstraintHinge(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint:
                obj = new PhysicsConstraintPointToPoint(builder);
                break;
                
                
                
	    case JLI_OBJECT_TYPE_PhysicsConstraintSlider:
		obj = new PhysicsConstraintSlider(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintConeTwist:
		obj = new PhysicsConstraintConeTwist(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintFixed:
		obj = new PhysicsConstraintFixed(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6Dof:
		obj = new PhysicsConstraintGeneric6Dof(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpring:
		obj = new PhysicsConstraintGeneric6DofSpring(builder);
		break;

                
                
            case JLI_OBJECT_TYPE_PhysicsCloseContact:
                obj = new PhysicsCloseContact(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsContact:
                obj = new PhysicsContact(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsField:
                obj = new PhysicsField(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsRayContact:
                obj = new PhysicsRayContact(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox:
                obj = new PhysicsShapeBox(builder);
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox2D:
                obj = new PhysicsShapeBox2D(builder);
                break;
                
                
	    case JLI_OBJECT_TYPE_PhysicsShapeSphere:
		obj = new PhysicsShapeSphere(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCylinder:
		obj = new PhysicsShapeCylinder(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCapsule:
		obj = new PhysicsShapeCapsule(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCone:
		obj = new PhysicsShapeCone(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeMultiSphere:
		obj = new PhysicsShapeMultiSphere(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexHull:
		obj = new PhysicsShapeConvexHull(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMesh:
		obj = new PhysicsShapeConvexTriangleMesh(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMesh:
		obj = new PhysicsShapeBvhTriangleMesh(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrain:
		obj = new PhysicsShapeHeightfieldTerrain(builder);
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeStaticPlane:
		obj = new PhysicsShapeStaticPlane(builder);
		break;

            case JLI_OBJECT_TYPE_PhysicsWorld:
                obj = new PhysicsWorld(builder);
                break;
            case JLI_OBJECT_TYPE_Plane:
                obj = new Plane(builder);
                break;
            case JLI_OBJECT_TYPE_Scene:
                obj = new Scene(builder);
                break;
            case JLI_OBJECT_TYPE_SceneState:
                obj = new SceneState(builder);
                break;
            case JLI_OBJECT_TYPE_SceneStateMachine:
                obj = new SceneStateMachine(builder);
                break;
            case JLI_OBJECT_TYPE_ShaderProgram:
                obj = new ShaderProgram(builder);
                break;
            case JLI_OBJECT_TYPE_Skinner:
                obj = new Skinner(builder);
                break;
            case JLI_OBJECT_TYPE_SliderHUD:
                obj = new SliderHUD(builder);
                break;
            case JLI_OBJECT_TYPE_Sound:
                obj = new Sound(builder);
                break;
            case JLI_OBJECT_TYPE_Sprite2D:
                obj = new Sprite2D(builder);
                break;
            case JLI_OBJECT_TYPE_SpriteFrameAtlas:
                obj = new SpriteFrameAtlas();
                break;
//                case JLI_OBJECT_TYPE_SteeringBehavior:
//                obj = new SteeringBehavior();
//                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorBuilder:
                obj = new SteeringBehaviorBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorAlignment:
                obj = new SteeringBehaviorAlignment();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorAlignmentBuilder:
                obj = new SteeringBehaviorAlignmentBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorArrive:
                obj = new SteeringBehaviorArrive();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorArriveBuilder:
                obj = new SteeringBehaviorArriveBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorCohesion:
                obj = new SteeringBehaviorCohesion();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorCohesionBuilder:
                obj = new SteeringBehaviorCohesionBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorEvade:
                obj = new SteeringBehaviorEvade();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder:
                obj = new SteeringBehaviorEvadeBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFlee:
                obj = new SteeringBehaviorFlee();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFleeBuilder:
                obj = new SteeringBehaviorFleeBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFollowPath:
                obj = new SteeringBehaviorFollowPath();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFollowPathBuilder:
                obj = new SteeringBehaviorFollowPathBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorHide:
                obj = new SteeringBehaviorHide();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorHideBuilder:
                obj = new SteeringBehaviorHideBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorInterpose:
                obj = new SteeringBehaviorInterpose();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder:
                obj = new SteeringBehaviorInterposeBuilder();
                break;
//                case JLI_OBJECT_TYPE_SteeringBehaviorMachine:
//                obj = new SteeringBehaviorMachine();
//                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineBuilder:
                obj = new SteeringBehaviorMachineBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineDithered:
                obj = new SteeringBehaviorMachineDithered();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineDitheredBuilder:
                obj = new SteeringBehaviorMachineDitheredBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritized:
                obj = new SteeringBehaviorMachinePrioritized();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritizedBuilder:
                obj = new SteeringBehaviorMachinePrioritizedBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeighted:
                obj = new SteeringBehaviorMachineWeighted();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeightedBuilder:
                obj = new SteeringBehaviorMachineWeightedBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidance:
                obj = new SteeringBehaviorObstacleAvoidance();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidanceBuilder:
                obj = new SteeringBehaviorObstacleAvoidanceBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuit:
                obj = new SteeringBehaviorOffsetPursuit();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuitBuilder:
                obj = new SteeringBehaviorOffsetPursuitBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorPursuit:
                obj = new SteeringBehaviorPursuit();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorPursuitBuilder:
                obj = new SteeringBehaviorPursuitBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeek:
                obj = new SteeringBehaviorSeek();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeekBuilder:
                obj = new SteeringBehaviorSeekBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeparation:
                obj = new SteeringBehaviorSeparation();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeparationBuilder:
                obj = new SteeringBehaviorSeparationBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidance:
                obj = new SteeringBehaviorWallAvoidance();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidanceBuilder:
                obj = new SteeringBehaviorWallAvoidanceBuilder();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWander:
                obj = new SteeringBehaviorWander();
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWanderBuilder:
                obj = new SteeringBehaviorWanderBuilder();
                break;
            case JLI_OBJECT_TYPE_StopWatch:
                obj = new StopWatch(builder);
                break;
            case JLI_OBJECT_TYPE_TextboxHUD:
                obj = new TextboxHUD(builder);
                break;
            case JLI_OBJECT_TYPE_Timer:
                obj = new Timer(builder);
                break;
            case JLI_OBJECT_TYPE_WorldState:
                obj = new WorldState(builder);
                break;
            case JLI_OBJECT_TYPE_WorldStateMachine:
                obj = new WorldStateMachine(builder);
                break;
            case JLI_OBJECT_TYPE_Xml:
                obj = new Xml(builder);
                break;
            default:
                obj = NULL;
                break;
        }
        return obj;
    }
    
    AbstractFactoryObject *WorldFactory::ctor(const AbstractFactoryObject &object)
    {
        AbstractFactoryObject *obj = NULL;
        
        switch (object.getType())
        {
            case JLI_OBJECT_TYPE_Action:
		    obj = new Action(*dynamic_cast<const Action*>(&object));
                break;
            case JLI_OBJECT_TYPE_ActionBuilder:
                obj = new ActionBuilder(*dynamic_cast<const ActionBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_ButtonHUD:
                obj = new ButtonHUD(*dynamic_cast<const ButtonHUD*>(&object));
                break;
            case JLI_OBJECT_TYPE_ButtonHUDBuilder:
                obj = new ButtonHUDBuilder(*dynamic_cast<const ButtonHUDBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Camera:
                obj = new Camera(*dynamic_cast<const Camera*>(&object));
                break;
            case JLI_OBJECT_TYPE_CameraBuilder:
                obj = new CameraBuilder(*dynamic_cast<const CameraBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_CheckboxHUD:
                obj = new CheckboxHUD(*dynamic_cast<const CheckboxHUD*>(&object));
                break;
            case JLI_OBJECT_TYPE_CheckboxHUDBuilder:
                obj = new CheckboxHUDBuilder(*dynamic_cast<const CheckboxHUDBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Clock:
                obj = new Clock(*dynamic_cast<const Clock*>(&object));
                break;
            case JLI_OBJECT_TYPE_ClockBuilder:
                obj = new ClockBuilder(*dynamic_cast<const ClockBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_CollisionResponse:
                obj = new CollisionResponse(*dynamic_cast<const CollisionResponse*>(&object));
                break;
            case JLI_OBJECT_TYPE_CollisionResponseBuilder:
                obj = new CollisionResponseBuilder(*dynamic_cast<const CollisionResponseBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Cube:
                obj = new Cube(*dynamic_cast<const Cube*>(&object));
                break;
            case JLI_OBJECT_TYPE_CubeBuilder:
                obj = new CubeBuilder(*dynamic_cast<const CubeBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_DropdownHUD:
                obj = new DropdownHUD(*dynamic_cast<const DropdownHUD*>(&object));
                break;
            case JLI_OBJECT_TYPE_DropdownHUDBuilder:
                obj = new DropdownHUDBuilder(*dynamic_cast<const DropdownHUDBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Font:
                obj = new Font(*dynamic_cast<const Font*>(&object));
                break;
            case JLI_OBJECT_TYPE_FontBuilder:
                obj = new FontBuilder(*dynamic_cast<const FontBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Image:
                obj = new Image(*dynamic_cast<const Image*>(&object));
                break;
            case JLI_OBJECT_TYPE_ImageBuilder:
                obj = new ImageBuilder(*dynamic_cast<const ImageBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_JsonJLI:
                obj = new JsonJLI(*dynamic_cast<const JsonJLI*>(&object));
                break;
            case JLI_OBJECT_TYPE_JsonJLIBuilder:
                obj = new JsonJLIBuilder(*dynamic_cast<const JsonJLIBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_LabelHUD:
                obj = new LabelHUD(*dynamic_cast<const LabelHUD*>(&object));
                break;
            case JLI_OBJECT_TYPE_LabelHUDBuilder:
                obj = new LabelHUDBuilder(*dynamic_cast<const LabelHUDBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Light:
                obj = new Light(*dynamic_cast<const Light*>(&object));
                break;
            case JLI_OBJECT_TYPE_LightBuilder:
                obj = new LightBuilder(*dynamic_cast<const LightBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_LevelOfDetail:
                obj = new LevelOfDetail(*dynamic_cast<const LevelOfDetail*>(&object));
                break;
            case JLI_OBJECT_TYPE_LevelOfDetailBuilder:
                obj = new LevelOfDetailBuilder(*dynamic_cast<const LevelOfDetailBuilder*>(&object));
                break;
//            case JLI_OBJECT_TYPE_Lua:
//                obj = new Lua(*dynamic_cast<const Lua*>(&object));
//                break;
//            case JLI_OBJECT_TYPE_LuaBuilder:
//                obj = new LuaBuilder(*dynamic_cast<const LuaBuilder*>(&object));
//                break;
            case JLI_OBJECT_TYPE_Material:
                obj = new Material(*dynamic_cast<const Material*>(&object));
                break;
            case JLI_OBJECT_TYPE_MaterialBuilder:
                obj = new MaterialBuilder(*dynamic_cast<const MaterialBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_MaterialProperty:
                obj = new MaterialProperty(*dynamic_cast<const MaterialProperty*>(&object));
                break;
            case JLI_OBJECT_TYPE_MaterialPropertyBuilder:
                obj = new MaterialPropertyBuilder(*dynamic_cast<const MaterialPropertyBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Node:
                obj = new Node(*dynamic_cast<const Node*>(&object));
                break;
            case JLI_OBJECT_TYPE_NodeBuilder:
                obj = new NodeBuilder(*dynamic_cast<const NodeBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_NodeState:
                obj = new NodeState(*dynamic_cast<const NodeState*>(&object));
                break;
            case JLI_OBJECT_TYPE_NodeStateBuilder:
                obj = new NodeStateBuilder(*dynamic_cast<const NodeStateBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_NodeStateMachine:
                obj = new NodeStateMachine(*dynamic_cast<const NodeStateMachine*>(&object));
                break;
            case JLI_OBJECT_TYPE_NodeStateMachineBuilder:
                obj = new NodeStateMachineBuilder(*dynamic_cast<const NodeStateMachineBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_ParticleEmitter:
                obj = new ParticleEmitter(*dynamic_cast<const ParticleEmitter*>(&object));
                break;
            case JLI_OBJECT_TYPE_ParticleEmitterBuilder:
                obj = new ParticleEmitterBuilder(*dynamic_cast<const ParticleEmitterBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyGhost:
                obj = new PhysicsBodyGhost(*dynamic_cast<const PhysicsBodyGhost*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyGhostBuilder:
                obj = new PhysicsBodyGhostBuilder(*dynamic_cast<const PhysicsBodyGhostBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyRigid:
                obj = new PhysicsBodyRigid(*dynamic_cast<const PhysicsBodyRigid*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsBodyRigidBuilder:
                obj = new PhysicsBodyRigidBuilder(*dynamic_cast<const PhysicsBodyRigidBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsBodySoft:
                obj = new PhysicsBodySoft(*dynamic_cast<const PhysicsBodySoft*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsBodySoftBuilder:
                obj = new PhysicsBodySoftBuilder(*dynamic_cast<const PhysicsBodySoftBuilder*>(&object));
                break;
//            case JLI_OBJECT_TYPE_PhysicsConstraint:
//                obj = new PhysicsConstraint(*dynamic_cast<const PhysicsConstraint*>(&object));
//                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintBuilder:
                obj = new PhysicsConstraintBuilder(*dynamic_cast<const PhysicsConstraintBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintHinge:
                obj = new PhysicsConstraintHinge(*dynamic_cast<const PhysicsConstraintHinge*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintHingeBuilder:
                obj = new PhysicsConstraintHingeBuilder(*dynamic_cast<const PhysicsConstraintHingeBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint:
                obj = new PhysicsConstraintPointToPoint(*dynamic_cast<const PhysicsConstraintPointToPoint*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsConstraintPointToPointBuilder:
                obj = new PhysicsConstraintPointToPointBuilder(*dynamic_cast<const PhysicsConstraintPointToPointBuilder*>(&object));
                break;
                
                
                
	    case JLI_OBJECT_TYPE_PhysicsConstraintSlider:
		obj = new PhysicsConstraintSlider(*dynamic_cast<const PhysicsConstraintSlider*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintSliderBuilder:
		obj = new PhysicsConstraintSliderBuilder(*dynamic_cast<const PhysicsConstraintSliderBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintConeTwist:
		obj = new PhysicsConstraintConeTwist(*dynamic_cast<const PhysicsConstraintConeTwist*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintConeTwistBuilder:
		obj = new PhysicsConstraintConeTwistBuilder(*dynamic_cast<const PhysicsConstraintConeTwistBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintFixed:
		obj = new PhysicsConstraintFixed(*dynamic_cast<const PhysicsConstraintFixed*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintFixedBuilder:
		obj = new PhysicsConstraintFixedBuilder(*dynamic_cast<const PhysicsConstraintFixedBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6Dof:
		obj = new PhysicsConstraintGeneric6Dof(*dynamic_cast<const PhysicsConstraintGeneric6Dof*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofBuilder:
		obj = new PhysicsConstraintGeneric6DofBuilder(*dynamic_cast<const PhysicsConstraintGeneric6DofBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpring:
		obj = new PhysicsConstraintGeneric6DofSpring(*dynamic_cast<const PhysicsConstraintGeneric6DofSpring*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpringBuilder:
		obj = new PhysicsConstraintGeneric6DofSpringBuilder(*dynamic_cast<const PhysicsConstraintGeneric6DofSpringBuilder*>(&object));
		break;

                
                
            case JLI_OBJECT_TYPE_PhysicsCloseContact:
                obj = new PhysicsCloseContact(*dynamic_cast<const PhysicsCloseContact*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsCloseContactBuilder:
                obj = new PhysicsCloseContactBuilder(*dynamic_cast<const PhysicsCloseContactBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsContact:
                obj = new PhysicsContact(*dynamic_cast<const PhysicsContact*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsContactBuilder:
                obj = new PhysicsContactBuilder(*dynamic_cast<const PhysicsContactBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsField:
                obj = new PhysicsField(*dynamic_cast<const PhysicsField*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsFieldBuilder:
                obj = new PhysicsFieldBuilder(*dynamic_cast<const PhysicsFieldBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsRayContact:
                obj = new PhysicsRayContact(*dynamic_cast<const PhysicsRayContact*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsRayContactBuilder:
                obj = new PhysicsRayContactBuilder(*dynamic_cast<const PhysicsRayContactBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox:
                obj = new PhysicsShapeBox(*dynamic_cast<const PhysicsShapeBox*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBoxBuilder:
                obj = new PhysicsShapeBoxBuilder(*dynamic_cast<const PhysicsShapeBoxBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox2D:
                obj = new PhysicsShapeBox2D(*dynamic_cast<const PhysicsShapeBox2D*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsShapeBox2DBuilder:
                obj = new PhysicsShapeBox2DBuilder(*dynamic_cast<const PhysicsShapeBox2DBuilder*>(&object));
                break;
                
                
	    case JLI_OBJECT_TYPE_PhysicsShapeSphere:
		obj = new PhysicsShapeSphere(*dynamic_cast<const PhysicsShapeSphere*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeSphereBuilder:
		obj = new PhysicsShapeSphereBuilder(*dynamic_cast<const PhysicsShapeSphereBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCylinder:
		obj = new PhysicsShapeCylinder(*dynamic_cast<const PhysicsShapeCylinder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCylinderBuilder:
		obj = new PhysicsShapeCylinderBuilder(*dynamic_cast<const PhysicsShapeCylinderBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCapsule:
		obj = new PhysicsShapeCapsule(*dynamic_cast<const PhysicsShapeCapsule*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCapsuleBuilder:
		obj = new PhysicsShapeCapsuleBuilder(*dynamic_cast<const PhysicsShapeCapsuleBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeCone:
		obj = new PhysicsShapeCone(*dynamic_cast<const PhysicsShapeCone*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConeBuilder:
		obj = new PhysicsShapeConeBuilder(*dynamic_cast<const PhysicsShapeConeBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeMultiSphere:
		obj = new PhysicsShapeMultiSphere(*dynamic_cast<const PhysicsShapeMultiSphere*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeMultiSphereBuilder:
		obj = new PhysicsShapeMultiSphereBuilder(*dynamic_cast<const PhysicsShapeMultiSphereBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexHull:
		obj = new PhysicsShapeConvexHull(*dynamic_cast<const PhysicsShapeConvexHull*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexHullBuilder:
		obj = new PhysicsShapeConvexHullBuilder(*dynamic_cast<const PhysicsShapeConvexHullBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMesh:
		obj = new PhysicsShapeConvexTriangleMesh(*dynamic_cast<const PhysicsShapeConvexTriangleMesh*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMeshBuilder:
		obj = new PhysicsShapeConvexTriangleMeshBuilder(*dynamic_cast<const PhysicsShapeConvexTriangleMeshBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMesh:
		obj = new PhysicsShapeBvhTriangleMesh(*dynamic_cast<const PhysicsShapeBvhTriangleMesh*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMeshBuilder:
		obj = new PhysicsShapeBvhTriangleMeshBuilder(*dynamic_cast<const PhysicsShapeBvhTriangleMeshBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrain:
		obj = new PhysicsShapeHeightfieldTerrain(*dynamic_cast<const PhysicsShapeHeightfieldTerrain*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrainBuilder:
		obj = new PhysicsShapeHeightfieldTerrainBuilder(*dynamic_cast<const PhysicsShapeHeightfieldTerrainBuilder*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeStaticPlane:
		obj = new PhysicsShapeStaticPlane(*dynamic_cast<const PhysicsShapeStaticPlane*>(&object));
		break;
	    case JLI_OBJECT_TYPE_PhysicsShapeStaticPlaneBuilder:
		obj = new PhysicsShapeStaticPlaneBuilder(*dynamic_cast<const PhysicsShapeStaticPlaneBuilder*>(&object));
		break;

                
                
            case JLI_OBJECT_TYPE_PhysicsWorld:
                obj = new PhysicsWorld(*dynamic_cast<const PhysicsWorld*>(&object));
                break;
            case JLI_OBJECT_TYPE_PhysicsWorldBuilder:
                obj = new PhysicsWorldBuilder(*dynamic_cast<const PhysicsWorldBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Plane:
                obj = new Plane(*dynamic_cast<const Plane*>(&object));
                break;
            case JLI_OBJECT_TYPE_PlaneBuilder:
                obj = new PlaneBuilder(*dynamic_cast<const PlaneBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Scene:
                obj = new Scene(*dynamic_cast<const Scene*>(&object));
                break;
            case JLI_OBJECT_TYPE_SceneBuilder:
                obj = new SceneBuilder(*dynamic_cast<const SceneBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_SceneState:
                obj = new SceneState(*dynamic_cast<const SceneState*>(&object));
                break;
            case JLI_OBJECT_TYPE_SceneStateBuilder:
                obj = new SceneStateBuilder(*dynamic_cast<const SceneStateBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_SceneStateMachine:
                obj = new SceneStateMachine(*dynamic_cast<const SceneStateMachine*>(&object));
                break;
            case JLI_OBJECT_TYPE_SceneStateMachineBuilder:
                obj = new SceneStateMachineBuilder(*dynamic_cast<const SceneStateMachineBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_ShaderProgram:
                obj = new ShaderProgram(*dynamic_cast<const ShaderProgram*>(&object));
                break;
            case JLI_OBJECT_TYPE_ShaderProgramBuilder:
                obj = new ShaderProgramBuilder(*dynamic_cast<const ShaderProgramBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Skinner:
                obj = new Skinner(*dynamic_cast<const Skinner*>(&object));
                break;
            case JLI_OBJECT_TYPE_SkinnerBuilder:
                obj = new SkinnerBuilder(*dynamic_cast<const SkinnerBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_SliderHUD:
                obj = new SliderHUD(*dynamic_cast<const SliderHUD*>(&object));
                break;
            case JLI_OBJECT_TYPE_SliderHUDBuilder:
                obj = new SliderHUDBuilder(*dynamic_cast<const SliderHUDBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Sound:
                obj = new Sound(*dynamic_cast<const Sound*>(&object));
                break;
            case JLI_OBJECT_TYPE_SoundBuilder:
                obj = new SoundBuilder(*dynamic_cast<const SoundBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Sprite2D:
                obj = new Sprite2D(*dynamic_cast<const Sprite2D*>(&object));
                break;
            case JLI_OBJECT_TYPE_Sprite2DBuilder:
                obj = new Sprite2DBuilder(*dynamic_cast<const Sprite2DBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_SpriteFrameAtlas:
                obj = new SpriteFrameAtlas(*dynamic_cast<const SpriteFrameAtlas*>(&object));
                break;
            case JLI_OBJECT_TYPE_SpriteFrameAtlasBuilder:
                obj = new SpriteFrameAtlasBuilder(*dynamic_cast<const SpriteFrameAtlasBuilder*>(&object));
                break;
//                case JLI_OBJECT_TYPE_SteeringBehavior:
//                obj = new SteeringBehavior(*dynamic_cast<const SteeringBehavior*>(&object));
//                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorBuilder:
                obj = new SteeringBehaviorBuilder(*dynamic_cast<const SteeringBehaviorBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorAlignment:
                obj = new SteeringBehaviorAlignment(*dynamic_cast<const SteeringBehaviorAlignment*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorAlignmentBuilder:
                obj = new SteeringBehaviorAlignmentBuilder(*dynamic_cast<const SteeringBehaviorAlignmentBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorArrive:
                obj = new SteeringBehaviorArrive(*dynamic_cast<const SteeringBehaviorArrive*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorArriveBuilder:
                obj = new SteeringBehaviorArriveBuilder(*dynamic_cast<const SteeringBehaviorArriveBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorCohesion:
                obj = new SteeringBehaviorCohesion(*dynamic_cast<const SteeringBehaviorCohesion*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorCohesionBuilder:
                obj = new SteeringBehaviorCohesionBuilder(*dynamic_cast<const SteeringBehaviorCohesionBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorEvade:
                obj = new SteeringBehaviorEvade(*dynamic_cast<const SteeringBehaviorEvade*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder:
                obj = new SteeringBehaviorEvadeBuilder(*dynamic_cast<const SteeringBehaviorEvadeBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFlee:
                obj = new SteeringBehaviorFlee(*dynamic_cast<const SteeringBehaviorFlee*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFleeBuilder:
                obj = new SteeringBehaviorFleeBuilder(*dynamic_cast<const SteeringBehaviorFleeBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFollowPath:
                obj = new SteeringBehaviorFollowPath(*dynamic_cast<const SteeringBehaviorFollowPath*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorFollowPathBuilder:
                obj = new SteeringBehaviorFollowPathBuilder(*dynamic_cast<const SteeringBehaviorFollowPathBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorHide:
                obj = new SteeringBehaviorHide(*dynamic_cast<const SteeringBehaviorHide*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorHideBuilder:
                obj = new SteeringBehaviorHideBuilder(*dynamic_cast<const SteeringBehaviorHideBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorInterpose:
                obj = new SteeringBehaviorInterpose(*dynamic_cast<const SteeringBehaviorInterpose*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder:
                obj = new SteeringBehaviorInterposeBuilder(*dynamic_cast<const SteeringBehaviorInterposeBuilder*>(&object));
                break;
//                case JLI_OBJECT_TYPE_SteeringBehaviorMachine:
//                obj = new SteeringBehaviorMachine(*dynamic_cast<const SteeringBehaviorMachine*>(&object));
//                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineBuilder:
                obj = new SteeringBehaviorMachineBuilder(*dynamic_cast<const SteeringBehaviorMachineBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineDithered:
                obj = new SteeringBehaviorMachineDithered(*dynamic_cast<const SteeringBehaviorMachineDithered*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineDitheredBuilder:
                obj = new SteeringBehaviorMachineDitheredBuilder(*dynamic_cast<const SteeringBehaviorMachineDitheredBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritized:
                obj = new SteeringBehaviorMachinePrioritized(*dynamic_cast<const SteeringBehaviorMachinePrioritized*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritizedBuilder:
                obj = new SteeringBehaviorMachinePrioritizedBuilder(*dynamic_cast<const SteeringBehaviorMachinePrioritizedBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeighted:
                obj = new SteeringBehaviorMachineWeighted(*dynamic_cast<const SteeringBehaviorMachineWeighted*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorMachineWeightedBuilder:
                obj = new SteeringBehaviorMachineWeightedBuilder(*dynamic_cast<const SteeringBehaviorMachineWeightedBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidance:
                obj = new SteeringBehaviorObstacleAvoidance(*dynamic_cast<const SteeringBehaviorObstacleAvoidance*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidanceBuilder:
                obj = new SteeringBehaviorObstacleAvoidanceBuilder(*dynamic_cast<const SteeringBehaviorObstacleAvoidanceBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuit:
                obj = new SteeringBehaviorOffsetPursuit(*dynamic_cast<const SteeringBehaviorOffsetPursuit*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuitBuilder:
                obj = new SteeringBehaviorOffsetPursuitBuilder(*dynamic_cast<const SteeringBehaviorOffsetPursuitBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorPursuit:
                obj = new SteeringBehaviorPursuit(*dynamic_cast<const SteeringBehaviorPursuit*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorPursuitBuilder:
                obj = new SteeringBehaviorPursuitBuilder(*dynamic_cast<const SteeringBehaviorPursuitBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeek:
                obj = new SteeringBehaviorSeek(*dynamic_cast<const SteeringBehaviorSeek*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeekBuilder:
                obj = new SteeringBehaviorSeekBuilder(*dynamic_cast<const SteeringBehaviorSeekBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeparation:
                obj = new SteeringBehaviorSeparation(*dynamic_cast<const SteeringBehaviorSeparation*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorSeparationBuilder:
                obj = new SteeringBehaviorSeparationBuilder(*dynamic_cast<const SteeringBehaviorSeparationBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidance:
                obj = new SteeringBehaviorWallAvoidance(*dynamic_cast<const SteeringBehaviorWallAvoidance*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidanceBuilder:
                obj = new SteeringBehaviorWallAvoidanceBuilder(*dynamic_cast<const SteeringBehaviorWallAvoidanceBuilder*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWander:
                obj = new SteeringBehaviorWander(*dynamic_cast<const SteeringBehaviorWander*>(&object));
                break;
                case JLI_OBJECT_TYPE_SteeringBehaviorWanderBuilder:
                obj = new SteeringBehaviorWanderBuilder(*dynamic_cast<const SteeringBehaviorWanderBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_StopWatch:
                obj = new StopWatch(*dynamic_cast<const StopWatch*>(&object));
                break;
            case JLI_OBJECT_TYPE_StopWatchBuilder:
                obj = new StopWatchBuilder(*dynamic_cast<const StopWatchBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_TextboxHUD:
                obj = new TextboxHUD(*dynamic_cast<const TextboxHUD*>(&object));
                break;
            case JLI_OBJECT_TYPE_TextboxHUDBuilder:
                obj = new TextboxHUDBuilder(*dynamic_cast<const TextboxHUDBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Timer:
                obj = new Timer(*dynamic_cast<const Timer*>(&object));
                break;
            case JLI_OBJECT_TYPE_TimerBuilder:
                obj = new TimerBuilder(*dynamic_cast<const TimerBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Thread:
                obj = new Thread(*dynamic_cast<const Thread*>(&object));
                break;
            case JLI_OBJECT_TYPE_ThreadBuilder:
                obj = new ThreadBuilder(*dynamic_cast<const ThreadBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_WorldState:
                obj = new WorldState(*dynamic_cast<const WorldState*>(&object));
                break;
            case JLI_OBJECT_TYPE_WorldStateBuilder:
                obj = new WorldStateBuilder(*dynamic_cast<const WorldStateBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_WorldStateMachine:
                obj = new WorldStateMachine(*dynamic_cast<const WorldStateMachine*>(&object));
                break;
            case JLI_OBJECT_TYPE_WorldStateMachineBuilder:
                obj = new WorldStateMachineBuilder(*dynamic_cast<const WorldStateMachineBuilder*>(&object));
                break;
            case JLI_OBJECT_TYPE_Xml:
                obj = new Xml(*dynamic_cast<const Xml*>(&object));
                break;
            case JLI_OBJECT_TYPE_XmlBuilder:
                obj = new XmlBuilder(*dynamic_cast<const XmlBuilder*>(&object));
                break;
            default:
                obj= NULL;
        }
        return obj;
    }
    
    AbstractFactoryObject *WorldFactory::create_Internal(const u32 type)
    {
        AbstractFactoryObject *object = ctor(type);
        
        if (addReference_Internal(object))
        {
            addObject_Internal(object);
        }
        else
        {
            DEBUG_LOG_WRITE_W(TAG, "called create_Internal but there is already a reference?");
        }
        
        return object;
    }
    
    AbstractFactoryObject *WorldFactory::create_Internal(const AbstractBuilder &builder)
    {
        AbstractFactoryObject *object = ctor(builder);
        
        if (addReference_Internal(object))
        {
            addObject_Internal(object);
        }
        else
        {
            DEBUG_LOG_WRITE_W(TAG, "called create_Internal but there is already a reference?");
        }
        
        return object;

    }
    
    AbstractFactoryObject *WorldFactory::clone_Internal(const AbstractFactoryObject &copy, bool share)
    {
        AbstractFactoryObject *object = const_cast<AbstractFactoryObject*>(&copy);
        
        if (share)
        {
            DEBUG_ASSERT(addReference_Internal(object) == false);
            return object;
        }
        
        AbstractFactoryObject *deepCopy_object = ctor(*object);
        
        if (addReference_Internal(deepCopy_object))
        {
            addObject_Internal(deepCopy_object);
        }
        else
        {
            DEBUG_LOG_WRITE_W(TAG, "called clone_Internal but there is already a reference?");
        }
        
        return deepCopy_object;

    }
    
    s32 WorldFactory::numberOfObjects_Internal()const
    {
        return m_ObjectList.size();
    }
    
    bool WorldFactory::removeObject_Internal(AbstractFactoryObject *object)
    {
        DEBUG_ASSERT_WRITE(object, "Object must not be null");
        
        ObjectList::iterator iter = std::find(m_ObjectList.begin(), m_ObjectList.end(), object);
        if(iter == m_ObjectList.end())
            return false;
        DEBUG_ASSERT (iter != m_ObjectList.end());
        
        if (object->canDelete())
        {
            m_ObjectList.erase(iter);
            delete object;
            object = NULL;
            return true;
        }
        return false;
        
    }
    
    void WorldFactory::addObject_Internal(AbstractFactoryObject *object)
    {
        DEBUG_ASSERT_WRITE(object, "Object must not be null");
        
        m_ObjectList.push_back(object);
    }
    
    s32 WorldFactory::numberOfArrayObjects_Internal()const
    {
        return m_ObjectArrayList.size();
    }
    
    void WorldFactory::removeArrayObject_Internal(AbstractFactoryObject **object)
    {
        DEBUG_ASSERT_WRITE(object, "Object must not be null");
        
        
        ObjectArrayList::iterator iter = std::find(m_ObjectArrayList.begin(), m_ObjectArrayList.end(), object);
        if(iter == m_ObjectArrayList.end())
            return;
        DEBUG_ASSERT(iter != m_ObjectArrayList.end());
        
        m_ObjectArrayList.erase(iter);
        delete [] object;
        object = NULL;
    }
    
    void WorldFactory::addArrayObject_Internal(AbstractFactoryObject **object)
    {
        DEBUG_ASSERT_WRITE(object, "Object must not be null");
        
        m_ObjectArrayList.push_back(object);
    }
    
    s32 WorldFactory::numberOfReferences_Internal(AbstractFactoryObject *object)
    {
        DEBUG_ASSERT_WRITE(object, "Object must not be null");
        
        ObjectDuplicateMap::iterator iter = m_ObjectDuplicateMap.find(object->getPointerValue());
        if(iter != m_ObjectDuplicateMap.end())
            return iter->second;
        return 0;
    }
    
    bool WorldFactory::removeReference_Internal(AbstractFactoryObject *object)
    {
        s32 count = numberOfReferences_Internal(object);
        if(count > 0)
        {
            m_ObjectDuplicateMap.erase(object->getPointerValue());
            m_ObjectDuplicateMap.insert(ObjectDuplicatePair(object->getPointerValue(), --count));
        }
//        else
//        {
//            DEBUG_LOG_WRITE_D(TAG, "object doesn't exist in the map");
//        }
        
        return (numberOfReferences_Internal(object) <= 0);
    }
    
    bool WorldFactory::addReference_Internal(AbstractFactoryObject *object)
    {
        s32 count = numberOfReferences_Internal(object);
        if(count >= 0)
        {
            m_ObjectDuplicateMap.erase(object->getPointerValue());
            m_ObjectDuplicateMap.insert(ObjectDuplicatePair(object->getPointerValue(), ++count));
        }
        else
        {
            DEBUG_LOG_WRITE_D(TAG, "object doesn't exist in the map");
        }
        
        return (numberOfReferences_Internal(object) == 1);
    }
    
    void WorldFactory::collectGarbage()
    {
//        DEBUG_LOG_V(TAG, "Total objects allocated: %lu\n", m_ObjectList.size() + m_ObjectArrayList.size());
        for (std::vector<AbstractFactoryObject*>::iterator i = m_ObjectsToDelete.begin(); i != m_ObjectsToDelete.end(); )
        {
            AbstractFactoryObject *object = *i;
            
            if(removeReference_Internal(object) && removeObject_Internal(object))
                i = m_ObjectsToDelete.erase(i);
            else
                ++i;
        }
        
        for (std::vector<AbstractFactoryObject**>::iterator i = m_ArrayObjectsToDelete.begin(); i != m_ArrayObjectsToDelete.end(); )
        {
            AbstractFactoryObject **object = *i;
            removeArrayObject_Internal(object);
            i = m_ArrayObjectsToDelete.erase(i);
        }
    }
    
    s64 WorldFactory::collectGarbageSize()const
    {
        return m_ObjectsToDelete.size() + m_ArrayObjectsToDelete.size();
    }
    
    void WorldFactory::collectGarbage_GPU()
    {
        for (std::vector<AbstractFactoryObject*>::iterator i = m_ObjectsToDelete_GPU.begin(); i != m_ObjectsToDelete_GPU.end(); )
        {
            AbstractFactoryObject *object = *i;
            
            if(removeReference_Internal(object) && removeObject_Internal(object))
                i = m_ObjectsToDelete_GPU.erase(i);
            else
                ++i;
        }
        
        for (std::vector<AbstractFactoryObject**>::iterator i = m_ArrayObjectsToDelete_GPU.begin(); i != m_ArrayObjectsToDelete_GPU.end(); )
        {
            AbstractFactoryObject **object = *i;
            removeArrayObject_Internal(object);
            i = m_ArrayObjectsToDelete_GPU.erase(i);
        }
    }
    
    s64 WorldFactory::collectGarbage_GPUSize()const
    {
        return m_ObjectsToDelete_GPU.size() + m_ArrayObjectsToDelete_GPU.size();
    }
}

