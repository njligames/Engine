#include "WorldSound.h"
#include "Log.h"
#define TAG "WorldSound.mm"
#include "JLIFactoryTypes.h"
#include "Sound.h"
//#import <AudioToolbox/AudioSession.h>
#import <AVFoundation/AVAudioSession.h>
#import <Foundation/Foundation.h>
#define FORMATSTRING "{\"njli::WorldSound\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "File.h"

#include "btQuickprof.h"

#define MAXCHANNELS (32)

//void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);
#define FMOD_ERRCHECK(_result) do { if (FMOD_LOGGING_ON) ERRCHECK_fn(_result, __FILE__, __LINE__); } while (0)

//void FMOD_ERRCHECK(FMOD_RESULT _result)
//{
//    do { if (FMOD_LOGGING_ON) ERRCHECK_fn(_result, __FILE__, __LINE__); } while (0);
//}

FMOD_RESULT F_CALLBACK fmodDebugCallback(FMOD_DEBUG_FLAGS flags, const char *file, int line, const char *func, const char *message)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_DEBUG_CALLBACK occured.\n");
    return FMOD_OK;
}

float  F_CALLBACK fmod3DRolloffCallback(FMOD_CHANNELCONTROL *channelcontrol, float distance)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_3D_ROLLOFF_CALLBACK occured.\n");
    return 0;
}

// fileName is actually a pointer to a SoundInstance, passed in from CreateSound().
FMOD_RESULT F_CALLBACK fmodFileOpenCallback(const char *name, unsigned int *filesize, void **handle, void *userdata)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_FILE_OPEN_CALLBACK occured.\n");
//    SoundInstance *soundInstance;
//    
//    assert(fileName);
//    
//    soundInstance = (SoundInstance *)fileName;
//    assert(soundInstance->fileArchive);
//    
//    *handle = (void *)soundInstance;
//    *userdata = NULL;
//    
//    soundInstance->streamPtr = soundInstance->fileArchive->open(soundInstance->fileName);
//    if (soundInstance->streamPtr.isNull())
//    {
//        *filesize = 0;
//        return FMOD_ERR_FILE_NOTFOUND;
//    }
//    
//    *filesize = (unsigned int)soundInstance->streamPtr->size();
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileCloseCallback(void *handle, void *userdata)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_FILE_CLOSE_CALLBACK occured.\n");
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileReadCallback(void *handle, void *buffer, unsigned int sizeBytes, unsigned int *bytesRead, void *userData)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_FILE_READ_CALLBACK occured.\n");
//    SoundInstance *soundInstance;
//    
//    soundInstance = (SoundInstance *)handle;
//    *bytesRead = (unsigned int)soundInstance->streamPtr->read(buffer, (size_t)sizeBytes);
//    if (*bytesRead == 0)
//        return FMOD_ERR_FILE_EOF;
    
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileSeekCallback(void *handle, unsigned int pos, void *userdata)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_FILE_SEEK_CALLBACK occured.\n");
//    SoundInstance *soundInstance;
//    
//    soundInstance = (SoundInstance *)handle;
//    soundInstance->streamPtr->seek((size_t)pos);
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileAsyncReadCallback(FMOD_ASYNCREADINFO *info, void *userdata)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_FILE_ASYNCREAD_CALLBACK occured.\n");
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileAsyncCancelCallback(FMOD_ASYNCREADINFO *info, void *userdata)
{
    if(FMOD_LOGGING_ON)
        DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_FILE_ASYNCCANCEL_CALLBACK occured.\n");
    return FMOD_OK;
}

static FMOD_RESULT F_CALLBACK fmodErrorCallback(FMOD_DEBUG_FLAGS flags, const char *file, int line, const char *func, const char *message)
{
    
    //MOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG
    switch (flags)
    {
        case FMOD_DEBUG_LEVEL_ERROR:
            DEBUG_LOG_E(TAG, "%s - %d - %s - %s\n", file, line, func, message);
            break;
        case FMOD_DEBUG_LEVEL_WARNING:
            DEBUG_LOG_W(TAG, "%s - %d - %s - %s\n", file, line, func, message);
            break;
        case FMOD_DEBUG_LEVEL_LOG:
            DEBUG_LOG_V(TAG, "%s - %d - %s - %s\n", file, line, func, message);
            break;
        default:
            break;
    }
    
    return FMOD_OK;
}

//http://www.fmod.org/docs/content/generated/FMOD_SYSTEM_CALLBACK.html
static FMOD_RESULT F_CALLBACK fmodSystemcallback(FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK_TYPE type, void *commanddata1, void *commanddata2, void* userdata)
{
    FMOD::System *sys = (FMOD::System *)system;
    
    switch (type)
    {
        case FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED:
        {
            int numdrivers;
            
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED occured.\n");
            
            sys->getNumDrivers(&numdrivers);
            
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_PRINT_V(TAG, "Numdevices = %d\n", numdrivers);
        }
            break;
        case FMOD_SYSTEM_CALLBACK_DEVICELOST:
        {
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_DEVICELOST occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_MEMORYALLOCATIONFAILED:
        {
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_WRITE_V(TAG, "ERROR : FMOD_SYSTEM_CALLBACK_MEMORYALLOCATIONFAILED occured.\n");
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_PRINT_V(TAG, "%s.\n", commanddata1);
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_PRINT_V(TAG, "%d bytes.\n", commanddata2);
        }
            break;
        case FMOD_SYSTEM_CALLBACK_THREADCREATED:
        {
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_THREADCREATED occured.\n");
//            if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_V(TAG, "Thread ID = %d\n", (int)commanddata1);
//            if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_V(TAG, "Thread Name = %s\n", (char *)commanddata2);
        }
            break;
        case FMOD_SYSTEM_CALLBACK_BADDSPCONNECTION:
        {
            FMOD::DSP *source = (FMOD::DSP *)commanddata1;
            FMOD::DSP *dest = (FMOD::DSP *)commanddata2;
            
            if(FMOD_LOGGING_ON)
                DEBUG_LOG_WRITE_V(TAG, "ERROR : FMOD_SYSTEM_CALLBACK_BADDSPCONNECTION occured.\n");
            if (source)
            {
                char name[256];
                source->getInfo(name, 0,0,0,0);
                if(FMOD_LOGGING_ON)
                    DEBUG_LOG_PRINT_V(TAG, "SOURCE = %s\n", name);
            }
            if (dest)
            {
                char name[256];
                dest->getInfo(name, 0,0,0,0);
                if(FMOD_LOGGING_ON)
                    DEBUG_LOG_PRINT_V(TAG, "DEST = %s\n", name);
            }
        }
            break;
        case FMOD_SYSTEM_CALLBACK_PREMIX:
        {
//            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_PREMIX occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_POSTMIX:
        {
//            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_POSTMIX occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_ERROR:
        {
            /*
             typedef struct {
             FMOD_RESULT result;
             FMOD_ERRORCALLBACK_INSTANCETYPE instancetype;
             void *instance;
             const char *functionname;
             const char *functionparams;
             } FMOD_ERRORCALLBACK_INFO;
             */
            FMOD_ERRORCALLBACK_INFO *errorInfo = (FMOD_ERRORCALLBACK_INFO *)commanddata1;
            switch (errorInfo->instancetype)
            {
                case FMOD_ERRORCALLBACK_INSTANCETYPE_NONE:
                {
                    if(FMOD_LOGGING_ON)
                        DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_SYSTEM:
                {
                    FMOD::System *ptr = (FMOD::System*)errorInfo->instance;
                    
                    if(FMOD_LOGGING_ON)
                        DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNEL:
                {
                    FMOD::Channel *ptr = (FMOD::Channel*)errorInfo->instance;

                    if(FMOD_LOGGING_ON)
                        DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELGROUP:
                {
                    FMOD::ChannelGroup *ptr = (FMOD::ChannelGroup*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)
                        DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELCONTROL:
                {
                    FMOD::ChannelControl *ptr = (FMOD::ChannelControl*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)
                        DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_SOUND:
                {
                    FMOD::Sound *ptr = (FMOD::Sound*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)
                        DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_SOUNDGROUP:
                {
                    FMOD::SoundGroup *ptr = (FMOD::SoundGroup*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_DSP:
                {
                    FMOD::DSP *ptr = (FMOD::DSP*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_DSPCONNECTION:
                {
                    FMOD::DSPConnection *ptr = (FMOD::DSPConnection*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_GEOMETRY:
                {
                    FMOD::Geometry *ptr = (FMOD::Geometry*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_REVERB3D:
                {
                    FMOD::Reverb3D *ptr = (FMOD::Reverb3D*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_SYSTEM:
                {
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                    case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTDESCRIPTION:
                {
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                
                }
                    break;
                    case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTINSTANCE:
                {
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                    case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_PARAMETERINSTANCE:
                {
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
//                    case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_CUEINSTANCE:
//                {
//                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
//                    
//                }
//                    break;
                    case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BUS:
                {
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                    case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_VCA:
                {
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BANK:
                {
                    if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                    
                default:
                    break;
            }
//            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_ERROR occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_MIDMIX:
        {
//            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_MIDMIX occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_THREADDESTROYED:
        {
            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_THREADDESTROYED occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_PREUPDATE:
        {
//            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_PREUPDATE occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_POSTUPDATE:
        {
//            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_V(TAG, "NOTE : FMOD_SYSTEM_CALLBACK_POSTUPDATE occured.\n");
        }
            break;
    }
    
    return FMOD_OK;
}

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        DEBUG_LOG_PRINT_E(TAG, "%s(%d): FMOD error %d - %s", file, line, result, FMOD_ErrorString(result));
    }
}



//@interface AudioBufferPlayer : NSObject <AVAudioSessionDelegate>
//@end
//
//@implementation AudioBufferPlayer
//- (void)beginInterruption
//{
//}
//
//- (void)endInterruption
//{
//}
//@end


//static void interruptionListenerCallback(void *inUserData, UInt32 interruptionState)
//{
//    if (interruptionState == kAudioSessionBeginInterruption)
//    {
////        gSuspendState = true;
//    }
//    else if (interruptionState == kAudioSessionEndInterruption)
//    {
////        UInt32 sessionCategory = kAudioSessionCategory_PlayAndRecord;
////        AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
////        AudioSessionSetActive(true);
//        
////        gSuspendState = false;
//    }
//}

namespace njli
{
    WorldSound::WorldSound()
    {
//        AudioSessionInitialize(NULL, NULL, interruptionListenerCallback, NULL);
//        
//        // Default to 'play and record' so we have recording available for examples that use it
////        UInt32 sessionCategory = kAudioSessionCategory_PlayAndRecord;
//        UInt32 sessionCategory = kAudioSessionCategory_MediaPlayback;
//        AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
        
//        AudioSessionSetActive(true);
        
        
        BOOL success = NO;
        NSError *error = nil;
        
        AVAudioSession *session = [AVAudioSession sharedInstance];
        
//        success = [session setCategory:AVAudioSessionCategoryPlayAndRecord error:&error];
        success = [session setCategory:AVAudioSessionCategoryPlayback error:&error];
        if(FMOD_LOGGING_ON)DEBUG_ASSERT_PRINT(success, "%s", [[error localizedDescription] UTF8String]);
        
        success = [session setActive:YES error:&error];
        if(FMOD_LOGGING_ON)DEBUG_ASSERT_PRINT(success, "%s", [[error localizedDescription] UTF8String]);
        
        FMOD_RESULT   result        = FMOD_OK;
        unsigned int  version       = 0;
        
//        FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_NONE | FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG, FMOD_DEBUG_MODE_CALLBACK, fmodErrorCallback);
        FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_NONE);// | FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG);
        
        result = FMOD::System_Create(&m_System);
        FMOD_ERRCHECK(result);
        
        result = m_System->getVersion(&version);
        FMOD_ERRCHECK(result);
        
//        s32 d = FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG | FMOD_DEBUG_TYPE_MEMORY | FMOD_DEBUG_TYPE_FILE | FMOD_DEBUG_TYPE_CODEC | FMOD_DEBUG_TYPE_TRACE | FMOD_DEBUG_DISPLAY_TIMESTAMPS | FMOD_DEBUG_DISPLAY_LINENUMBERS | FMOD_DEBUG_DISPLAY_THREAD;
//        result = FMOD::Debug_Initialize(d, FMOD_DEBUG_MODE_TTY, fmodDebugCallback);
//        FMOD_ERRCHECK(result);
        
        if (version < FMOD_VERSION)
        {
            if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_E(TAG, "FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
        }
        result = m_System->init(MAXCHANNELS, FMOD_INIT_NORMAL, 0);
        FMOD_ERRCHECK(result);
        
        result = m_System->setCallback(fmodSystemcallback);
        FMOD_ERRCHECK(result);
        
        result = m_System->setFileSystem(fmodFileOpenCallback, fmodFileCloseCallback, fmodFileReadCallback, fmodFileSeekCallback, fmodFileAsyncReadCallback, fmodFileAsyncCancelCallback, 2048);
        FMOD_ERRCHECK(result);
        
        result = m_System->set3DRolloffCallback(fmod3DRolloffCallback);
        FMOD_ERRCHECK(result);
        
    }
    WorldSound::~WorldSound()
    {
        FMOD_RESULT   result        = FMOD_OK;
        
        result = m_System->close();
        FMOD_ERRCHECK(result);
        result = m_System->release();
        FMOD_ERRCHECK(result);
        
        
        NSError *error = nil;
        BOOL success = [[AVAudioSession sharedInstance] setActive:NO error:&error];
        if(FMOD_LOGGING_ON)DEBUG_ASSERT_PRINT(success, "%s", [[error localizedDescription] UTF8String]);
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
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    void WorldSound::update()
    {
        BT_PROFILE("WorldSound::update");
        FMOD_RESULT result = m_System->update();
        FMOD_ERRCHECK(result);
    }
    
    void WorldSound::playSound(Sound &sound, bool isPaused)
    {
        if(sound.m_Sound)
        {
            FMOD_RESULT   result        = FMOD_OK;
            FMOD::Channel *channel = NULL;
            result = m_System->playSound(sound.m_Sound, 0, isPaused, &channel);
            FMOD_ERRCHECK(result);

            if(channel)
            {
                result = channel->getIndex(&sound.m_ChannelIndex);
                FMOD_ERRCHECK(result);
            }
        }
        else
        {
            if(FMOD_LOGGING_ON)DEBUG_LOG_WRITE_W(TAG, "The sound is not loaded");
        }
    }
    
    bool WorldSound::createSound(const char *fileContent, size_t file_size, Sound &sound)
    {
        FMOD_CREATESOUNDEXINFO info;
        memset(&info, 0, sizeof(FMOD_CREATESOUNDEXINFO));
        info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
        info.length = file_size;
        info.format = FMOD_SOUND_FORMAT_PCM16;
        info.numchannels = 1;
        info.defaultfrequency = 44100;
        
        //channels 1, format 2, freq 44100, mode 00000809
        
        
        FMOD::Sound * s = 0;
        FMOD_MODE mode = FMOD_OPENMEMORY;// | FMOD_LOOP_OFF | FMOD_OPENRAW;
//        FMOD_MODE mode = FMOD_DEFAULT | FMOD_LOOP_OFF;
        FMOD_RESULT result = m_System->createSound(fileContent, mode, &info, &s);
        FMOD_ERRCHECK(result);
        sound.m_Sound = s;
        sound.m_Mode = mode;
        
        return (result == FMOD_OK);
    }
    
    void WorldSound::enablePause(bool enable)
    {
        BOOL success = NO;
        NSError *error = nil;
        AVAudioSession *session = [AVAudioSession sharedInstance];
        
        if (enable)
        {
            success = [session setActive:NO error:&error];
            
            m_System->mixerSuspend();
        }
        else
        {
            success = [session setCategory:AVAudioSessionCategoryPlayback error:&error];
            success = [session setActive:YES error:&error];
            
            m_System->mixerResume();
        }
    }
    
    FMOD::Channel *WorldSound::getChannel(s32 channelindex)
    {
//        int channels;
//        m_System->getChannelsPlaying(&channels);
//        
//        if(FMOD_LOGGING_ON)DEBUG_LOG_PRINT_D(TAG, "Number of Channels Playing %d", channels);
        
        FMOD::Channel *channel;
        m_System->getChannel(channelindex, &channel);
        return channel;
    }
}
