//
//  WorldResourceLoader.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldResourceLoader__
#define __JLIGameEngineTest__WorldResourceLoader__

#include "AbstractObject.h"
#include "JLIFactoryTypes.h"
#include "btHashMap.h"
#include <vector>
#include <map>

class File;

namespace njli {


class Light;
class Image;
class Geometry;
class ShaderProgram;
class Font;
class Lua;
class Xml;
class JsonJLI;
class Image;
class Sound;
class Material;
class Skinner;
class Camera;
class ParticleEmitter;

/// <#Description#>
class WorldResourceLoader : public AbstractObject {

    struct FileData {
    public:
        FileData();
//        FileData(const FileData &rhs);
//        FileData(const void* buffer, long size);
        FileData(const char *filePath);
        
        virtual ~FileData();
        
        void* getBufferPtr()const;
        long getSize()const;
        
        void setFilename(const char *filename);
        const char *getFilename()const;
        
    protected:
        FileData &operator=(const FileData &rhs);
        bool load(const char *filePath);
        
        void* m_buffer;
        long m_fileSize;
        std::string m_fileName;
    };
    
    struct ImageFileData : public FileData{
        
        ImageFileData(const char *filePath);
        
//        virtual ~ImageFileData();
        
        s32 getWidth()const;
        s32 getHeight()const;
        s32 numberOfComponents()const;
        njliImageType getType()const;
    private:
        ImageFileData();
        ImageFileData(const ImageFileData &rhs);
        ImageFileData &operator=(const ImageFileData &rhs);
        
        s32 m_width;
        s32 m_height;
        s32 m_components;
        njliImageType m_type;
    };
    
    friend class Image;

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    /**
         *  @author James Folk, 16-02-11 18:02:19
         *
         *  @brief <#Description#>
         */
    WorldResourceLoader();

    /**
         *  @author James Folk, 16-02-11 18:02:24
         *
         *  @brief <#Description#>
         *
         *  @param getClassName <#getClassName description#>
         *
         *  @return <#return value description#>
         */
    virtual ~WorldResourceLoader();

    /**
         *  @author James Folk, 16-02-11 18:02:30
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;

    /**
         *  @author James Folk, 16-02-11 18:02:33
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;

    /**
         *  @author James Folk, 16-02-11 18:02:39
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const;
    //TODO: fill in specific methods for WorldLuaVirtualMachine
public:
    long dataPtrSize(const char* filePath)const;
//    bool copyDataPtr(const char* filePath, u8 **dataPtr, long *size)const;
    
    bool load(const char* filePath, Image *image);
    
    /**
         *  @author James Folk, 16-02-11 18:02:43
         *
         *  @brief <#Description#>
         *
         *  @param filePath <#filePath description#>
         *  @param img      <#img description#>
         *
         *  @return <#return value description#>
         */
//    bool load(const char* filePath, Image& img);

    /**
         *  @author James Folk, 16-02-11 18:02:48
         *
         *  @brief <#Description#>
         *
         *  @param file    <#file description#>
         *  @param emitter <#emitter description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, ParticleEmitter* emitter);

    /**
         *  @author James Folk, 16-02-11 18:02:52
         *
         *  @brief <#Description#>
         *
         *  @param vertexFile   <#vertexFile description#>
         *  @param fragmentFile <#fragmentFile description#>
         *  @param shader       <#shader description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* vertexFile,
        const char* fragmentFile,
        ShaderProgram* shader);

    /**
         *  @author James Folk, 16-02-11 18:02:57
         *
         *  @brief <#Description#>
         *
         *  @param file  <#file description#>
         *  @param sound <#sound description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Sound* sound); //Sound

    /**
         *  @author James Folk, 16-02-11 18:02:01
         *
         *  @brief <#Description#>
         *
         *  @param file  <#file description#>
         *  @param light <#light description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Light* light); //aiLight

    /**
         *  @author James Folk, 16-02-11 18:02:05
         *
         *  @brief <#Description#>
         *
         *  @param file <#file description#>
         *  @param geo  <#geo description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Geometry* geo); //aiMesh

    /**
         *  @author James Folk, 16-02-11 18:02:08
         *
         *  @brief <#Description#>
         *
         *  @param file <#file description#>
         *  @param font <#font description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Font* font); //Font

    /**
         *  @author James Folk, 16-02-11 18:02:12
         *
         *  @brief <#Description#>
         *
         *  @param file <#file description#>
         *  @param lua  <#lua description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Lua* lua); //Lua

    /**
         *  @author James Folk, 16-02-11 18:02:15
         *
         *  @brief <#Description#>
         *
         *  @param file <#file description#>
         *  @param xml  <#xml description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Xml* xml); //Xml

    /**
         *  @author James Folk, 16-02-11 18:02:19
         *
         *  @brief <#Description#>
         *
         *  @param file <#file description#>
         *  @param json <#json description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, JsonJLI* json); //JsonJLI

    /**
         *  @author James Folk, 16-02-11 18:02:23
         *
         *  @brief <#Description#>
         *
         *  @param file     <#file description#>
         *  @param material <#material description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Material* material); //aiMaterial

    /**
         *  @author James Folk, 16-02-11 18:02:27
         *
         *  @brief <#Description#>
         *
         *  @param file    <#file description#>
         *  @param skinner <#skinner description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Skinner* skinner);

    /**
         *  @author James Folk, 16-02-11 18:02:30
         *
         *  @brief <#Description#>
         *
         *  @param file   <#file description#>
         *  @param camera <#camera description#>
         *
         *  @return <#return value description#>
         */
    bool load(const char* file, Camera* camera); //aiCamera

    /**
         *  @author James Folk, 16-02-11 18:02:35
         *
         *  @brief <#Description#>
         *
         *  @param filePath  <#filePath description#>
         *  @param content   <#content description#>
         *  @param file_size <#file_size description#>
         *
         *  @return <#return value description#>
         */
//    bool load(const char* filePath, void** content, unsigned long* file_size);

    /**
         *  @author James Folk, 16-02-11 21:02:52
         *
         *  @brief <#Description#>
         *
         *  @param filePath <#filePath description#>
         *  @param password       <#"" description#>
         *
         *  @return <#return value description#>
         */
//    bool loadZip(const char* filePath, const char* password = "");
    
    bool load(const char *filePath, std::string *content);

    /**
         *  @author James Folk, 16-02-11 18:02:51
         *
         *  @brief <#Description#>
         *
         *  @param file <#file description#>
         *
         *  @return <#return value description#>
         */
    bool unLoad(const char* file);

    /**
         *  @author James Folk, 16-02-11 18:02:54
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    bool unLoadAll();

    /**
         *  @author James Folk, 16-02-11 18:02:57
         *
         *  @brief <#Description#>
         *
         *  @param filePath <#filePath description#>
         *  @param buff     <#buff description#>
         *  @param length   <#length description#>
         *
         *  @return <#return value description#>
         */
//    bool loadDataFromFile(const char* filePath, void** buff, unsigned long* length);
    
    

protected:
    FileData *loadFileData(const char* filePath);
    ImageFileData *loadImageFileData(const char* filePath);
//    bool setPvrImage(const char *filePath, Image &img);
    bool isLoaded(const char* file);
    njliFileType getType(const char* file) const;

    FileData *addFileData(const char* filePath);
    ImageFileData *addImageFileData(const char* filePath);
    FileData *createFileData(const char* filePath, const void* buffer, s32 size);

    bool removeFileData(const char* filePath);
    FileData *getFileData(const char* filePath)const;
//    bool getFileData(const char* filePath, void** buffer = NULL, unsigned long* size = NULL) const;

private:
    WorldResourceLoader(const WorldResourceLoader&);
    WorldResourceLoader& operator=(const WorldResourceLoader&);

    typedef std::map<std::string, FileData*> FileDataMap;
    typedef std::pair<std::string, FileData*> FileDataPair;
    
    FileDataMap m_FileDataMap;
    
};
}

#endif /* defined(__JLIGameEngineTest__WorldResourceLoaderWorldResourceLoader__) */
