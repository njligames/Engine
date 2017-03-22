#include "File.h"
// #include <android/asset_manager_jni.h>
#include <assert.h>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "Log.h"

#define MAC_PATH "/Users/jamesfolk/NJLI/GameEngine/COMMON/assets/"

// static int emscripten_read(void* cookie, char* buf, int size) {
//   return AAsset_read((AAsset*)cookie, buf, size);
// }

// static int emscripten_write(void* cookie, const char* buf, int size) {
//   return EACCES; // can't provide write access to the apk
// }

// static fpos_t emscripten_seek(void* cookie, fpos_t offset, int whence) {
//   return AAsset_seek((AAsset*)cookie, offset, whence);
// }

// static int emscripten_close(void* cookie) {
//   AAsset_close((AAsset*)cookie);
//   return 0;
// }

FILE* njli_fopen(const char* fname, const char* mode)
{
  // if(mode[0] == 'w') return NULL;

  return fopen(fname, mode);
  // AAsset* asset = AAssetManager_open(asset_manager, fname, 0);
  // if(!asset) return NULL;

  // return funopen(asset, emscripten_read, emscripten_write, emscripten_seek, emscripten_close);
}

const char *RESOURCE_PATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, MAC_PATH);
    return tempBuffer;
}

const char *ASSET_PATH(const char *file)
{
    static char tempBuffer[512];
    strcpy(tempBuffer, MAC_PATH);
    strcat(tempBuffer, file);
    return tempBuffer;
}

const char *BUNDLE_PATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, MAC_PATH);
    return tempBuffer;
}

const char *DOCUMENT_PATH(const char *file)
{
    static char tempBuffer[512];
    strcpy(tempBuffer, MAC_PATH);
    strcat(tempBuffer, file);
    return tempBuffer;
}

void sleepThread(float milliseconds)
{
    usleep(milliseconds);
}

const char *DOCUMENT_BASEPATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, MAC_PATH);
    return tempBuffer;
}
