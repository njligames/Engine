//
//  WorldDebugDrawer.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 3/23/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldDebugDrawer.h"
#include "JLIFactoryTypes.h"
#include "GLPlatform.h"
#include "Log.h"
#define TAG "WorldDebugDrawer.cpp"
#define FORMATSTRING "{\"njli::WorldDebugDrawer\":[]}"
#include "btPrint.h"

namespace njli
{
    WorldDebugDrawer::WorldDebugDrawer() :
    m_Line(NULL),
    m_Indexes(NULL),
//    m_DebugMode(btIDebugDraw::DBG_DrawAabb | btIDebugDraw::DBG_DrawWireframe)
    m_DebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE),
    m_Index(0)
    {
        load();
    }
    
    WorldDebugDrawer::~WorldDebugDrawer()
    {
        unLoad();
    }
    
    const char *WorldDebugDrawer::getClassName()const
    {
        return "WorldDebugDrawer";
    }
    
    s32 WorldDebugDrawer::getType()const
    {
        return JLI_OBJECT_TYPE_WorldClock;
    }
    
    WorldDebugDrawer::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    void WorldDebugDrawer::getVertices(LevelOfDetail *geometry, btVector3 **vertices, Node*node)const
    {
        
    }
    
    u64 WorldDebugDrawer::getNumberOfVertices(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void WorldDebugDrawer::getVertexColors(LevelOfDetail *geometry, btVector4 **colorVertices, Node*node)const
    {
        
    }
    
    u64 WorldDebugDrawer::getNumberOfVertexColors(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void WorldDebugDrawer::getTextureCoordinates(LevelOfDetail *geometry, btVector2 **textureCoordinates, Node*node)const
    {
        
    }
    
    u64 WorldDebugDrawer::getNumberOfTextureCoordinates(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void WorldDebugDrawer::setOpacity(Node *node, f32 opacity)
    {
        f32 o = (opacity > 1.0f)?1.0f:((opacity<0.0f)?0.0f:opacity);
    }
    
    void WorldDebugDrawer::setHidden(Node *node, bool hidden)
    {
        
    }
    
    bool WorldDebugDrawer::isHidden(Node *node)const
    {
        return false;
    }
    
    void WorldDebugDrawer::transformVertices(Node *node, const btTransform &transfrom)
    {
        
    }
    
    void WorldDebugDrawer::transformVertexColors(Node *node, const btTransform &transform)
    {
        
    }
    
    void WorldDebugDrawer::transformTextureCoordinates(Node *node, const btTransform &transform)
    {
        
    }
    
    s32 WorldDebugDrawer::numberOfVertices()const
    {
        return 2;
    }
    
    s32 WorldDebugDrawer::numberOfIndices()const
    {
        return 2;
    }
    
    const void *WorldDebugDrawer::getArrayBuffer()const
    {
        return (const void *)m_Line;
    }
    s64 WorldDebugDrawer::getArrayBufferSize()const
    {
        return sizeof(Line) * getMaxMeshes();
    }
    
    const void *WorldDebugDrawer::getElementArrayBuffer()const
    {
        return (const void *)m_Indexes;
    }
    s64 WorldDebugDrawer::getElementArrayBufferSize()const
    {
        return sizeof(GLushort) * getMaxMeshes() * numberOfIndices();
    }
    
    void WorldDebugDrawer::setSize(Node*node, const btVector3 &position, const f32 halfSize)
    {
        //TODO: implement
    }
    
    void WorldDebugDrawer::setColor(Node*node, const btVector4 &color)
    {
        //TODO: implement
    }
    
    void WorldDebugDrawer::applyShape(Node *node, PhysicsShape *physicsShape)
    {
        
    }
    void WorldDebugDrawer::hideGeometry(Node*node)
    {
        DEBUG_ASSERT(false);
    }
    void WorldDebugDrawer::render(Camera *camera, s32 mode)
    {
        Geometry::render(camera, GL_LINES);
        
        m_Index = 0;
    }
    
    void WorldDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
    {
        btVector4 _color(color.x(), color.y(), color.z(), 1.0f);
        setVertexPositions(m_Index, from, to);
        setVertexColors(m_Index, _color, _color);
        setTransform(m_Index, btTransform::getIdentity());
        m_Line[m_Index].pointA.opacity = 1.0f;
        m_Line[m_Index].pointB.opacity = 1.0f;
        ++m_Index;
    }
    
    void WorldDebugDrawer::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
    {
        DEBUG_LOG_WRITE_V(TAG, "drawContactPoint");
    }
    
    void WorldDebugDrawer::reportErrorWarning(const char* warningString)
    {
        DEBUG_LOG_WRITE_E(TAG, warningString);
    }
    
    void WorldDebugDrawer::draw3dText(const btVector3& location,const char* textString)
    {
        
    }
    
    void WorldDebugDrawer::setDebugMode(int debugMode)
    {
        m_DebugMode = debugMode;
    }
    
    int WorldDebugDrawer::getDebugMode() const
    {
        return m_DebugMode;
    }
    
    void WorldDebugDrawer::swapVertexData(const size_t idx1, const size_t idx2)
    {
        
    }
    
    void WorldDebugDrawer::setVertexPositions(const u64 spriteIndex,
                                      const btVector3 &from,
                                      const btVector3 &to)
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        m_Line[spriteIndex].pointA.vertex = from;
        m_Line[spriteIndex].pointB.vertex = to;
    }
    
    void WorldDebugDrawer::getVertexPositions(const u64 spriteIndex,
                                      btVector3 &from,
                                      btVector3 &to)const
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        from = m_Line[spriteIndex].pointA.vertex;
        to = m_Line[spriteIndex].pointB.vertex;
    }
    
    void WorldDebugDrawer::setVertexTextureCoordinates(const u64 spriteIndex,
                                               const btVector2 &from,
                                               const btVector2 &to)
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        m_Line[spriteIndex].pointA.texture = from;
        m_Line[spriteIndex].pointB.texture = to;
    }
    
    void WorldDebugDrawer::getVertexTextureCoordinates(const u64 spriteIndex,
                                               btVector2 &from,
                                               btVector2 &to)const
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        from = m_Line[spriteIndex].pointA.texture;
        to = m_Line[spriteIndex].pointB.texture;
    }
    
    void WorldDebugDrawer::setVertexColors(const u64 spriteIndex,
                                   const btVector4 &from,
                                   const btVector4 &to)
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        m_Line[spriteIndex].pointA.color = from;
        m_Line[spriteIndex].pointB.color = to;
    }
    
    void WorldDebugDrawer::getVertexColors(const u64 spriteIndex,
                                   btVector4 &from,
                                   btVector4 &to)const
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        from = m_Line[spriteIndex].pointA.color;
        to = m_Line[spriteIndex].pointB.color;
    }
    
    void WorldDebugDrawer::load()
    {
        Geometry::load();
        
        m_Line = new Line[getMaxMeshes()];
        memset(m_Line, 0, sizeof(Line) * getMaxMeshes());
        
        // Set up texture coordinates for all particles as these will not change.
        for(int i=0; i<getMaxMeshes(); i++)
        {
            m_Line[i].pointA.vertex = btVector3(0, 0, 0);
            m_Line[i].pointB.vertex = btVector3(1, 1, 0);
            
            m_Line[i].pointA.texture = btVector2(0, 0);
            m_Line[i].pointB.texture = btVector2(0, 0);
            
            m_Line[i].pointA.color = btVector4(1, 1, 1, 1);
            m_Line[i].pointB.color = btVector4(1, 1, 1, 1);
            
            m_Line[i].pointA.opacity = 1.0f;
            m_Line[i].pointB.opacity = 1.0f;
            
            m_Line[i].pointA.hidden = 0.0f;
            m_Line[i].pointB.hidden = 0.0f;
        }
        
        m_Indexes = new GLushort[getMaxMeshes() * numberOfIndices()];
        for (int i = 0; i < getMaxMeshes() * numberOfIndices(); ++i) {
            m_Indexes[i] = i;
        }
    }
    
    void WorldDebugDrawer::unLoad()
    {
        if(m_Indexes)
            delete [] m_Indexes;
        m_Indexes=NULL;
        
        if(m_Line)
            delete [] m_Line;
        m_Line=NULL;
        
        Geometry::unLoad();
    }
}
