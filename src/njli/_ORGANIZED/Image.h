//
//  Image.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Image__
#define __JLIGameEngineTest__Image__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"

#include "btVector2.h"
#include "btVector3.h"
#include "lua.hpp"
#include "JLIFactoryTypes.h"
#include "WorldResourceLoader.h"

//#include "PVRTTexture.h"

namespace njli {
class ImageBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Image : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class WorldResourceLoader;

protected:
    Image();
    Image(const AbstractBuilder&);
    Image(const Image&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Image();

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  <#Description#>
         *
         *  @param  <# description#>
         *
         *  @return <#return value description#>
         */
    Image& operator=(const Image&);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:03
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    operator std::string() const;

    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    static Image** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Image * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Image* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Image* create(const ImageBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Image* clone(const Image& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Image* copy(const Image& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Image * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Image & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    /**
         *  <#Description#>
         *
         *  @param imageSource <#imageSource description#>
         *  @param position    <#position description#>
         *  @param dimensions  <#dimensions description#>
         *
         *  @return <#return value description#>
         */
    static Image* createSubImage(const Image& imageSource, const btVector2& position, const btVector2& dimensions);

    //TODO: fill in specific methods for Image
    /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         *  @param color    <#color description#>
         *
         *  @return <#return value description#>
         */
    bool setPixel(const btVector2& position, const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @param position    <#position description#>
         *  @param imageSource <#imageSource description#>
         *
         *  @return <#return value description#>
         */
    bool setPixel(const btVector2& position, const Image& imageSource);
    /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         *  @param pixel    <#pixel description#>
         *
         *  @return <#return value description#>
         */
    bool getPixel(const btVector2& position, btVector4& pixel) const;
    btVector4 getPixel(const btVector2 &position)const;
    
    

    /**
         *  <#Description#>
         *
         *  @param position   <#position description#>
         *  @param dimensions <#dimensions description#>
         *  @param color      <#color description#>
         *
         *  @return <#return value description#>
         */
    bool setPixels(const btVector2& position,
        const btVector2& dimensions,
        const btVector4& color);

    /**
         *  <#Description#>
         *
         *  @param position    <#position description#>
         *  @param dimensions  <#dimensions description#>
         *  @param sourceImage <#sourceImage description#>
         *  @param 0           <#0 description#>
         *  @param 0           <#0 description#>
         *
         *  @return <#return value description#>
         */
    bool setPixels(const btVector2& position,
        const btVector2& dimensions,
        const Image& sourceImage,
        const btVector2& sourceImageOffset = btVector2(0, 0));

    /**
         *  <#Description#>
         *
         *  @param position         <#position description#>
         *  @param dimension        <#dimension description#>
         *  @param destinationImage <#destinationImage description#>
         *  @param 0                <#0 description#>
         *  @param 0                <#0 description#>
         *
         *  @return <#return value description#>
         */
    bool getPixels(const btVector2& position,
        const btVector2& dimension,
        Image& destinationImage,
        const btVector2& destinationImageOffset = btVector2(0, 0)) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u8 getNumberOfComponents() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u32 getWidth() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u32 getHeight() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* getFilename() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u8 getBytesPerPixel() const;
    
    
    u8 *getDataPtr()const;
    long getDataSize()const;
    
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
//    const u8* getDataRaw() const;
    
    bool isPvr()const;
    bool isCompressed()const;
    
    njliImageType getImageType()const;
    
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
//    u8* getDataRaw();
    /**
         *  <#Description#>
         *
         *  @param width              <#width description#>
         *  @param height             <#height description#>
         *  @param numberOfComponents <#numberOfComponents description#>
         *  @param const              <#const description#>
         *  @param 1.0f               <#1.0f description#>
         *  @param 1.0f               <#1.0f description#>
         *  @param 1.0f               <#1.0f description#>
         *  @param 0.0f               <#0.0f description#>
         */
//    void setDataRaw(u32 width, u32 height, u8 numberOfComponents, const u8* const, const btVector4& fillColor = btVector4(1.0f, 1.0f, 1.0f, 0.0f));
//    void copy(const char *fileName);
    
    /**
         *  <#Description#>
         *
         *  @param width              <#width description#>
         *  @param height             <#height description#>
         *  @param numberOfComponents <#numberOfComponents description#>
         *  @param 1.0f               <#1.0f description#>
         *  @param 1.0f               <#1.0f description#>
         *  @param 1.0f               <#1.0f description#>
         *  @param 1.0f               <#1.0f description#>
         */
    void generate(u32 width, u32 height, u8 numberOfComponents, const btVector4& fillColor = btVector4(1.0f, 1.0f, 1.0f, 1.0f));
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
//    u64 getDataRawLength() const;

    /**
         *  <#Description#>
         *
         *  @param from  <#from description#>
         *  @param to    <#to description#>
         *  @param color <#color description#>
         */
    void drawLine(const btVector2& from, const btVector2& to, const btVector4& color);

    /**
         *  <#Description#>
         *
         *  @param from        <#from description#>
         *  @param to          <#to description#>
         *  @param imageSource <#imageSource description#>
         */
    void drawLine(const btVector2& from, const btVector2& to, const Image& imageSource);

    /**
         *  <#Description#>
         */
    void blur();
    /**
         *  <#Description#>
         *
         *  @param image <#image description#>
         *
         *  @return <#return value description#>
         */
    bool setAlpha(const Image& image);
    /**
         *  <#Description#>
         *
         *  @param alpha <#alpha description#>
         *
         *  @return <#return value description#>
         */
    bool setAlpha(f32 alpha);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool hasAlpha() const;
    /**
         *  <#Description#>
         */
    void preMultiplyAlpha();
    /**
         *  <#Description#>
         */
    void flip();
    
    void rotate();
    
//    void setPVRData(u8 *pvrData, unsigned long dataSize, const char *fileName);
//    u8 *getCompressedData()const;

    //get the pixel row
    std::vector<btVector4> operator[] (u32 row);
protected:
    bool copyData(void *dataPtr, long dataSize, s32 width, s32 height, s32 components, njliImageType imageType, const std::string &filename);
    
    bool copyData(const WorldResourceLoader::ImageFileData *fileData);
    u32 getClosestValidGLDim(const u32 dim) const;
//    void setDataRawFromWorldResourceLoader(u8*, u32 x, u32 y, u8 numberOfComponents, const char* filename);
//    bool isInWorldResourceLoader() const;

    void setPixelRow(u8 * data, u32 row, u32 width, u32 xOffset = 0);
    void getPixelRow(u8 * data, u32 row, u32 width);
    

    u8* createFillRow_createsmemory(s32 xOffset, s32 fillWidth, const btVector4& fillColor = btVector4(1.0f, 1.0f, 1.0f, 1.0f));

private:
    // An output image with N components has the following components interleaved
    // in this order in each pixel:
    //
    //     N=#comp     components
    //       1           grey
    //       2           grey, alpha
    //       3           red, green, blue
    //       4           red, green, blue, alpha

    u8* m_RawData;

    long m_RawDataSize;
    njliImageType m_njliImageType;
    
    u32 m_Width;
    u32 m_Height;
    u8 m_Componenents;
    
    std::string m_Filename;
//    bool m_hasAlpha;
    
//    bool m_IsInWorldResourceLoader;
//    unsigned long m_pvrDataSize;
};
}

#endif /* defined(__JLIGameEngineTest__Image__) */
