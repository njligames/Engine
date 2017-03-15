//
//  TextboxHUD.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__TextboxHUD__
#define __JLIGameEngineTest__TextboxHUD__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

#include "AbstractFrameBufferObject.h"

class btVector2;
class btVector4;

namespace njli {
class TextboxHUDBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
TextboxHUD : public AbstractFactoryObject,
             public AbstractFrameBufferObject
{
    friend class WorldFactory;

protected:
    TextboxHUD();
    TextboxHUD(const AbstractBuilder&);
    TextboxHUD(const TextboxHUD&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~TextboxHUD();
    TextboxHUD& operator=(const TextboxHUD&);
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
    static TextboxHUD** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(TextboxHUD * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static TextboxHUD* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static TextboxHUD* create(const TextboxHUDBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static TextboxHUD* clone(const TextboxHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static TextboxHUD* copy(const TextboxHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(TextboxHUD * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(TextboxHUD & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for TextboxHUD
protected:
private:
    btVector2* m_dimensions;
    btVector2* m_position;
    btVector4* m_gradientStartColor;
    btVector4* m_gradientEndColor;
    f32 m_cornerRadius;
    f32 m_cornerFeather;
    btVector4* m_borderColor;
    f32 m_fontSize;
    std::string m_fontFace;
    btVector4* m_fontColor;
    s32 m_align;
    std::string m_text;
};
}

#endif /* defined(__JLIGameEngineTest__TextboxHUD__) */
