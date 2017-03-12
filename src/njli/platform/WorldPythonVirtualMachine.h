//
//  WorldPythonVirtualMachine.h
//  JLIGameEngineTest
//
//  Created by James Folk on 8/24/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldPythonVirtualMachine__
#define __JLIGameEngineTest__WorldPythonVirtualMachine__

#include <string>

#include "Util.h"

#include "AbstractState.h"
#include "DeviceTouch.h"
#include "Node.h"
#include "Scene.h"
#include "btDispatcher.h"
#include "btManifoldPoint.h"

#include "Action.h"
#include "PhysicsRayContact.h"
#include "btAlignedObjectArray.h"
#include "btAlignedObjectArray.h"

namespace njli {
/// <#Description#>
class WorldPythonVirtualMachine : public AbstractObject {
public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    /**
     *  @author James Folk, 16-02-11 19:02:53
     *
     *  @brief <#Description#>
     */
    WorldPythonVirtualMachine();

    /**
     *  @author James Folk, 16-02-11 19:02:57
     *
     *  @brief <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual ~WorldPythonVirtualMachine();

    /**
     *  @author James Folk, 16-02-11 19:02:01
     *
     *  @brief <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual const char* getClassName() const;

    /**
     *  @author James Folk, 16-02-11 19:02:05
     *
     *  @brief <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual s32 getType() const;

    /**
     *  @author James Folk, 16-02-11 19:02:11
     *
     *  @brief <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual operator std::string() const;

    /**
     *  @author James Folk, 16-02-11 19:02:15
     *
     *  @brief <#Description#>
     */
    void reset();

    /**
     *  @author James Folk, 16-02-11 19:02:24
     *
     *  @brief <#Description#>
     */
    void printStack();

    /**
     *  @author James Folk, 16-02-11 19:02:29
     *
     *  @brief <#Description#>
     *
     *  @param filePath <#filePath description#>
     */
    void loadFile(const char* filePath);

    /**
     *  @author James Folk, 16-02-11 19:02:33
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     */
    void loadString(const char* code);

    /**
     *  @author James Folk, 16-02-11 19:02:38
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code);

    /**
     *  @author James Folk, 16-02-11 19:02:42
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *  @param num  <#num description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, s32 num);

    /**
     *  @author James Folk, 16-02-11 19:02:49
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *  @param num  <#num description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, f32 num);

    /**
     *  @author James Folk, 16-02-11 19:02:55
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *  @param tele <#tele description#>
     *  @param b    <#b description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, const Telegram& tele, bool& b);

    /**
     *  @author James Folk, 16-02-11 19:02:00
     *
     *  @brief <#Description#>
     *
     *  @param code  <#code description#>
     *  @param scene <#scene description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Scene* scene);

    /**
     *  @author James Folk, 16-02-11 19:02:07
     *
     *  @brief <#Description#>
     *
     *  @param code  <#code description#>
     *  @param scene <#scene description#>
     *  @param num   <#num description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Scene* scene, f32 num);

    /**
     *  @author James Folk, 16-02-11 19:02:12
     *
     *  @brief <#Description#>
     *
     *  @param code  <#code description#>
     *  @param scene <#scene description#>
     *  @param tele  <#tele description#>
     *  @param b     <#b description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Scene* scene, const Telegram& tele, bool& b);

    /**
     *  @author James Folk, 16-02-11 19:02:17
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *  @param node <#node description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Node* node);

    /**
     *  @author James Folk, 16-02-11 19:02:23
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *  @param node <#node description#>
     *  @param num  <#num description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Node* node, f32 num);

    /**
     *  @author James Folk, 16-02-11 19:02:27
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *  @param node <#node description#>
     *  @param tele <#tele description#>
     *  @param b    <#b description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Node* node, const Telegram& tele, bool& b);

    /**
     *  @author James Folk, 16-02-11 19:02:32
     *
     *  @brief <#Description#>
     *
     *  @param code             <#code description#>
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, DeviceTouch** m_CurrentTouches);

    /**
     *  @author James Folk, 16-02-11 19:02:36
     *
     *  @brief <#Description#>
     *
     *  @param code <#code description#>
     *  @param Node <#Node description#>
     *  @param node <#node description#>
     *  @param mani <#mani description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Node*, Node* node, const btManifoldPoint& mani);

    /**
     *  @author James Folk, 16-02-11 19:02:41
     *
     *  @brief <#Description#>
     *
     *  @param code     <#code description#>
     *  @param node     <#node description#>
     *  @param node     <#node description#>
     *  @param dispatch <#dispatch description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Node* node, Node* node1, const btDispatcherInfo& dispatch);

    /**
     *  @author James Folk, 16-02-11 19:02:46
     *
     *  @brief <#Description#>
     *
     *  @param code    <#code description#>
     *  @param contact <#contact description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, const PhysicsRayContact& contact);

    /**
     *  @author James Folk, 16-02-11 19:02:51
     *
     *  @brief <#Description#>
     *
     *  @param code        <#code description#>
     *  @param rayContacts <#rayContacts description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, const btAlignedObjectArray<njli::PhysicsRayContact*>& rayContacts);

    /**
     *  @author James Folk, 16-02-11 19:02:56
     *
     *  @brief <#Description#>
     *
     *  @param code   <#code description#>
     *  @param action <#action description#>
     *
     *  @return <#return value description#>
     */
    bool execute(const char* code, Action* action);

    /**
     <#Description#>
     
     - returns: <#return value description#>
     */
    bool execute(const char* code, Action* action, f32 number);

protected:
    void init();
    void unInit();

    void getError(const char* code, int error);
    void compile();

    //        lua_State *m_lua_State;
    wchar_t* m_wpython_home;

private:
    WorldPythonVirtualMachine(const WorldPythonVirtualMachine&);
    WorldPythonVirtualMachine& operator=(const WorldPythonVirtualMachine&);
};
}

#endif /* defined(__JLIGameEngineTest__WorldPythonVirtualMachine__) */
