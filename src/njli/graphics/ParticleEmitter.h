//
//  ParticleEmitter.hpp
//  JLIGameEngineTest
//
//  Created by James Folk on 9/24/15.
//  Copyright © 2015 James Folk. All rights reserved.
//

#ifndef ParticleEmitter_hpp
#define ParticleEmitter_hpp

#pragma mark Header

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "Log.h"
#include "lua.hpp"

//#include "AbstractTransform.h"

class btVector3;
class btVector4;
class btTransform;

namespace njli {

class ParticleEmitterBuilder;
class Geometry;
class PhysicsBody;
class Node;
struct Particle;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
ParticleEmitter : public AbstractFactoryObject //,
//    public AbstractTransform
{
    friend class WorldFactory;
    friend class Scene;
    friend class Node;

protected:
    ParticleEmitter();
    ParticleEmitter(const AbstractBuilder&);
    ParticleEmitter(const ParticleEmitter&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~ParticleEmitter();
    ParticleEmitter& operator=(const ParticleEmitter&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  Calculate the buffer size of this object.
         *
         *  @return The buffer size.
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:37
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

    /**
         *  The name of this class.
         *
         *  @return The name of this class.
         */
    virtual const char* getClassName() const;
    /**
         *  Get the type of ::njliObjectEnumType enum value.
         *
         *  @return The ::njliObjectEnumType enum value.
         */
    virtual s32 getType() const;
    /**
         *  The string value for this object, which can be used for debugging.
         *
         *  @return "The string value for this object.
         */
    operator std::string() const;

    /**
         *  Create an Array of instances of this class.
         *
         *  @param size The amount of elements in the array.
         *
         *  @return Pointer to the newly created array.
         */
    static ParticleEmitter** createArray(const u32 size);
    /**
         *  Destroy an Array of this class type.
         *
         *  @param array The Pointer to the array to delete.
         */
    static void destroyArray(ParticleEmitter * *array, const u32 size = 0);
    /**
         *  Create an instance of this class.
         *
         *  @return Pointer to the newly created instance.
         */
    static ParticleEmitter* create();
    /**
         *  Create an instance of this class using a builder.
         *
         *  @param builder The builder to use for construction
         *
         *  @return Pointer to the newly created instance.
         */
    static ParticleEmitter* create(const ParticleEmitterBuilder& builder);
    /**
         *  Create a shallow copy of an instance of this class (sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
    static ParticleEmitter* clone(const ParticleEmitter& object);
    /**
         *  Create a deep copy of an instance of this class (NOT sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
    static ParticleEmitter* copy(const ParticleEmitter& object);
    /**
         *  Destroy an instance of this class.
         *
         *  @param object The object to destroy.
         */
    static void destroy(ParticleEmitter * object);
    /**
         *  Load a lua table representation of this class. This is used for JLIM.create(object).
         *
         *  @param object      The object to load.
         *  @param L           The current lua state.
         *  @param stack_index The stack index of the lua stack.
         */
    static void load(ParticleEmitter & object, lua_State * L, int stack_index);
    /**
         *  Get the type of ::njliObjectEnumType enum value.
         *
         *  @return The ::njliObjectEnumType enum value.
         */
    static u32 type();

public:
    //TODO: fill in specific methods for ParticleEmitter

    /**
         *  <#Description#>
         */
    void start();
    /**
         *  <#Description#>
         */
    void stop();
    /**
         *  <#Description#>
         */
    void reset();

    bool parseFileData(const char* source, const f32 z = 0);

    void setup(Node * particlesRootNode, Geometry * geometry, PhysicsBody* body = NULL);

    bool isActive() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node* getParent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Node* getParent() const;

    btTransform getWorldTransform() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getSourcePosition() const;

    /**
         *  <#Description#>
         *
         *  @param scale <#scale description#>
         */
    virtual void setScale(const btVector3& scale);

    /**
         *  <#Description#>
         *
         *  @param scale <#scale description#>
         */
    virtual void setScale(const f32 scale);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector3& getSourcePositionVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setSourcePositionVariance(const btVector3& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getAngle() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setAngle(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getAngleVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setAngleVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getSpeed() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setSpeed(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getSpeedVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setSpeedVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRadialAccel() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRadialAccel(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getTangentialAccel() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setTangentialAccel(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRadialAccelVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRadialAccelVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getTangentialAccelVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setTangentialAccelVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector3& getGravity() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setGravity(const btVector3& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getParticleLifespan() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setParticleLifespan(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getParticleLifespanVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setParticleLifespanVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getStartColor() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setStartColor(const btVector4& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getStartColorVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setStartColorVariance(const btVector4& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getFinishColor() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setFinishColor(const btVector4& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getFinishColorVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setFinishColorVariance(const btVector4& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getStartParticleSize() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setStartParticleSize(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getStartParticleSizeVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setStartParticleSizeVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getFinishParticleSize() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setFinishParticleSize(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getFinishParticleSizeVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setFinishParticleSizeVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const u32& getMaxParticles() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setMaxParticles(const u32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //        const s32 &getParticleCount()const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    //        void setParticleCount(const s32 &value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //        const f32 &getEmissionRate()const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    //        void setEmissionRate(const f32 &value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //        const f32 &getEmitCounter()const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    //        void setEmitCounter(const f32 &value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //        const f32 &getElapsedTime()const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    //        void setElapsedTime(const f32 &value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getDuration() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setDuration(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRotationStart() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRotationStart(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRotationStartVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRotationStartVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRotationEnd() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRotationEnd(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRotationEndVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRotationEndVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getMaxRadius() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setMaxRadius(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getMaxRadiusVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setMaxRadiusVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getMinRadius() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setMinRadius(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getMinRadiusVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setMinRadiusVariance(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRotatePerSecond() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRotatePerSecond(const f32& value);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const f32& getRotatePerSecondVariance() const;
    /**
         *  <#Description#>
         *
         *  @param value <#value description#>
         */
    void setRotatePerSecondVariance(const f32& value);

    const char* getTextureFilename() const;

protected:
    void update(f32 timeStep);

    bool addParticle();
    void setRenderCategory(Node * node);

private:
    s32 emitterType;
    btVector3* sourcePositionVariance;
    f32 speed;
    f32 speedVariance;
    f32 particleLifespan;
    f32 angle;
    f32 angleVariance;
    btVector3* gravity;
    f32 radialAcceleration;
    f32 tangentialAcceleration;
    btVector4* startColor;
    f32 particleLifespanVariance;
    f32 radialAccelVariance;
    f32 tangentialAccelVariance;
    btVector4* startColorVariance;
    btVector4* finishColor;
    btVector4* finishColorVariance;
    u32 maxParticles;
    f32 startParticleSize;
    f32 finishParticleSize;
    f32 startParticleSizeVariance;
    f32 finishParticleSizeVariance;
    f32 duration;
    s32 blendFuncSource, blendFuncDestination;
    f32 maxRadius;
    f32 maxRadiusVariance;
    f32 minRadius;
    f32 minRadiusVariance;
    f32 rotatePerSecond;
    f32 rotationStart;
    f32 rotationStartVariance;
    f32 rotationEnd;
    f32 rotationEndVariance;
    f32 rotatePerSecondVariance;
    std::string textureFilename;

    f32 emissionRate;
    f32 emitCounter;
    s32 particleCount;
    f32 elapsedTime;
    bool active;
    s32 particleIndex;

    Node** m_Nodes;

    struct Particle {
        Particle();
        ~Particle();

        btVector3* position;
        btVector3* direction;
        btVector3* startPos;
        btVector4* color;
        btVector4* deltaColor;
        f32 rotation;
        f32 rotationDelta;
        f32 radialAcceleration;
        f32 tangentialAcceleration;
        f32 radius;
        f32 radiusDelta;
        f32 angle;
        f32 degreesPerSecond;
        f32 particleSize;
        f32 particleSizeDelta;
        f32 timeToLive;
        Node* node;
        bool used;
    };
    Particle* m_ParticleArray;

    enum kParticleTypes {
        kParticleTypeGravity,
        kParticleTypeRadial
    };

    Node* m_particlesRootNode;
    Geometry* m_geometry;
    PhysicsBody* m_body;
    std::vector<Particle*> m_ActiveParticles;
    Particle* findUnusedParticle();
    btVector3* m_Scale;
};
}

#endif /* ParticleEmitter_hpp */
