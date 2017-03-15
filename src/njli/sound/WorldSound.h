//#include "AbstractSingleton.h"
#ifndef __JLIGameEngineTest__WorldSound__
#define __JLIGameEngineTest__WorldSound__

#include "SoundPlatform.h"

#ifdef USE_OPENAL
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenAL.framework/Versions/A/Headers/al.h"
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenAL.framework/Versions/A/Headers/alc.h"
#include <vector>
#endif
#ifdef USE_FMOD
#include "fmod.hpp"
#include "fmod_errors.h"
#endif

#include "AbstractObject.h"
#include "Util.h"
#include <string>

//#if defined(DEBUG) || defined (_DEBUG)
//#define FMOD_LOGGING_ON 1
//#else
//#define FMOD_LOGGING_ON 0
//#endif

//http://www.ogre3d.org/tikiwiki/tiki-index.php?page=FMOD+SoundManager

namespace njli {
class Sound;

class WorldSound : public AbstractObject {
//    friend class WorldResourceLoader;
    friend class Sound;
    friend class World;

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    WorldSound();
    ~WorldSound();

    virtual const s8* getClassName() const;
    virtual s32 getType() const;
    virtual operator std::string() const;

    void enablePause(bool enable = true);

    bool createSound(const char* fileContent, size_t file_size, Sound& sound);
protected:
    void update();

    void playSound(Sound& sound, bool isPaused = false);

    

#ifdef USE_OPENAL
    // OpenAL context for playing sounds
    ALCcontext* m_ALCcontext;

    // The device we are going to use to play sounds
    ALCdevice* m_ALCdevice;

    std::vector<u32> m_Sources;
#endif
#ifdef USE_FMOD
protected:
    FMOD::Channel* getChannel(s32 channelindex);

private:
    FMOD::System* m_System;
    FMOD::ChannelGroup* m_MasterChannel;
    int* m_ChannelsPlaying;
#endif
};
}

#endif