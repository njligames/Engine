CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)
PROJECT (NJLIGameEngine)

# The version number.
SET ( NJLIGameEngine_VERSION_MAJOR 1 )
SET ( NJLIGameEngine_VERSION_MINOR 0 )

SET ( CMAKE_INSTALL_INCLUDEDIR include/ CACHE STRING "The include directory" )
SET ( CMAKE_INSTALL_DATADIR data/ CACHE STRING "The data directory" )
SET ( CMAKE_INSTALL_DOCDIR doc/ CACHE STRING "The documentation directory" )
SET ( CMAKE_INSTALL_TESTDIR tests/ CACHE STRING "The tests directory" )
SET ( NJLI_THIRDPARTY_DIRECTORY "${CMAKE_SOURCE_DIR}/../External/thirdparty/" CACHE STRING "The third party include directory" )
SET ( NJLI_GRAPHICS_PLATFORM opengl_es_2.0 CACHE STRING  "The rendering platform to use" )
SET ( NJLI_BUILD_PLATFORM macOS CACHE STRING "The platform being created" )
SET ( NJLI_SOUND_PLATFORM fmod CACHE STRING "The sound to use" )
SET ( NJLI_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/src" CACHE STRING "The njli source directory" )
SET ( NJLI_SWIGIN_DIRECTORY "${CMAKE_SOURCE_DIR}/src/swig.in/" CACHE STRING "The njli source directory" )

SET( NJLI_ASSIMP_POSTFIX "" )
SET( NJLI_FMOD_POSTFIX "" )
STRING( COMPARE EQUAL "${CMAKE_BUILD_TYPE}" "Debug" is_equal )
IF( is_equal )
    SET(NJLI_ASSIMP_POSTFIX "d")
    SET(NJLI_FMOD_POSTFIX "L")
ENDIF( is_equal )

SET( NJLI_FMOD_EXTENSION "a")
IF( ${NJLI_FMOD_EXTENSION} EQUAL macOS )
    SET( NJLI_FMOD_EXTENSION "dylib" )
ELSEIF( ${NJLI_FMOD_EXTENSION} EQUAL android )
    SET( NJLI_FMOD_EXTENSION "so" )
ENDIF()

# configure a header file to pass some of the CMake settings
# to the source code
CONFIGURE_FILE (
    "${CMAKE_SOURCE_DIR}/cmake.in/NJLIGameEngineConfig.h.in"
    "${NJLI_SOURCE_DIRECTORY}/njli/generated/NJLIGameEngineConfig.h"
    )

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    ADD_CUSTOM_TARGET(documentation ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake.in
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
    INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/docbook DESTINATION ${CMAKE_INSTALL_DOCDIR})
    INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
    INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/latex DESTINATION ${CMAKE_INSTALL_DOCDIR})
    INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/rtf DESTINATION ${CMAKE_INSTALL_DOCDIR})
    INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/xml DESTINATION ${CMAKE_INSTALL_DOCDIR})
ENDIF(DOXYGEN_FOUND)

ADD_CUSTOM_TARGET(luadoc ALL
    ldoc ${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/ldoc.in/
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with LDoc" VERBATIM
    )
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ldoc DESTINATION ${CMAKE_INSTALL_DOCDIR})

SET(NJLIGameEngine_TESTFILES
    ${CMAKE_SOURCE_DIR}/cmake.in/Tests.in/lua/njli_test.lua
    )
INSTALL(FILES ${NJLIGameEngine_TESTFILES} DESTINATION ${CMAKE_INSTALL_TESTDIR})

SET(NJLIGameEngine_DATAFILES
    ${CMAKE_SOURCE_DIR}/cmake.in/DoxyFiles.in/images/logo.png
    )
INSTALL(FILES ${NJLIGameEngine_DATAFILES} DESTINATION ${CMAKE_INSTALL_DATADIR})

    
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
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/*.h
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/*.cpp
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/.*([.]cpp|[.]c|[.]h|[.]hpp)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND njli_generated_swig_lua ${filename})
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
    #"${NJLI_SOURCE_DIRECTORY}/lua/src/lua.h"
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
    ${njli_generated_swig_lua}
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

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/graphics/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/graphics/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/graphics/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_graphics ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/body/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/body/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/body/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_physics_body ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/constraint/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/constraint/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/constraint/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_physics_constraint ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/shape/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/shape/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/physics/shape/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_physics_shape ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/platform/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/platform/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/platform/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_platform ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

file( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/sound*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/sound*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/sound.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_sound ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/steering/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/steering/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/steering/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_steering ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/steering/behavior/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/steering/behavior/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/builders/steering/behavior/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_builders_steering_behavior ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/graphics/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/graphics/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/graphics/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_graphics ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_physics ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/body/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/body/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/body/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_physics_body ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/constraint/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/constraint/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/constraint/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_physics_constraint ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/shape/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/shape/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/physics/shape/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_physics_shape ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/platform/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/platform/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/platform/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_platform ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/sound/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/sound/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/sound/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_sound ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/steering/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/steering/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/steering/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_steering ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE( GLOB src
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/steering/behavior/*.i"
    "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/steering/behavior/*.swg"
    )
SET(REG "${NJLI_SOURCE_DIRECTORY}/swig.in/lua/njli/steering/behavior/.*([.]i|[.]swg)")
FOREACH(filename ${src})
    STRING(REGEX MATCH "${REG}" match_group_sources ${filename})
    IF(match_group_sources)
        LIST(APPEND swigin_lua_njli_steering_behavior ${filename})
    ELSE()
        LIST(APPEND interface_group_other ${filename})
    ENDIF()
ENDFOREACH()

FILE(GLOB NJLIGameEngine_ITFS
    ${swigin} 
    ${swigin_lua} 
    ${swigin_lua_njli} 
    ${swigin_lua_njli_builders} 
    ${swigin_lua_njli_builders_graphics} 
    ${swigin_lua_njli_builders} 
    ${swigin_lua_njli_builders_physics_body} 
    ${swigin_lua_njli_builders_physics_constraint} 
    ${swigin_lua_njli_builders_physics_shape} 
    ${swigin_lua_njli_builders_platform} 
    ${swigin_lua_njli_builders_sound} 
    ${swigin_lua_njli_builders_steering} 
    ${swigin_lua_njli_builders_steering_behavior} 
    ${swigin_lua_njli_graphics} 
    ${swigin_lua_njli_physics} 
    ${swigin_lua_njli_physics_body} 
    ${swigin_lua_njli_physics_constraint} 
    ${swigin_lua_njli_physics_shape} 
    ${swigin_lua_njli_platform} 
    ${swigin_lua_njli_sound} 
    ${swigin_lua_njli_steering} 
    ${swigin_lua_njli_steering_behavior} 
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

IF( ${NJLI_BUILD_PLATFORM} STREQUAL "appletvos" )
    SET( CMAKE_OSX_SYSROOT "appletvos" )
    SET( CMAKE_XCODE_EFFECTIVE_PLATFORMS "-appletvos;-appletvsimulator" )

    FILE(GLOB NJLIGameEngine_LBY
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/assimp/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libassimp${NJLI_ASSIMP_POSTFIX}.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet2FileLoader.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Collision.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Common.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Dynamics.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Geometry.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3OpenCL_clew.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletCollision.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletDynamics.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletFileLoader.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletInverseDynamics.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletInverseDynamicsUtils.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletSoftBody.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletWorldImporter.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletXmlWorldImporter.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libConvexDecomposition.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libGIMPACTUtils.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libHACD.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/lib/libLinearMath.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/imgui/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libimgui.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/ImGuizmo/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libImGuizmo.a
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/jsoncpp/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libjsoncpp.a
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/nanovg/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libnanovg.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/stb/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libstb.a
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/tinyxml2/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libtinyxml2.a
        ${NJLI_THIRDPARTY_DIRECTORY}/fmod/lib/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libfmod.${NJLI_FMOD_EXTENSION}
        ${NJLI_THIRDPARTY_DIRECTORY}/SDL/lib/${NJLI_BUILD_PLATFORM}/10.2/${CMAKE_OSX_SYSROOT}/Release/libSDL2.a
        )

    SET ( CMAKE_OSX_ARCHITECTURES ${ARCHS_STANDARD_32_BIT} CACHE string "Build architecture for iOS" )
    SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden" )
    SET ( EXTRA_PLATFORM_LIBS
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

    SET( ICONS 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Icon.png" 
        )
    SET( IMAGES 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Default.png" 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Default-568h@2x.png" 
        )
    SET( NJLI_RESOURCES ${ICONS} ${IMAGES} )
    SET( NJLI_DEVICE_FAMILY "3" )
ELSEIF( ${NJLI_BUILD_PLATFORM} STREQUAL "ios" )
    SET( CMAKE_OSX_SYSROOT "iphoneos" )
    SET( CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator" )

    FILE(GLOB NJLIGameEngine_LBY
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/assimp/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libassimp${NJLI_ASSIMP_POSTFIX}.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet2FileLoader.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Collision.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Common.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Dynamics.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3Geometry.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBullet3OpenCL_clew.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletCollision.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletDynamics.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletFileLoader.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletInverseDynamics.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletInverseDynamicsUtils.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletSoftBody.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletWorldImporter.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libBulletXmlWorldImporter.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libConvexDecomposition.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libGIMPACTUtils.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libHACD.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/bullet3/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/lib/libLinearMath.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/imgui/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libimgui.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/ImGuizmo/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libImGuizmo.a
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/jsoncpp/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libjsoncpp.a
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/nanovg/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libnanovg.a 
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/stb/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libstb.a
        ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/tinyxml2/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libtinyxml2.a
        ${NJLI_THIRDPARTY_DIRECTORY}/fmod/lib/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libfmod.${NJLI_FMOD_EXTENSION}
        ${NJLI_THIRDPARTY_DIRECTORY}/SDL/lib/${NJLI_BUILD_PLATFORM}/10.3/${CMAKE_OSX_SYSROOT}/Release/libSDL2.a
        )

    SET ( CMAKE_OSX_ARCHITECTURES ${ARCHS_STANDARD_32_BIT} CACHE string "Build architecture for iOS" )
    SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden" )
    SET ( EXTRA_PLATFORM_LIBS
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

    SET( ICONS 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Icon.png" 
        )
    SET( IMAGES 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Default.png" 
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Default-568h@2x.png" 
        )
    SET( NJLI_RESOURCES ${ICONS} ${IMAGES} )
    SET( NJLI_DEVICE_FAMILY "1,2" )


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

INCLUDE_DIRECTORIES( ${NJLIGameEngine_HDRS} )


IF(XCODE)
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
    SOURCE_GROUP("Sources\\njli\\generated\\swig\\lua"                FILES ${njli_generated_swig_lua})
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

    ADD_EXECUTABLE( Source ${NJLIGameEngine_SRCS} ${NJLI_RESOURCES} )
    IF( ${NJLI_BUILD_PLATFORM} STREQUAL "appletvos" OR ${NJLI_BUILD_PLATFORM} STREQUAL "ios" )
        SET_TARGET_PROPERTIES (
            Source
            PROPERTIES
            MACOSX_BUNDLE YES
            MACOSX_BUNDLE_INFO_PLIST
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Info.plist"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY ${NJLI_DEVICE_FAMILY}
            XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
            XCODE_ATTRIBUTE_INSTALL_PATH "${CMAKE_BINARY_DIR}/ProductRelease"
            XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES "NO"
            RESOURCE "${NJLI_RESOURCES}"
            )
        SET_TARGET_PROPERTIES(
            Source
            PROPERTIES
            XCODE_ATTRIBUTE_PRODUCT_NAME
            NJLIGameEngine
            XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER
            "com.njligames.engine.${NJLI_BUILD_PLATFORM}.source"
            )
    ENDIF()
    ADD_DEPENDENCIES( Source swig)
    TARGET_LINK_LIBRARIES( Source ${NJLIGameEngine_LBY} ${EXTRA_PLATFORM_LIBS}  )

    ADD_EXECUTABLE( Library 
        ${NJLI_SOURCE_DIRECTORY}/njli/platform/main.cpp 
        #${NJLI_SOURCE_DIRECTORY}/njli/platform/Game.h 
        #${NJLI_SOURCE_DIRECTORY}/njli/platform/Game.cpp
        ${NJLI_RESOURCES} 
        )

    IF( ${NJLI_BUILD_PLATFORM} STREQUAL "appletvos" OR ${NJLI_BUILD_PLATFORM} STREQUAL "ios" )
        SET_TARGET_PROPERTIES (
            Library
            PROPERTIES
            MACOSX_BUNDLE YES
            MACOSX_BUNDLE_INFO_PLIST
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake.in/Platform.in/${NJLI_BUILD_PLATFORM}/Info.plist"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY ${NJLI_DEVICE_FAMILY}
            XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
            XCODE_ATTRIBUTE_INSTALL_PATH "${CMAKE_BINARY_DIR}/ProductRelease"
            XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES "NO"
            RESOURCE "${NJLI_RESOURCES}"
            )
        SET_TARGET_PROPERTIES(
            Library
            PROPERTIES
            XCODE_ATTRIBUTE_PRODUCT_NAME
            NJLIGameEngine
            XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER
            "com.njligames.engine.${NJLI_BUILD_PLATFORM}.source"
            )
    ENDIF()
    ADD_DEPENDENCIES( Library libnjli_static swig )
    TARGET_LINK_LIBRARIES( Library libnjli_static ${NJLI_THIRDPARTY_DIRECTORY}/SDL/lib/${NJLI_BUILD_DIR}/Release/libSDL2.a ${EXTRA_PLATFORM_LIBS} )
ENDIF(XCODE)

LIST(REMOVE_ITEM NJLIGameEngine_SRCS 
    ${NJLI_SOURCE_DIRECTORY}/njli/platform/main.cpp
    )
LIST(REMOVE_ITEM NJLIGameEngine_LBY 
    ${NJLI_THIRDPARTY_DIRECTORY}/SDL/lib/${NJLI_BUILD_DIR}/Release/libSDL2.a
    )
ADD_LIBRARY( libnjli_static STATIC ${NJLIGameEngine_SRCS} )
SET_TARGET_PROPERTIES( libnjli_static PROPERTIES OUTPUT_NAME libnjli )
SET_TARGET_PROPERTIES( libnjli_static PROPERTIES PREFIX "")
ADD_DEPENDENCIES( libnjli_static swig)
TARGET_LINK_LIBRARIES( libnjli_static ${NJLIGameEngine_LBY} ${EXTRA_PLATFORM_LIBS} )
INSTALL( TARGETS libnjli_static DESTINATION lib/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE} )

ADD_LIBRARY( libnjli_shared SHARED ${NJLIGameEngine_SRCS} )
SET_TARGET_PROPERTIES( libnjli_shared PROPERTIES OUTPUT_NAME libnjli )
SET_TARGET_PROPERTIES( libnjli_shared PROPERTIES PREFIX "")
ADD_DEPENDENCIES( libnjli_shared swig)
TARGET_LINK_LIBRARIES( libnjli_shared ${EXTRA_PLATFORM_LIBS} ${NJLIGameEngine_LBY} )
INSTALL( TARGETS libnjli_shared DESTINATION lib/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE} )

IF(NOT XCODE)
    ADD_LIBRARY( libnjli_lua_module MODULE ${NJLIGameEngine_SRCS} )
    SET_TARGET_PROPERTIES( libnjli_lua_module PROPERTIES OUTPUT_NAME njli )
    SET_TARGET_PROPERTIES( libnjli_lua_module PROPERTIES PREFIX "")
    ADD_DEPENDENCIES( libnjli_lua_module swig)
    TARGET_LINK_LIBRARIES( libnjli_lua_module ${NJLIGameEngine_LBY} ${EXTRA_PLATFORM_LIBS} )
    INSTALL( TARGETS libnjli_lua_module DESTINATION module/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE} )
ENDIF(NOT XCODE)

SET(Binary_FILES
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/lua/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/bin/lua${NJLI_BINARY_EXTENSION}
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/lua/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/bin/luac${NJLI_BINARY_EXTENSION}
    ${NJLI_THIRDPARTY_DIRECTORY}/BUILD/lib/assimp/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE}/bin/assimp${NJLI_ASSIMP_POSTFIX}${NJLI_BINARY_EXTENSION}
    )
INSTALL(PROGRAMS ${Binary_FILES} DESTINATION bin/thirdparty/${NJLI_BUILD_DIR}/${CMAKE_BUILD_TYPE} )
INSTALL(FILES ${NJLI_SOURCE_DIRECTORY}/njli/platform/Game.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#EXECUTE_PROCESS(COMMAND ./swig_lua.sh ${CMAKE_CURRENT_BINARY_DIR}
#    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#    RESULT_VARIABLE swig_result
#    OUTPUT_VARIABLE swig_ver)
#INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lnjli.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/swig/lua)
#INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lbullet.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/swig/lua)
                                        
ADD_CUSTOM_COMMAND(
    OUTPUT ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/lnjli.cpp ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/lbullet.cpp
    COMMAND ./swig_lua.sh ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${NJLIGameEngine_SRCS} ${NJLIGameEngine_HDRS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
SET_SOURCE_FILES_PROPERTIES( ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/lnjli.cpp PROPERTIES GENERATED TRUE )
SET_SOURCE_FILES_PROPERTIES( ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/lbullet.cpp PROPERTIES GENERATED TRUE )
SET_SOURCE_FILES_PROPERTIES( ${CMAKE_CURRENT_BINARY_DIR}/lnjli.xml PROPERTIES GENERATED TRUE )
SET_SOURCE_FILES_PROPERTIES( ${CMAKE_CURRENT_BINARY_DIR}/lbullet.xml PROPERTIES GENERATED TRUE )
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lnjli.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/swig/lua)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lbullet.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/swig/lua)
ADD_CUSTOM_TARGET( swig ALL DEPENDS 
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/lnjli.cpp 
    ${NJLI_SOURCE_DIRECTORY}/njli/generated/swig/lua/lbullet.cpp 
    ${CMAKE_CURRENT_BINARY_DIR}/lnjli.xml
    ${CMAKE_CURRENT_BINARY_DIR}/lbullet.xml
    SOURCES ${NJLIGameEngine_ITFS}
    )

SOURCE_GROUP("Interfaces\\swig.in" FILES ${swigin} )
SOURCE_GROUP("Interfaces\\swig.in\\lua" FILES ${swigin_lua} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli" FILES ${swigin_lua_njli} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders" FILES ${swigin_lua_njli_builders} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders" FILES ${swigin_lua_njli_builders_graphics} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders" FILES ${swigin_lua_njli_builders} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders\\physics\\body" FILES ${swigin_lua_njli_builders_physics_body} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders\\physics\\constraint" FILES ${swigin_lua_njli_builders_physics_constraint} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders\\physics\\shape" FILES ${swigin_lua_njli_builders_physics_shape} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders\\platform" FILES ${swigin_lua_njli_builders_platform} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders\\sound" FILES ${swigin_lua_njli_builders_sound} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders\\steering" FILES ${swigin_lua_njli_builders_steering} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\builders\\steering\\behavior" FILES ${swigin_lua_njli_builders_steering_behavior} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\graphics" FILES ${swigin_lua_njli_graphics} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\physics" FILES ${swigin_lua_njli_physics} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\physics\\body" FILES ${swigin_lua_njli_physics_body} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\physics\\constraint" FILES ${swigin_lua_njli_physics_constraint} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\physics\\shape" FILES ${swigin_lua_njli_physics_shape} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\platform" FILES ${swigin_lua_njli_platform} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\sound" FILES ${swigin_lua_njli_sound} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\steering" FILES ${swigin_lua_njli_steering} )
SOURCE_GROUP("Interfaces\\swig.in\\lua\\njli\\steering\\behavior" FILES ${swigin_lua_njli_steering_behavior} )
