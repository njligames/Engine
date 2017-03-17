#!/bin/sh

PWD=`pwd`

MY_NJLI_INTERFACE_DIRECTORY=${PWD}/src/swig.in/lua
MY_BULLET_INTERFACE_DIRECTORY=${PWD}/../External/thirdparty/swig.in/lua/bullet3

MY_NJLI_SOURCE_DIRECTORY=${PWD}/src/njli
MY_NJLI_BULLET_SOURCE_DIRECTORY=${PWD}/src/bullet
MY_BULLET_SOURCE_DIRECTORY=${PWD}/../External/thirdparty/bullet3/src

MY_GENERATED_DIRECTORY=${MY_NJLI_SOURCE_DIRECTORY}/generated/swig/lua

MY_NJLI_CPP_OUTPUT=${MY_GENERATED_DIRECTORY}/lnjli.cpp
MY_BULLET_CPP_OUTPUT=${MY_GENERATED_DIRECTORY}/lbullet.cpp

MY_RUNTIME_OUTPUT=${MY_GENERATED_DIRECTORY}/swig_runtime.h

MY_XML_OUTPUT_DIRECTORY=$1

rm -rf ${MY_NJLI_SOURCE_DIRECTORY}/generated/swig/lua
mkdir -p ${MY_NJLI_SOURCE_DIRECTORY}/generated/swig/lua

if [ -z "${MY_XML_OUTPUT_DIRECTORY}" ]
then
    MY_XML_OUTPUT_DIRECTORY=.
fi

#bullet.
/usr/local/bin/swig -v -w201 -w312 -c++ -lua -includeall -ignoremissing -features directors,autodoc=1 -DBT_INFINITY \
    -I${MY_BULLET_SOURCE_DIRECTORY} \
    -I${MY_NJLI_BULLET_SOURCE_DIRECTORY} \
    -xmlout ${MY_XML_OUTPUT_DIRECTORY}/lbullet.xml \
    -o ${MY_BULLET_CPP_OUTPUT} \
    ${MY_BULLET_INTERFACE_DIRECTORY}/_LuaEntry.i

#njli
/usr/local/bin/swig -v -w201 -w312 -c++ -lua -includeall -ignoremissing -features directors,autodoc=1 \
    -I${MY_BULLET_SOURCE_DIRECTORY} \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/BroadphaseCollision \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/CollisionDispatch \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/CollisionShapes \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/Gimpact \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/NarrowPhaseCollision \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Character \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/ConstraintSolver \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Dynamics \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Featherstone \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/MLCPSolvers \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Vehicle \
    -I${MY_BULLET_SOURCE_DIRECTORY}/BulletSoftBody \
    -I${MY_BULLET_SOURCE_DIRECTORY}/LinearMath \
    \
    -I${MY_NJLI_BULLET_SOURCE_DIRECTORY} \
    \
    -I${MY_NJLI_SOURCE_DIRECTORY} \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/graphics \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/physics \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/physics/body \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/physics/constraint \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/physics/shape \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/platform \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/sound \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/steering \
    -I${MY_NJLI_SOURCE_DIRECTORY}/builders/steering/behavior \
    -I${MY_NJLI_SOURCE_DIRECTORY}/generated \
    -I${MY_NJLI_SOURCE_DIRECTORY}/graphics \
    -I${MY_NJLI_SOURCE_DIRECTORY}/physics \
    -I${MY_NJLI_SOURCE_DIRECTORY}/physics/body \
    -I${MY_NJLI_SOURCE_DIRECTORY}/physics/constraint \
    -I${MY_NJLI_SOURCE_DIRECTORY}/physics/shape \
    -I${MY_NJLI_SOURCE_DIRECTORY}/platform \
    -I${MY_NJLI_SOURCE_DIRECTORY}/sound \
    -I${MY_NJLI_SOURCE_DIRECTORY}/sound/fmod \
    -I${MY_NJLI_SOURCE_DIRECTORY}/sound/openal \
    -I${MY_NJLI_SOURCE_DIRECTORY}/steering \
    -I${MY_NJLI_SOURCE_DIRECTORY}/steering/behavior \
    \
    -I${MY_NJLI_INTERFACE_DIRECTORY} \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/graphics \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/physics \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/physics/body \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/physics/constraint \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/physics/shape \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/platform \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/sound \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/steering \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/builders/steering/behavior \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/graphics \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/physics \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/physics/body \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/physics/constraint \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/physics/shape \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/platform \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/sound \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/steering \
    -I${MY_NJLI_INTERFACE_DIRECTORY}/njli/steering/behavior \
    \
    -I${MY_BULLET_INTERFACE_DIRECTORY} \
    \
    -xmlout ${MY_XML_OUTPUT_DIRECTORY}/lnjli.xml \
    -o ${MY_NJLI_CPP_OUTPUT} \
    ${MY_NJLI_INTERFACE_DIRECTORY}/njli/_LuaEntry.i


/usr/local/bin/swig -lua -external-runtime ${MY_RUNTIME_OUTPUT}

