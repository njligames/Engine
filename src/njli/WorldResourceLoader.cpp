//
//  WorldResourceLoader.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "WorldResourceLoader.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "WorldResourceLoader.h"

#include "ParticleEmitter.h"
#include "Light.h"
#include "Image.h"
#include "Geometry.h"
#include "ShaderProgram.h"
#include "Font.h"
#include "Lua.h"
#include "Xml.h"
#include "JsonJLI.h"
#include "Image.h"
#include "Sound.h"
#include "Material.h"
#include "Skinner.h"
#include "Camera.h"

#include "File.h"

#include "stb_image.h"

#include "Log.h"

#include "unzip.h"

#define TAG "WORLDRESOURCELOADER.CPP"
#define FORMATSTRING "{\"njli::WorldResourceLoader\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

//#include "PVRTTexture.h"

namespace njli
{
    WorldResourceLoader::FileData::FileData():
    m_buffer(NULL),
    m_fileSize(0),
    m_fileName("")
    {
        
    }
//    WorldResourceLoader::FileData::FileData(const FileData &rhs):
//    m_buffer(malloc(rhs.m_fileSize)),
//    m_fileSize(rhs.m_fileSize),
//    m_fileName(rhs.m_fileName)
//    {
//        memcpy(m_buffer, rhs.m_buffer, rhs.m_fileSize);
//    }
    
//    WorldResourceLoader::FileData::FileData(const void* buffer, long size):
//    m_buffer(malloc(size)),
//    m_fileSize(size),
//    m_fileName("")
//    {
//        memcpy(m_buffer, buffer, size);
//    }
    
    WorldResourceLoader::FileData::FileData(const char *filePath):
    m_buffer(NULL),
    m_fileSize(0),
    m_fileName("")
    {
        load(filePath);
    }
    
    WorldResourceLoader::FileData::~FileData()
    {
        if(m_buffer)
            free(m_buffer);
        m_buffer = NULL;
    }

//    WorldResourceLoader::FileData &WorldResourceLoader::operator=(const WorldResourceLoader::FileData &rhs)
//    {
//        
//    }
//    WorldResourceLoader::FileData &WorldResourceLoader::operator=(const WorldResourceLoader::FileData &rhs)
//    {
//        
//    }
    
    void* WorldResourceLoader::FileData::getBufferPtr()const
    {
        return m_buffer;
    }
    long WorldResourceLoader::FileData::getSize()const
    {
        return m_fileSize;
    }
    
    void WorldResourceLoader::FileData::setFilename(const char *filename)
    {
        m_fileName = filename;
    }
    
    const char *WorldResourceLoader::FileData::getFilename()const
    {
        return m_fileName.c_str();
    }
    
    bool WorldResourceLoader::FileData::load(const char *filePath)
    {
        FILE *file = njli_fopen(ASSET_PATH(filePath), "rb");
        
        if(file)
        {
            fseek(file, 0, SEEK_END);
            m_fileSize = ftell(file);
            fseek(file, 0, SEEK_SET);
            
            if(m_buffer)
                free(m_buffer);
            m_buffer = malloc(m_fileSize);
            DEBUG_ASSERT(m_buffer);
            
            fread(m_buffer, 1, m_fileSize, file);
            
            fclose(file);
            
            m_fileName = filePath;
            
            return true;
        }
        else
        {
            DEBUG_LOG_PRINT_W(TAG, "Unable to open the file: %s", filePath);
        }
        return false;
    }
    
    
    
//    static u8 GetNumberOfComponents(const PVRTextureHeaderV3& sTextureHeader)
//    {
//        PVRTuint64 PixelFormat = sTextureHeader.u64PixelFormat;
//        EPVRTVariableType ChannelType = (EPVRTVariableType)sTextureHeader.u32ChannelType;
//        EPVRTColourSpace ColourSpace = (EPVRTColourSpace)sTextureHeader.u32ColourSpace;
//        
//        
//        //Get the last 32 bits of the pixel format.
//        PVRTuint64 PixelFormatPartHigh = PixelFormat&PVRTEX_PFHIGHMASK;
//        
//        //Check for a compressed format (The first 8 bytes will be 0, so the whole thing will be equal to the last 32 bits).
//        if (PixelFormatPartHigh==0)
//        {
//            //Format and type == 0 for compressed textures.
//            switch (PixelFormat)
//            {
//                case ePVRTPF_PVRTCI_2bpp_RGB:
//                {
//                    return 3;
//                }
//                case ePVRTPF_PVRTCI_2bpp_RGBA:
//                {
//                    return 4;
//                }
//                case ePVRTPF_PVRTCI_4bpp_RGB:
//                {
//                    return 3;
//                }
//                case ePVRTPF_PVRTCI_4bpp_RGBA:
//                {
//                    return 4;
//                }
//                default:
//                    return 4;
//            }
//        }
//        else
//        {
//            switch (ChannelType)
//            {
//                case ePVRTVarTypeFloat:
//                {
//                    switch (PixelFormat)
//                    {
//                            //HALF_FLOAT_OES
//                        case PVRTGENPIXELID4('r','g','b','a',16,16,16,16):
//                        {
//                            return 4;
//                        }
//                        case PVRTGENPIXELID3('r','g','b',16,16,16):
//                        {
//                            return 3;
//                        }
//                        case PVRTGENPIXELID2('l','a',16,16):
//                        {
//                            return 1;
//                        }
//                        case PVRTGENPIXELID1('l',16):
//                        {
//                            return 1;
//                        }
//                        case PVRTGENPIXELID1('a',16):
//                        {
//                            return 1;
//                        }
//                            //FLOAT (OES)
//                        case PVRTGENPIXELID4('r','g','b','a',32,32,32,32):
//                        {
//                            return 4;
//                        }
//                        case PVRTGENPIXELID3('r','g','b',32,32,32):
//                        {
//                            return 3;
//                        }
//                        case PVRTGENPIXELID2('l','a',32,32):
//                        {
//                            return 1;
//                        }
//                        case PVRTGENPIXELID1('l',32):
//                        {
//                            return 1;
//                        }
//                        case PVRTGENPIXELID1('a',32):
//                        {
//                            return 1;
//                        }
//                    }
//                    break;
//                }
//                case ePVRTVarTypeUnsignedByteNorm:
//                {
//                    switch (PixelFormat)
//                    {
//                        case PVRTGENPIXELID4('r','g','b','a',8,8,8,8):
//                        {
//                            return 4;
//                        }
//                        case PVRTGENPIXELID3('r','g','b',8,8,8):
//                        {
//                            return 3;
//                        }
//                        case PVRTGENPIXELID2('l','a',8,8):
//                        {
//                            return 1;
//                        }
//                        case PVRTGENPIXELID1('l',8):
//                        {
//                            return 1;
//                        }
//                        case PVRTGENPIXELID1('a',8):
//                        {
//                            return 1;
//                        }
//                        case PVRTGENPIXELID4('b','g','r','a',8,8,8,8):
//                        {
//                            return 4;
//                        }
//                    }
//                    break;
//                }
//                case ePVRTVarTypeUnsignedShortNorm:
//                {
//                    switch (PixelFormat)
//                    {
//                        case PVRTGENPIXELID4('r','g','b','a',4,4,4,4):
//                        {
//                            return 4;
//                        }
//                        case PVRTGENPIXELID4('r','g','b','a',5,5,5,1):
//                        {
//                            return 4;
//                        }
//                        case PVRTGENPIXELID3('r','g','b',5,6,5):
//                        {
//                            return 3;
//                        }
//                    }
//                    break;
//                }
//                default:
//                    return 4;
//            }
//        }
//        return 4;
//    }
    
    
    
    
    
    
    
//    WorldResourceLoader::ImageFileData::ImageFileData():
//    WorldResourceLoader::FileData(),
//    m_width(0),
//    m_height(0),
//    m_components(0),
//    m_type(JLI_IMAGE_TYPE_NONE)
//    {
//        
//    }
//    WorldResourceLoader::ImageFileData::ImageFileData(const WorldResourceLoader::ImageFileData &rhs):
//    WorldResourceLoader::FileData(rhs),
//    m_width(rhs.m_width),
//    m_height(rhs.m_height),
//    m_components(rhs.m_components)
//    {
//        
//    }
    WorldResourceLoader::ImageFileData::ImageFileData(const char *filePath):
    WorldResourceLoader::FileData(),
    m_width(0),
    m_height(0),
    m_components(0),
    m_type(JLI_IMAGE_TYPE_NONE)
    {
        std::string s(filePath);
        std::reverse(s.begin(), s.end());
        std::string extension = s.substr(0, s.find("."));
        std::reverse(extension.begin(), extension.end());
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        
        if(extension == "jpeg")m_type = JLI_IMAGE_TYPE_JPEG;
        if(extension == "png")m_type = JLI_IMAGE_TYPE_PNG;
        if(extension == "bmp")m_type = JLI_IMAGE_TYPE_BMP;
        if(extension == "gif")m_type = JLI_IMAGE_TYPE_GIF;
        if(extension == "psd")m_type = JLI_IMAGE_TYPE_PSD;
        if(extension == "pic")m_type = JLI_IMAGE_TYPE_PIC;
        if(extension == "hdr")m_type = JLI_IMAGE_TYPE_HDR;
        if(extension == "tga")m_type = JLI_IMAGE_TYPE_TGA;
        if(extension == "pvr")m_type = JLI_IMAGE_TYPE_PVR;
        
        if ((extension == "jpeg") ||
            (extension == "png") ||
            (extension == "bmp") ||
            (extension == "gif") ||
            (extension == "psd") ||
            (extension == "pic") ||
            (extension == "hdr") ||
            (extension == "tga"))
        {
            if(m_buffer)
                free(m_buffer);
            m_buffer = (void*)stbi_load(ASSET_PATH(filePath), &m_width, &m_height, &m_components, 0);
            DEBUG_ASSERT(m_buffer);
            
            m_fileSize = (m_width * m_height * m_components);
        }
        else if(extension == "pvr")
        {
            if(FileData::load(filePath))
            {
                DEBUG_ASSERT_WRITE(true, "Need to implement the PVR loading...");
//                PVRTextureHeaderV3 *header = (PVRTextureHeaderV3*)m_buffer;
//                m_fileSize = PVRTGetTextureDataSize(*header);
//                m_components = GetNumberOfComponents(*header);
//                m_width = header->u32Width;
//                m_height = header->u32Height;
            }
        }
        
        setFilename(filePath);
        
        DEBUG_ASSERT(m_buffer);
    }
    
//    WorldResourceLoader::ImageFileData::~ImageFileData()
//    {
//        if(m_buffer)
//            stbi_image_free(m_buffer);
//        m_buffer = NULL;
//    }
    
    s32 WorldResourceLoader::ImageFileData::getWidth()const
    {
        return m_width;
    }
    
    s32 WorldResourceLoader::ImageFileData::getHeight()const
    {
        return m_height;
    }
    
    s32 WorldResourceLoader::ImageFileData::numberOfComponents()const
    {
        return m_components;
    }
    
    njliImageType WorldResourceLoader::ImageFileData::getType()const
    {
        return m_type;
    }
    
    
    
    
    
    
    
    
    WorldResourceLoader::WorldResourceLoader()
    {
        
    }
    WorldResourceLoader::~WorldResourceLoader()
    {
        unLoadAll();
    }
    const char *WorldResourceLoader::getClassName()const
    {
        return "WorldResourceLoader";
    }
    
    
    
//    bool WorldResourceLoader::setPvrImage(const char *filePath, Image &img)
//    {
//        const void *content;
//        unsigned long file_size;
//        
////        if(njli::World::getInstance()->getWorldResourceLoader()->loadDataFromFile(filePath,
////                                                                               &content,
////                                                                               &file_size))
////        {
////            PVRTextureHeaderV3 *header = (PVRTextureHeaderV3*)content;
////            img.setPVRData((u8*)content, PVRTGetTextureDataSize(*header), filePath);
////            
////            return true;
////        }
//        
//        return false;
//    }
    
    s32 WorldResourceLoader::getType()const
    {
        return JLI_OBJECT_TYPE_WorldResourceLoader;
    }
    WorldResourceLoader::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    long WorldResourceLoader::dataPtrSize(const char* filePath)const
    {
        if (filePath)
        {
            FileData *fileData = getFileData(filePath);
            if(fileData)
            {
                return fileData->getSize();
            }
        }
        return 0;
    }
    
//    bool WorldResourceLoader::copyDataPtr(const char* filePath, u8 **dataPtr, long *size)const
//    {
//        bool retVal = false;
//        
//        DEBUG_ASSERT(*dataPtr);
//        DEBUG_ASSERT(*size);
//        
//        if (filePath)
//        {
//            FileData *fileData = getFileData(filePath);
//            if(fileData)
//            {
//                memcpy(*dataPtr, fileData->getBufferPtr(), fileData->getSize());
//                retVal = true;
//            }
//        }
//        return retVal;
//    }
    
#define ROUND(val,places) (roundf(val * pow(10,places)) / (pow(10,places)))
//    float rounded_down = floorf(val * 100) / 100;   /* Result: 37.77 */
//    float nearest = roundf(val * 100) / 100;  /* Result: 37.78 */
//    float rounded_up = ceilf(val * 100) / 100;      /* Result: 37.78 */
    
    bool WorldResourceLoader::load(const char* filePath, Image *image)
    {
        DEBUG_ASSERT(image);
        bool retVal = false;
        
        if (filePath)
        {
            ImageFileData *fileData = loadImageFileData(filePath);
            
            void *fileContent = fileData->getBufferPtr();
            
            if(fileContent)
            {
//                retVal = image->setData(fileData);
                retVal = image->copyData(fileData);
                
                image->flip();
                
                
                removeFileData(filePath);
                
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
//    bool WorldResourceLoader::load(const char *filePath, Image &img)
//    {
//        char buffer[2048] = "";
//        sprintf(buffer, "%s", filePath);
//        
//        char *s = strtok(buffer, "%");
//        char *end = strtok(NULL, "%");
//        if (end)
//        {
//            char buffer2[8];
//            strcpy(buffer2, end);
//            sprintf(buffer, "%s", s);
//            f32 aspect = ROUND(njli::World::getInstance()->getAspectRatio(), 1);
//            f32 ratio1 = ROUND(3.0f/2.0f, 1);
//            f32 ratio2 = ROUND(16.0f/9.0f, 1);
//            f32 ratio3 = ROUND(4.0f/3.0f, 1);
//            
//            //8:5
//            //128 : 75
//            //5 : 3
//            
//            if(aspect == ratio1)
//            {
//                strcat(buffer, "_3_2_");
//            }
//            else if(aspect == ratio2)
//            {
//                strcat(buffer, "_16_9_");
//            }
//            else if(aspect == ratio3)
//            {
//                strcat(buffer, "_4_3_");
//            }
//            
//            strcat(buffer, buffer2);
//        }
//        
//        {
//            s32 req_comp = 0;
//            s32 x, y, components;
//            unsigned char *fileContent = stbi_load(ASSET_PATH(buffer), &x, &y, &components, 0);
//            
//            u32 pixel_count = x * y;
//            bool hasAlpha = false;
//            if(comp == 4)
//            {
//                for (s32 i = 0, color = 0; i < pixel_count && !hasAlpha; ++i,color+=4)
//                {
//                    unsigned char alpha = fileContent[color + 3];
//                    if (alpha != 0xFF)
//                    {
//                        hasAlpha = true;
//                    }
//                }
//            }
//            img.m_hasAlpha = hasAlpha;
//            
//            `
//            if(fileContent)
//            {
//                img.setDataRawFromWorldResourceLoader(fileContent, x, y, comp, buffer);
//                stbi_image_free(fileContent);
//                
//                return true;
//            }
//            else
//            {
//                if(!setPvrImage(filePath, img))
//                {
//                    DEBUG_LOG_PRINT_V(TAG, "Error (%s) : %s", stbi_failure_reason(), buffer);
//                    img.generate(256, 256, 4, btVector4(1.0, 0.0, 1.0, 1.0));
//                    stbi_image_free(fileContent);
//                    return true;
//                }
//            }
//            return false;
//        }
//        
//        return true;
//    }
    
    bool WorldResourceLoader::load(const char *filePath, ParticleEmitter *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if(filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if (fileContent)
            {
                if(object->parseFileData(fileContent))
                {
                    removeFileData(filePath);
                    retVal = true;
                }
                else
                {
                    DEBUG_LOG_WRITE_W(TAG, "Unable to parse the ParticleEmitter file");
                }
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "Particle file content is empty.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *vertexFile,
                                   const char *fragmentFile,
                                   ShaderProgram *shader)
    {
        DEBUG_ASSERT(shader);
        bool retVal = false;
        
        if(vertexFile &&
           fragmentFile)
        {
            FileData *vertexFileData = loadFileData(vertexFile);
            FileData *fragmentFileData = loadFileData(fragmentFile);
            
            char *vertexFileContent = (char*)vertexFileData->getBufferPtr();
            long vertexFileSize = vertexFileData->getSize();
            vertexFileContent[vertexFileSize] = '\0';
            
            char *fragmentFileContent = (char*)fragmentFileData->getBufferPtr();
            long fragmentFileSize = fragmentFileData->getSize();
            fragmentFileContent[fragmentFileSize] = '\0';
            
            
            if(vertexFileContent != NULL &&
               fragmentFileContent != NULL)
            {
                shader->saveSource((char*)vertexFileData->getBufferPtr(), (char*)fragmentFileData->getBufferPtr());
                
                removeFileData(vertexFile);
                removeFileData(fragmentFile);
                retVal = true;
            }
            else
            {
                if(!vertexFileContent)
                    DEBUG_LOG_WRITE_W(TAG, "Vertex file content is empty.");
                if(!fragmentFileContent)
                    DEBUG_LOG_WRITE_W(TAG, "Fragment file content is empty.");
            }
        }
        else
        {
            if(!vertexFile)
                DEBUG_LOG_WRITE_W(TAG, "Vertex filename is empty.");
            if(!fragmentFile)
                DEBUG_LOG_WRITE_W(TAG, "Fragment filename is empty.");
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Sound *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            
            if(fileContent)
            {
                if(njli::World::getInstance()->getWorldSound()->createSound(fileContent,
                                                                            fileSize,
                                                                            *object))
                {
                    removeFileData(filePath);
                    retVal = true;
                }
                else
                {
                    DEBUG_LOG_WRITE_W(TAG, "Unable to create the Sound file");
                }
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Light *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Light object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Geometry *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Geometry object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Font *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Font object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Lua *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Lua object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Xml *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Xml object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, JsonJLI *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the JsonJLI object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Material *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Material object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Skinner *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Skinner object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::load(const char *filePath, Camera *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                //!!!TODO: load the Camera object...
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    /*
    bool WorldResourceLoader::loadZip(const char *filePath, const char *password)
    {
        static const char *RESOURCE_PATH[] =
        {
            "cameras",
            "curves",
            "fonts",
            "images",
            "lamps",
            "materials",
            "meshes",
            "particles",
            "scripts",
            "shaders",
            "sounds",
            "strings"
        };
        
        unz_global_info gi;
        unz_file_info fi;
        unzFile uf = unzOpen( ASSET_PATH(filePath) );
        unzGetGlobalInfo( uf, &gi );
        unzGoToFirstFile( uf );
        
        int i=0;
        while( i != gi.number_entry )
        {
            char name[ 1024 ] = {""};
            unzGetCurrentFileInfo( uf, &fi, name, 1024, NULL, 0, NULL, 0 );
            
            if( fi.uncompressed_size > 0 )
            {
                if( unzOpenCurrentFilePassword( uf, password ) == UNZ_OK )
                {
                    void *_buffer = malloc( fi.uncompressed_size + 1);
                    DEBUG_ASSERT(_buffer);
//                    buffer[ fi.uncompressed_size ] = 0;
                    uLong _size = fi.uncompressed_size;
                    
                    int error = UNZ_OK;
                    
                    do
                    {
                        error = unzReadCurrentFile( uf, _buffer, fi.uncompressed_size );
                        if ( error < 0 )
                        {
//                            DEBUG_LOG_E(TAG, "error %d\n", error);
//                            return false;
                            continue;
                        }
                        
                    } while ( error > 0 );
                    
                    unzCloseCurrentFile( uf );
                    
                    int j = 0;
                    while(j != 12)
                    {
                        char directory[1024];
                        strcpy(directory, name);
                        char * pch = strtok (directory, "/");
                        if(0 == strcmp(RESOURCE_PATH[j], pch) && (strstr(name, "/.DS_Store") == NULL))
                        {
                            
//                            void *p = NULL;
//                            bool exists = getFileData(name, &p, &_size);
                            
                            if(getFileData(name) != NULL)
                            {
                                addFileData(name);
                                DEBUG_LOG_V(TAG, "Added file: %s - size: %lu\n", name, _size);
                            }
                            else
                            {
                                DEBUG_LOG_V(TAG, "File exists: %s - size: %lu\n", name, _size);
                            }
                        }
                        ++j;
                    }
                    
                    free(_buffer);
                    _buffer = NULL;
                }
                else
                {
                    DEBUG_LOG_E(TAG, "Invalid password %s\n", "");
                    return false;
                }
            }
            
            unzGoToNextFile( uf );
            
            ++i;
        }
        
        unzClose( uf );
        
        return true;
    }
    */
    bool WorldResourceLoader::load(const char *filePath, std::string *object)
    {
        DEBUG_ASSERT(object);
        bool retVal = false;
        
        if (filePath)
        {
            FileData *fileData = loadFileData(filePath);
            
            char *fileContent = (char*)fileData->getBufferPtr();
            long fileSize = fileData->getSize();
            fileContent[fileSize] = '\0';
            
            if(fileContent)
            {
                *object = std::string(fileContent);
                removeFileData(filePath);
                retVal = true;
            }
            else
            {
                if(!fileContent)
                    DEBUG_LOG_WRITE_W(TAG, "filename is empty for the sound.");
            }
        }
        
        return retVal;
    }
    
    bool WorldResourceLoader::unLoad(const char *filePath)
    {
        return removeFileData(filePath);
    }
    
    bool WorldResourceLoader::unLoadAll()
    {
        for (FileDataMap::iterator i = m_FileDataMap.begin(); i != m_FileDataMap.end(); )
        {
            FileData *fileData = i->second;
            
            if (fileData)
                delete fileData;
            fileData = NULL;
            
            i = m_FileDataMap.erase(i);
        }
        m_FileDataMap.clear();
        
        return true;
    }
    
    WorldResourceLoader::ImageFileData *WorldResourceLoader::addImageFileData(const char* filePath)
    {
        ImageFileData *fileData = (ImageFileData*)getFileData(filePath);
        if(NULL == fileData)
        {
            fileData = new ImageFileData(filePath);
            
            DEBUG_ASSERT(fileData);
            
            m_FileDataMap.insert(FileDataPair(filePath, fileData));
        }
        return fileData;
    }
    
    WorldResourceLoader::FileData *WorldResourceLoader::addFileData(const char* filePath)
    {
        FileData *fileData = getFileData(filePath);
        if(NULL == fileData)
        {
            fileData = new FileData(filePath);
            
            DEBUG_ASSERT(fileData);
            
            m_FileDataMap.insert(FileDataPair(filePath, fileData));
        }
        return fileData;
    }
    
    bool WorldResourceLoader::removeFileData(const char *filePath)
    {
        FileDataMap::iterator m = m_FileDataMap.find(filePath);
        if(m != m_FileDataMap.end())
        {
            FileData *fileData = m->second;
            
            DEBUG_ASSERT(fileData);
            
            delete fileData;
            fileData=NULL;
            
            m_FileDataMap.erase(m);
            return true;
        }
        return false;
    }
    
    WorldResourceLoader::FileData *WorldResourceLoader::getFileData(const char* filePath)const
    {
        FileDataMap::const_iterator m = m_FileDataMap.find(filePath);
        if(m != m_FileDataMap.end())
        {
            FileData *cachedFileContent = m->second;
            
            DEBUG_ASSERT(cachedFileContent);
            
            return cachedFileContent;
        }
        return NULL;
    }
    
    WorldResourceLoader::FileData *WorldResourceLoader::loadFileData(const char* filePath)
    {
        FileData *fileData = getFileData(filePath);
        if(NULL == fileData)
        {
            fileData = addFileData(filePath);
            DEBUG_ASSERT(fileData);
        }
        return fileData;
    }
    
    WorldResourceLoader::ImageFileData *WorldResourceLoader::loadImageFileData(const char* filePath)
    {
        ImageFileData *fileData = (ImageFileData*)getFileData(filePath);
        if(NULL == fileData)
        {
            fileData = addImageFileData(filePath);
            DEBUG_ASSERT(fileData);
        }
        return fileData;
    }
}
