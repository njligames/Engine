//
//  ShaderProgram.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__ShaderProgram__
#define __JLIGameEngineTest__ShaderProgram__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "JLIFactoryTypes.h"
#include "lua.hpp"

#include <vector>
#include <map>
#include "btTransform.h"

typedef void (*GLInfoFunction)(u32 program,
    s32 pname,
    s32* params);

typedef void (*GLLogFunction)(u32 program,
    s32 bufsize,
    s32* length,
    s8* infolog);

namespace njli {
class ShaderProgramBuilder;
class Camera;
    class Geometry;
//    class btTransform;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
ShaderProgram : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class Geometry;
    friend class MaterialProperty;

protected:
    ShaderProgram();
    ShaderProgram(const AbstractBuilder&);
    ShaderProgram(const ShaderProgram&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

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
    static ShaderProgram** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(ShaderProgram * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static ShaderProgram* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static ShaderProgram* create(const ShaderProgramBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static ShaderProgram* clone(const ShaderProgram& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static ShaderProgram* copy(const ShaderProgram& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(ShaderProgram * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(ShaderProgram & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for ShaderProgram

    void saveSource(const std::string& vertexShaderSource,
        const std::string& fragmentShaderSource);

    bool isLinked() const;

    /**
         *  <#Description#>
         */
    void unLoadGPU();

protected:
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool link();

    /**
         *  <#Description#>
         *
         *  @param attributeName <#attributeName description#>
         */
    bool bindAttribute(const char* attributeName);

    /**
         *  <#Description#>
         *
         *  @param attributeName <#attributeName description#>
         *
         *  @return <#return value description#>
         */
    u32 getAttributeLocation(const char* attributeName) const;

public:
    bool setUniformValue(const char *uniformName, s32 value);
    bool getUniformValue(const char *uniformName, s32 &value);
    
    bool setUniformValue(const char *uniformName, const btTransform &value, bool transpose = false);
    bool getUniformValue(const char *uniformName, btTransform &value);
    /**
         *  <#Description#>
         *
         *  @param uniformName <#uniformName description#>
         *
         *  @return <#return value description#>
         */
    u32 getUniformLocation(const char* uniformName) ;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* vertexShaderLog() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* fragmentShaderLog() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char* programLog() const;

    /**
         *  <#Description#>
         */
    bool use();

    /**
         *  <#Description#>
         *
         *  @param fileContent <#fileContent description#>
         *  @param type        <#type description#>
         *
         *  @return <#return value description#>
         */
    bool compile(const char* fileContent, njliShaderType type);

    bool compileShader(s32 * shader, const u32 type, const char* source);
    const char* logForOpenGLObject(u32 object, GLInfoFunction infoFunc, GLLogFunction logFunc) const;

    Geometry* getParent();
    const Geometry* getParent() const;
private:
    s32 m_Program;
    s32 m_vertShader;
    s32 m_fragShader;

    std::string m_VertexShaderSource;
    std::string m_FragmentShaderSource;
    
    typedef std::map<std::string, s32> UniformValueMap;
    typedef std::pair<std::string, s32> UniformValuePair;
    UniformValueMap m_uniformValueMap;
    float *m_mat4Buffer;
};
}

#endif /* defined(__JLIGameEngineTest__ShaderProgram__) */
