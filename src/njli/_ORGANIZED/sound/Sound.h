//
//  Sound.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Sound__
#define __JLIGameEngineTest__Sound__

#include "GLPlatform.h"

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractTransform.h"
#include "lua.hpp"

#ifdef USE_OPENAL
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenAL.framework/Versions/A/Headers/al.h"
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenAL.framework/Versions/A/Headers/alc.h"
#endif
#ifdef USE_FMOD
#include "fmod.hpp"
#include "fmod_errors.h"
#endif

namespace njli {
class SoundBuilder;
class Node;

ATTRIBUTE_ALIGNED16(class)
Sound :
    //    class Sound:
    public AbstractFactoryObject,
    public AbstractTransform
{
    friend class WorldFactory;
    friend class WorldSound;

protected:
    Sound();
    Sound(const AbstractBuilder&);
    Sound(const Sound&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Sound();
    Sound& operator=(const Sound&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    virtual s32 calculateSerializeBufferSize() const;
    virtual void serialize(void*, btSerializer*) const;

    virtual const char* getClassName() const;
    virtual s32 getType() const;
    operator std::string() const;

    static Sound** createArray(const u32 size);
    static void destroyArray(Sound * *array, const u32 size = 0);
    static Sound* create();
    static Sound* create(const SoundBuilder& builder);
    static Sound* clone(const Sound& object);
    static Sound* copy(const Sound& object);
    static void destroy(Sound * object);
    static void load(Sound & object, lua_State * L, int stack_index);
    static u32 type();

public:
    //TODO: fill in specific methods for Sound
    f32 getTimePosition();
    void setTimePosition(f32 pos);
    f32 getTimeLength();

    bool isPlaying();
    void play(bool isPaused = false);
    void stop();

    bool isPaused();
    void pause();
    void unPause();

    bool isMuted();
    void mute();
    void unMute();

    f32 getVolume();
    void setVolume(f32 vol = 1.0f);

    s32 getLoopCount();
    void setLoopCount(s32 count);

    virtual btTransform getWorldTransform() const;

#ifdef USE_OPENAL
#endif
#ifdef USE_FMOD
protected:
    FMOD::Channel* getChannel();
    Node* getParent();
    const Node* getParent() const;

private:
    FMOD::Sound* m_Sound;
    s32 m_ChannelIndex;
    btTransform* m_Transform;
    FMOD_MODE m_Mode;
#endif

#ifndef __EMSCRIPTEN__

#endif
};
}

#endif /* defined(__JLIGameEngineTest__Sound__) */
