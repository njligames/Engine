#ifndef _JLIGAMEENGINE_FILE_H_
#define _JLIGAMEENGINE_FILE_H_

#include "Macros.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

FILE* njli_fopen(const char* fname, const char* mode);
const char* RESOURCE_PATH() SIMPLE_FUNCTION;
const char* ASSET_PATH(const char* file) SIMPLE_FUNCTION;
const char* BUNDLE_PATH() SIMPLE_FUNCTION;
const char* DOCUMENT_PATH(const char* file) SIMPLE_FUNCTION;
const char* DOCUMENT_BASEPATH() SIMPLE_FUNCTION;
void sleepThread(float milliseconds) SIMPLE_FUNCTION;

void setupFileSystem() SIMPLE_FUNCTION;

#ifdef __cplusplus
}
#endif

#endif
