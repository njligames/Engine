//
//  WorldLuaVirtualMachine.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//
//#include <Python/Python.h>
//#define PY_SSIZE_T_CLEAN

//#else

#include "lua.hpp"

#include "WorldLuaVirtualMachine.h"


#include "Log.h"
#define TAG "WorldLuaVirtualMachine"
#define FORMATSTRING "{\"njli::WorldLuaVirtualMachine\":[]}"
#include "btPrint.h"

#include "File.h"
#include "Util.h"


#include "lua.h"
#include "lauxlib.h"
extern "C" {
#include "lualoadexts.h"
}

#include "File.h"
#include "AbstractActionable.h"
#include "AbstractBuilder.h"
#include "AbstractClock.h"
#include "AbstractDecorator.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "AbstractObject.h"
#include "AbstractRender.h"
#include "AbstractState.h"
#include "AbstractStateMachine.h"
#include "AbstractTransform.h"
#include "Action.h"
#include "ActionBuilder.h"
#include "ButtonHUD.h"
#include "ButtonHUDBuilder.h"
#include "Camera.h"
#include "CameraBuilder.h"
#include "CheckboxHUD.h"
#include "CheckboxHUDBuilder.h"
#include "Clock.h"
#include "ClockBuilder.h"
#include "CollisionResponse.h"
#include "CollisionResponseBuilder.h"
#include "Cube.h"
#include "CubeBuilder.h"
#include "DropdownHUD.h"
#include "DropdownHUDBuilder.h"
#include "Font.h"
#include "FontBuilder.h"
#include "GameClock.h"
#include "Geometry.h"
#include "Image.h"
#include "ImageBuilder.h"
//#include "JLIBuilders.h"
//#include "JLIEngine.h"
#include "JLIFactoryTypes.h"
//#include "JLITransform.h"
#include "JsonJLI.h"
#include "JsonJLIBuilder.h"
#include "LabelHUD.h"
#include "LabelHUDBuilder.h"
#include "LevelOfDetail.h"
#include "LevelOfDetailBuilder.h"
#include "Light.h"
#include "LightBuilder.h"
//#include "Lua.h"
//#include "LuaBuilder.h"
#include "Material.h"
#include "MaterialBuilder.h"
#include "MaterialProperty.h"
#include "MaterialPropertyBuilder.h"
#include "Node.h"
#include "NodeBuilder.h"
#include "NodeState.h"
#include "NodeStateBuilder.h"
#include "NodeStateMachine.h"
#include "NodeStateMachineBuilder.h"
#include "ParticleEmitter.h"
#include "ParticleEmitterBuilder.h"
#include "PhysicsBody.h"
#include "PhysicsBodyGhost.h"
#include "PhysicsBodyGhostBuilder.h"
#include "PhysicsBodyRigid.h"
#include "PhysicsBodyRigidBuilder.h"
#include "PhysicsBodySoft.h"
#include "PhysicsBodySoftBuilder.h"
#include "PhysicsCloseContact.h"
#include "PhysicsCloseContactBuilder.h"
#include "PhysicsConstraint.h"
#include "PhysicsConstraintBuilder.h"
#include "PhysicsConstraintConeTwist.h"
#include "PhysicsConstraintConeTwistBuilder.h"
#include "PhysicsConstraintFixed.h"
#include "PhysicsConstraintFixedBuilder.h"
#include "PhysicsConstraintGeneric6Dof.h"
#include "PhysicsConstraintGeneric6DofBuilder.h"
#include "PhysicsConstraintGeneric6DofSpring.h"
#include "PhysicsConstraintGeneric6DofSpringBuilder.h"
#include "PhysicsConstraintHinge.h"
#include "PhysicsConstraintHingeBuilder.h"
#include "PhysicsConstraintPointToPoint.h"
#include "PhysicsConstraintPointToPointBuilder.h"
#include "PhysicsConstraintSlider.h"
#include "PhysicsConstraintSliderBuilder.h"
#include "PhysicsContact.h"
#include "PhysicsContactBuilder.h"
#include "PhysicsField.h"
#include "PhysicsFieldBuilder.h"
#include "PhysicsRayContact.h"
#include "PhysicsRayContactBuilder.h"
#include "PhysicsShape.h"
#include "PhysicsShapeBox.h"
#include "PhysicsShapeBox2D.h"
#include "PhysicsShapeBox2DBuilder.h"
#include "PhysicsShapeBoxBuilder.h"
#include "PhysicsShapeBvhTriangleMesh.h"
#include "PhysicsShapeBvhTriangleMeshBuilder.h"
#include "PhysicsShapeCapsule.h"
#include "PhysicsShapeCapsuleBuilder.h"
#include "PhysicsShapeCone.h"
#include "PhysicsShapeConeBuilder.h"
#include "PhysicsShapeConvexHull.h"
#include "PhysicsShapeConvexHullBuilder.h"
#include "PhysicsShapeConvexTriangleMesh.h"
#include "PhysicsShapeConvexTriangleMeshBuilder.h"
#include "PhysicsShapeCylinder.h"
#include "PhysicsShapeCylinderBuilder.h"
#include "PhysicsShapeHeightfieldTerrain.h"
#include "PhysicsShapeHeightfieldTerrainBuilder.h"
#include "PhysicsShapeMultiSphere.h"
#include "PhysicsShapeMultiSphereBuilder.h"
#include "PhysicsShapeSphere.h"
#include "PhysicsShapeSphereBuilder.h"
#include "PhysicsShapeStaticPlane.h"
#include "PhysicsShapeStaticPlaneBuilder.h"
#include "PhysicsWorld.h"
#include "PhysicsWorldBuilder.h"
#include "Plane.h"
#include "PlaneBuilder.h"
#include "Scene.h"
#include "SceneBuilder.h"
#include "SceneState.h"
#include "SceneStateBuilder.h"
#include "SceneStateMachine.h"
#include "SceneStateMachineBuilder.h"
#include "ShaderProgram.h"
#include "ShaderProgramBuilder.h"
#include "Skinner.h"
#include "SkinnerBuilder.h"
#include "SliderHUD.h"
#include "SliderHUDBuilder.h"
#include "SoundBuilder.h"
#include "Sprite2D.h"
#include "Sprite2DBuilder.h"
#include "SpriteFrameAtlas.h"
#include "SpriteFrameAtlasBuilder.h"
#include "StopWatch.h"
#include "StopWatchBuilder.h"
#include "TextboxHUD.h"
#include "TextboxHUDBuilder.h"
#include "Thread.h"
#include "ThreadBuilder.h"
#include "Timer.h"
#include "TimerBuilder.h"
#include "World.h"
#include "WorldClock.h"
#include "WorldDebugDrawer.h"
#include "WorldFactory.h"
#include "WorldHUD.h"
#include "WorldLuaVirtualMachine.h"
#include "WorldResourceLoader.h"
#include "WorldSQLite.h"
#include "WorldSocket.h"
#include "WorldState.h"
#include "WorldStateBuilder.h"
#include "WorldStateMachine.h"
#include "WorldStateMachineBuilder.h"
#include "Xml.h"
#include "XmlBuilder.h"
//#########################################################################################################
#include "DeviceInputTime.h"
#include "DeviceTouch.h"
#include "File.h"
//#include "Game.h"
//#include "JLIAssetUtil.h"
//#include "JLIFileUtil.h"
#include "Localization.h"
#include "Log.h"
#include "Macros.h"
#include "Sound.h"
#include "Util.h"
//#include "WorldFacebook.h"
#include "WorldInput.h"
//#include "WorldPythonVirtualMachine.h"
#include "WorldSound.h"


#include "njli_swig_runtime.h"
//#include "njli_swig_types.h"
////#include "swig_type_info.h"
extern swig_type_info *swig_types[597];



























lua_State *njli::WorldLuaVirtualMachine::globalL = NULL;
std::string njli::WorldLuaVirtualMachine::m_previousMessage = "";

/*
 ** Hook set by signal function to stop the interpreter.
 */
 void njli::WorldLuaVirtualMachine::lstop (lua_State *L, lua_Debug *ar) {
    (void)ar;  /* unused arg. */
    lua_sethook(L, NULL, 0, 0);  /* reset hook */
    luaL_error(L, "interrupted!");
}

/*
 ** Function to be called at a C signal. Because a C signal cannot
 ** just change a Lua state (as there is no proper synchronization),
 ** this function only sets a hook that, when called, will stop the
 ** interpreter.
 */
 void njli::WorldLuaVirtualMachine::laction (int i) {
    signal(i, SIG_DFL); /* if another SIGINT happens, terminate process */
    lua_sethook(globalL, lstop, LUA_MASKCALL | LUA_MASKRET | LUA_MASKCOUNT, 1);
}

/*
 ** Message handler used to run all chunks
 */
 int njli::WorldLuaVirtualMachine::msghandler (lua_State *L) {
    const char *msg = lua_tostring(L, 1);
    if (msg == NULL) {  /* is error object not a string? */
        if (luaL_callmeta(L, 1, "__tostring") &&  /* does it have a metamethod */
            lua_type(L, -1) == LUA_TSTRING)  /* that produces a string? */
            return 1;  /* that is the message */
        else
            msg = lua_pushfstring(L, "(error object is a %s value)",
                                  luaL_typename(L, 1));
    }
    luaL_traceback(L, L, msg, 1);  /* append a standard traceback */
    return 1;  /* return the traceback */
}


/*
 ** Interface to 'lua_pcall', which sets appropriate message function
 ** and C-signal handler. Used to run all chunks.
 */
int njli::WorldLuaVirtualMachine::docall (lua_State *L, int narg, int nres) {
    int status;
    int base = lua_gettop(L) - narg;  /* function index */
    lua_pushcfunction(L, msghandler);  /* push message handler */
    lua_insert(L, base);  /* put it under function and args */
    globalL = L;  /* to be available to 'laction' */
    signal(SIGINT, laction);  /* set C-signal handler */
    status = lua_pcall(L, narg, nres, base);
    signal(SIGINT, SIG_DFL); /* reset C-signal handler */
    lua_remove(L, base);  /* remove message handler from the stack */
    return status;
}


/*
 ** Prints an error message, adding the program name in front of it
 ** (if present)
 */
void njli::WorldLuaVirtualMachine::l_message (const char *pname, const char *msg) {
    if (pname) lua_writestringerror("%s: ", pname);
    if(strcmp(msg, m_previousMessage.c_str()) != 0)
    {
        lua_writestringerror("%s\n", "<ERROR>" );
        lua_writestringerror("%s\n", msg);
        lua_writestringerror("%s\n", "</ERROR>" );
    }
    m_previousMessage = msg;
    
}


/*
 ** Check whether 'status' is not OK and, if so, prints the error
 ** message on the top of the stack. It assumes that the error object
 ** is a string, as it was either generated by Lua or by 'msghandler'.
 */
//int njli::WorldLuaVirtualMachine::report (lua_State *L, int status) {
//    if (status != LUA_OK) {
//        const char *msg = lua_tostring(L, -1);
//        l_message(progname, msg);
//        lua_pop(L, 1);  /* remove message */
//    }
//    return status;
//}








static int appendLuaPath(lua_State* L, const char* path)
{
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
    std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
    cur_path.append(";"); // do your path magic here
    cur_path.append(path);
    lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring(L, cur_path.c_str()); // push the new one
    lua_setfield(L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
    lua_pop(L, 1); // get rid of package table from top of stack
    return 0; // all done!
}










static void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L);
    
    DEBUG_LOG_PRINT_V(TAG, "%s", "\n\n\n ----------------  Stack Dump ----------------\n" );
    DEBUG_LOG_PRINT_V(TAG, "%s", "\n");  /* end the listing */
    for (i = 1; i <= top; i++)
    {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
                
            case LUA_TSTRING:  /* strings */
                DEBUG_LOG_PRINT_V(TAG, "'%s'\n", lua_tostring(L, i));
                break;
                
            case LUA_TBOOLEAN:  /* booleans */
                DEBUG_LOG_PRINT_V(TAG, "%s", lua_toboolean(L, i) ? "true\n" : "false\n");
                break;
                
            case LUA_TNUMBER:  /* numbers */
                DEBUG_LOG_PRINT_V(TAG, "%g\n", lua_tonumber(L, i));
                break;
                
            default:  /* other values */
                DEBUG_LOG_PRINT_V(TAG, "%s\n", lua_typename(L, t));
                break;
                
        }
//        DEBUG_LOG_PRINT_V(TAG, "  ");  /* put a separator */
    }
    DEBUG_LOG_PRINT_V(TAG, "%s", "\n");  /* end the listing */
    DEBUG_LOG_PRINT_V(TAG, "%s", " --------------- Stack Dump Finished ---------------\n" );
}

//http://giderosmobile.com/forum/discussion/584/passing-a-table-to-c-func-and-back-to-lua-code/p1

typedef void (*luaTableIterFunc)(lua_State*, int, const char *);

static void printLuaTableKeyAndValues(lua_State *L, int index, const char *key)
{
    if(lua_isnumber(L, index))
    {
        double number = lua_tonumber(L, index);
        printf("%s => %f\n", key, number);
    }
    else if(lua_isstring(L, index))
    {
        const char *value = lua_tostring(L, index);
        printf("%s => %s\n", key, value);
    }
    else if(lua_isuserdata(L, index))
    {
        swig_lua_userdata *usr;
        swig_type_info *type;
        DEBUG_ASSERT(lua_isuserdata(L,index));
        usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
        type = usr->type;
        njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
        printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
        
    }
}

static void iterate_and_print(lua_State *L, int index)
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
            iterate_and_print(L, -2);
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
                const char *value = lua_tostring(L, index);
                printf("%s => %s\n", key, value);
            }
            else if(lua_isuserdata(L, index))
            {
                swig_lua_userdata *usr;
                swig_type_info *type;
                DEBUG_ASSERT(lua_isuserdata(L,index));
                usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
                type = usr->type;
                njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
                printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                
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

static void populate_builder(lua_State *L, int index, njli::AbstractFactoryObject &object)
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
            iterate_and_print(L, -2);
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
                swig_lua_userdata *usr;
                swig_type_info *type;
                DEBUG_ASSERT(lua_isuserdata(L,index));
                usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
                type = usr->type;
                njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
                printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                
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

//static s32 countParameters = 0;
//static njli::Rect rect;
//static void populateSpriteAtlas(lua_State *L, int index, njli::SpriteFrameAtlas &object)
//{
//    // Push another reference to the table on top of the stack (so we know
//    // where it is, and this function can work for negative, positive and
//    // pseudo indices
//    lua_pushvalue(L, index);
//    // stack now contains: -1 => table
//    lua_pushnil(L);
//    // stack now contains: -1 => nil; -2 => table
//    
//    
//    
//    while (lua_next(L, -2))
//    {
//        // stack now contains: -1 => value; -2 => key; -3 => table
//        // copy the key so that lua_tostring does not modify the original
//        lua_pushvalue(L, -2);
//        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
//        const char *key = lua_tostring(L, -1);
//        const char *value = lua_tostring(L, -2);
//        if(lua_istable(L, -2))
//        {
//            DEBUG_ASSERT(countParameters == 0 || countParameters == 7);
//            
//            if(countParameters == 7)
//                object.addFrame(rect);
//            countParameters = 0;
//            
//            populateSpriteAtlas(L, -2, object);
//        }
//        else
//        {
//            std::string key(lua_tostring(L, -1));
//            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
//            
//            if(strcmp(key.c_str(), "sheetcontentwidth") == 0)
//            {
//                double number = lua_tonumber(L, index);
//                object.setSheetContentWidth(number);
//            }
//            else if(strcmp(key.c_str(), "sheetcontentheight") == 0)
//            {
//                double number = lua_tonumber(L, index);
//                object.setSheetContentHeight(number);
//            }
//            else if(strcmp(key.c_str(), "filename") == 0)
//            {
//                const char *value = lua_tostring(L, index);
//                object.setSourceFilename(value);
//            }
//            else
//            {
//                ++countParameters;
//                
//                if(strcmp(key.c_str(), "x") == 0)
//                {
//                    double number = lua_tonumber(L, index);
//                    rect.setX(number);
//                }
//                else if(strcmp(key.c_str(), "y") == 0)
//                {
//                    double number = lua_tonumber(L, index);
//                    rect.setY(number);
//                }
//                else if(strcmp(key.c_str(), "width") == 0)
//                {
//                    double number = lua_tonumber(L, index);
//                    rect.setWidth(number);
//                }
//                else if(strcmp(key.c_str(), "height") == 0)
//                {
//                    double number = lua_tonumber(L, index);
//                    rect.setHeight(number);
//                }
//                else if(strcmp(key.c_str(), "pivotx") == 0)
//                {
//                    double number = lua_tonumber(L, index);
//                    rect.setPivotX(number);
//                }
//                else if(strcmp(key.c_str(), "pivoty") == 0)
//                {
//                    double number = lua_tonumber(L, index);
//                    rect.setPivotY(number);
//                }
//                else if(strcmp(key.c_str(), "trimmedname") == 0)
//                {
//                    const char *value = lua_tostring(L, index);
//                    rect.setTrimmedName(value);
//                }
//                else
//                {
//                    Log("invalid key: %s\n", key.c_str());
//                    DEBUG_ASSERT(false);
//                }
//            }
//        }
//        // pop value + copy of key, leaving original key
//        lua_pop(L, 2);
//        // stack now contains: -1 => key; -2 => table
//    }
//    // stack now contains: -1 => table (when lua_next returns 0 it pops the key
//    // but does not push anything.)
//    // Pop table
//    lua_pop(L, 1);
//    // Stack is now the same as it was on entry to this function
//}












static int printLuaTable(lua_State *L)
{
//    stackDump(L);
    iterate_and_print(L, -1);
    return 1;
}

static int create(lua_State *L)
{
//    iterate_and_build(L);
    return 1;
}

//static swig_lua_method JLIM_Module_methods[]= {
//    { "printLuaTable",	printLuaTable },
//    { "create",	create },
//    { NULL, NULL }
//};
//
//static swig_lua_attribute JLIM_Module_attributes[] = {
//    {0,0,0}
//};
//
//static swig_lua_const_info JLIM_Module_constants[]= {
//    {0,0,0,0,0,0}
//};
//static swig_lua_class* JLIM_Module_classes[]= {
//    0
//};
//static swig_lua_namespace* JLIM_Module_namespaces[] = {
//    0
//};
//
//static swig_lua_namespace JLIM_Module = {
//    "JLIM",
//    JLIM_Module_methods,
//    JLIM_Module_attributes,
//    JLIM_Module_constants,
//    JLIM_Module_classes,
//    JLIM_Module_namespaces
//};

LUALIB_API int luaopen_JLIM(lua_State *L)
{
//http://passingcuriosity.com/2009/extending-lua-in-c/
    
    // Create the table
    lua_createtable(L,0,0);
    
    // Create the meta-table
    lua_createtable(L,0,1);
    
    // Add the __index
    lua_pushcfunction(L, create);
    lua_setfield(L, -2, "__index");
    
    // Set the meta-table
    lua_setmetatable(L, -2);
    
    // Set the global hash
//    lua_setfield(L, LUA_GLOBALSINDEX, "create");
    lua_pushglobaltable(L);
    
    
    lua_register(L, "create",	create);
    return 0;
//    int globalRegister = 1;
//    
//    swig_lua_namespace *ns = &JLIM_Module;
//    int reg = globalRegister;
//    
//    /* 1 argument - table on the top of the stack */
//    const int SWIGUNUSED begin = lua_gettop(L);
//    DEBUG_ASSERT(lua_istable(L,-1)); /* just in case. This is supposed to be module table or parent namespace table */
//    lua_checkstack(L,5);
//    lua_newtable(L); /* namespace itself */
//    lua_newtable(L); /* metatable for namespace */
//    
//    /* add a table called ".get" */
//    lua_pushstring(L,".get");
//    lua_newtable(L);
//    lua_rawset(L,-3);
//    /* add a table called ".set" */
//    lua_pushstring(L,".set");
//    lua_newtable(L);
//    lua_rawset(L,-3);
//    /* add a table called ".fn" */
//    lua_pushstring(L,".fn");
//    lua_newtable(L);
//    lua_rawset(L,-3);
//    
//    /* add accessor fns for using the .get,.set&.fn */
//    SWIG_Lua_add_function(L,"__index",SWIG_Lua_namespace_get);
//    SWIG_Lua_add_function(L,"__newindex",SWIG_Lua_namespace_set);
//    
//    lua_setmetatable(L,-2); /* set metatable */
//    
//    /* Register all functions, variables etc */
//    SWIG_Lua_add_namespace_details(L,ns);
//    /* Register classes */
//    SWIG_Lua_add_namespace_classes(L,ns);
//    
//    swig_lua_namespace **sub_namespace = ns->ns_namespaces;
//    if( sub_namespace != 0) {
//        while(*sub_namespace != 0) {
//            SWIG_Lua_namespace_register(L, *sub_namespace, 1);
//            lua_pop(L,1); /* removing sub-namespace table */
//            sub_namespace++;
//        }
//    }
//    
//    if (reg) {
//        lua_pushstring(L,ns->name);
//        lua_pushvalue(L,-2);
//        lua_rawset(L,-4); /* add namespace to module table */
//    }
//    const int SWIGUNUSED end = lua_gettop(L);
//    
//    DEBUG_ASSERT(lua_gettop(L) == begin+1);
    
    
    
    
    
    
//    lua_setmetatable(L,-2); /* set metatable */
//    
//    /* Register all functions, variables etc */
//    SWIG_Lua_add_namespace_details(L,ns);
//    /* Register classes */
//    SWIG_Lua_add_namespace_classes(L,ns);
//    
//    swig_lua_namespace **sub_namespace = ns->ns_namespaces;
//    if( sub_namespace != 0) {
//        while(*sub_namespace != 0) {
//            SWIG_Lua_namespace_register(L, *sub_namespace, 1);
//            lua_pop(L,1); /* removing sub-namespace table */
//            sub_namespace++;
//        }
//    }
//    
//    if (reg) {
//        lua_pushstring(L,ns->name);
//        lua_pushvalue(L,-2);
//        lua_rawset(L,-4); /* add namespace to module table */
//    }
//    const int SWIGUNUSED end = lua_gettop(L);
//    DEBUG_ASSERT(lua_gettop(L) == begin+1);
    
    
    
    
//    lua_newtable(L);
//    luaL_setfuncs (L,JLIEngineManualFuncs,0);
//    lua_pushvalue(L,-1);        // pluck these lines out if they offend you
//    lua_setglobal(L,"JLIM"); // for they clobber the Holy _G
    return 1;
}
















//static std::string buildSublimeCompletions()
//{
//    char trigger_value[512];
//    char completion_value[512];
//    
//    std::string trigger0 = "\t\t{\"trigger\": \"";
//    std::string trigger1 = "\", \"contents\": \"";
//    std::string trigger2 = "\" },\n";
//    
//    std::string sublime_completions = "";
//    
//    
//    for (int j = 0; swig_SwigModule.ns_constants[j].name; ++j)
//    {
//        sprintf(trigger_value, "%s",swig_SwigModule.ns_constants[j].name);
//        sprintf(completion_value, "JLI.%s",swig_SwigModule.ns_constants[j].name);
//        
//        sublime_completions += trigger0;
//        sublime_completions += trigger_value;
//        sublime_completions += trigger1;
//        sublime_completions += completion_value;
//        sublime_completions += trigger2;
//        
//    }
//    
//    for (int j = 0; swig_SwigModule.ns_attributes[j].name; ++j)
//    {
//        sprintf(trigger_value, "%s",swig_SwigModule.ns_constants[j].name);
//        sprintf(completion_value, "JLI.%s",swig_SwigModule.ns_constants[j].name);
//        
//        sublime_completions += trigger0;
//        sublime_completions += trigger_value;
//        sublime_completions += trigger1;
//        sublime_completions += completion_value;
//        sublime_completions += trigger2;
//        
//    }
//    
//    return sublime_completions;
//}


static std::string printMethods(const char* name)
{
    std::string output = "-- Automatically generated tests for JLI game engine.\n\n";
    char trigger_value[512];
    char completion_value[512];
    
    std::string trigger0 = "\t\t{\"trigger\": \"";
    std::string trigger1 = "\", \"contents\": \"";
    std::string trigger2 = "\" },\n";
    
//    std::string sublime_completions = "\n{\n\t\"scope\": \"source.lua - source - meta.tag, punctuation.definition.tag.begin\",\n";
//    
//    sublime_completions += "\n\n\t\"completions\":\n\t[\n";
    
    std::string sublime_completions = "";
    
    //this touches the SWIG internals, please be careful:
    for (int i = 0; swig_types[i]; i++)
    {
        if (swig_types[i]->clientdata)
        {
            swig_lua_class* ptr=(swig_lua_class*)(swig_types[i]->clientdata);

            if (strcmp(name,ptr->name)==0)
            {
//                sprintf("test%sFunctions", ptr->name);
                
                for (int j = 0; ptr->cls_static->ns_constants[j].name; ++j)
                {
                    
                    sprintf(trigger_value, "%s",ptr->cls_static->ns_constants[j].name);
                    sprintf(completion_value, "JLI.%s",ptr->cls_static->ns_constants[j].name);
                    
                    sublime_completions += trigger0;
                    sublime_completions += trigger_value;
                    sublime_completions += trigger1;
                    sublime_completions += completion_value;
                    sublime_completions += trigger2;
                    
                }
                
                for(int j = 0; ptr->cls_static->ns_methods[j].name; ++j)
                {
                    sprintf(trigger_value, "static %s.%s",ptr->name,ptr->cls_static->ns_methods[j].name);
                    sprintf(completion_value, "JLI.%s.%s",ptr->name,ptr->cls_static->ns_methods[j].name);
                    
                    sublime_completions += trigger0;
                    sublime_completions += trigger_value;
                    sublime_completions += trigger1;
                    sublime_completions += completion_value;
                    sublime_completions += trigger2;
                }
                
                for(int j = 0; ptr->metatable[j].name; ++j)
                {
                    if(strcmp("Node", ptr->name) == 0)
                    {
                        printf("%s:%s\n",ptr->name,ptr->metatable[j].name);
                    }
                }
                for(int j = 0; ptr->methods[j].name; ++j)
                {
                    if(strcmp("Node", ptr->name) == 0)
                    {
                        printf("%s:%s\n",ptr->name,ptr->methods[j].name);
                        
                        printf("%s:%s\n",ptr->name,ptr->methods[j].name);
                    }
                }

                for(int j = 0; ptr->methods[j].name; ++j)
                {
                    if(strcmp("Node", ptr->name) == 0)
                    {
                        swig_lua_method method = ptr->methods[j];
                        sprintf(trigger_value, "%s.%s",ptr->name,ptr->methods[j].name);
                        sprintf(completion_value, "%s",ptr->methods[j].name);
                    }
                    
                    sprintf(trigger_value, "%s.%s",ptr->name,ptr->methods[j].name);
                    sprintf(completion_value, "%s",ptr->methods[j].name);
                    
                    sublime_completions += trigger0;
                    sublime_completions += trigger_value;
                    sublime_completions += trigger1;
                    sublime_completions += completion_value;
                    sublime_completions += trigger2;
                }
                
//                for(int j=0;ptr->methods[j].name;j++)
//                {
//                    sprintf(buffer, "%s::%s()\n",ptr->name,ptr->methods[j].name);
////                    functions += buffer;
//						DEBUG_LOG_PRINT_V(TAG, "%s::%s()\n",ptr->name,ptr->methods[j].name);
//                }
            }
        }
    }
//    sublime_completions += "\t]\n}";
//    DEBUG_LOG_PRINT_V(TAG, "%s",sublime_completions.c_str());
    return sublime_completions;
//    Log("%s", functions.c_str());
}

static void printWrappedClasses()
{
    std::string sublime_completions = "\n{\n\t\"scope\":\"source.lua\",\n";
    //std::string sublime_completions = "\n{\n\t\"scope\": \"source.lua - source - meta.tag, punctuation.definition.tag.begin\",\n";
    
    sublime_completions += "\n\n\t\"completions\":\n\t[\n";
    
    //this touches the SWIG internals, please be careful:
    for (int i = 0; swig_types[i]; i++)
    {
        if (swig_types[i]->clientdata)
        {
            swig_lua_class* ptr=(swig_lua_class*)(swig_types[i]->clientdata);
            sublime_completions += printMethods(ptr->name);
        }
    }
    
//    sublime_completions += buildSublimeCompletions();
    
    sublime_completions += "\t]\n}";
    
    DEBUG_LOG_PRINT_V(TAG, "%s",sublime_completions.c_str());
}

namespace njli
{
    WorldLuaVirtualMachine::WorldLuaVirtualMachine():
    m_lua_State(NULL)
    {
//        init();
    }
    
    WorldLuaVirtualMachine::~WorldLuaVirtualMachine()
    {
        unInit();
    }
    
    WorldLuaVirtualMachine::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    const char *WorldLuaVirtualMachine::getClassName()const
    {
        return "WorldLuaVirtualMachine";
    }
    
    s32 WorldLuaVirtualMachine::getType()const
    {
        return JLI_OBJECT_TYPE_WorldLuaVirtualMachine;
    }
    
//    void WorldLuaVirtualMachine::reset()
//    {
//        unInit();
//        init();
//    }
    
    void WorldLuaVirtualMachine::printStack()
    {
        if(m_lua_State)
            stackDump(m_lua_State);
    }
    
    bool WorldLuaVirtualMachine::loadFile(const char *filePath)
    {
        if(m_lua_State)
        {
            std::string script;
            if(njli::World::getInstance()->getWorldResourceLoader()->load(filePath, &script))
            {
                return loadString(script.c_str());
            }
            else
            {
                DEBUG_LOG_WRITE_W(TAG, "Unable to load script file");
            }
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::loadString(const char *code)
    {
        if(m_lua_State)
        {
            int error_code = luaL_loadstring(m_lua_State, code);
            
            if(LUA_OK == error_code)
                return true;
            getError(code, error_code);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::doFile(const char *filePath)
    {
        if(m_lua_State)
        {
            int error_code = luaL_dofile(m_lua_State, filePath);
            
            if(LUA_OK == error_code)
                return true;
            getError("", error_code);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::doString(const char *code)
    {
        if(m_lua_State)
        {
            int error_code = luaL_dostring(m_lua_State, code);
            
            if(LUA_OK == error_code)
                return true;
            getError(code, error_code);
        }
        return false;
    }
    
    void WorldLuaVirtualMachine::reset()
    {
        if(m_lua_State)
        {
            int count = 0;
            int previous_count = count;
            
            lua_settop(m_lua_State, 0);
            count = lua_gc(m_lua_State, LUA_GCCOLLECT, 0);
            
            do
            {
                previous_count = count;
                count = lua_gc(m_lua_State, LUA_GCCOUNT, 0);
                
            }while(count != previous_count);
            
            World::getInstance()->getWorldFactory()->destroyAll();
            
            unInit();
            init();
        }
    }
    
    
    double WorldLuaVirtualMachine::getMaxNumber()const
    {
        return std::numeric_limits<lua_Number>::max();
    }
    
    double WorldLuaVirtualMachine::getMinNumber()const
    {
        return std::numeric_limits<lua_Number>::min();
    }
    
    void WorldLuaVirtualMachine::init()
    {
        if (m_lua_State)
            unInit();
        
        
        
//        DEBUG_LOG_V(TAG, "Lua version: %s\n", LUA_VERSION);
        
#if defined(LUAI_THROW)
        DEBUG_LOG_V(TAG, "%s", "Lua LUAI_THROW: yes\n");
#else
        DEBUG_LOG_V(TAG, "%s", "Lua LUAI_THROW: no\n");
#endif
        
#if defined(LUA_USE_LONGJMP)
        DEBUG_LOG_V(TAG, "%s", "Lua LUA_USE_LONGJMP: yes\n");
#else
        DEBUG_LOG_V(TAG, "%s", "Lua LUA_USE_LONGJMP: no\n");
#endif
        
#if defined(__cplusplus)
        DEBUG_LOG_V(TAG, "%s", "Lua __cplusplus: yes\n");
#else
        DEBUG_LOG_V(TAG, "%s", "Lua __cplusplus: no\n");
#endif
        
#if defined(LUA_USE_ULONGJMP)
        DEBUG_LOG_V(TAG, "%s", "Lua LUA_USE_ULONGJMP: yes\n");
#else
        DEBUG_LOG_V(TAG, "%s", "Lua LUA_USE_ULONGJMP: no\n");
#endif
        
        m_lua_State = luaL_newstate();
        luaL_checkversion(m_lua_State);
        
        DEBUG_LOG_V(TAG, "Lua version: %s\n", LUA_VERSION);
        
        luaL_openlibs(m_lua_State);
        
        luax_loadexts(m_lua_State);
        
        const char *paths[] =
        {
            "scripts",
            "scripts/?",
        };
        
        for (s32 i = 0; i < 2; ++i)
        {
            std::string bundlePath = BUNDLE_PATH();
            bundlePath.append(paths[i]);
            bundlePath.append("/?.lua");
            appendLuaPath(m_lua_State, bundlePath.c_str());
        }
        
        for (s32 i = 0; i < 2; ++i)
        {
            std::string bundlePath = DOCUMENT_BASEPATH();
            bundlePath.append("/");
            bundlePath.append(paths[i]);
            bundlePath.append("/?.lua");
            appendLuaPath(m_lua_State, bundlePath.c_str());
        }
        
        
#if defined(DEBUG) || defined (_DEBUG)
//        printWrappedClasses();
#endif
    }
    
    void WorldLuaVirtualMachine::unInit()
    {
        if( m_lua_State )
        {
            lua_gc(m_lua_State, LUA_GCCOLLECT, 0);
            lua_close( m_lua_State );
            
            m_lua_State = NULL;
        }
    }
    
    bool WorldLuaVirtualMachine::error(const char *desc)
    {
        int status = luaL_error(m_lua_State, "%s", desc);
        
        if(LUA_OK == status)
            return true;
        getError("", status);
        
        return false;
    }
    
    void WorldLuaVirtualMachine::getError(const char *code, int error)
    {
        std::string value;
        switch (error)
        {
            case LUA_YIELD:
                value = "(LUA_YIELD)";
                break;
            case LUA_ERRRUN:
                value = "(LUA_ERRRUN - a runtime error)";
                break;
            case LUA_ERRSYNTAX:
                value = "LUA_ERRSYNTAX";
                break;
            case LUA_ERRMEM:
                value = "(LUA_ERRMEM - memory allocation error. For such errors, Lua does not call the error handler function)";
                break;
            case LUA_ERRGCMM:
                value = "(LUA_ERRGCMM)";
                break;
            case LUA_ERRERR:
                value = "(LUA_ERRERR - error while running the error handler function)";
                break;
            default:
                break;
        }

        if(m_lua_State)
        {
            const char *msg = lua_tostring(m_lua_State, -1);
            l_message(NULL, msg);
//            DEBUG_LOG_E(TAG, "%s %s %s\n", value.c_str(), code, lua_tostring( m_lua_State, -1 ));
            lua_pop(m_lua_State, 1);  /* remove message */
        }
    }
    
    bool WorldLuaVirtualMachine::compile()
    {
        if(m_lua_State)
        {
//            int error_code = lua_pcall( m_lua_State, 0, LUA_MULTRET, 0 );
            int status = docall(m_lua_State, 0, LUA_MULTRET);
            
            if(LUA_OK == status)
                return true;
            getError("", status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
//            int error_code = lua_pcall(m_lua_State, 0, 0, 0);
            int status = docall(m_lua_State, 0, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, const char *_char)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            /* the first argument */
            lua_pushstring(m_lua_State, _char);
            
            /* call the function with 1 arguments, return 0 result */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, s32 _s32)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            /* the first argument */
            lua_pushnumber(m_lua_State, _s32);
            
            /* call the function with 1 arguments, return 0 result */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, f32 _btScalar)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            /* the first argument */
            lua_pushnumber(m_lua_State, _btScalar);
            
            /* call the function with 1 arguments, return 0 result */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }

    bool WorldLuaVirtualMachine::execute(const char *code, const Telegram &telegram, bool &returnValue)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *telegramTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Telegram" );
            SWIG_NewPointerObj(m_lua_State,(void *) &telegram, telegramTypeInfo,0);
            
            /* do the call (1 arguments, 1 result) */
//            int error_code = lua_pcall(m_lua_State, 1, 1, 0);
            int status = docall(m_lua_State, 1, 1);
            
            if(LUA_OK == status)
            {
                returnValue = lua_toboolean(m_lua_State, -1);
                lua_pop(m_lua_State, 1);
                return true;
            }
            getError(code, status);
        }

        return false;
    }
    
    
    bool WorldLuaVirtualMachine::execute(const char *code, Scene *pEntity)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *sceneTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Scene" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity, sceneTypeInfo,0);
            
            /* do the call (1 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Scene *scene, const char* str)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *sceneTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Scene" );
            SWIG_NewPointerObj(m_lua_State,(void *) scene, sceneTypeInfo,0);
            
            lua_pushstring(m_lua_State, str);
            
            /* do the call (1 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 2, 0, 0);
            int status = docall(m_lua_State, 2, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Scene *pEntity, f32 _btScalar)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *sceneTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Scene" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity,sceneTypeInfo,0);
            lua_pushnumber(m_lua_State, _btScalar);
            
            /* do the call (2 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 2, 0, 0);
            int status = docall(m_lua_State, 2, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Scene *pEntity, const Telegram &telegram, bool &returnValue)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *sceneTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Scene" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity,sceneTypeInfo,0);
            swig_type_info *telegramTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Telegram" );
            SWIG_NewPointerObj(m_lua_State,(void *) &telegram,telegramTypeInfo,0);
            
            /* do the call (2 arguments, 1 result) */
//            int error_code = lua_pcall(m_lua_State, 2, 1, 0);
            int status = docall(m_lua_State, 2, 1);
            
            if(LUA_OK == status)
            {
                returnValue = lua_toboolean(m_lua_State, -1);
                lua_pop(m_lua_State, 1);
                return true;
            }
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Node *pEntity)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *nodeTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Node" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity, nodeTypeInfo,0);
            
            /* do the call (1 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Node *pEntity, f32 _btScalar)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *nodeTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Node" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity, nodeTypeInfo,0);
            lua_pushnumber(m_lua_State, _btScalar);
            
            /* do the call (2 arguments, 1 result) */
//            int error_code = lua_pcall(m_lua_State, 2, 0, 0);
            int status = docall(m_lua_State, 2, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Node *pEntity, const Telegram &telegram, bool &returnValue)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *nodeTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Node" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity, nodeTypeInfo,0);
            swig_type_info *telegramTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Telegram" );
            SWIG_NewPointerObj(m_lua_State,(void *) &telegram, telegramTypeInfo,0);
            
            /* do the call (2 arguments, 1 result) */
//            int error_code = lua_pcall(m_lua_State, 2, 1, 0);
            int status = docall(m_lua_State, 2, 1);
            
            if(LUA_OK == status)
            {
                returnValue = lua_toboolean(m_lua_State, -1);
                lua_pop(m_lua_State, 1);
                return true;
            }
            
            getError(code, status);
        }
        return false;
    }
    
//    void PushFloatArray(float *array, int size)
//    
//    {
//        
//        lua_newtable(state);
//        
//        
//        
//        for (int i = 0; i < size; i++)
//            
//        {
//            
//            lua_pushnumber(state, i); // push the index
//            
//            lua_pushnumber(state, array[i]); // push the value at 'i'
//            
//            
//            
//            // the table is now at -3 on the stack. This tells Lua
//            
//            // to put "stack[-1]" at "stack[-2]" and pop them off,
//            
//            // leaving the table at the top of the stack
//            
//            lua_settable(state, -3);
//            
//        }
//        
//    }
//
    
    bool WorldLuaVirtualMachine::execute(const char *code, DeviceTouch **touches)
    {
//        DEBUG_LOG_V(TAG, "WorldLuaVirtualMachine::execute(%s)\n", code);
        
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            s32 i;
            lua_newtable(m_lua_State);
            for (i = 0; i < DeviceTouch::MAX_TOUCHES; i++){
                swig_type_info * deviceTouchTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__DeviceTouch" );
                SWIG_NewPointerObj(m_lua_State,(void *) touches[i],deviceTouchTypeInfo,0);
                lua_rawseti(m_lua_State,-2,i+1);/* -1 is the number, -2 is the table*/
            }
            
            /* call the function with 1 arguments, return 0 result */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Scene *pEntity, DeviceTouch **touches)
    {
        //        DEBUG_LOG_V(TAG, "WorldLuaVirtualMachine::execute(%s)\n", code);
        
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *sceneTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Scene" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity,sceneTypeInfo,0);
            
            s32 i;
            lua_newtable(m_lua_State);
            for (i = 0; i < DeviceTouch::MAX_TOUCHES; i++)
            {
                swig_type_info * deviceTouchTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__DeviceTouch" );
                SWIG_NewPointerObj(m_lua_State,(void *) touches[i],deviceTouchTypeInfo,0);
                lua_rawseti(m_lua_State,-2,i+1);/* -1 is the number, -2 is the table*/
            }
            
            /* call the function with 2 arguments, return 0 result */
//            int error_code = lua_pcall(m_lua_State, 2, 0, 0);
            int status = docall(m_lua_State, 2, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Node *node1, Node *node2, const btManifoldPoint& pt)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *nodeTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Node" );
            swig_type_info *manifoldTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_btManifoldPoint" );
            
            
            SWIG_NewPointerObj(m_lua_State,(void *) node1,nodeTypeInfo,0);
            SWIG_NewPointerObj(m_lua_State,(void *) node2,nodeTypeInfo,0);
            SWIG_NewPointerObj(m_lua_State,(void *) &pt,manifoldTypeInfo,0);
            
            /* do the call (3 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 3, 0, 0);
            int status = docall(m_lua_State, 3, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Node *node1, Node *node2, const btDispatcherInfo &dispatchInfo)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *nodeTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Node" );
            swig_type_info *dispatcherInfoTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_btDispatcherInfo" );
            
            
            SWIG_NewPointerObj(m_lua_State,(void *) node1,nodeTypeInfo,0);
            SWIG_NewPointerObj(m_lua_State,(void *) node2,nodeTypeInfo,0);
            SWIG_NewPointerObj(m_lua_State,(void *) &dispatchInfo,dispatcherInfoTypeInfo,0);
            
            /* do the call (3 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 3, 0, 0);
            int status = docall(m_lua_State, 3, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, const PhysicsRayContact &rayContact)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            swig_type_info * physicsRayContactTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__PhysicsRayContact" );
            SWIG_NewPointerObj(m_lua_State,(void *) &rayContact,physicsRayContactTypeInfo,0);
            
            /* do the call (1 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, const btAlignedObjectArray<njli::PhysicsRayContact*> &rayContacts)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            s32 i;
            lua_newtable(m_lua_State);
            for (i = 0; i < rayContacts.size(); i++){
                swig_type_info * physicsRayContactTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__PhysicsRayContact" );
                SWIG_NewPointerObj(m_lua_State,(void *) rayContacts[i], physicsRayContactTypeInfo, 0);
                lua_rawseti(m_lua_State,-2,i+1);/* -1 is the number, -2 is the table*/
            }
            
            /* call the function with 1 arguments, return 0 result */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char* code, s32 width, s32 height, s32 orientation)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            lua_pushnumber(m_lua_State, width);
            lua_pushnumber(m_lua_State, height);
            lua_pushnumber(m_lua_State, orientation);
            
            /* do the call (2 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 3, 0, 0);
            int status = docall(m_lua_State, 3, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Action *action)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info * actionTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Action" );
            SWIG_NewPointerObj(m_lua_State,(void *) action,actionTypeInfo,0);
            
            /* do the call (1 arguments, 0 result) */
//            int error_code = lua_pcall(m_lua_State, 1, 0, 0);
            int status = docall(m_lua_State, 1, 0);
            
            if(LUA_OK == status)
                return true;
            
            getError(code, status);
        }
        
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Action *pEntity, f32 _btScalar)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info * actionTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Action" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity,actionTypeInfo,0);
            
            lua_pushnumber(m_lua_State, _btScalar);
            
            /* do the call (2 arguments, 1 result) */
//            int error_code = lua_pcall(m_lua_State, 2, 0, 0);
            int status = docall(m_lua_State, 2, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
        
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Node *pEntity, DeviceTouch **touches)
    {
        //        DEBUG_LOG_V(TAG, "WorldLuaVirtualMachine::execute(%s)\n", code);
        
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *sceneTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Node" );
            SWIG_NewPointerObj(m_lua_State,(void *) pEntity,sceneTypeInfo,0);
            
            s32 i;
            lua_newtable(m_lua_State);
            for (i = 0; i < DeviceTouch::MAX_TOUCHES; i++)
            {
                swig_type_info * deviceTouchTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__DeviceTouch" );
                SWIG_NewPointerObj(m_lua_State,(void *) touches[i],deviceTouchTypeInfo,0);
                lua_rawseti(m_lua_State,-2,i+1);/* -1 is the number, -2 is the table*/
            }
            
            /* call the function with 2 arguments, return 0 result */
            //            int error_code = lua_pcall(m_lua_State, 2, 0, 0);
            int status = docall(m_lua_State, 2, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        return false;
    }
    
    bool WorldLuaVirtualMachine::execute(const char *code, Node *node, const char* str)
    {
        if(m_lua_State)
        {
            lua_getglobal(m_lua_State, code);
            
            swig_type_info *sceneTypeInfo = SWIG_TypeQuery( m_lua_State, "_p_njli__Node" );
            SWIG_NewPointerObj(m_lua_State,(void *) node, sceneTypeInfo,0);
            
            lua_pushstring(m_lua_State, str);
            
            /* do the call (2 arguments, 0 result) */
            //            int error_code = lua_pcall(m_lua_State, 2, 0, 0);
            int status = docall(m_lua_State, 2, 0);
            
            if(LUA_OK == status)
                return true;
            getError(code, status);
        }
        
        return false;
    }
    
}
