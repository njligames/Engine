//
//  Sprite2D.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/15/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Sprite2D__
#define __JLIGameEngineTest__Sprite2D__

#include "Geometry.h"
#include "AbstractBuilder.h"
#include "btTransform.h"
#include "SpriteFrameAtlas.h"
#include "lua.hpp"

/*
 Billboard Tutorial...
 http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/billboards/
 */
namespace njli
{
    class Sprite2DBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) Sprite2D:
    public Geometry
    {
        friend class WorldFactory;
    protected:
        Sprite2D();
        Sprite2D(const AbstractBuilder&);
        Sprite2D(const Sprite2D &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~Sprite2D();
        Sprite2D &operator=(const Sprite2D &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        /**
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
        virtual	void serialize(void*, btSerializer*) const;
        
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
        
        /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
        static Sprite2D **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(Sprite2D **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static Sprite2D *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static Sprite2D *create(const Sprite2DBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static Sprite2D *clone(const Sprite2D &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static Sprite2D *copy(const Sprite2D &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(Sprite2D *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(Sprite2D &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    public:
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
        virtual void transformVertexColors(Node *node ,const btTransform &transform);
        /**
         *  <#Description#>
         *
         *  @param node      <#node description#>
         *  @param transform <#transform description#>
         */
        virtual void transformTextureCoordinates(Node *node, const btTransform &transform);
        
    protected:
        
        virtual void applyShape(Node *node, PhysicsShape *physicsShape);
        
//        btVector3 getBillBoardVertexPosition(Camera *camera, const btVector2 &vertexPosition);
    public:
//        void applyBillboard(Camera *camera);
        
        void setSpriteAtlasFrame(Node *node, const f32 &xoffset, const f32 &yoffset, const f32 &xdim, const f32 &ydim);
        
        void setSpriteAtlasFrame(Node *node, const btVector2 &offset, const btVector2 &dimension);
        
        void setSpriteAtlasFrame(Node *node, const Rect &dimension);
        
        void setSpriteAtlasFrame(Node *node, SpriteFrameAtlas *atlas, const char *frameName, bool matchDimension = true);
        
        void setSpriteAtlasFrame(Node *node, SpriteFrameAtlas *atlas, int frameIndex, bool matchDimension = true);
        
        void setDimensions(Node *node, const btVector2 &dimensions,
                           const btVector2 &spritePivotPoint = btVector2(0.5f, 0.5f));
        virtual bool shouldApplyShape(Node *node)const;
        
        btVector2 getDimensions(Node *node)const;
        virtual void getAabb(Node *node, btVector3& aabbMin,btVector3& aabbMax) const;
        
        btVector2 getPivotPoint(Node *node)const;
        
        void setTextureOffsets(Node *node,
                               const btVector2 &textureCoordOffset,
                               const btVector2 &textureCoordDimensions);
        
        btVector2 getTextureCoordinateOffsets(Node *node)const;
        btVector2 getTextureCoordinateDimensions(Node *node)const;
        
        void setColors(Node *node,
                       const btVector4 &bottomLeft,
                       const btVector4 &bottomRight,
                       const btVector4 &topLeft,
                       const btVector4 &topRight);
        
        void setColors(Node *node, const btVector4 &color);
        
        btVector4 getColorBottomLeft(Node *node)const;
        btVector4 getColorBottomRight(Node *node)const;
        btVector4 getColorTopLeft(Node *node)const;
        btVector4 getColorTopRight(Node *node)const;
        
        virtual inline s32 numberOfVertices()const
        {
            return 4;
        }
        virtual inline s32 numberOfIndices()const
        {
            return 6;
        }
        
        void setVertexPositions(Node *node,
                                const btVector2 &bottomLeft,
                                const btVector2 &bottomRight,
                                const btVector2 &topLeft,
                                const btVector2 &topRight);
    protected:
        
        void setVertexPositions(const u64 spriteIndex,
                                const btVector2 &bottomLeft,
                                const btVector2 &bottomRight,
                                const btVector2 &topLeft,
                                const btVector2 &topRight);
        
        void getVertexPositions(const u64 spriteIndex,
                                btVector2 &bottomLeft,
                                btVector2 &bottomRight,
                                btVector2 &topLeft,
                                btVector2 &topRight)const;
        
        void setVertexTextureCoordinates(const u64 spriteIndex,
                                         const btVector2 &bottomLeft,
                                         const btVector2 &bottomRight,
                                         const btVector2 &topLeft,
                                         const btVector2 &topRight);
        
        void getVertexTextureCoordinates(const u64 spriteIndex,
                                         btVector2 &bottomLeft,
                                         btVector2 &bottomRight,
                                         btVector2 &topLeft,
                                         btVector2 &topRight)const;
        
        void setVertexColors(const u64 spriteIndex,
                             const btVector4 &bottomLeft,
                             const btVector4 &bottomRight,
                             const btVector4 &topLeft,
                             const btVector4 &topRight);
        
        void getVertexColors(const u64 spriteIndex,
                             btVector4 &bottomLeft,
                             btVector4 &bottomRight,
                             btVector4 &topLeft,
                             btVector4 &topRight)const;
        
        virtual void load();
        virtual void unLoad();
        
    protected:
        void swapVertexData(const size_t idx1, const size_t idx2);
        
        
        class SpriteQuad
        {
        public:
            TexturedColoredVertex bl;
            TexturedColoredVertex br;
            TexturedColoredVertex tl;
            TexturedColoredVertex tr;
            
            operator std::string() const
            {
                std::string bottomLeft(bl);
                std::string bottomRight(br);
                std::string topLeft(tl);
                std::string topRight(tr);
                
                return std::string("\nbl: ") + bottomLeft +
                std::string("\nbr: ") + bottomRight +
                std::string("\ntl: ") + topLeft +
                std::string("\ntr: ") + topRight;
            }
            SpriteQuad &operator=(const SpriteQuad &rhs)
            {
                if(this != &rhs)
                {
                    bl = rhs.bl;
                    br = rhs.br;
                    tl = rhs.tl;
                    tr = rhs.tr;
                }
                return *this;
            }
        };
        
        virtual const void *getArrayBuffer()const;
        virtual s64 getArrayBufferSize()const;
        
        virtual const void *getElementArrayBuffer()const;
        virtual s64 getElementArrayBufferSize()const;
        virtual void setSize(Node*node, const btVector3 &position, const f32 halfSize);
        virtual void setColor(Node*node, const btVector4 &color);
        
        void hideGeometry(Node*);
    private:
        SpriteQuad *m_Sprite2D;        // Array holding quad information for each particle;
        u16 *m_Indexes;
        
        btVector2 *m_SpritePivots;
        bool *m_changedDimensionArray;
        
    };
}

#endif /* defined(__JLIGameEngineTest__Sprite2D__) */
