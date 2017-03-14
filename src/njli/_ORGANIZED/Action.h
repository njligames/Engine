//
//  Action.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Action__
#define __JLIGameEngineTest__Action__

#include "AbstractActionable.h"
#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "JLIFactoryTypes.h"
#include "btAlignedObjectArray.h"
#include "lua.hpp"

#include <queue>
#include <vector>

namespace njli {
class ActionBuilder;
class Node;

ATTRIBUTE_ALIGNED16(class)
Action : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class AbstractActionable;

public:
    // Robert Penner's easing functions in GLSL
    // https://github.com/stackgl/glsl-easings
    // http://easings.net
    static float linear(float t);
    static float exponentialIn(float t);
    static float exponentialOut(float t);
    static float exponentialInOut(float t);
    static float sineIn(float t);
    static float sineOut(float t);
    static float sineInOut(float t);
    static float qinticIn(float t);
    static float qinticOut(float t);
    static float qinticInOut(float t);
    static float quarticIn(float t);
    static float quarticOut(float t);
    static float quarticInOut(float t);
    static float quadraticInOut(float t);
    static float quadraticIn(float t);
    static float quadraticOut(float t);
    static float cubicIn(float t);
    static float cubicOut(float t);
    static float cubicInOut(float t);
    static float elasticIn(float t);
    static float elasticOut(float t);
    static float elasticInOut(float t);
    static float circularIn(float t);
    static float circularOut(float t);
    static float circularInOut(float t);
    static float bounceOut(float t);
    static float bounceIn(float t);
    static float bounceInOut(float t);
    static float backIn(float t);
    static float backOut(float t);
    static float backInOut(float t);
protected:
    Action();
    Action(const AbstractBuilder&);
    Action(const Action&);

    virtual ~Action();
    Action& operator=(const Action&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    BT_DECLARE_ALIGNED_ALLOCATOR();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:42
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
    static Action** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Action * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Action* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Action* create(const ActionBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Action* clone(const Action& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Action* copy(const Action& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Action * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Action & object, lua_State * L, int stack_index);
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
         *  @param actions <#actions description#>
         *  @param size    <#size description#>
         *
         *  @return <#return value description#>
         */
    static Action* createGroup(Action * *actions, u32 size);
    /**
         *  <#Description#>
         *
         *  @param actions <#actions description#>
         *  @param size    <#size description#>
         *
         *  @return <#return value description#>
         */
    static Action* createSequence(Action * *actions, u32 size);

    /**
         *  <#Description#>
         *
         *  @param count <#count description#>
         */
    void setRepeat(u32 count);
    /**
         *  <#Description#>
         */
    void setRepeatForever();

    /**
         *  <#Description#>
         *
         *  @param factor <#factor description#>
         */
    void setSpeedFactor(f32 factor);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getSpeedFactor() const;

    /**
         *  <#Description#>
         *
         *  @param duration <#duration description#>
         */
    void setDuration(f32 duration);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getDuration() const;

    /**
         *  <#Description#>
         *
         *  @param mode <#mode description#>
         */
    void setTimingMode(njliActionTimingMode mode);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliActionTimingMode getTimingMode() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getTimeLeft() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isRepeatingForever() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    s32 getRepeatCount() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node* getParent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Node* getParent() const;

protected:
    virtual void update(f32 timeStep);
    virtual bool isFinished() const;
    virtual bool isFinishedRepeating() const;
    virtual bool isChildrenFinished() const;

    void handleActionChildren(f32 timeStep);
    void decrementRepeatCounter();

private:
    struct Sequence {
        std::queue<Action*>* sequenceQueue;
        s32 numberOfActions;
    };

    std::vector<Sequence*> m_ActionGroups;

    f32 m_SpeedFactor;
    f32 m_Duration;
    njliActionTimingMode m_TimingMode;
    f64 m_timeLeft;
    s32 m_RepeatCount;
};
}

#endif /* defined(__JLIGameEngineTest__Action__) */
