//
//  WorldPythonVirtualMachine.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 8/24/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldPythonVirtualMachine.h"
#include "File.h"

//#include <Python/Python.h>
#include <dlfcn.h>

//#ifndef Py_PYTHON_H
//#error Python headers needed to compile C extensions, please install development version of Python.
//#endif

namespace njli
{
    WorldPythonVirtualMachine::WorldPythonVirtualMachine()
    {
        init();
    }
    
    WorldPythonVirtualMachine::~WorldPythonVirtualMachine()
    {
        unInit();
    }
    
    const char *WorldPythonVirtualMachine::getClassName()const
    {
        return "WorldPythonVirtualMachine";
    }
    
    s32 WorldPythonVirtualMachine::getType()const
    {
        return JLI_OBJECT_TYPE_WorldPythonVirtualMachine;
    }
    
    WorldPythonVirtualMachine::operator std::string() const
    {
        return "TODO";
    }
    
    void WorldPythonVirtualMachine::reset()
    {
    }
    
    void WorldPythonVirtualMachine::printStack()
    {
    }
    
    void WorldPythonVirtualMachine::loadFile(const char *filePath)
    {
    }
    
    void WorldPythonVirtualMachine::loadString(const char *code)
    {
    }
    
    bool WorldPythonVirtualMachine::execute(const char *)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, s32)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, f32)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, const Telegram &, bool &)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Scene *)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Scene *, f32)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Scene *, const Telegram &, bool &)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Node *)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Node *, f32)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Node *, const Telegram &, bool &)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *code, DeviceTouch **m_CurrentTouches)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Node *, Node *, const btManifoldPoint&)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Node *, Node *, const btDispatcherInfo&)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, const PhysicsRayContact&)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, const btAlignedObjectArray<njli::PhysicsRayContact*> &rayContacts)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Action *)
    {
        return false;
    }
    
    bool WorldPythonVirtualMachine::execute(const char *, Action *, f32)
    {
        return false;
    }
    
    void WorldPythonVirtualMachine::init()
    {
//        putenv((char *)"PYTHONOPTIMIZE=1");
//        putenv((char *)"PYTHONDONTWRITEBYTECODE=1");
//        
//        static char python_home[2048];
//        sprintf(python_home, "%s/Library/Python.framework/Resources", RESOURCE_PATH());
//        
////        const size_t cSize = strlen(python_home)+1;
////        m_wpython_home = new wchar_t[cSize];
////        mbstowcs (m_wpython_home, python_home, cSize);
//        
//        m_wpython_home = _Py_char2wchar(python_home, NULL);
//        Py_SetPythonHome(m_wpython_home);
//        
//        // iOS provides a specific directory for temp files.
//        static char tmp_path[2048];
//        sprintf(tmp_path, "TMP=%s/tmp", RESOURCE_PATH());
//        putenv((char *)tmp_path);
//        
//        Py_Initialize();
    }
    
    void WorldPythonVirtualMachine::unInit()
    {
//        PyMem_RawFree(m_wpython_home);
    }
    
    void WorldPythonVirtualMachine::getError(const char *code, int error)
    {
    }
    
    void WorldPythonVirtualMachine::compile()
    {
    }
}
