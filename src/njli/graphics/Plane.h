//
//  Plane.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/26/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Plane__
#define __JLIGameEngineTest__Plane__

#include "Geometry.h"
#include "lua.hpp"

namespace njli
{
    class PlaneBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) Plane:
    public Geometry
    {
        friend class WorldFactory;
    protected:
        Plane();
        Plane(const AbstractBuilder&);
        Plane(const Plane &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~Plane();
        Plane &operator=(const Plane &);
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
        static Plane **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(Plane **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static Plane *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static Plane *create(const PlaneBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static Plane *clone(const Plane &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static Plane *copy(const Plane &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(Plane *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(Plane &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
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
         */
        virtual void loadGPU();
        /**
         *  <#Description#>
         */
        virtual void unLoadGPU();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual bool isLoadedGPU()const;
        
       
        
        
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
        //TODO: fill in specific methods for Plane
    protected:
        virtual bool shouldApplyShape(Node *node)const{DEBUG_ASSERT(true); return true;}
        void swapVertexData(const size_t idx1, const size_t idx2);
        
        virtual const void *getArrayBuffer()const;
        virtual s64 getArrayBufferSize()const;
        
        virtual const void *getElementArrayBuffer()const;
        virtual s64 getElementArrayBufferSize()const;
        virtual void setSize(Node*node, const btVector3 &position, const f32 halfSize);
        virtual void setColor(Node*node, const btVector4 &color);
        
        virtual void applyShape(Node *node, PhysicsShape *physicsShape);
        
        void hideGeometry(Node*);
    private:
    };
}

#endif /* defined(__JLIGameEngineTest__Plane__) */
