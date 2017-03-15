//
//  SpriteFrameAtlas.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/25/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SpriteFrameAtlas__
#define __JLIGameEngineTest__SpriteFrameAtlas__

#pragma mark Header

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "btAlignedObjectArray.h"
#include "lua.hpp"
#include "lua.hpp"

class btVector2;

namespace njli {
/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Rect
{
public:
    /**
     *  <#Description#>
     */
    Rect();
    /**
     *  <#Description#>
     */
    Rect(const Rect& copy);
    /**
     *  <#Description#>
     *
     *  @param rhs <#rhs description#>
     *
     *  @return <#return value description#>
     */
    Rect& operator=(const Rect& rhs);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual ~Rect();

    /**
     *  <#Description#>
     *
     *  @param x <#x description#>
     */
    void setX(const f32 x);
    /**
     *  <#Description#>
     *
     *  @param y <#y description#>
     */
    void setY(const f32 y);
    /**
     *  <#Description#>
     *
     *  @param width <#width description#>
     */
    void setWidth(const f32 width);
    /**
     *  <#Description#>
     *
     *  @param height <#height description#>
     */
    void setHeight(const f32 height);
    /**
     *  <#Description#>
     *
     *  @param width <#width description#>
     */
    void setWidthFile(const f32 width);
    /**
     *  <#Description#>
     *
     *  @param height <#height description#>
     */
    void setHeightFile(const f32 height);
    /**
     *  <#Description#>
     *
     *  @param x <#x description#>
     */
    void setPivotX(const f32 x);
    /**
     *  <#Description#>
     *
     *  @param y <#y description#>
     */
    void setPivotY(const f32 y);

    /**
     *  <#Description#>
     *
     *  @param offset <#offset description#>
     */
    void setOffset(const btVector2& offset);
    /**
     *  <#Description#>
     *
     *  @param dimension <#dimension description#>
     */
    void setDimension(const btVector2& dimension);

    /**
     *  <#Description#>
     *
     *  @param dimension <#dimension description#>
     */
    void setDimensionFile(const btVector2& dimension);
    /**
     *  <#Description#>
     *
     *  @param pivotPoint <#pivotPoint description#>
     */
    void setPivotPoint(const btVector2& pivotPoint);
    /**
     *  <#Description#>
     *
     *  @param trimmedname <#trimmedname description#>
     */
    void setTrimmedName(const char* trimmedname);

    bool finishedPopulating() const;
    void resetPopulation();

    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    const btVector2& getOffset() const;
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    const btVector2& getDimension() const;
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    const btVector2& getDimensionFile() const;
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    const btVector2& getPivotPoint() const;
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    const std::string& getTrimmedName() const;

    operator std::string() const;

    void setSouceX(const f32 x);
    void setSourceY(const f32 y);
    void setSourceWidth(const f32 width);
    void setSourceHeight(const f32 height);

    const btVector2& getSource() const;
    const btVector2& getSourceDimension() const;

private:
    btVector2* offset;
    btVector2* dimension;
    btVector2* dimensionFile;
    btVector2* pivotPoint;
    std::string trimmedname;
    btVector2* sourcePosition;
    btVector2* sourceDimension;

    s32 populationCount;
};

class SpriteFrameAtlasBuilder;

/**
 *  <#Description#>
 */
ATTRIBUTE_ALIGNED16(class)
SpriteFrameAtlas : public AbstractFactoryObject
{
    friend class WorldFactory;

protected:
    SpriteFrameAtlas();
    SpriteFrameAtlas(const AbstractBuilder&);
    SpriteFrameAtlas(const SpriteFrameAtlas&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SpriteFrameAtlas();
    SpriteFrameAtlas& operator=(const SpriteFrameAtlas&);

    static s32 countParameters;
    static njli::Rect rect;

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
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;
    /**
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void*, btSerializer*) const;

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
    static SpriteFrameAtlas** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(SpriteFrameAtlas * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static SpriteFrameAtlas* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static SpriteFrameAtlas* create(const SpriteFrameAtlasBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SpriteFrameAtlas* clone(const SpriteFrameAtlas& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SpriteFrameAtlas* copy(const SpriteFrameAtlas& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(SpriteFrameAtlas * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(SpriteFrameAtlas & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for SpriteFrameAtlas
    /**
         *  <#Description#>
         *
         *  @param filename <#filename description#>
         */
    void setSourceFilename(const char* filename);
    /**
         *  <#Description#>
         *
         *  @param width <#width description#>
         */
    void setSheetContentWidth(const u32 width);
    /**
         *  <#Description#>
         *
         *  @param height <#height description#>
         */
    void setSheetContentHeight(const u32 height);
    /**
         *  <#Description#>
         *
         *  @param rect <#rect description#>
         */
    void addFrame(Rect rect);

    /**
         *  <#Description#>
         *
         *  @param name <#name description#>
         *
         *  @return <#return value description#>
         */
    const Rect& getFrame(const char* name) const;
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    const Rect& getFrame(int index) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const std::string& getSourceFilename() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u32 numberOfFrames() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector2& contentDimension() const;

protected:
private:
    std::string m_SourceFilename;
    btVector2* m_ContentDimension;
    btAlignedObjectArray<Rect> m_Frames;
    //        btHashMap<btHashString, Rect> m_FrameNames;
};
}

#endif /* defined(__JLIGameEngineTest__SpriteFrameAtlas__) */
