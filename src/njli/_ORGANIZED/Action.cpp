//
//  Action.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Action.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "ActionBuilder.h"

#include "Log.h"
#define TAG "Action.cpp"
#define FORMATSTRING "{\"njli::Action\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btQuickprof.h"

namespace njli
{
    // Robert Penner's easing functions in GLSL
    // https://github.com/stackgl/glsl-easings
    float Action::linear(float t) {
        assert(t >= 0 && t <= 1.0);
        return t;
    }
    
    float Action::exponentialIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return t == 0.0 ? t : pow(2.0, 10.0 * (t - 1.0));
    }
    
    float Action::exponentialOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t == 1.0 ? t : 1.0 - pow(2.0, -10.0 * t);
    }
    
    float Action::exponentialInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t == 0.0 || t == 1.0
        ? t
        : t < 0.5
        ? +0.5 * pow(2.0, (20.0 * t) - 10.0)
        : -0.5 * pow(2.0, 10.0 - (t * 20.0)) + 1.0;
    }
    
    float Action::sineIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return sin((t - 1.0) * SIMD_HALF_PI) + 1.0;
    }
    
    float Action::sineOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return sin(t * SIMD_HALF_PI);
    }
    
    float Action::sineInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return -0.5 * (cos(PI * t) - 1.0);
    }
    
    float Action::qinticIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return pow(t, 5.0);
    }
    
    float Action::qinticOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return 1.0 - (pow(t - 1.0, 5.0));
    }
    
    float Action::qinticInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t < 0.5
        ? +16.0 * pow(t, 5.0)
        : -0.5 * pow(2.0 * t - 2.0, 5.0) + 1.0;
    }
    
    float Action::quarticIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return pow(t, 4.0);
    }
    
    float Action::quarticOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return pow(t - 1.0, 3.0) * (1.0 - t) + 1.0;
    }
    
    float Action::quarticInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t < 0.5
        ? +8.0 * pow(t, 4.0)
        : -8.0 * pow(t - 1.0, 4.0) + 1.0;
    }
    
    float Action::quadraticInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        float p = 2.0 * t * t;
        return t < 0.5 ? p : -p + (4.0 * t) - 1.0;
    }
    
    float Action::quadraticIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return t * t;
    }
    
    float Action::quadraticOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return -t * (t - 2.0);
    }
    
    float Action::cubicIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return t * t * t;
    }
    
    float Action::cubicOut(float t) {
        assert(t >= 0 && t <= 1.0);
        float f = t - 1.0;
        return f * f * f + 1.0;
    }
    
    float Action::cubicInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t < 0.5
        ? 4.0 * t * t * t
        : 0.5 * pow(2.0 * t - 2.0, 3.0) + 1.0;
    }
    
    float Action::elasticIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return sin(13.0 * t * SIMD_HALF_PI) * pow(2.0, 10.0 * (t - 1.0));
    }
    
    float Action::elasticOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return sin(-13.0 * (t + 1.0) * SIMD_HALF_PI) * pow(2.0, -10.0 * t) + 1.0;
    }
    
    float Action::elasticInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t < 0.5
        ? 0.5 * sin(+13.0 * SIMD_HALF_PI * 2.0 * t) * pow(2.0, 10.0 * (2.0 * t - 1.0))
        : 0.5 * sin(-13.0 * SIMD_HALF_PI * ((2.0 * t - 1.0) + 1.0)) * pow(2.0, -10.0 * (2.0 * t - 1.0)) + 1.0;
    }
    
    float Action::circularIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return 1.0 - sqrt(1.0 - t * t);
    }
    
    float Action::circularOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return sqrt((2.0 - t) * t);
    }
    
    float Action::circularInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t < 0.5
        ? 0.5 * (1.0 - sqrt(1.0 - 4.0 * t * t))
        : 0.5 * (sqrt((3.0 - 2.0 * t) * (2.0 * t - 1.0)) + 1.0);
    }
    
    float Action::bounceOut(float t) {
        assert(t >= 0 && t <= 1.0);
        const float a = 4.0 / 11.0;
        const float b = 8.0 / 11.0;
        const float c = 9.0 / 10.0;
        
        const float ca = 4356.0 / 361.0;
        const float cb = 35442.0 / 1805.0;
        const float cc = 16061.0 / 1805.0;
        
        float t2 = t * t;
        
        return t < a
        ? 7.5625 * t2
        : t < b
        ? 9.075 * t2 - 9.9 * t + 3.4
        : t < c
        ? ca * t2 - cb * t + cc
        : 10.8 * t * t - 20.52 * t + 10.72;
    }
    
    float Action::bounceIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return 1.0 - bounceOut(1.0 - t);
    }
    
    float Action::bounceInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        return t < 0.5
        ? 0.5 * (1.0 - bounceOut(1.0 - t * 2.0))
        : 0.5 * bounceOut(t * 2.0 - 1.0) + 0.5;
    }
    
    float Action::backIn(float t) {
        assert(t >= 0 && t <= 1.0);
        return pow(t, 3.0) - t * sin(t * PI);
    }
    
    float Action::backOut(float t) {
        assert(t >= 0 && t <= 1.0);
        float f = 1.0 - t;
        return 1.0 - (pow(f, 3.0) - f * sin(f * PI));
    }
    
    float Action::backInOut(float t) {
        assert(t >= 0 && t <= 1.0);
        float f = t < 0.5
        ? 2.0 * t
        : 1.0 - (2.0 * t - 1.0);
        
        float g = pow(f, 3.0) - f * sin(f * PI);
        
        return t < 0.5
        ? 0.5 * g
        : 0.5 * (1.0 - g) + 0.5;
    }
    
    Action::Action():
    AbstractFactoryObject(this),
    m_SpeedFactor(1.0f),
    m_Duration(0.0f),
    m_TimingMode(JLI_ACTION_TIMING_MODE_EASEIN),
//    m_Name("MyAction"),
    m_timeLeft(0),
    m_RepeatCount(0)
    {
        
    }
    
    Action::Action(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_SpeedFactor(1.0f),
    m_Duration(0.0f),
    m_TimingMode(JLI_ACTION_TIMING_MODE_EASEIN),
//    m_Name("MyAction"),
    m_timeLeft(0),
    m_RepeatCount(0)
    {
        
    }
    
    Action::Action(const Action &copy):
    AbstractFactoryObject(this),
    m_SpeedFactor(1.0f),
    m_Duration(0.0f),
    m_TimingMode(JLI_ACTION_TIMING_MODE_EASEIN),
//    m_Name("MyAction"),
    m_timeLeft(0),
    m_RepeatCount(0)
    {
        
    }
    
    Action::~Action()
    {
        while (!m_ActionGroups.empty())
        {
            Sequence *sequence = m_ActionGroups.back();
            m_ActionGroups.pop_back();
            
            delete sequence->sequenceQueue;sequence->sequenceQueue=NULL;
            delete sequence;sequence=NULL;
        }
    }
    
    Action &Action::operator=(const Action &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	Action::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Action::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Action::getClassName()const
    {
        return "Action";
    }
    
    s32 Action::getType()const
    {
        return Action::type();
    }
    
    Action::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Action **Action::createArray(const u32 size)
    {
        return (Action**)World::getInstance()->getWorldFactory()->createArray(Action::type(), size);
    }
    
    void Action::destroyArray(Action **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Action *Action::create()
    {
        return dynamic_cast<Action*>(World::getInstance()->getWorldFactory()->create(Action::type()));
    }
    
    Action *Action::create(const ActionBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Action*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Action *Action::clone(const Action &object)
    {
        return dynamic_cast<Action*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Action *Action::copy(const Action &object)
    {
        return dynamic_cast<Action*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Action::destroy(Action *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Action::load(Action &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
        {
            // stack now contains: -1 => value; -2 => key; -3 => table
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                Action::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
//                    swig_lua_userdata *usr;
//                    swig_type_info *type;
//                    assert(lua_isuserdata(L,index));
//                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
//                    type = usr->type;
//                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
//                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 Action::type()
    {
        return JLI_OBJECT_TYPE_Action;
    }
    
    Action *Action::createGroup(Action **actions, u32 count)
    {
        Action *action = create();
        
        for (u32 i = 0; i < count; ++i)
        {
            Sequence *sequence = new Sequence();
            sequence->sequenceQueue = new std::queue<Action*>();
            sequence->sequenceQueue->push(actions[i]);
            sequence->numberOfActions = 1;
            
            action->m_ActionGroups.push_back(sequence);
        }
        
        return action;
    }
    Action *Action::createSequence(Action **actions, u32 count)
    {
        Action *action = create();
        
        Sequence *sequence = new Sequence();
        sequence->sequenceQueue = new std::queue<Action*>();
        sequence->numberOfActions = 0;
        
        for (u32 i = 0; i < count; ++i)
        {
            Action *currentAction = actions[i];
            sequence->sequenceQueue->push(currentAction);
            ++sequence->numberOfActions;
        }
        
        action->m_ActionGroups.push_back(sequence);
        
        return action;
    }
    
    void Action::setRepeat(u32 count)
    {
        m_RepeatCount = count;
    }
    
    void Action::setRepeatForever()
    {
        m_RepeatCount = std::numeric_limits<s32>::min();
    }
    
    void Action::setSpeedFactor(f32 factor)
    {
        m_SpeedFactor = factor;
    }
    
    f32 Action::getSpeedFactor()const
    {
        return m_SpeedFactor;
    }
    void Action::setDuration(f32 duration)
    {
        m_Duration = duration;
        m_timeLeft = duration;
    }
    f32 Action::getDuration()const
    {
        return m_Duration;
    }
    void Action::setTimingMode(njliActionTimingMode mode)
    {
        m_TimingMode = mode;
    }
    njliActionTimingMode Action::getTimingMode()const
    {
        return m_TimingMode;
    }
    
    
    f32 Action::getTimeLeft()const
    {
        return m_timeLeft;
    }
    
    bool Action::isRepeatingForever()const
    {
        return m_RepeatCount == std::numeric_limits<s32>::min();
    }
    
    s32 Action::getRepeatCount()const
    {
        if(m_RepeatCount == std::numeric_limits<s32>::min())
            return 0;
        return m_RepeatCount;
    }
    
    Node *Action::getParent()
    {
        return dynamic_cast<Node*>(AbstractDecorator::getParent());
    }
    
    const Node *Action::getParent()const
    {
        return dynamic_cast<const Node*>(AbstractDecorator::getParent());
    }
    
    void Action::update(f32 timeStep)
    {
        BT_PROFILE("Action::update");
        char buffer[BUFFER_SIZE] = "__NJLINodeActionUpdate";
//        sprintf(buffer, "%sUpdate", this->getName());
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, this, timeStep);
        
        handleActionChildren(timeStep);
        
        f32 step = (timeStep * getSpeedFactor());
        m_timeLeft -= step;
        
        if(m_timeLeft <= 0)
        {
            if(!isFinishedRepeating())
                decrementRepeatCounter();
        }
    }
    
    bool Action::isFinished()const
    {
        return (m_timeLeft <= 0);
    }
    
    bool Action::isFinishedRepeating()const
    {
        if(m_RepeatCount == std::numeric_limits<s32>::min())
        {
            return false;
        }
        
        return (m_RepeatCount <= 0);
    }
    
    bool Action::isChildrenFinished()const
    {
        for (u32 i = 0; i < m_ActionGroups.size(); ++i)
        {
            Sequence *sequence = m_ActionGroups.at(i);
            if(sequence->numberOfActions > 0)
                return false;
        }
        return true;
    }
    
    void Action::handleActionChildren(f32 timeStep)
    {
        for (u32 i = 0; i < m_ActionGroups.size(); ++i)
        {
            Sequence *currentSequence = m_ActionGroups.at(i);
            
            if(currentSequence->numberOfActions > 0)
            {
                std::queue<Action*> *currentQueue = m_ActionGroups.at(i)->sequenceQueue;
                
                if(currentQueue->size() > 0)
                {
                    Action *currentAction = currentQueue->front();
                    
                    currentAction->update(timeStep);
                    
                    if (currentAction->isFinished() && currentAction->isFinishedRepeating() && currentAction->isChildrenFinished())
                    {
                        currentQueue->pop();
                        
                        currentAction->m_timeLeft = currentAction->getDuration();
                        
                        currentQueue->push(currentAction);
                        
                        --m_ActionGroups.at(i)->numberOfActions;
                    }
                }
                
            }
        }
    }
    
    void Action::decrementRepeatCounter()
    {
        if(m_RepeatCount != std::numeric_limits<s32>::min())
        {
            --m_RepeatCount;
        }
        
        m_timeLeft = m_Duration;
        for (u32 i = 0; i < m_ActionGroups.size(); ++i)
        {
            m_ActionGroups.at(i)->numberOfActions = m_ActionGroups.at(i)->sequenceQueue->size();
            
        }
    }
}
