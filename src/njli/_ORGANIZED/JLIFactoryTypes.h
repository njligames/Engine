//
//  JLIFactoryTypes.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/23/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_JLIFactoryTypes_h
#define JLIGameEngineTest_JLIFactoryTypes_h

#include "Util.h"
#include "btBroadphaseProxy.h"

namespace njli
{
    
    enum njliImageType
    {
        JLI_IMAGE_TYPE_NONE,
        JLI_IMAGE_TYPE_JPEG,
        JLI_IMAGE_TYPE_PNG,
        JLI_IMAGE_TYPE_BMP,
        JLI_IMAGE_TYPE_GIF,
        JLI_IMAGE_TYPE_PSD,
        JLI_IMAGE_TYPE_PIC,
        JLI_IMAGE_TYPE_HDR,
        JLI_IMAGE_TYPE_TGA,
        JLI_IMAGE_TYPE_PVR,
        JLI_IMAGE_TYPE_MAX
    };
    
    enum njliActionTimingMode
    {
        JLI_ACTION_TIMING_MODE_NONE,
        JLI_ACTION_TIMING_MODE_LINEAR,
        JLI_ACTION_TIMING_MODE_EASEIN,
        JLI_ACTION_TIMING_MODE_EASEOUT,
        JLI_ACTION_TIMING_MODE_EASEINEASEOUT,
        JLI_ACTION_TIMING_MODE_MAX
    };
    
    enum njliHUDSolidity
    {
        JLI_HUD_SOLIDITY_NONE,
        JLI_HUD_SOLIDITY_SOLID = 1,
        JLI_HUD_SOLIDITY_HOLE = 2,
        JLI_HUD_SOLIDITY_MAX
    };
    enum njliHUDAlign
    {
        JLI_HUD_ALIGN_NONE,
        JLI_HUD_ALIGN_LEFT 		= 1<<0,	// Default, align text horizontally to left.
        JLI_HUD_ALIGN_CENTER 	= 1<<1,	// Align text horizontally to center.
        JLI_HUD_ALIGN_RIGHT 	= 1<<2,	// Align text horizontally to right.
        JLI_HUD_ALIGN_TOP 		= 1<<3,	// Align text vertically to top.
        JLI_HUD_ALIGN_MIDDLE	= 1<<4,	// Align text vertically to middle.
        JLI_HUD_ALIGN_BOTTOM	= 1<<5,	// Align text vertically to bottom.
        JLI_HUD_ALIGN_BASELINE	= 1<<6, // Default, align text vertically to baseline.
        JLI_HUD_ALIGN_MAX
    };
    
    enum njliHUDWinding
    {
        JLI_HUD_WINDING_NONE,
        JLI_HUD_WINDING_CCW = 1,
        JLI_HUD_WINDING_CW = 2,
        JLI_HUD_WINDING_MAX
    };
    
    enum njliHUDImageFlags
    {
        JLI_HUD_IMAGE_FLAGS_NONE,
        JLI_HUD_IMAGE_FLAGS_GENERATE_MIPMAPS = 1<<0,     // Generate mipmaps during creation of the image.
        JLI_HUD_IMAGE_FLAGS_REPEATX          = 1<<1,		// Repeat image in X direction.
        JLI_HUD_IMAGE_FLAGS_REPEATY          = 1<<2,		// Repeat image in Y direction.
        JLI_HUD_IMAGE_FLAGS_FLIPY            = 1<<3,		// Flips (inverses) image in Y direction when rendered.
        JLI_HUD_IMAGE_FLAGS_PREMULTIPLIED    = 1<<4,		// Image data has premultiplied alpha.
        JLI_HUD_IMAGE_FLAGS_MAX
    };
    enum njliHUDLineCap
    {
        JLI_HUD_LINECAP_NONE = -1,
        JLI_HUD_LINECAP_BUTT,
        JLI_HUD_LINECAP_ROUND,
        JLI_HUD_LINECAP_SQUARE,
        JLI_HUD_LINECAP_BEVEL,
        JLI_HUD_LINECAP_MITER,
        JLI_HUD_LINECAP_MAX
    };
    /*
     const Image &negativeX,
     const Image &negativeY,
     const Image &negativeZ,
     const Image &positiveX,
     const Image &positiveY,
     const Image &positiveZ
     */
    enum njliTextureCubeSides
    {
        JLI_TEXTURECUBE_SIDE_NONE,
        JLI_TEXTURECUBE_SIDE_NEGATIVE_X,
        JLI_TEXTURECUBE_SIDE_NEGATIVE_Y,
        JLI_TEXTURECUBE_SIDE_NEGATIVE_Z,
        JLI_TEXTURECUBE_SIDE_POSITIVE_X,
        JLI_TEXTURECUBE_SIDE_POSITIVE_Y,
        JLI_TEXTURECUBE_SIDE_POSITIVE_Z,
        JLI_TEXTURECUBE_SIDE_MAX
    };
    
    enum njliTextureType
    {
        JLI_TEXTURE_TYPE_NONE,
        JLI_TEXTURE_TYPE_2D,
        JLI_TEXTURE_TYPE_CUBEMAP,
        JLI_TEXTURE_TYPE_MAX
    };
    
    enum njliTextureMinificationValueType
    {
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NONE,
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NEAREST,
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR,
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NEAREST_MIPMAP_NEAREST,
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_NEAREST_MIPMAP_LINEAR,
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR_MIPMAP_NEAREST,
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_LINEAR_MIPMAP_LINEAR,
        JLI_TEXTURE_MINIFICATION_VALUE_TYPE_MAX
    };
    
    enum njliTextureMagnificationValueType
    {
        JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_NONE,
        JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_NEAREST,
        JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_LINEAR,
        JLI_TEXTURE_MAGNIFICATION_VALUE_TYPE_MAX
    };
    
    enum njliTextureWrapType
    {
        JLI_TEXTURE_WRAP_TYPE_NONE,
        JLI_TEXTURE_WRAP_TYPE_REPEAT,
        JLI_TEXTURE_WRAP_TYPE_CLAMP_TO_EDGE,
        JLI_TEXTURE_WRAP_TYPE_MIRRORED_REPEAT,
        JLI_TEXTURE_WRAP_TYPE_MAX
    };
    
    enum njliShaderType
    {
        JLI_SHADER_TYPE_NONE,
        JLI_SHADER_TYPE_VERTEX,
        JLI_SHADER_TYPE_FRAGMENT,
        JLI_SHADER_TYPE_MAX
    };
    
    enum njliFileType
    {
        JLI_FILE_TYPE_NONE,
        JLI_FILE_TYPE_XML,
        JLI_FILE_TYPE_JSON,
        JLI_FILE_TYPE_LUA,
        JLI_FILE_TYPE_ZIP,
        JLI_FILE_TYPE_PARTICLE,
        
        JLI_FILE_TYPE_SOUND_WAV,
        
        JLI_FILE_TYPE_IMAGE_PNG,
        JLI_FILE_TYPE_IMAGE_TGA,
        
        JLI_FILE_TYPE_SHADER_VERTEX,
        JLI_FILE_TYPE_SHADER_FRAGMENT,
        JLI_FILE_TYPE_MAX,
    };
    
    enum njliPhysicsType
    {
        JLI_PHYSICS_TYPE_NONE,
        JLI_PHYSICS_TYPE_Static,
        JLI_PHYSICS_TYPE_Dynamic,
        JLI_PHYSICS_TYPE_Kinematic,
        JLI_PHYSICS_TYPE_MAX
    };
    
    enum njliTransparencyMode
    {
        JLI_TRANSPARENCY_NONE,
        
        JLI_TRANSPARENCY_AlphaOne,
        JLI_TRANSPARENCY_RGBZero,
        
        JLI_TRANSPARENCY_MAX
    };
    
    enum njliCullMode
    {
        JLI_CULLMODE_NONE,
        
        JLI_CULLMODE_Front,
        JLI_CULLMODE_Back,
        
        JLI_CULLMODE_MAX
    };
    
    
    
    
    
    enum njliBitCategories
    {
        JLI_BIT_CATEGORY_NONE = 0,
        JLI_BIT_CATEGORY_1 = 1 << 0,
        JLI_BIT_CATEGORY_2 = 1 << 1,
        JLI_BIT_CATEGORY_3 = 1 << 2,
        JLI_BIT_CATEGORY_4 = 1 << 3,
        JLI_BIT_CATEGORY_5 = 1 << 4,
        JLI_BIT_CATEGORY_6 = 1 << 5,
        JLI_BIT_CATEGORY_7 = 1 << 6,
        JLI_BIT_CATEGORY_8 = 1 << 7,
        JLI_BIT_CATEGORY_9 = 1 << 8,
        JLI_BIT_CATEGORY_10 = 1 << 9,
        JLI_BIT_CATEGORY_11 = 1 << 10,
        JLI_BIT_CATEGORY_12 = 1 << 11,
        JLI_BIT_CATEGORY_13 = 1 << 12,
        JLI_BIT_CATEGORY_14 = 1 << 13,
        JLI_BIT_CATEGORY_15 = 1 << 14,
        JLI_BIT_CATEGORY_16 = 1 << 15,
        JLI_BIT_CATEGORY_17 = 1 << 16,
        JLI_BIT_CATEGORY_18 = 1 << 17,
        JLI_BIT_CATEGORY_19 = 1 << 18,
        JLI_BIT_CATEGORY_20 = 1 << 19,
        JLI_BIT_CATEGORY_21 = 1 << 20,
        JLI_BIT_CATEGORY_22 = 1 << 21,
        JLI_BIT_CATEGORY_23 = 1 << 22,
        JLI_BIT_CATEGORY_24 = 1 << 23,
        JLI_BIT_CATEGORY_25 = 1 << 24,
        JLI_BIT_CATEGORY_26 = 1 << 25,
        JLI_BIT_CATEGORY_27 = 1 << 26,
        JLI_BIT_CATEGORY_28 = 1 << 27,
        JLI_BIT_CATEGORY_29 = 1 << 28,
        JLI_BIT_CATEGORY_30 = 1 << 29,
        JLI_BIT_CATEGORY_31 = 1 << 30,
        JLI_BIT_CATEGORY_ALL = 0xFFFFFFFF,
        JLI_BIT_CATEGORY_DefaultFilter = btBroadphaseProxy::DefaultFilter,
        JLI_BIT_CATEGORY_StaticFilter = btBroadphaseProxy::StaticFilter,
        JLI_BIT_CATEGORY_KinematicFilter = btBroadphaseProxy::KinematicFilter,
        JLI_BIT_CATEGORY_DebrisFilter = btBroadphaseProxy::DebrisFilter,
        JLI_BIT_CATEGORY_SensorTrigger = btBroadphaseProxy::SensorTrigger,
        JLI_BIT_CATEGORY_CharacterFilter = btBroadphaseProxy::CharacterFilter,
        JLI_BIT_CATEGORY_AllFilter = btBroadphaseProxy::AllFilter,
    };
    
    extern const u32 njliRenderCategoryValues[32];
    
    enum njliObjectEnumType
    {
        JLI_OBJECT_TYPE_None = 0,
        
        JLI_OBJECT_TYPE_World,
        JLI_OBJECT_TYPE_WorldFacebook,
        JLI_OBJECT_TYPE_WorldFactory,
        JLI_OBJECT_TYPE_WorldLuaVirtualMachine,
        JLI_OBJECT_TYPE_WorldPythonVirtualMachine,
        JLI_OBJECT_TYPE_WorldResourceLoader,
        JLI_OBJECT_TYPE_WorldSocket,
        JLI_OBJECT_TYPE_WorldHUD,
        JLI_OBJECT_TYPE_WorldInput,
        JLI_OBJECT_TYPE_WorldClock,
        JLI_OBJECT_TYPE_WorldSound,
        
        JLI_OBJECT_TYPE_DeviceTouch,
        
        JLI_OBJECT_TYPE_Geometry,
        JLI_OBJECT_TYPE_PhysicsShape,
        
        JLI_OBJECT_TYPE_Action,
        JLI_OBJECT_TYPE_ActionBuilder,
        JLI_OBJECT_TYPE_ButtonHUD,
        JLI_OBJECT_TYPE_ButtonHUDBuilder,
        JLI_OBJECT_TYPE_Camera,
        JLI_OBJECT_TYPE_CameraBuilder,
        JLI_OBJECT_TYPE_CheckboxHUD,
        JLI_OBJECT_TYPE_CheckboxHUDBuilder,
        JLI_OBJECT_TYPE_Clock,
        JLI_OBJECT_TYPE_ClockBuilder,
        JLI_OBJECT_TYPE_CollisionResponse,
        JLI_OBJECT_TYPE_CollisionResponseBuilder,
        JLI_OBJECT_TYPE_Cube,
        JLI_OBJECT_TYPE_CubeBuilder,
        JLI_OBJECT_TYPE_DropdownHUD,
        JLI_OBJECT_TYPE_DropdownHUDBuilder,
        JLI_OBJECT_TYPE_Font,
        JLI_OBJECT_TYPE_FontBuilder,
        JLI_OBJECT_TYPE_Image,
        JLI_OBJECT_TYPE_ImageBuilder,
        JLI_OBJECT_TYPE_JsonJLI,
        JLI_OBJECT_TYPE_JsonJLIBuilder,
        JLI_OBJECT_TYPE_LabelHUD,
        JLI_OBJECT_TYPE_LabelHUDBuilder,
        JLI_OBJECT_TYPE_Light,
        JLI_OBJECT_TYPE_LightBuilder,
        JLI_OBJECT_TYPE_LevelOfDetail,
        JLI_OBJECT_TYPE_LevelOfDetailBuilder,
//        JLI_OBJECT_TYPE_Lua,
//        JLI_OBJECT_TYPE_LuaBuilder,
        JLI_OBJECT_TYPE_Material,
        JLI_OBJECT_TYPE_MaterialBuilder,
        JLI_OBJECT_TYPE_MaterialProperty,
        JLI_OBJECT_TYPE_MaterialPropertyBuilder,
        JLI_OBJECT_TYPE_Node,
        JLI_OBJECT_TYPE_NodeBuilder,
        JLI_OBJECT_TYPE_NodeState,
        JLI_OBJECT_TYPE_NodeStateBuilder,
        JLI_OBJECT_TYPE_NodeStateMachine,
        JLI_OBJECT_TYPE_NodeStateMachineBuilder,
        JLI_OBJECT_TYPE_ParticleEmitter,
        JLI_OBJECT_TYPE_ParticleEmitterBuilder,
        JLI_OBJECT_TYPE_PhysicsBody,
        JLI_OBJECT_TYPE_PhysicsBodyGhost,
        JLI_OBJECT_TYPE_PhysicsBodyGhostBuilder,
        JLI_OBJECT_TYPE_PhysicsBodyRigid,
        JLI_OBJECT_TYPE_PhysicsBodyRigidBuilder,
        JLI_OBJECT_TYPE_PhysicsBodySoft,
        JLI_OBJECT_TYPE_PhysicsBodySoftBuilder,
        JLI_OBJECT_TYPE_PhysicsConstraint,
        JLI_OBJECT_TYPE_PhysicsConstraintBuilder,
        JLI_OBJECT_TYPE_PhysicsConstraintHinge,
        JLI_OBJECT_TYPE_PhysicsConstraintHingeBuilder,
        JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint,
        JLI_OBJECT_TYPE_PhysicsConstraintPointToPointBuilder,
        
        JLI_OBJECT_TYPE_PhysicsConstraintSlider,
        JLI_OBJECT_TYPE_PhysicsConstraintSliderBuilder,
        JLI_OBJECT_TYPE_PhysicsConstraintConeTwist,
        JLI_OBJECT_TYPE_PhysicsConstraintConeTwistBuilder,
        JLI_OBJECT_TYPE_PhysicsConstraintFixed,
        JLI_OBJECT_TYPE_PhysicsConstraintFixedBuilder,
        JLI_OBJECT_TYPE_PhysicsConstraintGeneric6Dof,
        JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofBuilder,
        JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpring,
        JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpringBuilder,

        
        JLI_OBJECT_TYPE_PhysicsContact,
        JLI_OBJECT_TYPE_PhysicsContactBuilder,
        JLI_OBJECT_TYPE_PhysicsCloseContact,
        JLI_OBJECT_TYPE_PhysicsCloseContactBuilder,
        JLI_OBJECT_TYPE_PhysicsField,
        JLI_OBJECT_TYPE_PhysicsFieldBuilder,
        JLI_OBJECT_TYPE_PhysicsRayContact,
        JLI_OBJECT_TYPE_PhysicsRayContactBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeBox,
        JLI_OBJECT_TYPE_PhysicsShapeBoxBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeBox2D,
        JLI_OBJECT_TYPE_PhysicsShapeBox2DBuilder,
        
        JLI_OBJECT_TYPE_PhysicsShapeSphere,
        JLI_OBJECT_TYPE_PhysicsShapeSphereBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeCylinder,
        JLI_OBJECT_TYPE_PhysicsShapeCylinderBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeCapsule,
        JLI_OBJECT_TYPE_PhysicsShapeCapsuleBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeCone,
        JLI_OBJECT_TYPE_PhysicsShapeConeBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeMultiSphere,
        JLI_OBJECT_TYPE_PhysicsShapeMultiSphereBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeConvexHull,
        JLI_OBJECT_TYPE_PhysicsShapeConvexHullBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMesh,
        JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMeshBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMesh,
        JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMeshBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrain,
        JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrainBuilder,
        JLI_OBJECT_TYPE_PhysicsShapeStaticPlane,
        JLI_OBJECT_TYPE_PhysicsShapeStaticPlaneBuilder,
        
        
        JLI_OBJECT_TYPE_PhysicsWorld,
        JLI_OBJECT_TYPE_PhysicsWorldBuilder,
        JLI_OBJECT_TYPE_Plane,
        JLI_OBJECT_TYPE_PlaneBuilder,
        JLI_OBJECT_TYPE_Scene,
        JLI_OBJECT_TYPE_SceneBuilder,
        JLI_OBJECT_TYPE_SceneState,
        JLI_OBJECT_TYPE_SceneStateBuilder,
        JLI_OBJECT_TYPE_SceneStateMachine,
        JLI_OBJECT_TYPE_SceneStateMachineBuilder,
        JLI_OBJECT_TYPE_ShaderProgram,
        JLI_OBJECT_TYPE_ShaderProgramBuilder,
        JLI_OBJECT_TYPE_Skinner,
        JLI_OBJECT_TYPE_SkinnerBuilder,
        JLI_OBJECT_TYPE_SliderHUD,
        JLI_OBJECT_TYPE_SliderHUDBuilder,
        JLI_OBJECT_TYPE_Sound,
        JLI_OBJECT_TYPE_SoundBuilder,
        JLI_OBJECT_TYPE_Sprite2D,
        JLI_OBJECT_TYPE_Sprite2DBuilder,
        JLI_OBJECT_TYPE_SpriteFrameAtlas,
        JLI_OBJECT_TYPE_SpriteFrameAtlasBuilder,
        
        JLI_OBJECT_TYPE_SteeringBehavior,
        JLI_OBJECT_TYPE_SteeringBehaviorBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorAlignment,
        JLI_OBJECT_TYPE_SteeringBehaviorAlignmentBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorArrive,
        JLI_OBJECT_TYPE_SteeringBehaviorArriveBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorCohesion,
        JLI_OBJECT_TYPE_SteeringBehaviorCohesionBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorEvade,
        JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorFlee,
        JLI_OBJECT_TYPE_SteeringBehaviorFleeBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorFollowPath,
        JLI_OBJECT_TYPE_SteeringBehaviorFollowPathBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorHide,
        JLI_OBJECT_TYPE_SteeringBehaviorHideBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorInterpose,
        JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorMachine,
        JLI_OBJECT_TYPE_SteeringBehaviorMachineBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorMachineDithered,
        JLI_OBJECT_TYPE_SteeringBehaviorMachineDitheredBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritized,
        JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritizedBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorMachineWeighted,
        JLI_OBJECT_TYPE_SteeringBehaviorMachineWeightedBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidance,
        JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidanceBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuit,
        JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuitBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorPursuit,
        JLI_OBJECT_TYPE_SteeringBehaviorPursuitBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorSeek,
        JLI_OBJECT_TYPE_SteeringBehaviorSeekBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorSeparation,
        JLI_OBJECT_TYPE_SteeringBehaviorSeparationBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidance,
        JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidanceBuilder,
        JLI_OBJECT_TYPE_SteeringBehaviorWander,
        JLI_OBJECT_TYPE_SteeringBehaviorWanderBuilder,
        
        JLI_OBJECT_TYPE_StopWatch,
        JLI_OBJECT_TYPE_StopWatchBuilder,
        JLI_OBJECT_TYPE_TextboxHUD,
        JLI_OBJECT_TYPE_TextboxHUDBuilder,
        JLI_OBJECT_TYPE_Thread,
        JLI_OBJECT_TYPE_ThreadBuilder,
        JLI_OBJECT_TYPE_Timer,
        JLI_OBJECT_TYPE_TimerBuilder,
        JLI_OBJECT_TYPE_WorldState,
        JLI_OBJECT_TYPE_WorldStateBuilder,
        JLI_OBJECT_TYPE_WorldStateMachine,
        JLI_OBJECT_TYPE_WorldStateMachineBuilder,
        JLI_OBJECT_TYPE_Xml,
        JLI_OBJECT_TYPE_XmlBuilder,
        JLI_OBJECT_TYPE_NumberOfTypes
    };
    
    
}
#endif
