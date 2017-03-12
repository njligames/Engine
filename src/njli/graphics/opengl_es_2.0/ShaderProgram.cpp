//
//  ShaderProgram.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "ShaderProgram.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "ShaderProgramBuilder.h"
#include "GLPlatform.h"
#include "Camera.h"

#include "Log.h"
#define TAG "ShaderProgram.cpp"
#define FORMATSTRING "{\"njli::ShaderProgram\":[]}"
#include "btPrint.h"
//#include "btTransform.h"
#include "JsonJLI.h"

enum njliGLSLVarType
{
    JLI_GL_FLOAT = GL_FLOAT,
    JLI_GL_FLOAT_VEC2 = GL_FLOAT_VEC2,
    JLI_GL_FLOAT_VEC3 = GL_FLOAT_VEC3,
    JLI_GL_FLOAT_VEC4 = GL_FLOAT_VEC4,
    JLI_GL_INT = GL_INT,
    JLI_GL_INT_VEC2 = GL_INT_VEC2,
    JLI_GL_INT_VEC3 = GL_INT_VEC3,
    JLI_GL_INT_VEC4 = GL_INT_VEC4,
    JLI_GL_BOOL = GL_BOOL,
    JLI_GL_BOOL_VEC2 = GL_BOOL_VEC2,
    JLI_GL_BOOL_VEC3 = GL_BOOL_VEC3,
    JLI_GL_BOOL_VEC4 = GL_BOOL_VEC4,
    JLI_GL_FLOAT_MAT2 = GL_FLOAT_MAT2,
    JLI_GL_FLOAT_MAT3 = GL_FLOAT_MAT3,
    JLI_GL_FLOAT_MAT4 = GL_FLOAT_MAT4,
    JLI_GL_SAMPLER_2D = GL_SAMPLER_2D,
    JLI_GL_SAMPLER_CUBE = GL_SAMPLER_CUBE
};

static const char *getGLSLVarTypeName(njliGLSLVarType var)
{
    switch (var)
    {
        case JLI_GL_FLOAT: return "GL_FLOAT";
        case JLI_GL_FLOAT_VEC2: return "GL_FLOAT_VEC2";
        case JLI_GL_FLOAT_VEC3: return "GL_FLOAT_VEC3";
        case JLI_GL_FLOAT_VEC4: return "GL_FLOAT_VEC4";
        case JLI_GL_INT: return "GL_INT";
        case JLI_GL_INT_VEC2: return "GL_INT_VEC2";
        case JLI_GL_INT_VEC3: return "GL_INT_VEC3";
        case JLI_GL_INT_VEC4: return "GL_INT_VEC4";
        case JLI_GL_BOOL: return "GL_BOOL";
        case JLI_GL_BOOL_VEC2: return "GL_BOOL_VEC2";
        case JLI_GL_BOOL_VEC3: return "GL_BOOL_VEC3";
        case JLI_GL_BOOL_VEC4: return "GL_BOOL_VEC4";
        case JLI_GL_FLOAT_MAT2: return "GL_FLOAT_MAT2";
        case JLI_GL_FLOAT_MAT3: return "GL_FLOAT_MAT3";
        case JLI_GL_FLOAT_MAT4: return "GL_FLOAT_MAT4";
        case JLI_GL_SAMPLER_2D: return "GL_SAMPLER_2D";
        case JLI_GL_SAMPLER_CUBE: return "GL_SAMPLER_CUBE";
        default:
            return "UNKNOW UNIFORM VARIABLE";
    }
}

static void log_v_fixed_length(const GLchar* source, const GLint length) {
    if (LOGGING_ON) {
        char log_buffer[length + 1];
        memcpy(log_buffer, source, length);
        log_buffer[length] = '\0';
        
//        DEBUG_LOG_V(TAG, "<glGetShaderSource>\n%s\n</glGetShaderSource>", log_buffer);
    }
}

static void log_shader_info_log(GLuint shader_object_id) {
    if (LOGGING_ON) {
        DEBUG_ASSERT_PRINT(glIsShader(shader_object_id), "%s:%d", "Not a shader", shader_object_id);
        
        GLint log_length = 0;
        glGetShaderiv(shader_object_id, GL_INFO_LOG_LENGTH, &log_length);DEBUG_GL_ERROR_WRITE("glGetShaderiv");
        if(log_length > 0)
        {
            GLchar log_buffer[log_length];
            glGetShaderInfoLog(shader_object_id, log_length, NULL, log_buffer);DEBUG_GL_ERROR_WRITE("glGetShaderInfoLog");
            
            DEBUG_LOG_PRINT_E(TAG, "The glGetShaderiv log = `%s`", log_buffer);
        }
    }
}

static void log_program_info_log(GLuint program_object_id) {
    if (LOGGING_ON) {
        DEBUG_ASSERT_PRINT(glIsProgram(program_object_id), "%s:%d", "Not a shader", program_object_id);
        
        GLint log_length;
        glGetProgramiv(program_object_id, GL_INFO_LOG_LENGTH, &log_length);DEBUG_GL_ERROR_WRITE("glGetProgramiv");
        if(log_length > 1)
        {
            GLchar log_buffer[log_length];
            glGetProgramInfoLog(program_object_id, log_length, NULL, log_buffer);DEBUG_GL_ERROR_WRITE("glGetProgramInfoLog");
            DEBUG_LOG_PRINT_E(TAG, "The glGetProgramiv log(%d) = `%s`", log_length, log_buffer);
        }
    }
}

static GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length) {
    DEBUG_ASSERT(source != NULL);
    DEBUG_ASSERT(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);
    GLuint shader_object_id = glCreateShader(type);DEBUG_GL_ERROR_WRITE("glCreateShader");
    
//    log_shader_info_log(shader_object_id);
    GLint compile_status;
    
    DEBUG_ASSERT(shader_object_id != 0);
//    DEBUG_LOG_V("compile_shader", "id=%d", shader_object_id);
    
    GLchar**str = new GLchar*[1];
    str[0] = new GLchar[length];
    strcpy(str[0], source);
    
//    DEBUG_LOG_V(TAG, "source : %s", source);
    
    glShaderSource(shader_object_id, 1, (const GLchar**)&(str[0]), NULL);DEBUG_GL_ERROR_PRINT("glShaderSource", "id:%d,source:%s",shader_object_id,str[0]);
    log_shader_info_log(shader_object_id);
    glCompileShader(shader_object_id);DEBUG_GL_ERROR_WRITE("glCompileShader");
    log_shader_info_log(shader_object_id);
    glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &compile_status);DEBUG_GL_ERROR_WRITE("glGetShaderiv");
    log_shader_info_log(shader_object_id);
    
    delete [] str[0];str[0]=NULL;
    delete [] str;str=NULL;
    
    if (false && LOGGING_ON) {
        DEBUG_LOG_D(TAG, "Results of compiling shader source = %s", (compile_status==GL_TRUE)?"true":"false");
        GLsizei bufSize = 0;
        GLsizei _length = 0;
        glGetShaderiv(shader_object_id, GL_SHADER_SOURCE_LENGTH, &bufSize);DEBUG_GL_ERROR_WRITE("glGetShaderiv");
        log_shader_info_log(shader_object_id);
        DEBUG_ASSERT(bufSize>0);
        GLchar *the_source = new GLchar[bufSize];
        glGetShaderSource(shader_object_id, bufSize, &_length, the_source);DEBUG_GL_ERROR_WRITE("glGetShaderSource");
//        log_shader_info_log(shader_object_id);
        log_v_fixed_length(the_source, _length);
        delete [] the_source;the_source=NULL;
        
    }
    
    DEBUG_ASSERT(compile_status != 0);
    
    return shader_object_id;
}

static GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader) {
    GLuint program_object_id = glCreateProgram();DEBUG_GL_ERROR_WRITE("glCreateProgram");
//    log_program_info_log(program_object_id);
    
    
    DEBUG_ASSERT(program_object_id != 0);
//    DEBUG_LOG_V("link_program", "id=%d", program_object_id);
    
    glAttachShader(program_object_id, vertex_shader);DEBUG_GL_ERROR_WRITE("glAttachShader");
//    log_shader_info_log(vertex_shader);
//    log_program_info_log(program_object_id);
    glAttachShader(program_object_id, fragment_shader);DEBUG_GL_ERROR_WRITE("glAttachShader");
//    log_shader_info_log(fragment_shader);
//    log_program_info_log(program_object_id);
    glLinkProgram(program_object_id);DEBUG_GL_ERROR_WRITE("glLinkProgram");
//    log_program_info_log(program_object_id);
    
    
    return program_object_id;
}

static GLint validate_program(const GLuint program) {
    if (LOGGING_ON) {
        int validate_status;
        
        glValidateProgram(program);DEBUG_GL_ERROR_WRITE("glValidateProgram");
//        log_program_info_log(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_status);DEBUG_GL_ERROR_WRITE("glGetProgramiv");
        DEBUG_LOG_D(TAG, "Results of validating program = %s\n", (validate_status==GL_TRUE)?"true":"false");
//        log_program_info_log(program);
        return validate_status;
    }
    
    return GL_TRUE;
}

namespace njli
{
    ShaderProgram::ShaderProgram():
    AbstractFactoryObject(this),
    m_Program(-1),//glCreateProgram()),
    m_vertShader(-1),
    m_fragShader(-1),
    m_VertexShaderSource(""),
    m_FragmentShaderSource(""),
    m_mat4Buffer(new float[16])
    {
        enableRenderObject();
        m_uniformValueMap.clear();
    }
    
    ShaderProgram::ShaderProgram(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_Program(-1),//glCreateProgram()),
    m_vertShader(-1),
    m_fragShader(-1),
    m_VertexShaderSource(""),
    m_FragmentShaderSource(""),
    m_mat4Buffer(new float[16])
    {
        enableRenderObject();
        m_uniformValueMap.clear();
    }
    
    ShaderProgram::ShaderProgram(const ShaderProgram &copy):
    AbstractFactoryObject(this),
    m_Program(-1),//glCreateProgram()),
    m_vertShader(-1),
    m_fragShader(-1),
    m_VertexShaderSource(""),
    m_FragmentShaderSource(""),
    m_mat4Buffer(new float[16])
    {
        enableRenderObject();
        m_uniformValueMap.clear();
    }
    
    ShaderProgram::~ShaderProgram()
    {
        delete [] m_mat4Buffer;
        m_mat4Buffer = NULL;
        
        unLoadGPU();
    }
    
    ShaderProgram &ShaderProgram::operator=(const ShaderProgram &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	ShaderProgram::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void ShaderProgram::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *ShaderProgram::getClassName()const
    {
        return "ShaderProgram";
    }
    
    s32 ShaderProgram::getType()const
    {
        return ShaderProgram::type();
    }
    
    ShaderProgram::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    ShaderProgram **ShaderProgram::createArray(const u32 size)
    {
        return (ShaderProgram**)World::getInstance()->getWorldFactory()->createArray(ShaderProgram::type(), size);
    }
    
    void ShaderProgram::destroyArray(ShaderProgram **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    ShaderProgram *ShaderProgram::create()
    {
        return dynamic_cast<ShaderProgram*>(World::getInstance()->getWorldFactory()->create(ShaderProgram::type()));
    }
    
    ShaderProgram *ShaderProgram::create(const ShaderProgramBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<ShaderProgram*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    ShaderProgram *ShaderProgram::clone(const ShaderProgram &object)
    {
        return dynamic_cast<ShaderProgram*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    ShaderProgram *ShaderProgram::copy(const ShaderProgram &object)
    {
        return dynamic_cast<ShaderProgram*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void ShaderProgram::destroy(ShaderProgram *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void ShaderProgram::load(ShaderProgram &object, lua_State *L, int index)
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
                ShaderProgram::load(object, L, -2);
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
//                    DEBUG_ASSERT(lua_isuserdata(L,index));
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
    
    u32 ShaderProgram::type()
    {
        return JLI_OBJECT_TYPE_ShaderProgram;
    }
    
    bool ShaderProgram::compile(const char *source, njliShaderType type)
    {
        bool ret = false;
        
        switch (type) {
            case JLI_SHADER_TYPE_FRAGMENT:
            {
                if (-1 != m_fragShader)
                {
                    glDeleteShader(m_fragShader);DEBUG_GL_ERROR_WRITE("glDeleteShader");
                }
                
                compileShader(&m_fragShader, GL_FRAGMENT_SHADER, source);
                DEBUG_ASSERT(glIsShader(m_fragShader));
                ret = true;

            }
                break;
            case JLI_SHADER_TYPE_VERTEX:
            {
                if (-1 != m_vertShader)
                {
                    glDeleteShader(m_vertShader);DEBUG_GL_ERROR_WRITE("glDeleteShader");
                }
                
                compileShader(&m_vertShader, GL_VERTEX_SHADER, source);
                DEBUG_ASSERT(glIsShader(m_vertShader));
                ret = true;

            }
                break;
            default:
                break;
        }
        return ret;
    }
    
    bool ShaderProgram::bindAttribute(const char *attributeName)
    {
        s32 location = getAttributeLocation(attributeName);
        GLint currentProgram=0;
        
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        DEBUG_ASSERT(currentProgram != 0);
        
        DEBUG_ASSERT(m_Program == currentProgram);
        DEBUG_ASSERT(glIsProgram(m_Program));
        
        DEBUG_ASSERT_PRINT(-1 != location, "The named attribute variable (%s) is not an active attribute in the specified program object or if name starts with the reserved prefix \"gl_\"", attributeName);
        
        glBindAttribLocation(m_Program, location, attributeName);
        DEBUG_GL_ERROR_PRINT("glBindAttribLocation", "glBindAttribLocation(%d, %d, %s)",currentProgram,location, attributeName);
        
        return true;
    }
    
    u32 ShaderProgram::getAttributeLocation(const char *attributeName)const
    {
        GLint currentProgram=0;
        
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        
        DEBUG_ASSERT(m_Program == currentProgram);
        DEBUG_ASSERT(currentProgram != 0);
        
        s32 location = glGetAttribLocation(m_Program, attributeName);
        DEBUG_GL_ERROR_WRITE("glGetAttribLocation\n");
        
        DEBUG_ASSERT_PRINT(-1 != location, "The named attribute variable (%s) is not an active attribute in the specified program object or if name starts with the reserved prefix \"gl_\"", attributeName);
        
        return location;
    }
    
    bool ShaderProgram::setUniformValue(const char *uniformName, s32 value)
    {
        s32 location = getUniformLocation(uniformName);
        GLint currentProgram=0;
        
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        DEBUG_ASSERT(currentProgram != 0);
        
        DEBUG_ASSERT(m_Program == currentProgram);
        DEBUG_ASSERT(glIsProgram(m_Program));
        
        if (location != -1)
        {
            s32 tvalue=value;
            if(getUniformValue(uniformName, tvalue))
            {
                if(tvalue != value)
                {
                    glUniform1i(location, value);
                    DEBUG_GL_ERROR_PRINT("glUniform1i", "glUniform1i(%s, %d)",uniformName,value);
                }
                
                return true;
            }
        }
        return false;
    }
    
    bool ShaderProgram::getUniformValue(const char *uniformName, s32 &value)
    {
        s32 location = getUniformLocation(uniformName);
        GLint currentProgram=0;
        
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        DEBUG_ASSERT(currentProgram != 0);
        
        DEBUG_ASSERT(m_Program == currentProgram);
        DEBUG_ASSERT(glIsProgram(m_Program));
        
        if (location != -1)
        {
            glGetUniformiv(currentProgram, location, &value);
            DEBUG_GL_ERROR_PRINT("glGetUniformiv", "glGetUniformiv(%d, %s)",currentProgram,uniformName);
            
            return true;
        }
        return false;
    }
    
    bool ShaderProgram::setUniformValue(const char *uniformName, const btTransform &value, bool transpose)
    {
        s32 location = getUniformLocation(uniformName);
        GLint currentProgram=0;
        
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        DEBUG_ASSERT(currentProgram != 0);
        
        DEBUG_ASSERT(m_Program == currentProgram);
        DEBUG_ASSERT(glIsProgram(m_Program));
        
        if (location != -1)
        {
            btTransform tvalue=value;
            if(getUniformValue(uniformName, tvalue))
            {
                if(tvalue != value)
                {
                    value.getOpenGLMatrix(m_mat4Buffer);
                    glUniformMatrix4fv(location,
                                       1,
                                       (transpose)?GL_TRUE:GL_FALSE,
                                       m_mat4Buffer);
//                    DEBUG_GL_ERROR_PRINT("glUniformMatrix4fv", "glUniformMatrix4fv(%s, %d, %s)",
//                                         uniformName,
//                                         transpose,
//                                         toJsonString(value).c_str());
                }
                
                return true;
            }
            
        }
        return false;
    }
    
    bool ShaderProgram::getUniformValue(const char *uniformName, btTransform &value)
    {
        s32 location = getUniformLocation(uniformName);
        GLint currentProgram=0;
        
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        DEBUG_ASSERT(currentProgram != 0);
        
        DEBUG_ASSERT(m_Program == currentProgram);
        DEBUG_ASSERT(glIsProgram(m_Program));
        
        if (location != -1)
        {
            glGetUniformfv(currentProgram, location, m_mat4Buffer);
//            DEBUG_GL_ERROR_PRINT("glGetUniformfv", "glGetUniformfv(%s, %s)",
//                                 uniformName,
//                                 toJsonString(value).c_str());
            value.setFromOpenGLMatrix(m_mat4Buffer);
            
            return true;
        }
        return false;
    }
    
    u32 ShaderProgram::getUniformLocation(const char *uniformName)
    {
        GLint currentProgram=0;
        
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        DEBUG_GL_ERROR_WRITE("glGetIntegerv");
        
//        DEBUG_ASSERT(m_Program == currentProgram);
        
        s32 location = -1;
        
        if(m_Program == currentProgram)
        {
            UniformValueMap::iterator iter = m_uniformValueMap.find(std::string(uniformName));
            if(iter != m_uniformValueMap.end())
            {
                location = iter->second;
            }
            else
            {
                DEBUG_ASSERT(glIsProgram(m_Program));
                
                location = glGetUniformLocation(currentProgram, uniformName);
                DEBUG_GL_ERROR_PRINT("glGetUniformLocation\n", "%d, %s",m_Program,uniformName);
                
                m_uniformValueMap.insert(UniformValuePair(std::string(uniformName), location));
            }
            
            DEBUG_ASSERT_PRINT(-1 != location, "The named uniform variable (%s) is not an active uniform in the specified program object or if name starts with the reserved prefix \"gl_\"", uniformName);
        }
        
        
        
        return location;
    }
    
    bool ShaderProgram::link()
    {
        DEBUG_ASSERT(!isLinked());
        
        if(!compile(m_VertexShaderSource.c_str(), JLI_SHADER_TYPE_VERTEX))
        {
            if(-1 != m_vertShader)
                glDeleteShader(m_vertShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
            m_vertShader = -1;
            
            if(-1 != m_fragShader)
                glDeleteShader(m_fragShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
            m_fragShader = -1;
            
            DEBUG_LOG_PRINT_E(TAG, "Vertex log: `%s`\n", vertexShaderLog());
            return false;
        }
        
        if(!compile(m_FragmentShaderSource.c_str(), JLI_SHADER_TYPE_FRAGMENT))
        {
            DEBUG_LOG_PRINT_E(TAG, "Vertex log: `%s`\n", fragmentShaderLog());
            
            if(-1 != m_vertShader)
                glDeleteShader(m_vertShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
            m_vertShader = -1;
            
            if(-1 != m_fragShader)
                glDeleteShader(m_fragShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
            m_fragShader = -1;
            
            return false;
        }
        
        DEBUG_ASSERT(glIsShader(m_vertShader));
        DEBUG_ASSERT(glIsShader(m_fragShader));
        m_Program = link_program(m_vertShader, m_fragShader);
        DEBUG_ASSERT(glIsProgram(m_Program));
        
        GLint link_status;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &link_status);DEBUG_GL_ERROR_WRITE("glGetProgramiv");
        //    log_program_info_log(program_object_id);
        
        if (LOGGING_ON) {
            DEBUG_LOG_D(TAG, "Results of linking program = %s\n", (link_status==GL_TRUE)?"true":"false");
            log_program_info_log(m_Program);
        }
        
        if(GL_FALSE == link_status)
        {
            if(-1 != m_vertShader)
                glDeleteShader(m_vertShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
            m_vertShader = -1;
            
            if(-1 != m_fragShader)
                glDeleteShader(m_fragShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
            m_fragShader = -1;
            
            if(-1 != m_Program)
                glDeleteProgram(m_Program);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
            m_Program = -1;
            
            return false;
        }
        
        GLint status = validate_program(m_Program);
        
        if( LOGGING_ON && GL_TRUE == status)
        {
            GLint active = 0;
            GLsizei length = 0;
            GLsizei size = 0;
            GLenum type = 0;
            GLint nameMaxLength = 0;
            GLchar *variableName = NULL;
            
            glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &active);DEBUG_GL_ERROR_WRITE("glGetProgramiv\n");
            glGetProgramiv(m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nameMaxLength);DEBUG_GL_ERROR_WRITE("glGetProgramiv\n");
            
            variableName = new GLchar[nameMaxLength];
            for(GLuint index = 0; index < active; ++index)
            {
                glGetActiveUniform(m_Program, index, nameMaxLength, &length, &size, &type, variableName);DEBUG_GL_ERROR_WRITE("glGetActiveUniform\n");
//                DEBUG_LOG_V(TAG, "Uniform Variable Loaded: %s %s (size=%d)", getGLSLVarTypeName((njliGLSLVarType)type), variableName, size);
                
            }
            delete [] variableName;
            variableName=NULL;
            
            
            
            
            glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTES, &active);DEBUG_GL_ERROR_WRITE("glGetProgramiv\n");
            glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nameMaxLength);DEBUG_GL_ERROR_WRITE("glGetProgramiv\n");
            
            variableName = new GLchar[nameMaxLength];
            for(GLuint index = 0; index < active; ++index)
            {
                glGetActiveAttrib(m_Program, index, nameMaxLength, &length, &size, &type, variableName);DEBUG_GL_ERROR_WRITE("glGetActiveAttrib\n");

                
            }
            delete [] variableName;variableName=NULL;
        }
        

        
        if (status == GL_FALSE)
            return false;
        
        return true;
    }
    
    void ShaderProgram::saveSource(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
    {
        m_VertexShaderSource = vertexShaderSource;
        m_FragmentShaderSource = fragmentShaderSource;
        
        Geometry *geometry = getParent();
        if(NULL != geometry)
        {
            geometry->setupShader();
        }
    }
    
    bool ShaderProgram::isLinked()const
    {
        return (m_Program != -1);
    }
    
    bool ShaderProgram::use()
    {
        if(glIsProgram(m_Program))
        {
            glUseProgram(m_Program);
            return true;
        }
        return false;
    }
    
//    void ShaderProgram::unUse()
//    {
////        glUseProgram(0);DEBUG_GL_ERROR_WRITE("glUseProgram");
//    }
    
    const char *ShaderProgram::vertexShaderLog()const
    {
        return logForOpenGLObject(m_vertShader, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
    }
    
    const char *ShaderProgram::fragmentShaderLog()const
    {
        return logForOpenGLObject(m_fragShader, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
    }
    
    const char *ShaderProgram::programLog()const
    {
        return logForOpenGLObject(m_Program, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
    }
    
    void ShaderProgram::unLoadGPU()
    {
        if(-1 != m_vertShader)
            glDeleteShader(m_vertShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
        m_vertShader = -1;
        
        if(-1 != m_fragShader)
            glDeleteShader(m_fragShader);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
        m_fragShader = -1;
        
        if(-1 != m_Program)
            glDeleteProgram(m_Program);DEBUG_GL_ERROR_WRITE("glDeleteProgram\n");
        m_Program = -1;
        m_uniformValueMap.clear();
    }
    
    bool ShaderProgram::compileShader(s32 *shader, const GLenum type, const char *source)
    {
        *shader = compile_shader(type, source, (int)strlen(source) + 1);
        
        return GL_TRUE;
        
    }
    
    const char *ShaderProgram::logForOpenGLObject(u32 object, GLInfoFunction infoFunc, GLLogFunction logFunc)const
    {
        GLint logLength = 0, charsWritten = 0;
        
        infoFunc(object, GL_INFO_LOG_LENGTH, &logLength);DEBUG_GL_ERROR_WRITE("GLInfoFunction\n");
        if (logLength < 1)
            return NULL;
        
        static char logBytes[2048];
//        char *logBytes = new char[logLength];
        logFunc(object, logLength, &charsWritten, logBytes);DEBUG_GL_ERROR_WRITE("GLLogFunction\n");
        return logBytes;
//        std::string s(logBytes);
////        delete [] logBytes;logBytes=NULL;
//        return s.c_str();
    }
    
    Geometry* ShaderProgram::getParent()
    {
        return dynamic_cast<Geometry*>(AbstractDecorator::getParent());
    }
    
    const Geometry* ShaderProgram::getParent() const
    {
        return dynamic_cast<const Geometry*>(AbstractDecorator::getParent());
    }
}
