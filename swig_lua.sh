#!/bin/sh

PWD=`pwd`

MY_NJLI_INTERFACE_DIRECTORY=${PWD}/src/swig.in/lua
MY_BULLET_INTERFACE_DIRECTORY=${PWD}/../External/thirdparty/swig.in/lua/bullet3

MY_NJLI_SOURCE_DIRECTORY=${PWD}/src/njli
MY_BULLET_SOURCE_DIRECTORY=${PWD}/../External/thirdparty/bullet3/src

MY_GENERATED_DIRECTORY=${MY_NJLI_SOURCE_DIRECTORY}/generated/swig/lua

MY_NJLI_CPP_OUTPUT=${MY_GENERATED_DIRECTORY}/lnjli.cpp
MY_BULLET_CPP_OUTPUT=${MY_GENERATED_DIRECTORY}/lbullet.cpp

MY_RUNTIME_OUTPUT=${MY_GENERATED_DIRECTORY}/swig_runtime.h

MY_XML_OUTPUT_DIRECTORY=$1

rm -rf ${MY_NJLI_SOURCE_DIRECTORY}/generated/swig/lua
mkdir -p ${MY_NJLI_SOURCE_DIRECTORY}/generated/swig/lua

/usr/local/bin/swig -version

if [ -z "${MY_XML_OUTPUT_DIRECTORY}" ]
then
    #bullet.
#    /usr/local/bin/swig -v -w312 -w201 -O -c++ -lua -includeall -ignoremissing -features directors,autodoc=1 -DBT_INFINITY \
#        -I- \
#        -I${MY_NJLI_INTERFACE_DIRECTORY}/njli\
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/BroadphaseCollision \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/CollisionDispatch \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/CollisionShapes \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/Gimpact \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletCollision/NarrowPhaseCollision \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Character \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/ConstraintSolver \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Dynamics \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Featherstone \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/MLCPSolvers \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletDynamics/Vehicle \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/BulletSoftBody \
#        -I${MY_BULLET_SOURCE_DIRECTORY}/LinearMath \
#        -o ${MY_BULLET_CPP_OUTPUT} \
#        ${MY_BULLET_INTERFACE_DIRECTORY}/_LuaEntry.i

    #njli
    /usr/local/bin/swig -w312 -w201 -O -c++ -lua -includeall -ignoremissing -features directors,autodoc=1 \
        -I- \
        -I${MY_NJLI_INTERFACE_DIRECTORY} \
        -I${MY_BULLET_INTERFACE_DIRECTORY} \
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
        -I${MY_NJLI_SOURCE_DIRECTORY} \
        -o ${MY_NJLI_CPP_OUTPUT} \
        ${MY_NJLI_INTERFACE_DIRECTORY}/njli/_LuaEntry.i
else
    /usr/local/bin/swig -w312 -w201 -O -c++ -lua -includeall -ignoremissing -features directors,autodoc=1 \
        -I${MY_NJLI_SOURCE_DIRECTORY} \
        -I${MY_NJLI_SOURCE_DIRECTORY}/builders \
        -I${MY_NJLI_SOURCE_DIRECTORY}/builders/graphics \
        -I${MY_NJLI_SOURCE_DIRECTORY}/builders/platform \
        -I${MY_NJLI_SOURCE_DIRECTORY}/builders/sound \
        -I${MY_NJLI_SOURCE_DIRECTORY}/generated \
        -I${MY_NJLI_SOURCE_DIRECTORY}/graphics \
        -I${MY_NJLI_SOURCE_DIRECTORY}/platform \
        -I${MY_NJLI_SOURCE_DIRECTORY}/sound \
        -xmlout ${MY_XML_OUTPUT_DIRECTORY}/lnjli.xml \
        -o ${MY_NJLI_CPP_OUTPUT} \
        ${MY_NJLI_INTERFACE_DIRECTORY}/njli/_LuaEntry.i
fi

/usr/local/bin/swig -lua -external-runtime ${MY_RUNTIME_OUTPUT}

