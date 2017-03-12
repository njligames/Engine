#include "File.h"
#include "Log.h"
#include <android/asset_manager_jni.h>
#include <assert.h>
#include <errno.h>
#include <string>
#include <unistd.h>

#define ANDROID_PATH ""

#include "GLPlatform.h"

AAssetManager* asset_manager;
// static AAssetManager* asset_manager;

#ifndef _Included_com_example_njligameenginetest_File
#define _Included_com_example_njligameenginetest_File
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_android_gl2jni_GL2JNILib
 * Method:    init_asset_manager
 * Signature: (Landroid/content/res/AssetManager;)V
 */
// JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init_1asset_1manager
//   (JNIEnv *env, jclass cls, jobject java_asset_manager)
//   {
//     asset_manager = AAssetManager_fromJava(env, java_asset_manager);
//   }

#ifdef __cplusplus
}
#endif
#endif

// static FileData get_asset_data(const char* relative_path) {
//     assert(relative_path != NULL);
//     AAsset* asset = AAssetManager_open(asset_manager, relative_path, AASSET_MODE_STREAMING);
//     assert(asset != NULL);

//     return (FileData) { AAsset_getLength(asset), AAsset_getBuffer(asset), asset };
// }

// static void release_asset_data(const FileData* file_data) {
//     assert(file_data != NULL);
//     assert(file_data->file_handle != NULL);
//     AAsset_close((AAsset*)file_data->file_handle);
// }

static int android_read(void* cookie, char* buf, int size)
{
    return AAsset_read((AAsset*)cookie, buf, size);
}

static int android_write(void* cookie, const char* buf, int size)
{
    return EACCES; // can't provide write access to the apk
}

static fpos_t android_seek(void* cookie, fpos_t offset, int whence)
{
    return AAsset_seek((AAsset*)cookie, offset, whence);
}

static int android_close(void* cookie)
{
    AAsset_close((AAsset*)cookie);
    return 0;
}

FILE* njli_fopen(const char* fname, const char* mode)
{
    // if(mode[0] == 'w') return NULL;

    AAsset* asset = AAssetManager_open(asset_manager, fname, 0);
    if (!asset)
        return NULL;

    return funopen(asset, android_read, android_write, android_seek, android_close);
}

const char* RESOURCE_PATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, ANDROID_PATH);
    return tempBuffer;
}

const char* ASSET_PATH(const char* file)
{
    static char tempBuffer[512];
    strcpy(tempBuffer, ANDROID_PATH);
    strcat(tempBuffer, file);
    return tempBuffer;
}

const char* BUNDLE_PATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, ANDROID_PATH);
    return tempBuffer;
}

const char* DOCUMENT_PATH(const char* file)
{
    static char tempBuffer[512];
    strcpy(tempBuffer, ANDROID_PATH);
    strcat(tempBuffer, file);
    return tempBuffer;
}

void sleepThread(float milliseconds)
{
    usleep(milliseconds);
}

const char* DOCUMENT_BASEPATH()
{
    // NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    // NSString *documentsDirectory = [paths objectAtIndex:0]; // Get documents folder
    // return [documentsDirectory UTF8String];
    return "";
}

// const char *File::asset_path(const char *file)
// {
// 	return file;
// static char tempBuffer[512];
// strcpy(tempBuffer, "file:///android_asset/");
// strcat(tempBuffer, file);
// return tempBuffer;
// }

// bool File::readAsset(const char * filepath)
// {
// 	AAsset* asset = AAssetManager_open(asset_manager, filepath, AASSET_MODE_UNKNOWN);

// 	if (asset)
// 	{
// 		Log("Asset is opened.");

// 		if(file_content)
// 		{
// 			free(file_content);
// 		}

// 		file_size = AAsset_getLength(asset);
// 		file_content = malloc(file_size);

// 		int bytesread = AAsset_read(asset, file_content, file_size);
// 		if (bytesread)
// 		{
// 			Log("bytesread: %d.", bytesread);
// 			Log("text: %s.", (unsigned char*)file_content);
// 		}
// 		else
// 		{
// 			Log("unable to read file %s", filepath);
// 		}
// 		AAsset_close(asset);

// 		return true;
// 	}

// 	return false;
// }

// bool File::write(const char * filepath, const char *data)
// {
//     return true;
// }
//
//
//
//
//
//char *File::asset_path(const char *file, char *filePath)
//{
//	strcpy(filePath, "file:///android_asset/");
//
//	strcat(filePath, file);
//
//	return filePath;
//}
//
//bool File::readAsset(const std::string filepath)
//{
//	AAsset* asset = AAssetManager_open(asset_manager, filepath.c_str(), AASSET_MODE_UNKNOWN);
//
//	if (asset)
//	{
//		Log("Asset is opened.");
//
//		if(file_content)
//		{
//			free(file_content);
//		}
//
//		file_size = AAsset_getLength(asset);
//		file_content = malloc(file_size);
//
//		int bytesread = AAsset_read(asset, file_content, file_size);
//		if (bytesread)
//		{
//			Log("bytesread: %d.", bytesread);
//			Log("text: %s.", (unsigned char*)file_content);
//		}
//		else
//		{
//			Log("unable to read file %s", filepath.c_str());
//		}
//		AAsset_close(asset);
//
//		return true;
//	}
//
//	return false;
//}
//
//bool File::write(const std::string filepath, const char *data)
//{
//	return false;
//}
