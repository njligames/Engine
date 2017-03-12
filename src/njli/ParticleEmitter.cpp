//
//  ParticleEmitter.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 9/24/15.
//  Copyright © 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "ParticleEmitter.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "ParticleEmitterBuilder.h"
#define TAG "ParticleEmitter.cpp"

#define FORMATSTRING "{\"njli::ParticleEmitter\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "tinyxml.h"

#include "btVector3.h"

#include "btQuickprof.h"

// Macro which returns a random value between -1 and 1
#define RANDOM_MINUS_1_TO_1() ((random() / (f32)0x3fffffff )-1.0f)

// Macro which returns a random number between 0 and 1
#define RANDOM_0_TO_1() ((random() / (f32)0x7fffffff ))


// Macro which converts degrees into radians
#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0 * M_PI)

// Macro that allows you to clamp a value within the defined bounds
#define CLAMP(X, A, B) ((X < A) ? A : ((X > B) ? B : X))

#include "Node.h"


namespace njli
{
    ParticleEmitter::ParticleEmitter():
    AbstractFactoryObject(this),
    emitterType(0),
    sourcePositionVariance(new btVector3(0, 0, 0)),
    speed(0),
    speedVariance(190.79f),
    particleLifespan(0.7237f),
    angle(244.11f),
    angleVariance(142.62f),
    gravity(new btVector3(0.0f, 671.05f, 0.0f)),
    radialAcceleration(0),
    tangentialAcceleration(144.74f),
    startColor(new btVector4(0.8373094f, 0.3031555f, 0.0f, 1.0f)),
    particleLifespanVariance(0),
    radialAccelVariance(0),
    tangentialAccelVariance(92.11f),
    startColorVariance(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    finishColor(new btVector4(1.0f, 0.5443883f, 0.3699196f, 0)),
    finishColorVariance(new btVector4(0.0f, 0.0f, 0.0f, 0.0f)),
    maxParticles(500),
    startParticleSize(50.95f),
    finishParticleSize(64),
    startParticleSizeVariance(53.47f),
    finishParticleSizeVariance(64),
    duration(-1),
    blendFuncSource(0),
    blendFuncDestination(0),
    maxRadius(0),
    maxRadiusVariance(72.63f),
    minRadius(0),
    minRadiusVariance(0),
    rotatePerSecond(0),
    rotationStart(0),
    rotationStartVariance(153.95f),
    rotationEnd(0),
    rotationEndVariance(0),
    rotatePerSecondVariance(153.95f),
    emissionRate(0),
    emitCounter(0),
    particleCount(0),
    elapsedTime(0),
    active(true),
    particleIndex(0),
    m_Nodes(NULL),
    m_ParticleArray(NULL),
    m_particlesRootNode(NULL),
    m_geometry(NULL),
    m_body(NULL),
    m_Scale(new btVector3(1,1,1))
    {
        
    }
    
    ParticleEmitter::ParticleEmitter(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    emitterType(0),
    sourcePositionVariance(new btVector3(0, 0, 0)),
    speed(0),
    speedVariance(190.79f),
    particleLifespan(0.7237f),
    angle(244.11f),
    angleVariance(142.62f),
    gravity(new btVector3(0.0f, 671.05f, 0.0f)),
    radialAcceleration(0),
    tangentialAcceleration(144.74f),
    startColor(new btVector4(0.8373094f, 0.3031555f, 0.0f, 1.0f)),
    particleLifespanVariance(0),
    radialAccelVariance(0),
    tangentialAccelVariance(92.11f),
    startColorVariance(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    finishColor(new btVector4(1.0f, 0.5443883f, 0.3699196f, 0)),
    finishColorVariance(new btVector4(0.0f, 0.0f, 0.0f, 0.0f)),
    maxParticles(500),
    startParticleSize(50.95f),
    finishParticleSize(64),
    startParticleSizeVariance(53.47f),
    finishParticleSizeVariance(64),
    duration(-1),
    blendFuncSource(0),
    blendFuncDestination(0),
    maxRadius(0),
    maxRadiusVariance(72.63f),
    minRadius(0),
    minRadiusVariance(0),
    rotatePerSecond(0),
    rotationStart(0),
    rotationStartVariance(153.95f),
    rotationEnd(0),
    rotationEndVariance(0),
    rotatePerSecondVariance(153.95f),
    emissionRate(0),
    emitCounter(0),
    particleCount(0),
    elapsedTime(0),
    active(true),
    particleIndex(0),
    m_Nodes(NULL),
    m_ParticleArray(NULL),
    m_particlesRootNode(NULL),
    m_geometry(NULL),
    m_body(NULL),
    m_Scale(new btVector3(1,1,1))
    {
        
    }
    
    ParticleEmitter::ParticleEmitter(const ParticleEmitter &copy):
    AbstractFactoryObject(this),
    emitterType(0),
    sourcePositionVariance(new btVector3(0, 0, 0)),
    speed(0),
    speedVariance(190.79f),
    particleLifespan(0.7237f),
    angle(244.11f),
    angleVariance(142.62f),
    gravity(new btVector3(0.0f, 671.05f, 0.0f)),
    radialAcceleration(0),
    tangentialAcceleration(144.74f),
    startColor(new btVector4(0.8373094f, 0.3031555f, 0.0f, 1.0f)),
    particleLifespanVariance(0),
    radialAccelVariance(0),
    tangentialAccelVariance(92.11f),
    startColorVariance(new btVector4(0.0f, 0.0f, 0.0f, 1.0f)),
    finishColor(new btVector4(1.0f, 0.5443883f, 0.3699196f, 0)),
    finishColorVariance(new btVector4(0.0f, 0.0f, 0.0f, 0.0f)),
    maxParticles(500),
    startParticleSize(50.95f),
    finishParticleSize(64),
    startParticleSizeVariance(53.47f),
    finishParticleSizeVariance(64),
    duration(-1),
    blendFuncSource(0),
    blendFuncDestination(0),
    maxRadius(0),
    maxRadiusVariance(72.63f),
    minRadius(0),
    minRadiusVariance(0),
    rotatePerSecond(0),
    rotationStart(0),
    rotationStartVariance(153.95f),
    rotationEnd(0),
    rotationEndVariance(0),
    rotatePerSecondVariance(153.95f),
    emissionRate(0),
    emitCounter(0),
    particleCount(0),
    elapsedTime(0),
    active(true),
    particleIndex(0),
    m_Nodes(NULL),
    m_ParticleArray(NULL),
    m_particlesRootNode(NULL),
    m_geometry(NULL),
    m_body(NULL),
    m_Scale(new btVector3(1,1,1))
    {
        
    }
    
    ParticleEmitter::~ParticleEmitter()
    {
        delete m_Scale;
        m_Scale = NULL;
        
        m_particlesRootNode = NULL;
        m_geometry = NULL;
        m_body = NULL;
        
        if(m_ParticleArray)
            delete [] m_ParticleArray;
        m_ParticleArray=NULL;
        
        if(m_Nodes)
            Node::destroyArray(m_Nodes, maxParticles);
        m_Nodes = NULL;
        
        delete finishColorVariance;
        finishColorVariance = NULL;
        
        delete finishColor;
        finishColor = NULL;
        
        delete startColorVariance;
        startColorVariance = NULL;
        
        delete startColor;
        startColor = NULL;
        
        delete gravity;
        gravity = NULL;
        
        delete sourcePositionVariance;
        sourcePositionVariance = NULL;
    }
    
    ParticleEmitter &ParticleEmitter::operator=(const ParticleEmitter &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	ParticleEmitter::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void ParticleEmitter::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *ParticleEmitter::getClassName()const
    {
        return "ParticleEmitter";
    }
    
    s32 ParticleEmitter::getType()const
    {
        return ParticleEmitter::type();
    }
    
    ParticleEmitter::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        njli::JsonJLI *json = njli::JsonJLI::create();
        s = json->parse(s.c_str());
        njli::JsonJLI::destroy(json);
        
        return s;
    }
    
    ParticleEmitter **ParticleEmitter::createArray(const u32 size)
    {
        return (ParticleEmitter**)World::getInstance()->getWorldFactory()->createArray(ParticleEmitter::type(), size);
    }
    
    void ParticleEmitter::destroyArray(ParticleEmitter **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    ParticleEmitter *ParticleEmitter::create()
    {
        return dynamic_cast<ParticleEmitter*>(World::getInstance()->getWorldFactory()->create(ParticleEmitter::type()));
    }
    
    ParticleEmitter *ParticleEmitter::create(const ParticleEmitterBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<ParticleEmitter*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    ParticleEmitter *ParticleEmitter::clone(const ParticleEmitter &object)
    {
        return dynamic_cast<ParticleEmitter*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    ParticleEmitter *ParticleEmitter::copy(const ParticleEmitter &object)
    {
        return dynamic_cast<ParticleEmitter*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void ParticleEmitter::destroy(ParticleEmitter *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void ParticleEmitter::load(ParticleEmitter &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
        {
            // stack now contains: -1 => value; -2 => key; -3 => table
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                ParticleEmitter::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
                    //                    swig_lua_userdata *usr;
                    //                    swig_type_info *type;
                    //                    assert(lua_isuserdata(L,index));
                    //                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
                    //                    type = usr->type;
                    //                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
                    //                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 ParticleEmitter::type()
    {
        return JLI_OBJECT_TYPE_ParticleEmitter;
    }
    
    void ParticleEmitter::start()
    {
        active = true;
    }
    
    void ParticleEmitter::stop()
    {
        active = false;
        elapsedTime = 0;
        emitCounter = 0;
    }
    
    void ParticleEmitter::reset()
    {
        active = false;
        elapsedTime = 0;
        for (int i = 0; i < particleCount; i++) {
            Particle *p = &m_ParticleArray[i];
            p->timeToLive = 0;
        }
        emitCounter = 0;
        emissionRate = maxParticles / ((particleLifespan==0)?1.0f:particleLifespan);
    }
    
    bool ParticleEmitter::parseFileData(const char *source, const f32 z)
    {
        TiXmlDocument document;
        document.Parse(source);
        
        TiXmlNode* ele = 0;
        int i = 0;
        while ( (ele = document.FirstChildElement( "particleEmitterConfig" )->IterateChildren( ele ) ) != 0 )
        {
            f64 double_value, x, y, r, g, b, a;
            int int_value;
            
            TiXmlElement *e = ele->ToElement();
            e->Attribute("value", &int_value);
            e->Attribute("value", &double_value);
            e->Attribute("x", &x);
            e->Attribute("y", &y);
            e->Attribute("red", &r);
            e->Attribute("green", &g);
            e->Attribute("blue", &b);
            e->Attribute("alpha", &a);
            
            if(strcmp("emitterType", ele->Value()) == 0)
            {
                emitterType = int_value;
                ++i;
            }
            else if(strcmp("sourcePosition", ele->Value()) == 0)
            {
                btTransform t(btTransform::getIdentity());
//                t.setOrigin(btVector3(x, y, z));
//                setTransform(t);
                ++i;
            }
            else if(strcmp("sourcePositionVariance", ele->Value()) == 0)
            {
                *sourcePositionVariance = btVector3(x, y, 0);
                ++i;
            }
            else if(strcmp("speed", ele->Value()) == 0)
            {
                speed = double_value;
                ++i;
            }
            else if(strcmp("speedVariance", ele->Value()) == 0)
            {
                speedVariance = double_value;
                ++i;
            }
            else if(strcmp("particleLifeSpan", ele->Value()) == 0)
            {
                particleLifespan = double_value;
                ++i;
            }
            else if(strcmp("particleLifespanVariance", ele->Value()) == 0)
            {
                particleLifespanVariance = double_value;
                ++i;
            }
            else if(strcmp("angle", ele->Value()) == 0)
            {
                angle = double_value;
                ++i;
            }
            else if(strcmp("angleVariance", ele->Value()) == 0)
            {
                angleVariance = double_value;
                ++i;
            }
            else if(strcmp("gravity", ele->Value()) == 0)
            {
                gravity->setX(x);
                gravity->setY(y);
                gravity->setZ(0);
                ++i;
            }
            else if(strcmp("radialAcceleration", ele->Value()) == 0)
            {
                radialAcceleration = double_value;
                ++i;
            }
            else if(strcmp("radialAccelVariance", ele->Value()) == 0)
            {
                radialAccelVariance = double_value;
                ++i;
            }
            else if(strcmp("tangentialAcceleration", ele->Value()) == 0)
            {
                tangentialAcceleration = double_value;
                ++i;
            }
            else if(strcmp("tangentialAccelVariance", ele->Value()) == 0)
            {
                tangentialAccelVariance = double_value;
                ++i;
            }
            else if(strcmp("startColor", ele->Value()) == 0)
            {
                startColor->setX(r);
                startColor->setY(g);
                startColor->setZ(b);
                startColor->setW(a);
                ++i;
            }
            else if(strcmp("startColorVariance", ele->Value()) == 0)
            {
                startColorVariance->setX(r);
                startColorVariance->setY(g);
                startColorVariance->setZ(b);
                startColorVariance->setW(a);
                ++i;
            }
            else if(strcmp("finishColor", ele->Value()) == 0)
            {
                finishColor->setX(r);
                finishColor->setY(g);
                finishColor->setZ(b);
                finishColor->setW(a);
                ++i;
            }
            else if(strcmp("finishColorVariance", ele->Value()) == 0)
            {
                finishColorVariance->setX(r);
                finishColorVariance->setY(g);
                finishColorVariance->setZ(b);
                finishColorVariance->setW(a);
                ++i;
            }
            else if(strcmp("maxParticles", ele->Value()) == 0)
            {
                maxParticles = int_value;
                ++i;
            }
            else if(strcmp("startParticleSize", ele->Value()) == 0)
            {
                startParticleSize = double_value;
                ++i;
            }
            else if(strcmp("startParticleSizeVariance", ele->Value()) == 0)
            {
                startParticleSizeVariance = double_value;
                ++i;
            }
            else if(strcmp("finishParticleSize", ele->Value()) == 0)
            {
                finishParticleSize = double_value;
                ++i;
            }
            else if(strcmp("finishParticleSizeVariance", ele->Value()) == 0)
            {
                finishParticleSizeVariance = double_value;
                ++i;
            }
            else if(strcmp("duration", ele->Value()) == 0)
            {
                duration = double_value;
                ++i;
            }
            else if(strcmp("blendFuncSource", ele->Value()) == 0)
            {
                blendFuncSource = int_value;
                ++i;
            }
            else if(strcmp("blendFuncDestination", ele->Value()) == 0)
            {
                blendFuncDestination = int_value;
                ++i;
            }
            else if(strcmp("maxRadius", ele->Value()) == 0)
            {
                maxRadius = double_value;
                ++i;
            }
            else if(strcmp("maxRadiusVariance", ele->Value()) == 0)
            {
                maxRadiusVariance = double_value;
                ++i;
            }
            else if(strcmp("minRadius", ele->Value()) == 0)
            {
                minRadius = double_value;
                ++i;
            }
            else if(strcmp("minRadiusVariance", ele->Value()) == 0)
            {
                minRadiusVariance = double_value;
                ++i;
            }
            else if(strcmp("rotatePerSecond", ele->Value()) == 0)
            {
                rotatePerSecond = double_value;
                ++i;
            }
            else if(strcmp("rotatePerSecondVariance", ele->Value()) == 0)
            {
                rotatePerSecondVariance = double_value;
                ++i;
            }
            else if(strcmp("rotationStart", ele->Value()) == 0)
            {
                rotationStart = double_value;
                ++i;
            }
            else if(strcmp("rotationStartVariance", ele->Value()) == 0)
            {
                rotationStartVariance = double_value;
                ++i;
            }
            else if(strcmp("rotationEnd", ele->Value()) == 0)
            {
                rotationEnd = double_value;
                ++i;
            }
            else if(strcmp("rotationEndVariance", ele->Value()) == 0)
            {
                rotationEndVariance = double_value;
                ++i;
            }
            else if(strcmp("texture", ele->Value()) == 0)
            {
                textureFilename = e->Attribute("name");
                ++i;
            }
            else
            {
                DEBUG_LOG_PRINT_V(TAG, "unused: %s\n", ele->Value());
            }
        }
        
        return (i >= 37);
    }
    
    void ParticleEmitter::setup(Node *particlesRootNode, Geometry *geometry, PhysicsBody *body)
    {
        DEBUG_ASSERT(particlesRootNode);
        DEBUG_ASSERT(geometry);
        
        if(m_Nodes)
            Node::destroyArray(m_Nodes, maxParticles);
        m_Nodes = Node::createArray(maxParticles);
        
        geometry->setBlendSource(blendFuncSource);
        geometry->setBlendDestination(blendFuncDestination);
        geometry->enableDepthTest(false);
        
        for (u32 i = 0; i < maxParticles; ++i)
        {
            Node *node = m_Nodes[i];
            
            particlesRootNode->addChildNode(node);
            
            node->setGeometry(geometry);
            
            node->setRenderCategory(getParent());
            
            if (body)
                node->setPhysicsBody(body);
        }
        
        if(m_ParticleArray)
            delete [] m_ParticleArray;
        m_ParticleArray = new Particle[maxParticles];
        
        // Calculate the emission rate
        emissionRate                = maxParticles / ((particleLifespan==0)?1.0f:particleLifespan);
        emitCounter                 = 0;
        
        // By default the particle emitter is active when created
//        active = true;
        
        for (int i = 0; i < maxParticles; i++)
        {
            Particle *p = &m_ParticleArray[i];
            p->timeToLive = 0;
            p->node = m_Nodes[i];
            p->used = false;
        }
        
        // Set the particle count to zero
        particleCount = 0;
        
        // Reset the elapsed time
        elapsedTime = 0;
        
        m_particlesRootNode = particlesRootNode;
        m_geometry = geometry;
        m_body = body;
    }
    
    bool ParticleEmitter::isActive()const
    {
        return particleCount > 0 ;
    }
    
    Node *ParticleEmitter::getParent()
    {
        return dynamic_cast<Node*>(AbstractDecorator::getParent());
    }
    
    const Node *ParticleEmitter::getParent()const
    {
        return dynamic_cast<const Node*>(AbstractDecorator::getParent());
    }
    
    btTransform ParticleEmitter::getWorldTransform()const
    {
        btTransform t(btTransform::getIdentity());
        if (getParent())
            t = getParent()->getWorldTransform() * t;
        return t;
//        btTransform t(getTransform());
//        if(getParent())
//            t = getParent()->getWorldTransform() * getTransform();
//        return t;
    }
    
    btVector3 ParticleEmitter::getSourcePosition()const
    {
        return getWorldTransform().getOrigin();
    }
    
    void ParticleEmitter::setScale(const btVector3 &scale)
    {
        *m_Scale = scale;
    }
    
    void ParticleEmitter::setScale(const f32 scale)
    {
        ParticleEmitter::setScale(btVector3(scale, scale, scale));
    }
    
    const btVector3 &ParticleEmitter::getSourcePositionVariance()const
    {
        return *sourcePositionVariance;
    }
    
    void ParticleEmitter::setSourcePositionVariance(const btVector3 &value)
    {
        *sourcePositionVariance = value;
    }
    
    const f32 &ParticleEmitter::getAngle()const
    {
        return angle;
    }
    
    void ParticleEmitter::setAngle(const f32 &value)
    {
        angle = value;
    }
    
    const f32 &ParticleEmitter::getAngleVariance()const
    {
        return angleVariance;
    }
    
    void ParticleEmitter::setAngleVariance(const f32 &value)
    {
        angleVariance = value;
    }
    
    const f32 &ParticleEmitter::getSpeed()const
    {
        return speed;
    }
    
    void ParticleEmitter::setSpeed(const f32 &value)
    {
        speed = value;
    }
    
    const f32 &ParticleEmitter::getSpeedVariance()const
    {
        return speedVariance;
    }
    
    void ParticleEmitter::setSpeedVariance(const f32 &value)
    {
        speedVariance = value;
    }
    
    const f32 &ParticleEmitter::getRadialAccel()const
    {
        return radialAcceleration;
    }
    
    void ParticleEmitter::setRadialAccel(const f32 &value)
    {
        radialAcceleration = value;
    }
    
    const f32 &ParticleEmitter::getTangentialAccel()const
    {
        return tangentialAcceleration;
    }
    
    void ParticleEmitter::setTangentialAccel(const f32 &value)
    {
        tangentialAcceleration = value;
    }
    
    const f32 &ParticleEmitter::getRadialAccelVariance()const
    {
        return radialAccelVariance;
    }
    
    void ParticleEmitter::setRadialAccelVariance(const f32 &value)
    {
        radialAccelVariance = value;
    }
    
    const f32 &ParticleEmitter::getTangentialAccelVariance()const
    {
        return tangentialAccelVariance;
    }
    
    void ParticleEmitter::setTangentialAccelVariance(const f32 &value)
    {
        tangentialAccelVariance = value;
    }
    
    const btVector3 &ParticleEmitter::getGravity()const
    {
        return *gravity;
    }
    
    void ParticleEmitter::setGravity(const btVector3 &value)
    {
        *gravity = value;
    }
    
    const f32 &ParticleEmitter::getParticleLifespan()const
    {
        return particleLifespan;
    }
    
    void ParticleEmitter::setParticleLifespan(const f32 &value)
    {
        particleLifespan = value;
        
        if(m_particlesRootNode || m_geometry)
            setup(m_particlesRootNode, m_geometry, m_body);
    }
    
    const f32 &ParticleEmitter::getParticleLifespanVariance()const
    {
        return particleLifespanVariance;
    }
    
    void ParticleEmitter::setParticleLifespanVariance(const f32 &value)
    {
        particleLifespanVariance = value;
    }
    
    const btVector4 &ParticleEmitter::getStartColor()const
    {
        return *startColor;
    }
    
    void ParticleEmitter::setStartColor(const btVector4 &value)
    {
        *startColor = value;
    }
    
    const btVector4 &ParticleEmitter::getStartColorVariance()const
    {
        return *startColorVariance;
    }
    
    void ParticleEmitter::setStartColorVariance(const btVector4 &value)
    {
        *startColorVariance = value;
    }
    
    const btVector4 &ParticleEmitter::getFinishColor()const
    {
        return *finishColor;
    }
    
    void ParticleEmitter::setFinishColor(const btVector4 &value)
    {
        *finishColor = value;
    }
    
    const btVector4 &ParticleEmitter::getFinishColorVariance()const
    {
        return *finishColorVariance;
    }
    
    void ParticleEmitter::setFinishColorVariance(const btVector4 &value)
    {
        *finishColorVariance = value;
    }
    
    const f32 &ParticleEmitter::getStartParticleSize()const
    {
        return startParticleSize;
    }
    
    void ParticleEmitter::setStartParticleSize(const f32 &value)
    {
        startParticleSize = value;
    }
    
    const f32 &ParticleEmitter::getStartParticleSizeVariance()const
    {
        return startParticleSizeVariance;
    }
    
    void ParticleEmitter::setStartParticleSizeVariance(const f32 &value)
    {
        startParticleSizeVariance = value;
    }
    
    const f32 &ParticleEmitter::getFinishParticleSize()const
    {
        return finishParticleSize;
    }
    
    void ParticleEmitter::setFinishParticleSize(const f32 &value)
    {
        finishParticleSize = value;
    }
    
    const f32 &ParticleEmitter::getFinishParticleSizeVariance()const
    {
        return finishParticleSizeVariance;
    }
    
    void ParticleEmitter::setFinishParticleSizeVariance(const f32 &value)
    {
        finishParticleSizeVariance = value;
    }
    
    const u32 &ParticleEmitter::getMaxParticles()const
    {
        return maxParticles;
    }
    
    void ParticleEmitter::setMaxParticles(const u32 &value)
    {
        maxParticles = value;
        
        if(m_particlesRootNode || m_geometry)
            setup(m_particlesRootNode, m_geometry, m_body);
    }
    
//    const s32 &ParticleEmitter::getParticleCount()const
//    {
//        return particleCount;
//    }
//    
//    void ParticleEmitter::setParticleCount(const s32 &value)
//    {
//        particleCount = value;
//    }
    
//    const f32 &ParticleEmitter::getEmissionRate()const
//    {
//        return emissionRate;
//    }
//    
//    void ParticleEmitter::setEmissionRate(const f32 &value)
//    {
//        emissionRate = value;
//    }
    
//    const f32 &ParticleEmitter::getEmitCounter()const
//    {
//        return emitCounter;
//    }
//    
//    void ParticleEmitter::setEmitCounter(const f32 &value)
//    {
//        emitCounter = value;
//    }
    
//    const f32 &ParticleEmitter::getElapsedTime()const
//    {
//        return elapsedTime;
//    }
//    
//    void ParticleEmitter::setElapsedTime(const f32 &value)
//    {
//        elapsedTime = value;
//    }
    
    const f32 &ParticleEmitter::getDuration()const
    {
        return duration;
    }
    
    void ParticleEmitter::setDuration(const f32 &value)
    {
        duration = value;
    }
    
    const f32 &ParticleEmitter::getRotationStart()const
    {
        return rotationStart;
    }
    
    void ParticleEmitter::setRotationStart(const f32 &value)
    {
        rotationStart = value;
    }
    
    const f32 &ParticleEmitter::getRotationStartVariance()const
    {
        return rotationStartVariance;
    }
    
    void ParticleEmitter::setRotationStartVariance(const f32 &value)
    {
        rotationStartVariance = value;
    }
    
    const f32 &ParticleEmitter::getRotationEnd()const
    {
        return rotationEnd;
    }
    
    void ParticleEmitter::setRotationEnd(const f32 &value)
    {
        rotationEnd = value;
    }
    
    const f32 &ParticleEmitter::getRotationEndVariance()const
    {
        return rotationEndVariance;
    }
    
    void ParticleEmitter::setRotationEndVariance(const f32 &value)
    {
        rotationEndVariance = value;
    }
    
    const f32 &ParticleEmitter::getMaxRadius()const
    {
        return maxRadius;
    }
    
    void ParticleEmitter::setMaxRadius(const f32 &value)
    {
        maxRadius = value;
    }
    
    const f32 &ParticleEmitter::getMaxRadiusVariance()const
    {
        return maxRadiusVariance;
    }
    
    void ParticleEmitter::setMaxRadiusVariance(const f32 &value)
    {
        maxRadiusVariance = value;
    }
    
    const f32 &ParticleEmitter::getMinRadius()const
    {
        return minRadius;
    }
    
    void ParticleEmitter::setMinRadius(const f32 &value)
    {
        minRadius = value;
    }
    
    const f32 &ParticleEmitter::getMinRadiusVariance()const
    {
        return minRadiusVariance;
    }
    
    void ParticleEmitter::setMinRadiusVariance(const f32 &value)
    {
        minRadiusVariance = value;
    }
    
    const f32 &ParticleEmitter::getRotatePerSecond()const
    {
        return rotatePerSecond;
    }
    
    void ParticleEmitter::setRotatePerSecond(const f32 &value)
    {
        rotatePerSecond = value;
    }
    
    const f32 &ParticleEmitter::getRotatePerSecondVariance()const
    {
        return rotatePerSecondVariance;
    }
    
    void ParticleEmitter::setRotatePerSecondVariance(const f32 &value)
    {
        rotatePerSecondVariance = value;
    }
    
    const char *ParticleEmitter::getTextureFilename()const
    {
        return textureFilename.c_str();
    }
    
    void ParticleEmitter::update(f32 timeStep)
    {
        BT_PROFILE("ParticleEmitter::update");
        
        f32 scale = (m_Scale->x() + m_Scale->y() + m_Scale->z())/3.0f;
        
        if (active && emissionRate)
        {
            f32 rate = 1.0f/emissionRate;
            
            if (particleCount < maxParticles)
                emitCounter += timeStep;
            
            while (particleCount < maxParticles && emitCounter > rate)
            {
                addParticle();
                emitCounter -= rate;
            }
            
            elapsedTime += timeStep;
            
            if (duration != -1 && duration < elapsedTime)
            {
                stop();
            }
        }
        
        for (std::vector<Particle*>::iterator i = m_ActiveParticles.begin(); i != m_ActiveParticles.end();)
        {
            Particle *currentParticle = *i;//&m_ParticleArray[particleIndex];
            Node *currentNode = currentParticle->node;
            
            currentParticle->timeToLive -= timeStep;
            
            // If the current particle is alive then update it
            if (currentParticle->timeToLive > 0)
            {
                
                // If maxRadius is greater than 0 then the particles are going to spin otherwise they are effected by speed and gravity
                if (emitterType == kParticleTypeRadial)
                {
                    
                    // FIX 2
                    // Update the angle of the particle from the sourcePosition and the radius.  This is only done of the particles are rotating
                    currentParticle->angle += currentParticle->degreesPerSecond * timeStep;
                    currentParticle->radius += currentParticle->radiusDelta * timeStep;
                    
                    btVector3 tmp(0,0,0);
                    tmp.setX(getSourcePosition().x() - cosf(currentParticle->angle) * currentParticle->radius);
                    tmp.setY(getSourcePosition().y() - sinf(currentParticle->angle) * currentParticle->radius);
                    *(currentParticle->position) = tmp;
                    
                }
                else
                {
                    btVector3 tmp, radial, tangential;
                    btVector3 zero = {0,0,0};
                    
                    radial.setX(0);
                    radial.setY(0);
                    radial.setZ(0);
                    
                    // By default this emitters particles are moved relative to the emitter node position
                    
                    
                    btVector3 positionDifference = *(currentParticle->startPos) - zero;
                    *(currentParticle->position) = *(currentParticle->position) - (positionDifference * scale);
                    
                    if(currentParticle->position->x() || currentParticle->position->y())
                        radial = currentParticle->position->normalized();
                    
                    tangential = radial;
                    radial *= currentParticle->radialAcceleration;
                    
                    f32 newy = tangential.x();
                    tangential.setX(-tangential.y());
                    tangential.setY(newy);
                    tangential *= currentParticle->tangentialAcceleration;
                    
                    tmp = ((radial + tangential) + (*gravity * 1));
                    tmp *= timeStep;
                    *(currentParticle->direction) = *(currentParticle->direction) + tmp;
                    tmp = *(currentParticle->direction) * timeStep;
                    *(currentParticle->position) = *(currentParticle->position) + (tmp * scale);
                    
                    // Now apply the difference calculated early causing the particles to be relative in position to the emitter position
                    *(currentParticle->position) = *(currentParticle->position) + (positionDifference * scale);
                    
                    
                }
                
                // Update the particles color
                currentParticle->color->setX(currentParticle->color->x() + (currentParticle->deltaColor->x() * timeStep));
                currentParticle->color->setY(currentParticle->color->y() + (currentParticle->deltaColor->y() * timeStep));
                currentParticle->color->setZ(currentParticle->color->z() + (currentParticle->deltaColor->z() * timeStep));
                currentParticle->color->setW(currentParticle->color->w() + (currentParticle->deltaColor->w() * timeStep));
                
                // Update the particle size
                currentParticle->particleSize += currentParticle->particleSizeDelta * timeStep;
                currentParticle->particleSize = btMax<f32>(0, currentParticle->particleSize);
                
                // Update the rotation of the particle
                currentParticle->rotation += currentParticle->rotationDelta * timeStep;
                
                // As we are rendering the particles as quads, we need to define 6 vertices for each particle
                f32 halfSize = currentParticle->particleSize * 0.5f;
                
                // If a rotation has been defined for this particle then apply the rotation to the vertices that define
                // the particle
                if (currentParticle->rotation)
                {
                    float x1 = -halfSize;
                    float y1 = -halfSize;
                    float x2 = halfSize;
                    float y2 = halfSize;
                    float x = currentParticle->position->x();
                    float y = currentParticle->position->y();
                    float r = btRadians(currentParticle->rotation);
                    float cr = cosf(r);
                    float sr = sinf(r);
                    float ax = x1 * cr - y1 * sr + x;
                    float ay = x1 * sr + y1 * cr + y;
                    float bx = x2 * cr - y1 * sr + x;
                    float by = x2 * sr + y1 * cr + y;
                    float cx = x2 * cr - y2 * sr + x;
                    float cy = x2 * sr + y2 * cr + y;
                    float dx = x1 * cr - y2 * sr + x;
                    float dy = x1 * sr + y2 * cr + y;
                    
                    
                    //                    m_Sprite2D[particleIndex].bl.vertex.setX(ax);
                    //                    m_Sprite2D[particleIndex].bl.vertex.setY(ay);
                    //                    m_Sprite2D[particleIndex].bl.color = currentParticle->color;
                    //
                    //                    m_Sprite2D[particleIndex].br.vertex.setX(bx);
                    //                    m_Sprite2D[particleIndex].br.vertex.setY(by);
                    //                    m_Sprite2D[particleIndex].br.color = currentParticle->color;
                    //
                    //                    m_Sprite2D[particleIndex].tl.vertex.setX(dx);
                    //                    m_Sprite2D[particleIndex].tl.vertex.setY(dy);
                    //                    m_Sprite2D[particleIndex].tl.color = currentParticle->color;
                    //
                    //                    m_Sprite2D[particleIndex].tr.vertex.setX(cx);
                    //                    m_Sprite2D[particleIndex].tr.vertex.setY(cy);
                }
                else
                {
                    // Using the position of the particle, work out the four vertices for the quad that will hold the particle
                    // and load those into the quads array.
                    
                    currentNode->getGeometry()->setColor(currentNode, *(currentParticle->color));
                    currentNode->getGeometry()->setSize(currentNode, *(currentParticle->position), halfSize);
                }
                ++i;
            }
            else
            {
                --particleCount;
                currentParticle->used = false;
                currentNode->getGeometry()->setOpacity(currentNode, 0.0f);
                i = m_ActiveParticles.erase(i);
            }
        }
    }
    
    ParticleEmitter::Particle *ParticleEmitter::findUnusedParticle()
    {
        DEBUG_ASSERT(particleCount < maxParticles);
        
        for (int i = particleCount, counter = 0; counter < maxParticles; ++i, ++counter)
        {
            particleIndex = i % maxParticles;
            if (!m_ParticleArray[particleIndex].used)
            {
                m_ParticleArray[particleIndex].used = true;
                Node *currentNode = m_ParticleArray[particleIndex].node;
                currentNode->getGeometry()->setOpacity(currentNode, 1.0f);
                return &m_ParticleArray[particleIndex];
            }
        }
        return NULL;
    }
    
    bool ParticleEmitter::addParticle()
    {
        f32 scale = (m_Scale->x() + m_Scale->y() + m_Scale->z())/3.0f;
        
        // If we have already reached the maximum number of particles then do nothing
        if (particleCount == maxParticles)
            return false;
        
        // Take the next particle out of the particle pool we have created and initialize it
//        Particle *particle = &m_ParticleArray[particleCount];
        Particle *particle = findUnusedParticle();
        //        [self initParticle:particle];
        
        
        // Init the position of the particle.  This is based on the source position of the particle emitter
        // plus a configured variance.  The RANDOM_MINUS_1_TO_1 macro allows the number to be both positive
        // and negative
        particle->position->setX(getSourcePosition().x() + sourcePositionVariance->x() * RANDOM_MINUS_1_TO_1());
        
        particle->position->setY(getSourcePosition().y() + sourcePositionVariance->y() * RANDOM_MINUS_1_TO_1());
        
        particle->startPos->setX(getSourcePosition().x());
        
        particle->startPos->setY(getSourcePosition().y());
        
//        *(particle->startPos) *= scale;
        
        // Init the direction of the particle.  The newAngle is calculated using the angle passed in and the
        // angle variance.
        f32 newAngle = btRadians(angle + angleVariance * RANDOM_MINUS_1_TO_1());
        
        // Create a new btVector2 using the newAngle
        btVector2 vector(cosf(newAngle), sinf(newAngle));
        
        // Calculate the vectorSpeed using the speed and speedVariance which has been passed in
        f32 vectorSpeed = speed + speedVariance * RANDOM_MINUS_1_TO_1();
        
        // The particles direction vector is calculated by taking the vector calculated above and
        // multiplying that by the speed
        *(particle->direction) = vector * vectorSpeed;
        
        // Calculate the particles life span using the life span and variance passed in
        particle->timeToLive = btMax<f32>(0, particleLifespan + particleLifespanVariance * RANDOM_MINUS_1_TO_1() * scale);
        
        f32 startRadius = maxRadius + maxRadiusVariance * RANDOM_MINUS_1_TO_1();
        f32 endRadius = minRadius + minRadiusVariance * RANDOM_MINUS_1_TO_1();
        
        // Set the default diameter of the particle from the source position
        particle->radius = startRadius;
        particle->radiusDelta = (endRadius - startRadius) / particle->timeToLive;
        particle->angle = btRadians(angle + angleVariance * RANDOM_MINUS_1_TO_1());
        particle->degreesPerSecond = btRadians(rotatePerSecond + rotatePerSecondVariance * RANDOM_MINUS_1_TO_1());
        
        particle->radialAcceleration = radialAcceleration + radialAccelVariance * RANDOM_MINUS_1_TO_1() * scale;
        particle->tangentialAcceleration = tangentialAcceleration + tangentialAccelVariance * RANDOM_MINUS_1_TO_1() * scale;
        
        // Calculate the particle size using the start and finish particle sizes
        f32 particleStartSize = startParticleSize + startParticleSizeVariance * RANDOM_MINUS_1_TO_1() * scale;
        f32 particleFinishSize = finishParticleSize + finishParticleSizeVariance * RANDOM_MINUS_1_TO_1() * scale;
        particle->particleSizeDelta = ((particleFinishSize - particleStartSize) / particle->timeToLive);
        particle->particleSize = btMax<f32>(0, particleStartSize);
        
        // Calculate the color the particle should have when it starts its life.  All the elements
        // of the start color passed in along with the variance are used to calculate the star color
        btVector4 start = {0, 0, 0, 0};
        start.setX(startColor->x() + startColorVariance->x() * RANDOM_MINUS_1_TO_1());
        start.setY(startColor->y() + startColorVariance->y() * RANDOM_MINUS_1_TO_1());
        start.setZ(startColor->z() + startColorVariance->z() * RANDOM_MINUS_1_TO_1());
        start.setW(startColor->w() + startColorVariance->w() * RANDOM_MINUS_1_TO_1());
        
        // Calculate the color the particle should be when its life is over.  This is done the same
        // way as the start color above
        btVector4 end = {0, 0, 0, 0};
        end.setX(finishColor->x() + finishColorVariance->x() * RANDOM_MINUS_1_TO_1());
        end.setY(finishColor->y() + finishColorVariance->y() * RANDOM_MINUS_1_TO_1());
        end.setZ(finishColor->z() + finishColorVariance->z() * RANDOM_MINUS_1_TO_1());
        end.setW(finishColor->w() + finishColorVariance->w() * RANDOM_MINUS_1_TO_1());
        
        // Calculate the delta which is to be applied to the particles color during each cycle of its
        // life.  The delta calculation uses the life span of the particle to make sure that the
        // particles color will transition from the start to end color during its life time.  As the game
        // loop is using a fixed delta value we can calculate the delta color once saving cycles in the
        // update method
        
        *(particle->color) = start;
        particle->deltaColor->setX((end.x() - start.x()) / particle->timeToLive);
        particle->deltaColor->setY((end.y() - start.y()) / particle->timeToLive);
        particle->deltaColor->setZ((end.z() - start.z()) / particle->timeToLive);
        particle->deltaColor->setW((end.w() - start.w()) / particle->timeToLive);
        
        // Calculate the rotation
        f32 startA = rotationStart + rotationStartVariance * RANDOM_MINUS_1_TO_1() * scale;
        f32 endA = rotationEnd + rotationEndVariance * RANDOM_MINUS_1_TO_1() * scale;
        particle->rotation = startA;
        particle->rotationDelta = (endA - startA) / particle->timeToLive;
        
        m_ActiveParticles.push_back(particle);
        
        // Increment the particle count
        particleCount++;
        
        // Return YES to show that a particle has been created
        return true;
    }
    
    void ParticleEmitter::setRenderCategory(Node *node)
    {
        for (u32 i = 0; i < maxParticles; ++i)
        {
            Node *_node = m_Nodes[i];
            
            _node->setRenderCategory(node);
        }
    }
    
    
    ParticleEmitter::Particle::Particle():
    position(new btVector3(0,0,0)),
    direction(new btVector3(0,0,0)),
    startPos(new btVector3(0,0,0)),
    color(new btVector4(0,0,0,0)),
    deltaColor(new btVector4(0,0,0,0)),
    rotation(0),
    rotationDelta(0),
    radialAcceleration(0),
    tangentialAcceleration(0),
    radius(0),
    radiusDelta(0),
    angle(0),
    degreesPerSecond(0),
    particleSize(0),
    particleSizeDelta(0),
    timeToLive(0),
    node(NULL),
    used(false){}
    
    ParticleEmitter::Particle::~Particle()
    {
        delete deltaColor;
        deltaColor = NULL;
        
        delete color;
        color = NULL;
        
        delete startPos;
        startPos = NULL;
        
        delete direction;
        direction = NULL;
        
        delete position;
        position = NULL;
    }
}
