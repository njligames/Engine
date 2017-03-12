#include "WorldSound.h"
#include "Log.h"
#define TAG "WorldSound.mm"
#include "JLIFactoryTypes.h"
#include "Sound.h"

#include "File.h"

#define MAXCHANNELS (32)


namespace njli
{
    WorldSound::WorldSound()
    {
        // Get the device we are going to use for sound.  Using NULL gets the default device
        m_ALCdevice = alcOpenDevice(NULL);
        
        // If a device has been found we then need to create a context, make it current and then
        // preload the OpenAL Sources
        if(m_ALCdevice)
        {
            // Use the device we have now got to create a context "air"
            m_ALCcontext = alcCreateContext(m_ALCdevice, NULL);
            // Make the context we have just created into the active context
            alcMakeContextCurrent(m_ALCcontext);
            // Pre-create 32 sound sources which can be dynamically allocated to buffers (sounds)
            u32 sourceID;
            for(int index = 0; index < MAXCHANNELS; index++)
            {
                // Generate an OpenAL source
                alGenSources(1, &sourceID);
                m_Sources.push_back(sourceID);
                // Add the generated sourceID to our array of sound sources
                // [_SFXSources addObject:[NSNumber numberWithUnsignedInt:sourceID]];
            }
        }
    }
    WorldSound::~WorldSound()
    {
        for(int index = 0; index < MAXCHANNELS; index++)
        {
            u32 sourceID = m_Sources.at(index);
            alDeleteSources(1, &sourceID);
        }

        // Disable and then destroy the context
        alcMakeContextCurrent(NULL);
        if(m_ALCcontext)
            alcDestroyContext(m_ALCcontext);
        
        // Close the device
        if(m_ALCdevice)
            alcCloseDevice(m_ALCdevice);
    }
    
    const s8 *WorldSound::getClassName()const
    {
        return "WorldSound";
    }
    
    s32 WorldSound::getType()const
    {
        return JLI_OBJECT_TYPE_WorldSound;
    }
    
    WorldSound::operator std::string() const
    {
        return std::string("TODO");
    }
    
    void WorldSound::update()
    {
        // FMOD_RESULT result = m_System->update();
        // FMOD_ERRCHECK(result);
    }
    
    void WorldSound::playSound(Sound &sound, bool isPaused)
    {
        // if(sound.m_Sound)
        // {
        //     FMOD::Channel *channel = NULL;
        //     FMOD_ERRCHECK(m_System->playSound(sound.m_Sound, 0, isPaused, &channel));
        //     if(channel)
        //         channel->getIndex(&sound.m_ChannelIndex);
        // }
        // else
        // {
        //     DEBUG_LOG_WRITE_W(TAG, "The sound is not loaded");
        // }
    }
    
    void WorldSound::createSound(const char *fileContent, size_t file_size, Sound &sound)
    {
        // FMOD_CREATESOUNDEXINFO info;
        // memset(&info, 0, sizeof(FMOD_CREATESOUNDEXINFO));
        // info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
        // info.length = file_size;
        
        // FMOD::Sound * s = 0;
        // FMOD_MODE mode = FMOD_OPENMEMORY | FMOD_LOOP_OFF;
        // FMOD_RESULT result = m_System->createSound(fileContent, mode, &info, &s);
        // FMOD_ERRCHECK(result);
        // sound.m_Sound = s;
        // sound.m_Mode = mode;
    }
    
    // FMOD::Channel *WorldSound::getChannel(s32 channelindex)
    // {
    //     // FMOD::Channel *channel;
    //     // m_System->getChannel(channelindex, &channel);
    //     // return channel;
    // }
    // 
    void WorldSound::enableSuspend(bool enable)
    {
        if (enable)
        {
            // m_System->mixerSuspend();
        }
        else
        {
            // m_System->mixerResume();
        }
    }
}
