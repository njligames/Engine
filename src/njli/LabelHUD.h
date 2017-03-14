//
//  LabelHUD.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__LabelHUD__
#define __JLIGameEngineTest__LabelHUD__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "lua.hpp"

//#include "nanovg_gl_utils.h"

class btVector2;
class btVector4;

namespace njli {
class LabelHUDBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
LabelHUD : public AbstractFactoryObject,
           public AbstractFrameBufferObject
{
    friend class WorldFactory;

protected:
    LabelHUD();
    LabelHUD(const AbstractBuilder&);
    LabelHUD(const LabelHUD&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~LabelHUD();
    LabelHUD& operator=(const LabelHUD&);
    virtual void renderFunction(Camera * camera);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;
    using AbstractFrameBufferObject::isHidden;
    using AbstractFrameBufferObject::hide;
    using AbstractFrameBufferObject::show;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:30
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
    static LabelHUD** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(LabelHUD * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static LabelHUD* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static LabelHUD* create(const LabelHUDBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static LabelHUD* clone(const LabelHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static LabelHUD* copy(const LabelHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(LabelHUD * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(LabelHUD & object, lua_State * L, int stack_index);
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
         *  @param size <#size description#>
         */
    void setFontSize(f32 size);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getFontSize() const;

    /**
         *  <#Description#>
         *
         *  @param fontFace <#fontFace description#>
         */
    void setFontFace(const char* fontFace);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* getFontFace() const;

    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void setFillColor(const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getFillColor() const;

    /**
         *  <#Description#>
         *
         *  @param align <#align description#>
         */
    void setAlign(s32 align);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    s32 getAlign() const;

    /**
         *  <#Description#>
         *
         *  @param pos <#pos description#>
         */
    void setPosition(const btVector2& pos);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector2& getPosition() const;

    /**
         *  <#Description#>
         *
         *  @param text <#text description#>
         */
    void setText(const char* text);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* getText() const;

protected:
private:
    f32 m_fontSize;
    std::string m_fontFace;
    btVector4* m_fillColor;
    s32 m_align;
    btVector2* m_position;
    btVector2* m_dimensions;
    std::string m_text;

    //        NVGLUframebuffer *m_FBO;
};
}

#endif /* defined(__JLIGameEngineTest__LabelHUD__) */
