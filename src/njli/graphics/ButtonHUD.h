//
//  ButtonHUD.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__ButtonHUD__
#define __JLIGameEngineTest__ButtonHUD__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "lua.hpp"

class btVector2;
class btVector4;

namespace njli {
class ButtonHUDBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
ButtonHUD : public AbstractFactoryObject,
            public AbstractFrameBufferObject
{
    friend class WorldFactory;

protected:
    ButtonHUD();
    ButtonHUD(const AbstractBuilder&);
    ButtonHUD(const ButtonHUD&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~ButtonHUD();
    ButtonHUD& operator=(const ButtonHUD&);
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
         *  @author James Folk, 16-02-11 15:02:57
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
    static ButtonHUD** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(ButtonHUD * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static ButtonHUD* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static ButtonHUD* create(const ButtonHUDBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static ButtonHUD* clone(const ButtonHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static ButtonHUD* copy(const ButtonHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(ButtonHUD * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(ButtonHUD & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for ButtonHUD
    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         */
    void setFontSize(f32 size);
    /**
         *  <#Description#>
         *
         *  @param face <#face description#>
         */
    void setFontFace(const char* face);
    /**
         *  <#Description#>
         *
         *  @param pos <#pos description#>
         */
    void setPosition(const btVector2& pos);
    /**
         *  <#Description#>
         *
         *  @param dim <#dim description#>
         */
    void setDimensions(const btVector2& dim);
    /**
         *  <#Description#>
         *
         *  @param text <#text description#>
         */
    void setText(const char* text);
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void setFillColor(const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void setBorderColor(const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void setTextColor(const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void setTextShadowColor(const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @param start <#start description#>
         */
    void setGradientStartColor(const btVector4& start);
    /**
         *  <#Description#>
         *
         *  @param end <#end description#>
         */
    void setGradientEndColor(const btVector4& end);
    /**
         *  <#Description#>
         *
         *  @param radius <#radius description#>
         */
    void setCornerRadius(f32 radius);

    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    f32 getFontSize(f32 size);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* getFontFace() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector2& getPosition() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector2& getDimensions() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* getText() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getFillColor() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getBorderColor() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getTextColor() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getTextShadowColor() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getGradientStartColor() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4& getGradientEndColor() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getCornerRadius() const;

protected:
private:
    f32 m_fontSize;
    std::string m_fontFace;
    s32 m_align;
    btVector2* m_position;
    btVector2* m_dimensions;
    std::string m_text;
    btVector4* m_fillColor;
    btVector4* m_borderColor;
    btVector4* m_textColor;
    btVector4* m_textShadowColor;
    btVector4* m_gradientStartColor;
    btVector4* m_gradientEndColor;
    f32 m_cornerRadius;
};
}

#endif /* defined(__JLIGameEngineTest__ButtonHUD__) */
