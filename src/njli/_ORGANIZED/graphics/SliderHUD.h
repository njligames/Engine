//
//  SliderHUD.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SliderHUD__
#define __JLIGameEngineTest__SliderHUD__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "lua.hpp"

class btVector2;
class btVector4;

namespace njli {
class SliderHUDBuilder;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
SliderHUD : public AbstractFactoryObject,
            public AbstractFrameBufferObject
{
    friend class WorldFactory;

protected:
    SliderHUD();
    SliderHUD(const AbstractBuilder&);
    SliderHUD(const SliderHUD&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SliderHUD();
    SliderHUD& operator=(const SliderHUD&);
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
    static SliderHUD** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(SliderHUD * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static SliderHUD* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static SliderHUD* create(const SliderHUDBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SliderHUD* clone(const SliderHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SliderHUD* copy(const SliderHUD& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(SliderHUD * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(SliderHUD & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for SliderHUD
    void setValue(f32 v);
    f32 getValue() const;

protected:
private:
    btVector2* m_dimensions;
    btVector2* m_position;
    f32 m_knobPos;

    f32 m_slotHeight;
    f32 m_slotRadius;
    f32 m_slotFeather;
    btVector4* m_gradientStartColor;
    btVector4* m_gradientEndColor;

    btVector4* m_knobShadowGradientStartColor;
    btVector4* m_knobShadowGradientEndColor;

    btVector4* m_knobGradientStartColor;
    btVector4* m_knobGradientEndColor;
    btVector4* m_knobColor;
};
}

#endif /* defined(__JLIGameEngineTest__SliderHUD__) */
