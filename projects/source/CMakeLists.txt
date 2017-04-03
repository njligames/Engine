CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)
PROJECT (NJLIGameEngine)


SET ( CMAKE_SOURCE_DIR "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/source" )
SET ( CMAKE_CURRENT_SOURCE_DIR "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/source" )

SET ( NJLI_THIRDPARTY_DIRECTORY "${CMAKE_SOURCE_DIR}/../External/thirdparty/" CACHE STRING "The third party include directory")
SET ( NJLI_THIRDPARTY_DIRECTORY "${CMAKE_SOURCE_DIR}/../External/thirdparty/" CACHE STRING "The third party include directory")
SET ( NJLI_GRAPHICS_PLATFORM opengl_es_2.0 CACHE STRING  "The rendering platform to use" )
SET ( NJLI_BUILD_PLATFORM macOS CACHE STRING "The platform being created" )
SET ( NJLI_SOUND_PLATFORM fmod CACHE STRING "The sound to use" )
SET ( NJLI_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/src" CACHE STRING "The njli source directory")
SET ( NJLI_SWIGIN_DIRECTORY "${CMAKE_SOURCE_DIR}/src/swig.in/" CACHE STRING "The njli source directory")

SET( NJLI_ASSIMP_POSTFIX "" )
SET( NJLI_FMOD_POSTFIX "" )
string( COMPARE EQUAL "${CMAKE_BUILD_TYPE}" "Debug" is_equal )
IF( is_equal )
    SET(NJLI_ASSIMP_POSTFIX "d")
    SET(NJLI_FMOD_POSTFIX "L")
ENDIF()

SET( NJLI_FMOD_EXTENSION "a")
IF( ${NJLI_FMOD_EXTENSION} EQUAL macOS )
    SET( NJLI_FMOD_EXTENSION "dylib" )
ELSEIF( ${NJLI_FMOD_EXTENSION} EQUAL android )
    SET( NJLI_FMOD_EXTENSION "so" )
ENDIF()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/platform/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/platform/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/platform/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_platform ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE(GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/platform/${NJLI_BUILD_PLATFORM}/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/platform/${NJLI_BUILD_PLATFORM}/*.mm
    ${NJLI_SOURCE_DIRECTORY}/njli/platform/${NJLI_BUILD_PLATFORM}/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/platform/${NJLI_BUILD_PLATFORM}/.*([.]cpp|[.]c|[.]h|[.]hpp|[.]m|[.]mm)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_platform_specific ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/bullet/*.h
    ${NJLI_SOURCE_DIRECTORY}/bullet/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/bullet/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND bullet ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/graphics/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/graphics/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/graphics/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_graphics ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_physics ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/body/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/body/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/body/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_physics_body ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/constraint/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/constraint/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/constraint/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_physics_constraint ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/shape/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/shape/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/shape/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_physics_shape ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/platform/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/platform/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/platform/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_platform ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/sound/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/sound/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/sound/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_sound ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()
    
FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/steering/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/steering/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/steering/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_steering ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/steering/behavior/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/steering/behavior/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/builders/steering/behavior/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_builders_steering_behavior ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/generated/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_generated ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_generated_swig ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/graphics/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/graphics/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/graphics/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_graphics ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/graphics/${NJLI_GRAPHICS_PLATFORM}/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/graphics/${NJLI_GRAPHICS_PLATFORM}/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/graphics/${NJLI_GRAPHICS_PLATFORM}/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_graphics_specific ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/physics/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_physics ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/body/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/body/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/physics/body/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_physics_body ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/constraint/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/constraint/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/physics/constraint/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_physics_constraint ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/shape/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/shape/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/physics/shape/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_physics_shape ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()
    
file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/sound/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/sound/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/sound/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_sound ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/sound/${NJLI_SOUND_PLATFORM}/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/sound/${NJLI_SOUND_PLATFORM}/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/sound/${NJLI_SOUND_PLATFORM}/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_sound_specific ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/steering/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/steering/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/steering/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_steering ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    ${NJLI_SOURCE_DIRECTORY}/njli/steering/behavior/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/steering/behavior/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/steering/behavior/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_steering_behavior ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()


file( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/*.h"
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/*.c"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/lua/exts/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND lua_exts ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket/*.h"
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket/*.c"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND lua_exts_luasocket ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/lua/src/*.h"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/*.c"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/lua/src/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND lua_src ${filename})
    ELSE()
        LIST(APPEND group_other ${filename})
    ENDIF()
ENDFOREACH()

MESSAGE("${lua_exts}")


LIST(REMOVE_ITEM lua_exts_luasocket 
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket/compat.c"
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket/compat.h"
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket/wsocket.c"
    "${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket/wsocket.h"
    )
LIST(REMOVE_ITEM lua_src 
    "${NJLI_SOURCE_DIRECTORY}/lua/src/loadlib_rel.c"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/lobject.h"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/lua.c"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/lua.h"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/lua.rc"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/luac.c"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/luac.rc"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/luaconf.h.in"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/lualib.h"
    "${NJLI_SOURCE_DIRECTORY}/lua/src/wmain.c"
    )
FILE(GLOB NJLIGameEngine_SRCS
    ${bullet} 
    ${group_other}
    ${lua_exts} 
    ${lua_exts_luasocket} 
    ${lua_src} 
    ${njli} 
    ${njli_builders}
    ${njli_builders_graphics}
    ${njli_builders_physics}
    ${njli_builders_physics_body}
    ${njli_builders_physics_constraint}
    ${njli_builders_physics_shape}
    ${njli_builders_platform}
    ${njli_builders_sound}
    ${njli_builders_steering}
    ${njli_builders_steering_behavior}
    ${njli_generated}
    ${njli_generated_swig}
    ${njli_graphics}
    ${njli_graphics_specific}
    ${njli_physics}
    ${njli_physics_body}
    ${njli_physics_constraint}
    ${njli_physics_shape}
    ${njli_platform} 
    ${njli_platform_specific} 
    ${njli_sound}
    ${njli_sound_specific}
    ${njli_steering}
    ${njli_steering_behavior}
    )

FILE(GLOB NJLIGameEngine_HDRS
    ${NJLI_SOURCE_DIRECTORY} 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/assimp 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet2FileLoader 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet2FileLoader/autogenerated 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Collision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Collision/BroadPhaseCollision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Collision/BroadPhaseCollision/shared 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Collision/NarrowPhaseCollision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Collision/NarrowPhaseCollision/shared 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Common 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Common/shared 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Dynamics 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Dynamics/ConstraintSolver 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Dynamics/shared 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3Geometry 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/BroadphaseCollision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/BroadphaseCollision/kernels 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/Initialize 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/NarrowphaseCollision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/NarrowphaseCollision/kernels 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/ParallelPrimitives 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/ParallelPrimitives/kernels 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/Raycast 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/Raycast/kernels 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/RigidBody 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/Bullet3OpenCL/RigidBody/kernels 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletCollision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletCollision/BroadphaseCollision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletCollision/CollisionDispatch 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletCollision/CollisionShapes 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletCollision/Gimpact 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletCollision/NarrowPhaseCollision 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletDynamics 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletDynamics/Character 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletDynamics/ConstraintSolver 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletDynamics/Dynamics 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletDynamics/Featherstone 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletDynamics/MLCPSolvers 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletDynamics/Vehicle 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletFileLoader 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletFileLoader/autogenerated 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletInverseDynamics 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletInverseDynamics/details 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletSoftBody 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletWorldImporter 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/BulletXmlWorldImporter 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/ConvexDecomposition 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/GIMPACTUtils 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/HACD 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/InverseDynamics 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/bullet3/LinearMath 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/glm 
    ${NJLI_THIRDPARTY_DIRECTORY}/fmod/include 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/imgui 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/ImGuizmo 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/jsoncpp 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/nanovg 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/stb 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/include/tinyxml2 
    ${NJLI_SOURCE_DIRECTORY}/bullet 
    ${NJLI_SOURCE_DIRECTORY}/lua/src 
    ${NJLI_SOURCE_DIRECTORY}/lua/exts 
    ${NJLI_SOURCE_DIRECTORY}/lua/exts/luasocket 
    ${NJLI_SOURCE_DIRECTORY}/njli 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/graphics 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/body 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/constraint 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/physics/shape 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/platform 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/sound 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/steering 
    ${NJLI_SOURCE_DIRECTORY}/njli/builders/steering/behavior 
    ${NJLI_SOURCE_DIRECTORY}/njli/generated 
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig 
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua 
    ${NJLI_SOURCE_DIRECTORY}/njli/graphics 
    ${NJLI_SOURCE_DIRECTORY}/njli/graphics/${NJLI_GRAPHICS_PLATFORM} 
    ${NJLI_SOURCE_DIRECTORY}/njli/physics 
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/body 
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/constraint 
    ${NJLI_SOURCE_DIRECTORY}/njli/physics/shape 
    ${NJLI_SOURCE_DIRECTORY}/njli/sound 
    ${NJLI_SOURCE_DIRECTORY}/njli/steering 
    ${NJLI_SOURCE_DIRECTORY}/njli/steering/behavior 
    ${NJLI_SOURCE_DIRECTORY}/njli/platform 
    ${NJLI_SOURCE_DIRECTORY}/njli/platform/${NJLI_BUILD_PLATFORM} 
    ${NJLI_THIRDPARTY_DIRECTORY}/SDL/include
    )
IF( ${NJLI_BUILD_PLATFORM} STREQUAL "appletvos" )
    LIST(APPEND NJLIGameEngine_HDRS /Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS.sdk/System/Library/Frameworks )
ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "ios" )
    LIST(APPEND NJLIGameEngine_HDRS /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/System/Library/Frameworks  )
ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "macOS" )
    LIST(APPEND NJLIGameEngine_HDRS /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks  )
ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "emscripten" )
ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "android" )
    LIST(APPEND NJLIGameEngine_HDRS /Users/jamesfolk/Library/Android/sdk/ndk-bundle/platforms/android-24/arch-arm/usr/include  )
ENDIF()

FILE(GLOB NJLIGameEngine_LBY
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/assimp/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libassimp${NJLI_ASSIMP_POSTFIX}.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBullet2FileLoader.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBullet3Collision.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBullet3Common.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBullet3Dynamics.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBullet3Geometry.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBullet3OpenCL_clew.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletCollision.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletDynamics.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletFileLoader.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletInverseDynamics.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletInverseDynamicsUtils.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletSoftBody.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletWorldImporter.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libBulletXmlWorldImporter.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libConvexDecomposition.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libGIMPACTUtils.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libHACD.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/lib/libLinearMath.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/imgui/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libimgui.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/ImGuizmo/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libImGuizmo.a
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/jsoncpp/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libjsoncpp.a
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/nanovg/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libnanovg.a 
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/stb/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libstb.a
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/tinyxml2/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libtinyxml2.a
    )
IF( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
    LIST(APPEND NJLIGameEngine_LBY ${NJLI_THIRDPARTY_DIRECTORY}/fmod/lib/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libfmod.${NJLI_FMOD_EXTENSION})
    LIST(APPEND NJLIGameEngine_LBY ${NJLI_THIRDPARTY_DIRECTORY}/SDL/lib/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/libSDL2.a)
ELSE()
    LIST(APPEND NJLIGameEngine_LBY ${NJLI_THIRDPARTY_DIRECTORY}/fmod/lib/${NJLI_BUILD_DIR}/Release/libfmod.${NJLI_FMOD_EXTENSION})
    LIST(APPEND NJLIGameEngine_LBY ${NJLI_THIRDPARTY_DIRECTORY}/SDL/lib/${NJLI_BUILD_DIR}/Release/libSDL2.a)
ENDIF()

IF( ${NJLI_BUILD_PLATFORM} STREQUAL "appletvos" )
    set (IOS_SDK_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS.sdk")

    # Set the sysroot default to the most recent SDK
    set (CMAKE_OSX_SYSROOT ${IOS_SDK_ROOT} CACHE PATH "Sysroot used for iOS support")

    # set the architecture for iOS - this env var sets armv6,armv7 and appears to be XCode's standard. The other found is ARCHS_UNIVERSAL_IPHONE_OS but that is armv7 only
    set (CMAKE_OSX_ARCHITECTURES "${IOS_ARCH}" CACHE string "Build architecture for iOS")

    # set up the default search directories for frameworks
    set (CMAKE_SYSTEM_FRAMEWORK_PATH ${IOS_SDK_ROOT}/Developer/Library/Frameworks)

    #http://stackoverflow.com/questions/17070101/why-i-cannot-link-the-mac-framework-file-with-cmake
    SET(EXTRA_PLATFORM_LIBS "-framework Foundation -framework OpenGLES -framework AudioToolbox -framework AVFoundation -lfmod")

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden" )
ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "ios" )
    set (IOS_SDK_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.3.sdk")

    # Set the sysroot default to the most recent SDK
    set (CMAKE_OSX_SYSROOT ${IOS_SDK_ROOT} CACHE PATH "Sysroot used for iOS support")

    # set the architecture for iOS - this env var sets armv6,armv7 and appears to be XCode's standard. The other found is ARCHS_UNIVERSAL_IPHONE_OS but that is armv7 only
    set (CMAKE_OSX_ARCHITECTURES "${IOS_ARCH}" CACHE string "Build architecture for iOS")

    # set up the default search directories for frameworks
    set (CMAKE_SYSTEM_FRAMEWORK_PATH ${IOS_SDK_ROOT}/Developer/Library/Frameworks)

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden" )

ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "macOS" )
    set (IOS_SDK_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")

    # Set the sysroot default to the most recent SDK
    set (CMAKE_OSX_SYSROOT ${IOS_SDK_ROOT} CACHE PATH "Sysroot used for iOS support")

    # set the architecture for iOS - this env var sets armv6,armv7 and appears to be XCode's standard. The other found is ARCHS_UNIVERSAL_IPHONE_OS but that is armv7 only
    set (CMAKE_OSX_ARCHITECTURES "${IOS_ARCH}" CACHE string "Build architecture for iOS")

    # set up the default search directories for frameworks
    set (CMAKE_SYSTEM_FRAMEWORK_PATH ${IOS_SDK_ROOT}/Developer/Library/Frameworks)

    #http://stackoverflow.com/questions/17070101/why-i-cannot-link-the-mac-framework-file-with-cmake
    SET(EXTRA_PLATFORM_LIBS "-framework Foundation -framework AudioToolbox -framework AVFoundation -lfmod -lGLESv2")

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGL_GLEXT_PROTOTYPES -fvisibility=hidden" )
    SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGL_GLEXT_PROTOTYPES" )
    #SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -framework Foundation -framework AudioToolbox -framework AVFoundation -lfmod -lGLESv2" )

ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "emscripten" )
ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "android" )
    SET( EXTRA_PLATFORM_LIBS "-lfmod -ldl -lGLESv2 -llog -landroid -lm -lc -lEGL -lstdc++")
    SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGL_GLEXT_PROTOTYPES" )
ENDIF()

SOURCE_GROUP("Sources\\bullet"                                    FILES ${bullet} )
SOURCE_GROUP("Sources\\lua"                                       FILES ${group_other})
SOURCE_GROUP("Sources\\lua\\exts"                                 FILES ${lua_exts} )
SOURCE_GROUP("Sources\\lua\\exts\\luasocket"                      FILES ${lua_exts_luasocket} )
SOURCE_GROUP("Sources\\lua\\src"                                  FILES ${lua_src} )
SOURCE_GROUP("Sources\\njli"                                      FILES ${njli} )
SOURCE_GROUP("Sources\\njli\\builders"                            FILES ${njli_builders})
SOURCE_GROUP("Sources\\njli\\builders\\graphics"                  FILES ${njli_builders_graphics})
SOURCE_GROUP("Sources\\njli\\builders\\physics"                   FILES ${njli_builders_physics})
SOURCE_GROUP("Sources\\njli\\builders\\physics\\body"             FILES ${njli_builders_physics_body})
SOURCE_GROUP("Sources\\njli\\builders\\physics\\constraint"       FILES ${njli_builders_physics_constraint})
SOURCE_GROUP("Sources\\njli\\builders\\physics\\shape"            FILES ${njli_builders_physics_shape})
SOURCE_GROUP("Sources\\njli\\builders\\platform"                  FILES ${njli_builders_platform})
SOURCE_GROUP("Sources\\njli\\builders\\sound"                     FILES ${njli_builders_sound})
SOURCE_GROUP("Sources\\njli\\builders\\steering"                  FILES ${njli_builders_steering})
SOURCE_GROUP("Sources\\njli\\builders\\steering\\behavior"        FILES ${njli_builders_steering_behavior})
SOURCE_GROUP("Sources\\njli\\generated"                           FILES ${njli_generated})
SOURCE_GROUP("Sources\\njli\\generated\\swig"                     FILES ${njli_generated_swig})
SOURCE_GROUP("Sources\\njli\\graphics"                            FILES ${njli_graphics})
SOURCE_GROUP("Sources\\njli\\graphics\\${NJLI_GRAPHICS_PLATFORM}" FILES ${njli_graphics_specific})
SOURCE_GROUP("Sources\\njli\\physics"                             FILES ${njli_physics})
SOURCE_GROUP("Sources\\njli\\physics\\body"                       FILES ${njli_physics_body})
SOURCE_GROUP("Sources\\njli\\physics\\constraint"                 FILES ${njli_physics_constraint})
SOURCE_GROUP("Sources\\njli\\physics\\shape"                      FILES ${njli_physics_shape})
SOURCE_GROUP("Sources\\njli\\platform"                            FILES ${njli_platform} )
SOURCE_GROUP("Sources\\njli\\platform\\${NJLI_BUILD_PLATFORM}"    FILES ${njli_platform_specific} )
SOURCE_GROUP("Sources\\njli\\sound"                               FILES ${njli_sound})
SOURCE_GROUP("Sources\\njli\\sound\\${NJLI_SOUND_PLATFORM}"       FILES ${njli_sound_specific})
SOURCE_GROUP("Sources\\njli\\steering"                            FILES ${njli_steering})
SOURCE_GROUP("Sources\\njli\\steering\\behavior"                  FILES ${njli_steering_behavior})

INCLUDE_DIRECTORIES( NJLIGameEngine_HDRS )
ADD_EXECUTABLE( Source ${NJLIGameEngine_SRCS} ${IOS_RESOURCES} )
SET_TARGET_PROPERTIES( Source PROPERTIES OUTPUT_NAME njli_source_project )
SET_TARGET_PROPERTIES( Source PROPERTIES PREFIX "")
TARGET_LINK_LIBRARIES( Source ${NJLIGameEngine_LBY} )

IF(XCODE)
    SET( CMAKE_OSX_SYSROOT "iphoneos" )
    SET( CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator" )
    SET( CMAKE_DEBUG_POSTFIX d )

    SET( IOS_ICONS 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/ios/Icon.png" 
        )
    SET( IOS_IMAGES 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/ios/Default.png" 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/ios/Default-568h@2x.png" 
        )
    SET( IOS_RESOURCES ${IOS_ICONS} ${IOS_IMAGES} )


    SET_TARGET_PROPERTIES (
        Source
        PROPERTIES
        MACOSX_BUNDLE YES
        MACOSX_BUNDLE_INFO_PLIST
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/ios/Info.plist"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
        XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
        XCODE_ATTRIBUTE_INSTALL_PATH "${CMAKE_BINARY_DIR}/ProductRelease"
        XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES "NO"
        RESOURCE "${IOS_RESOURCES}"
        )
    SET_TARGET_PROPERTIES(
        Source
        PROPERTIES
        XCODE_ATTRIBUTE_PRODUCT_NAME
        NJLIGameEngine
        XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER
        "com.njligames.engine.ios.source"
        )

    TARGET_LINK_LIBRARIES(
        Source
        "-framework AVFoundation"
        "-framework GameController"
        "-framework CoreMotion"
        "-framework CoreGraphics"
        "-framework AudioToolbox"
        "-framework QuartzCore"
        "-framework OpenGLES"
        "-framework UIKit"
        "-framework Foundation"
        )
ENDIF(XCODE)

