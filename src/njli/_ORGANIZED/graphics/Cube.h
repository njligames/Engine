//
//  Cube.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/2/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Cube__
#define __JLIGameEngineTest__Cube__

#include "Geometry.h"
#include "AbstractBuilder.h"


#include "lua.hpp"

namespace njli
{
    class CubeBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) Cube:
    public Geometry
    {
        friend class WorldFactory;
    protected:
        Cube();
        Cube(const AbstractBuilder&);
        Cube(const Cube &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~Cube();
        Cube &operator=(const Cube &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:13
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
        virtual	void serialize(void*dataBuffer, btSerializer*) const;
        
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
        static Cube **createArray(const u32 size);
        
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(Cube **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static Cube *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static Cube *create(const CubeBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static Cube *clone(const Cube &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static Cube *copy(const Cube &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(Cube *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(Cube &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    public:
        
        /**
         *  @author James Folk, 16-02-11 16:02:52
         *
         *  @brief <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param vertices <#vertices description#>
         *  @param node     <#node description#>
         */
        virtual void getVertices(LevelOfDetail *geometry, btVector3 **vertices, Node*node)const;
        
        /**
         *  @author James Folk, 16-02-11 16:02:00
         *
         *  @brief <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
        virtual u64 getNumberOfVertices(LevelOfDetail *geometry, Node*node)const;
        
        /**
         *  @author James Folk, 16-02-11 16:02:53
         *
         *  @brief <#Description#>
         *
         *  @param geometry      <#geometry description#>
         *  @param colorVertices <#colorVertices description#>
         *  @param node          <#node description#>
         */
        virtual void getVertexColors(LevelOfDetail *geometry, btVector4 **colorVertices, Node*node)const;
        
        /**
         *  @author James Folk, 16-02-11 16:02:06
         *
         *  @brief <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
        virtual u64 getNumberOfVertexColors(LevelOfDetail *geometry, Node*node)const;
        
        /**
         *  @author James Folk, 16-02-11 16:02:57
         *
         *  @brief <#Description#>
         *
         *  @param geometry           <#geometry description#>
         *  @param textureCoordinates <#textureCoordinates description#>
         *  @param node               <#node description#>
         */
        virtual void getTextureCoordinates(LevelOfDetail *geometry, btVector2 **textureCoordinates, Node*node)const;
        
        /**
         *  @author James Folk, 16-02-11 17:02:23
         *
         *  @brief <#Description#>
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
         *  @param node      <#node description#>
         *  @param transfrom <#transfrom description#>
         */
        
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
    public:
        //TODO: fill in specific methods for Cube
        
    protected:
        virtual bool shouldApplyShape(Node *node)const{DEBUG_ASSERT(true); return true;}
        void swapVertexData(const size_t idx1, const size_t idx2);
        
        ATTRIBUTE_ALIGNED16(struct) CubeVerts
        {
            TexturedColoredVertex vertices[24];
        };
        virtual void load();
        virtual void unLoad();
    
        virtual const void *getArrayBuffer()const;
        virtual s64 getArrayBufferSize()const;
        
        virtual const void *getElementArrayBuffer()const;
        virtual s64 getElementArrayBufferSize()const;
        virtual void setSize(Node*node, const btVector3 &position, const f32 halfSize);
        virtual void setColor(Node*node, const btVector4 &color);
    
    virtual void applyShape(Node *node, PhysicsShape *physicsShape);
    
        void hideGeometry(Node*);
    private:
        CubeVerts *m_CubeVerts;
        u16 *m_Indexes;
    };
}

#endif /* defined(__JLIGameEngineTest__Cube__) */
