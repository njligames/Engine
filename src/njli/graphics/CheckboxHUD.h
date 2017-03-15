//
//  CheckboxHUD.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__CheckboxHUD__
#define __JLIGameEngineTest__CheckboxHUD__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "lua.hpp"

#include "JLIFactoryTypes.h"

class btVector2;
class btVector4;

namespace njli {
class CheckboxHUDBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
CheckboxHUD : public AbstractFactoryObject,
              public AbstractFrameBufferObject
{
    friend class WorldFactory;

protected:
    CheckboxHUD();
    CheckboxHUD(const AbstractBuilder&);
    CheckboxHUD(const CheckboxHUD&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~CheckboxHUD();
    CheckboxHUD& operator=(const CheckboxHUD&);
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
    static CheckboxHUD** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(CheckboxHUD * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static CheckboxHUD* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static CheckboxHUD* create(const CheckboxHUDBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static CheckboxHUD* clone(const CheckboxHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static CheckboxHUD* copy(const CheckboxHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(CheckboxHUD * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(CheckboxHUD & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for CheckboxHUD
    void setDimensions(const btVector2& dim);
    void setPosition(const btVector2& pos);
    void setFontSize(f32 fontSize);
    void setFontFace(const char* fontFace);
    void setFontColor(const btVector4& color);
    void setText(const char* text);
    void setFontAlign(njliHUDAlign align);
    void setCheckboxRadius(f32 radius);
    void setCheckboxFeather(f32 feather);
    void setCheckboxGradientStartColor(const btVector4& start);
    void setCheckboxGradientEndColor(const btVector4& end);
    void setCheckboxDimensions(const btVector2& dim);
    void setFontSizeIcon(f32 size);
    void setFontFaceIcon(const char* fontFace);
    void setFontColorIcon(const btVector4& color);
    void setTextIcon(const char* text);

    const btVector2& getDimensions() const;
    const btVector2& getPosition(const btVector2& pos) const;
    f32 getFontSize() const;
    const char* getFontFace() const;
    const btVector4& getFontColor() const;
    const char* getText() const;
    njliHUDAlign getFontAlign() const;
    f32 getCheckboxRadius() const;
    f32 getCheckboxFeather() const;
    const btVector4& getCheckboxGradientStartColor() const;
    const btVector4& getCheckboxGradientEndColor() const;
    const btVector2& getCheckboxDimensions() const;
    f32 getFontSizeIcon() const;
    const char* getFontFaceIcon() const;
    const btVector4& getFontColorIcon() const;
    const char* getTextIcon() const;

    void check();
    void unCheck();
    bool isChecked() const;

protected:
private:
    btVector2* m_dimensions;
    btVector2* m_position;
    f32 m_fontSize;
    std::string m_fontFace;
    btVector4* m_fillColor;
    s32 m_align;
    f32 m_cornerRadius;
    f32 m_feather;
    btVector4* m_gradientStartColor;
    btVector4* m_gradientEndColor;
    f32 m_iconFontSize;
    std::string m_iconFontFace;
    btVector4* m_iconFillColor;
    std::string m_iconText;
    std::string m_text;
    btVector2* m_checkboxDimension;
    bool m_isChecked;
};
}

#endif /* defined(__JLIGameEngineTest__CheckboxHUD__) */
