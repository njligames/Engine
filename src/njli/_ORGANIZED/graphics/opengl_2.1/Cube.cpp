//
//  Cube.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 2/2/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "Cube.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "CubeBuilder.h"
#include "GLPlatform.h"
#include "ShaderProgram.h"

#include "Log.h"
#define TAG "Cube.cpp"
#define FORMATSTRING "{\"njli::Cube\":[]}"
#include "btPrint.h"

//// Vertex Data
//cubeVertexData = new Vector3f[] {
//				new Vector3f (-1.0f, -1.0f, 1.0f),
//				new Vector3f (1.0f, -1.0f, 1.0f),
//				new Vector3f (1.0f, 1.0f, 1.0f),
//				new Vector3f (-1.0f, 1.0f, 1.0f),
//				new Vector3f (-1.0f, -1.0f, -1.0f),
//				new Vector3f (1.0f, -1.0f, -1.0f),
//				new Vector3f (1.0f, 1.0f, -1.0f),
//				new Vector3f (-1.0f, 1.0f, -1.0f)
//};
//
//// Normal Data for the Cube Verticies
//cubeNormalData = new Vector3f[] {
//				new Vector3f (-1.0f, -1.0f, 1.0f),
//				new Vector3f (1.0f, -1.0f, 1.0f),
//				new Vector3f (1.0f, 1.0f, 1.0f),
//				new Vector3f (-1.0f, 1.0f, 1.0f),
//				new Vector3f (-1.0f, -1.0f, -1.0f),
//				new Vector3f (1.0f, -1.0f, -1.0f),
//				new Vector3f (1.0f, 1.0f, -1.0f),
//				new Vector3f (-1.0f, 1.0f, -1.0f)
//};
//
//// Color Data for the Cube Verticies
//colorData = new int[] {
//				ColorToRgba32 (Color.Cyan),
//				ColorToRgba32 (Color.Cyan),
//				ColorToRgba32 (Color.DarkCyan),
//				ColorToRgba32 (Color.DarkCyan),
//				ColorToRgba32 (Color.Cyan),
//				ColorToRgba32 (Color.Cyan),
//				ColorToRgba32 (Color.DarkCyan),
//				ColorToRgba32 (Color.DarkCyan)
//};
//
//// Element Indicies for the Cube
//indicesVboData = new uint[] {
//				0, 1, 2, 2, 3, 0,
//				3, 2, 6, 6, 7, 3,
//				7, 6, 5, 5, 4, 7,
//				4, 0, 3, 3, 7, 4,
//				0, 1, 5, 5, 4, 0,
//				1, 5, 6, 6, 2, 1
//};







//				new Vector3f (-1.0f, -1.0f, 1.0f),
//				new Vector3f (1.0f, -1.0f, 1.0f),
//				new Vector3f (1.0f, 1.0f, 1.0f),
//				new Vector3f (-1.0f, 1.0f, 1.0f),
//				new Vector3f (-1.0f, -1.0f, -1.0f),
//				new Vector3f (1.0f, -1.0f, -1.0f),
//				new Vector3f (1.0f, 1.0f, -1.0f),
//				new Vector3f (-1.0f, 1.0f, -1.0f)

namespace njli
{
    static const btVector4 DEFAULTCOLOR = {1.0, 1.0, 1.0, 1.0};
    static const btVector4 REDCOLOR = {1.0, 0.0, 0.0, 1.0};
    static const btVector4 GREENCOLOR = {0.0, 1.0, 0.0, 1.0};
    static const btVector4 BLUECOLOR = {0.0, 0.0, 1.0, 1.0};
    
    /*
     // Back
     {{-1, 1, -1}, DEFAULTCOLOR, {1, 0}},
     {{-1, -1, -1}, DEFAULTCOLOR, {1, 1}},
     {{1, -1, -1}, DEFAULTCOLOR, {0, 1}},
     {{1, 1, -1}, DEFAULTCOLOR, {0, 0}},
     */
    const Geometry::TexturedColoredVertex CubeVertices[] =
    {
        // Front
        {{1, -1, 1}, DEFAULTCOLOR, {1, 0}, 1.0f, 0.0f},
        {{1, 1, 1}, DEFAULTCOLOR, {1, 1}, 1.0f, 0.0f},
        {{-1, 1, 1}, DEFAULTCOLOR, {0, 1}, 1.0f, 0.0f},
        {{-1, -1, 1}, DEFAULTCOLOR, {0, 0}, 1.0f, 0.0f},
        // Back
        {{1, -1, -1}, DEFAULTCOLOR, {1, 0}, 1.0f, 0.0f},
        {{-1, -1, -1}, DEFAULTCOLOR, {1, 1}, 1.0f, 0.0f},
        {{-1, 1, -1}, DEFAULTCOLOR, {0, 1}, 1.0f, 0.0f},
        {{1, 1, -1}, DEFAULTCOLOR, {0, 0}, 1.0f, 0.0f},
        // Left
        {{-1, -1, 1}, DEFAULTCOLOR, {1, 0}, 1.0f, 0.0f},
        {{-1, 1, 1}, DEFAULTCOLOR, {1, 1}, 1.0f, 0.0f},
        {{-1, 1, -1}, DEFAULTCOLOR, {0, 1}, 1.0f, 0.0f},
        {{-1, -1, -1}, DEFAULTCOLOR, {0, 0}, 1.0f, 0.0f},
        // Right
        {{1, -1, -1}, DEFAULTCOLOR, {1, 0}, 1.0f, 0.0f},
        {{1, 1, -1}, DEFAULTCOLOR, {1, 1}, 1.0f, 0.0f},
        {{1, 1, 1}, DEFAULTCOLOR, {0, 1}, 1.0f, 0.0f},
        {{1, -1, 1}, DEFAULTCOLOR, {0, 0}, 1.0f, 0.0f},
        // Top
        {{1, 1, 1}, DEFAULTCOLOR, {1, 0}, 1.0f, 0.0f},
        {{1, 1, -1}, DEFAULTCOLOR, {1, 1}, 1.0f, 0.0f},
        {{-1, 1, -1}, DEFAULTCOLOR, {0, 1}, 1.0f, 0.0f},
        {{-1, 1, 1}, DEFAULTCOLOR, {0, 0}, 1.0f, 0.0f},
        // Bottom
        {{1, -1, -1}, DEFAULTCOLOR, {1, 0}, 1.0f, 0.0f},
        {{1, -1, 1}, DEFAULTCOLOR, {1, 1}, 1.0f, 0.0f},
        {{-1, -1, 1}, DEFAULTCOLOR, {0, 1}, 1.0f, 0.0f},
        {{-1, -1, -1}, DEFAULTCOLOR, {0, 0}, 1.0f, 0.0f}
    };
    
    const GLubyte Indices[] =
    {
        // Front
        0, 1, 2,
        2, 3, 0,
        // Back
        4, 5, 6,
        6, 7, 4,
        // Left
        8, 9, 10,
        10, 11, 8,
        // Right
        12, 13, 14,
        14, 15, 12,
        // Top
        16, 17, 18,
        18, 19, 16,
        // Bottom
        20, 21, 22,
        22, 23, 20
    };
    
    Cube::Cube():
    Geometry(),
    m_CubeVerts(NULL),
    m_Indexes(NULL)
    {
        load();
    }
    
    Cube::Cube(const AbstractBuilder &builder):
    Geometry(builder),
    m_CubeVerts(NULL),
    m_Indexes(NULL)
    {
        load();
    }
    
    Cube::Cube(const Cube &copy):
    Geometry(copy),
    m_CubeVerts(NULL),
    m_Indexes(NULL)
    {
        load();
    }
    
    Cube::~Cube()
    {
        unLoad();
        unLoadGPU();
    }
    
    Cube &Cube::operator=(const Cube &rhs)
    {
        if(this != &rhs)
        {
            //TODO:implement..
        }
        return *this;
    }
    
    s32	Cube::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Cube::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Cube::getClassName()const
    {
        return "Cube";
    }
    
    s32 Cube::getType()const
    {
        return Cube::type();
    }
    
    Cube::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    Cube **Cube::createArray(const u32 size)
    {
        return (Cube**)World::getInstance()->getWorldFactory()->createArray(Cube::type(), size);
    }
    
    void Cube::destroyArray(Cube **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Cube *Cube::create()
    {
        return dynamic_cast<Cube*>(World::getInstance()->getWorldFactory()->create(Cube::type()));
    }
    
    Cube *Cube::create(const CubeBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Cube*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Cube *Cube::clone(const Cube &object)
    {
        return dynamic_cast<Cube*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Cube *Cube::copy(const Cube &object)
    {
        return dynamic_cast<Cube*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Cube::destroy(Cube *object)
    {
        if(object)
        {
            Geometry::destroy(object);
        }
    }
    
    void Cube::load(Cube &object, lua_State *L, int index)
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
                Cube::load(object, L, -2);
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
    
    u32 Cube::type()
    {
        return JLI_OBJECT_TYPE_Cube;
    }
    
    void Cube::getVertices(LevelOfDetail *geometry, btVector3 **vertices, Node*node)const
    {
    }
    
    u64 Cube::getNumberOfVertices(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Cube::getVertexColors(LevelOfDetail *geometry, btVector4 **colorVertices, Node*node)const
    {
    }
    
    u64 Cube::getNumberOfVertexColors(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Cube::getTextureCoordinates(LevelOfDetail *geometry, btVector2 **textureCoordinates, Node*node)const
    {
    }
    
    u64 Cube::getNumberOfTextureCoordinates(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Cube::setOpacity(Node *node, f32 opacity)
    {
        
    }
    
    void Cube::setHidden(Node *node, bool hidden)
    {
        
    }
    
    bool Cube::isHidden(Node *node)const
    {
        return false;
    }
    
    void Cube::transformVertices(Node *node, const btTransform &transfrom)
    {
        
    }
    
    void Cube::transformVertexColors(Node *node, const btTransform &transform)
    {
        
    }
    
    void Cube::transformTextureCoordinates(Node *node, const btTransform &transform)
    {
        
    }
    
    void Cube::applyShape(Node *node, PhysicsShape *physicsShape)
    {
        
    }
    
    void Cube::hideGeometry(Node*)
    {
        DEBUG_ASSERT(false);
    }
    
    s32 Cube::numberOfVertices()const
    {
        return 24;
    }
    s32 Cube::numberOfIndices()const
    {
        return 36;
    }
    
    void Cube::swapVertexData(const size_t idx1, const size_t idx2)
    {
        
    }
    
    void Cube::load()
    {
        Geometry::load();
        
        m_CubeVerts = new CubeVerts[getMaxMeshes()];
        
        for(int i=0; i<getMaxMeshes(); i++)
        {
            for (int j = 0; j < numberOfVertices(); ++j)
            {
                m_CubeVerts[(i * numberOfVertices())].vertices[j].vertex = CubeVertices[j].vertex;
                m_CubeVerts[(i * numberOfVertices())].vertices[j].texture = CubeVertices[j].texture;
                m_CubeVerts[(i * numberOfVertices())].vertices[j].color = DEFAULTCOLOR;
                m_CubeVerts[(i * numberOfVertices())].vertices[j].opacity = 1.0f;
                m_CubeVerts[(i * numberOfVertices())].vertices[j].hidden = 0.0f;
            }
        }
        
        m_Indexes = new GLushort[getMaxMeshes() * numberOfIndices()];
        for( int i=0;i< getMaxMeshes();i++)
        {
            for (int j = 0; j < numberOfIndices(); ++j)
            {
                m_Indexes[(i * numberOfIndices()) + j] = Indices[j];
            }
        }
    }
    
    void Cube::unLoad()
    {
        if(m_Indexes)
            delete [] m_Indexes;
        m_Indexes=NULL;
        
        if(m_CubeVerts)
            delete [] m_CubeVerts;
        m_CubeVerts=NULL;
        
        Geometry::unLoad();
    }
    
    const void *Cube::getArrayBuffer()const
    {
        return (const void *)m_CubeVerts;
    }
    
    s64 Cube::getArrayBufferSize()const
    {
        return sizeof(CubeVerts) * getMaxMeshes();
    }
    
    const void *Cube::getElementArrayBuffer()const
    {
        return (const void *)m_Indexes;
    }
    
    s64 Cube::getElementArrayBufferSize()const
    {
        return sizeof(GLushort) * getMaxMeshes() * numberOfIndices();
    }
    
    void Cube::setSize(Node*node, const btVector3 &position, const f32 halfSize)
    {
        //TODO: implement
    }
    
    void Cube::setColor(Node*node, const btVector4 &color)
    {
        //TODO: implement
    }
}

