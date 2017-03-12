//
//  SceneState.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SceneState__
#define __JLIGameEngineTest__SceneState__

#include "AbstractBuilder.h"
#include "AbstractState.h"
#include "Scene.h"
#include "lua.hpp"
#include "DeviceTouch.h"

namespace njli {
class SceneStateBuilder;
    class DeviceTouch;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
SceneState : public AbstractState<Scene>
{
    friend class WorldFactory;

protected:
    SceneState();
    SceneState(const AbstractBuilder&);
    SceneState(const SceneState&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SceneState();
    SceneState& operator=(const SceneState&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;
    using AbstractState::isFinished;
    using AbstractState::enableFinished;
    using AbstractState::enableCanDelete;

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

public:
    /**
         *  @author James Folk, 16-02-11 17:02:48
         *
         *  @brief <#Description#>
         *
         *  @param scene <#scene description#>
         */
    virtual void enter(Scene * scene);

    /**
         *  @author James Folk, 16-02-11 17:02:57
         *
         *  @brief <#Description#>
         *
         *  @param scene    <#scene description#>
         *  @param timestep <#timestep description#>
         */
    virtual void update(Scene * scene, f32 timestep);

    /**
         *  @author James Folk, 16-02-11 17:02:04
         *
         *  @brief <#Description#>
         *
         *  @param scene <#scene description#>
         */
    virtual void exit(Scene * scene);

    /**
         *  @author James Folk, 16-02-11 17:02:22
         *
         *  @brief <#Description#>
         *
         *  @param scene    <#scene description#>
         *  @param telegram <#telegram description#>
         *
         *  @return <#return value description#>
         */
    virtual bool onMessage(Scene * scene, const Telegram& telegram) const;

    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchDown(Scene *object, DeviceTouch * *m_CurrentTouches);
    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchUp(Scene *object, DeviceTouch * *m_CurrentTouches);
    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchMove(Scene *object, DeviceTouch * *m_CurrentTouches);
    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchCancelled(Scene *object, DeviceTouch * *m_CurrentTouches);
    
    void keyboardShow(Scene *object);
    void keyboardCancel(Scene *object);
    void keyboardReturn(Scene *object, const char* text);
    
    void renderHUD(Scene *object);
    void pauseGame(Scene *object);
    void unPauseGame(Scene *object);
    
    void willResignActive(Scene *object);
    void didBecomeActive(Scene *object);
    void didEnterBackground(Scene *object);
    void willEnterForeground(Scene *object);
    void willTerminate(Scene *object);
    void interrupt(Scene *object);
    void resumeInterrupt(Scene *object);
    
    void receivedMemoryWarning(Scene *object);
    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    static SceneState** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(SceneState * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static SceneState* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static SceneState* create(const SceneStateBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SceneState* clone(const SceneState& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SceneState* copy(const SceneState& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(SceneState * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(SceneState & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

protected:
private:
    //        std::string m_Name;
};
}

#endif /* defined(__JLIGameEngineTest__SceneState__) */
