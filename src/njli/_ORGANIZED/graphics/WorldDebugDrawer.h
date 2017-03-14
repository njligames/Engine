//
//  WorldDebugDrawer.h
//  JLIGameEngineTest
//
//  Created by James Folk on 3/23/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__DebugDrawer__
#define __JLIGameEngineTest__DebugDrawer__

#include <string>
#include "Geometry.h"
#include "btIDebugDraw.h"

namespace njli
{
    /// <#Description#>
    class WorldDebugDrawer :
    public Geometry,
    public btIDebugDraw
    {
        friend class World;
    public:
        /**
         *  <#Description#>
         */
        WorldDebugDrawer();
        /**
         *  <#Description#>
         */
        BT_DECLARE_ALIGNED_ALLOCATOR();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual ~WorldDebugDrawer();
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const char *getClassName()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 getType()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        operator std::string() const;
        
    protected:
        //TODO: fill in specific methods for WorldDebugDrawer
        /**
         *  <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param vertices <#vertices description#>
         *  @param node     <#node description#>
         */
        virtual void getVertices(LevelOfDetail *geometry, btVector3 **vertices, Node*node)const;
        /**
         *  <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
        virtual u64 getNumberOfVertices(LevelOfDetail *geometry, Node*node)const;
        
        /**
         *  <#Description#>
         *
         *  @param geometry      <#geometry description#>
         *  @param colorVertices <#colorVertices description#>
         *  @param node          <#node description#>
         */
        virtual void getVertexColors(LevelOfDetail *geometry, btVector4 **colorVertices, Node*node)const;
        /**
         *  <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
        virtual u64 getNumberOfVertexColors(LevelOfDetail *geometry, Node*node)const;
        
        /**
         *  <#Description#>
         *
         *  @param geometry           <#geometry description#>
         *  @param textureCoordinates <#textureCoordinates description#>
         *  @param node               <#node description#>
         */
        virtual void getTextureCoordinates(LevelOfDetail *geometry, btVector2 **textureCoordinates, Node*node)const;
        /**
         *  <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
        virtual u64 getNumberOfTextureCoordinates(LevelOfDetail *geometry, Node*node)const;
        
        /**
         *  <#Description#>
         *
         *  @param node    <#node description#>
         *  @param opacity <#opacity description#>
         */
        virtual void setOpacity(Node *node, f32 opacity);
        
        /**
         *  <#Description#>
         *
         *  @param node    <#node description#>
         *  @param opacity <#opacity description#>
         */
        virtual void setHidden(Node *node, bool hidden = true);
        
        /**
         *  <#Description#>
         *
         *  @param node    <#node description#>
         *  @param opacity <#opacity description#>
         */
        virtual bool isHidden(Node *node)const;
        
        /**
         *  <#Description#>
         *
         *  @param node      <#node description#>
         *  @param transfrom <#transfrom description#>
         */
        virtual void transformVertices(Node *node, const btTransform &transfrom);
        /**
         *  <#Description#>
         *
         *  @param node      <#node description#>
         *  @param transform <#transform description#>
         */
        virtual void transformVertexColors(Node *node, const btTransform &transform);
        /**
         *  <#Description#>
         *
         *  @param node      <#node description#>
         *  @param transform <#transform description#>
         */
        virtual void transformTextureCoordinates(Node *node, const btTransform &transform);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 numberOfVertices()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 numberOfIndices()const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const void *getArrayBuffer()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s64 getArrayBufferSize()const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const void *getElementArrayBuffer()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s64 getElementArrayBufferSize()const;
        virtual void setSize(Node*node, const btVector3 &position, const f32 halfSize);
        virtual void setColor(Node*node, const btVector4 &color);
        
        /**
         *  <#Description#>
         *
         *  @param node         <#node description#>
         *  @param physicsShape <#physicsShape description#>
         */
        virtual void applyShape(Node *node, PhysicsShape *physicsShape);
        
        /**
         *  <#Description#>
         *
         *  @param node <#node description#>
         */
        void hideGeometry(Node*node);
        
        /**
         *  <#Description#>
         *
         *  @param camera <#camera description#>
         */
        void render(Camera *camera, s32 mode = 0x0004);
    public:
        /**
         *  <#Description#>
         *
         *  @param from  <#from description#>
         *  @param to    <#to description#>
         *  @param color <#color description#>
         */
        virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
        /**
         *  <#Description#>
         *
         *  @param PointOnB  <#PointOnB description#>
         *  @param normalOnB <#normalOnB description#>
         *  @param distance  <#distance description#>
         *  @param lifeTime  <#lifeTime description#>
         *  @param color     <#color description#>
         */
        virtual void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
        /**
         *  <#Description#>
         *
         *  @param warningString <#warningString description#>
         */
        virtual void reportErrorWarning(const char* warningString);
        
        /**
         *  <#Description#>
         *
         *  @param location   <#location description#>
         *  @param textString <#textString description#>
         */
        virtual void draw3dText(const btVector3& location,const char* textString);
        
        /**
         *  <#Description#>
         *
         *  @param debugMode <#debugMode description#>
         */
        virtual void setDebugMode(int debugMode);
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int getDebugMode() const;
    protected:
        virtual bool shouldApplyShape(Node *node)const{DEBUG_ASSERT(true); return true;}
        void swapVertexData(const size_t idx1, const size_t idx2);
        
        
        void setVertexPositions(const u64 index,
                                const btVector3 &from,
                                const btVector3 &to);
        
        void getVertexPositions(const u64 index,
                                btVector3 &from,
                                btVector3 &to)const;
        
        void setVertexTextureCoordinates(const u64 index,
                                         const btVector2 &from,
                                         const btVector2 &to);
        
        void getVertexTextureCoordinates(const u64 index,
                                         btVector2 &from,
                                         btVector2 &to)const;
        
        void setVertexColors(const u64 index,
                             const btVector4 &from,
                             const btVector4 &to);
        
        void getVertexColors(const u64 index,
                             btVector4 &from,
                             btVector4 &to)const;
        
        virtual void load();
        virtual void unLoad();
    private:
        WorldDebugDrawer(const WorldDebugDrawer &);
        WorldDebugDrawer &operator=(const WorldDebugDrawer &);
        
        typedef struct
        {
            TexturedColoredVertex pointA;
            TexturedColoredVertex pointB;
        } Line;
        
        Line *m_Line;        // Array holding quad information for each particle;
        u16 *m_Indexes;
        
        int m_DebugMode;
        s32 m_Index;
    };
}

#endif /* defined(__JLIGameEngineTest__DebugDrawer__) */
