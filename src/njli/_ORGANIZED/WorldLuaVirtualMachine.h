//
//  WorldLuaVirtualMachine.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldLuaVirtualMachine__
#define __JLIGameEngineTest__WorldLuaVirtualMachine__

#include <string>

#include "Util.h"
#include "lua.hpp"

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
class WorldLuaVirtualMachine : public AbstractObject {
public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    /**
         *  @author James Folk, 16-02-11 18:02:10
         *
         *  @brief <#Description#>
         */
    WorldLuaVirtualMachine();

    /**
         *  @author James Folk, 16-02-11 18:02:14
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~WorldLuaVirtualMachine();

    /**
         *  @author James Folk, 16-02-11 18:02:17
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;

    /**
         *  @author James Folk, 16-02-11 18:02:21
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;

    /**
         *  @author James Folk, 16-02-11 18:02:24
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const;

    /**
         *  @author James Folk, 16-02-11 18:02:30
         *
         *  @brief <#Description#>
         */
    void printStack();

    /**
         *  @author James Folk, 16-02-11 18:02:33
         *
         *  @brief <#Description#>
         *
         *  @param filePath <#filePath description#>
         *
         *  @return <#return value description#>
         */
    bool loadFile(const char* filePath);

    /**
         *  @author James Folk, 16-02-11 18:02:37
         *
         *  @brief <#Description#>
         *
         *  @param code <#code description#>
         *
         *  @return <#return value description#>
         */
    bool loadString(const char* code);

    /**
         *  @author James Folk, 16-02-11 18:02:43
         *
         *  @brief <#Description#>
         *
         *  @param filePath <#filePath description#>
         *
         *  @return <#return value description#>
         */
    bool doFile(const char* filePath);

    /**
         *  @author James Folk, 16-02-11 18:02:46
         *
         *  @brief <#Description#>
         *
         *  @param code <#code description#>
         *
         *  @return <#return value description#>
         */
    bool doString(const char* code);

    /**
         *  @author James Folk, 16-02-11 18:02:48
         *
         *  @brief <#Description#>
         */
    void reset();

    /**
         *  @author James Folk, 16-02-11 18:02:53
         *
         *  @brief <#Description#>
         *
         *  @param code <#code description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code);

    /**
         *  @author James Folk, 16-02-11 18:02:57
         *
         *  @brief <#Description#>
         *
         *  @param code <#code description#>
         *  @param str  <#str description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code, const char* str);

    /**
         *  @author James Folk, 16-02-11 18:02:00
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
         *  @author James Folk, 16-02-11 18:02:04
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
         *  @author James Folk, 16-02-11 18:02:10
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
         *  @author James Folk, 16-02-11 18:02:15
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
     <#Description#>

     @param code  <#code description#>
     @param scene <#scene description#>
     @param str   <#str description#>

     @return <#return value description#>
     */
    bool execute(const char *code, Scene *scene, const char* str);

    /**
         *  @author James Folk, 16-02-11 18:02:19
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
         *  @author James Folk, 16-02-11 18:02:23
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
         *  @author James Folk, 16-02-11 18:02:28
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
         *  @author James Folk, 16-02-11 18:02:31
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
         *  @author James Folk, 16-02-11 18:02:35
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
         *  @author James Folk, 16-02-11 18:02:39
         *
         *  @brief <#Description#>
         *
         *  @param code             <#code description#>
         *  @param m_CurrentTouches <#m_CurrentTouches description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code, DeviceTouch** m_CurrentTouches);
    
    bool execute(const char *code, Scene *pEntity, DeviceTouch **m_CurrentTouches);

    /**
         *  @author James Folk, 16-02-11 18:02:43
         *
         *  @brief <#Description#>
         *
         *  @param code  <#code description#>
         *  @param node  <#node description#>
         *  @param node2 <#node2 description#>
         *  @param mani  <#mani description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code, Node* node, Node* node2, const btManifoldPoint& mani);

    /**
         *  @author James Folk, 16-02-11 18:02:47
         *
         *  @brief <#Description#>
         *
         *  @param code  <#code description#>
         *  @param node  <#node description#>
         *  @param node2 <#node2 description#>
         *  @param mani  <#mani description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code, Node* node, Node* node2, const btDispatcherInfo& mani);

    /**
         *  @author James Folk, 16-02-11 18:02:51
         *
         *  @brief <#Description#>
         *
         *  @param code       <#code description#>
         *  @param rayContact <#rayContact description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code, const PhysicsRayContact& rayContact);

    /**
         *  @author James Folk, 16-02-11 18:02:55
         *
         *  @brief <#Description#>
         *
         *  @param code        <#code description#>
         *  @param rayContacts <#rayContacts description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code, const btAlignedObjectArray<njli::PhysicsRayContact*>& rayContacts);
    
    bool execute(const char* code, s32 width, s32 height, s32 orientation);

    /**
         *  @author James Folk, 16-02-11 18:02:58
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
         *  @author James Folk, 16-02-11 18:02:02
         *
         *  @brief <#Description#>
         *
         *  @param code   <#code description#>
         *  @param action <#action description#>
         *  @param num    <#num description#>
         *
         *  @return <#return value description#>
         */
    bool execute(const char* code, Action* action, f32 num);
    
    
    /**
     <#Description#>

     @param code    <#code description#>
     @param pEntity <#pEntity description#>
     @param touches <#touches description#>

     @return <#return value description#>
     */
    bool execute(const char *code, Node *pEntity, DeviceTouch **touches);

    
    /**
     <#Description#>

     @param code <#code description#>
     @param node <#node description#>
     @param str  <#str description#>

     @return <#return value description#>
     */
    bool execute(const char *code, Node *node, const char* str);
    
    /**
         *  @author James Folk, 16-02-11 18:02:04
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    double getMaxNumber() const;

    /**
         *  @author James Folk, 16-02-11 18:02:07
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    double getMinNumber() const;

    /**
         *  @author James Folk, 16-02-11 18:02:10
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         */
    bool compile();

    /**
         <#Description#>
         
         - returns: <#return value description#>
         */
    void init();
//    int initLua(int argc, char **argv);
//    lua_State *init(int argc, char **argv);

    /**
         *  @author James Folk, 16-02-11 18:02:16
         *
         *  @brief <#Description#>
         */
    void unInit();
    
    bool error(const char *description);
    
    /*
     ** Do the REPL: repeatedly read (load) a line, evaluate (call) it, and
     ** print any results.
     */
//    void doREPL ();

protected:
    void getError(const char* code, int error);

    lua_State* m_lua_State;

private:
    WorldLuaVirtualMachine(const WorldLuaVirtualMachine&);
    WorldLuaVirtualMachine& operator=(const WorldLuaVirtualMachine&);

    //        swig_type_info* typeinfo = SWIG_TypeQuery( m_L, "njli::Scene" );
//    swig_type_info* m_SceneTypeInfo;
//    swig_type_info* m_TelegramTypeInfo;
//    swig_type_info* m_NodeTypeInfo;
//    swig_type_info* m_DeviceTouchTypeInfo;
//    swig_type_info* m_PhysicsRayContactTypeInfo;
//    swig_type_info* m_ActionTypeInfo;
    
private:
    static std::string m_previousMessage;
    static lua_State *globalL;
    static void lstop (lua_State *L, lua_Debug *ar);
    static void laction (int i);
    static int msghandler (lua_State *L);
    static int docall (lua_State *L, int narg, int nres);
    
    static void l_message (const char *pname, const char *msg);
//    static int report (lua_State *L, int status);
    
    
};
}

#endif /* defined(__JLIGameEngineTest__WorldLuaVirtualMachine__) */
