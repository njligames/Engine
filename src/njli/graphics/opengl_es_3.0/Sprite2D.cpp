//
//  Sprite2D.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/15/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "Sprite2D.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "Sprite2DBuilder.h"
#include "GLPlatform.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "MaterialProperty.h"
#include "Log.h"
#define TAG "Sprite2D.cpp"

#include "PhysicsShapeBox2D.h"
#include "PhysicsShapeBox.h"

#define FORMATSTRING "{\"njli::Sprite2D\":[]}"
#include "btPrint.h"


static const btVector3 BL_VERTEX = { -0.5f, -0.5f, 0.0f };
static const btVector3 BR_VERTEX = {  0.5f, -0.5f, 0.0f };
static const btVector3 TL_VERTEX = { -0.5f,  0.5f, 0.0f };
static const btVector3 TR_VERTEX = {  0.5f,  0.5f, 0.0f };

static const btVector2 BL_TEXTURECOORD = { 0.0f, 0.0f };
static const btVector2 BR_TEXTURECOORD = { 1.0f, 0.0f };
static const btVector2 TL_TEXTURECOORD = { 0.0f, 1.0f };
static const btVector2 TR_TEXTURECOORD = { 1.0f, 1.0f };

static const btVector4 DEFAULTCOLOR = {1.0f, 1.0f, 1.0f, 1.0f};

static const btVector2 DEFAULTPIVOT = btVector2(0.5f, 0.5f);

namespace njli
{
    Sprite2D::Sprite2D():
    Geometry(),
    m_Sprite2D(NULL),
    m_Indexes(NULL),
    m_SpritePivots(NULL)
    {
        m_SpritePivots = new btVector2[getMaxMeshes()];
        for(int i=0; i<getMaxMeshes(); i++)
        {
            m_SpritePivots[i] = DEFAULTPIVOT;
        }
        
        load();
    }
    
    Sprite2D::Sprite2D(const AbstractBuilder &builder):
    Geometry(builder),
    m_Sprite2D(NULL),
    m_Indexes(NULL),
    m_SpritePivots(NULL)
    {
        m_SpritePivots = new btVector2[getMaxMeshes()];
        for(int i=0; i<getMaxMeshes(); i++)
        {
            m_SpritePivots[i] = DEFAULTPIVOT;
        }
        
        load();
    }
    
    Sprite2D::Sprite2D(const Sprite2D &copy):
    Geometry(copy),
    m_Sprite2D(NULL),
    m_Indexes(NULL),
    m_SpritePivots(NULL)
    {
        m_SpritePivots = new btVector2[getMaxMeshes()];
        for(int i=0; i<getMaxMeshes(); i++)
        {
            m_SpritePivots[i] = DEFAULTPIVOT;
        }
        
        load();
    }
    
    Sprite2D::~Sprite2D()
    {
        if(m_SpritePivots)
            delete [] m_SpritePivots;
        m_SpritePivots=NULL;
        
        unLoad();
        unLoadGPU();
    }
    
    Sprite2D &Sprite2D::operator=(const Sprite2D &rhs)
    {
        if(this != &rhs)
        {
            //TODO:implement..
        }
        return *this;
    }
    
    s32	Sprite2D::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Sprite2D::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Sprite2D::getClassName()const
    {
        return "Sprite2D";
    }
    
    s32 Sprite2D::getType()const
    {
        return Sprite2D::type();
    }
    
    Sprite2D::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    Sprite2D **Sprite2D::createArray(const u32 size)
    {
        return (Sprite2D**)World::getInstance()->getWorldFactory()->createArray(Sprite2D::type(), size);
    }
    
    void Sprite2D::destroyArray(Sprite2D **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Sprite2D *Sprite2D::create()
    {
        return dynamic_cast<Sprite2D*>(World::getInstance()->getWorldFactory()->create(Sprite2D::type()));
    }
    
    Sprite2D *Sprite2D::create(const Sprite2DBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Sprite2D*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Sprite2D *Sprite2D::clone(const Sprite2D &object)
    {
        return dynamic_cast<Sprite2D*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Sprite2D *Sprite2D::copy(const Sprite2D &object)
    {
        return dynamic_cast<Sprite2D*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Sprite2D::destroy(Sprite2D *object)
    {
        if(object)
        {
            Geometry::destroy(object);
        }
    }
    
    void Sprite2D::load(Sprite2D &object, lua_State *L, int index)
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
                Sprite2D::load(object, L, -2);
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
    
    u32 Sprite2D::type()
    {
        return JLI_OBJECT_TYPE_Sprite2D;
    }
    
    void Sprite2D::getVertices(LevelOfDetail *geometry, btVector3 **vertices, Node*node)const
    {
    }
    
    u64 Sprite2D::getNumberOfVertices(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Sprite2D::getVertexColors(LevelOfDetail *geometry, btVector4 **colorVertices, Node*node)const
    {
    }
    
    u64 Sprite2D::getNumberOfVertexColors(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Sprite2D::getTextureCoordinates(LevelOfDetail *geometry, btVector2 **textureCoordinates, Node*node)const
    {
    }
    
    u64 Sprite2D::getNumberOfTextureCoordinates(LevelOfDetail *geometry, Node*node)const
    {
        return 0;
    }
    
    void Sprite2D::setOpacity(Node *node, f32 opacity)
    {
        f32 o = (opacity > 1.0f)?1.0f:((opacity<0.0f)?0.0f:opacity);
        s64 index = node->getGeometryIndex();
        
        if(m_Sprite2D)
        {
            m_Sprite2D[index].bl.opacity = o;
            m_Sprite2D[index].br.opacity = o;
            m_Sprite2D[index].tl.opacity = o;
            m_Sprite2D[index].tr.opacity = o;
            
            enableBufferModified();
        }
    }
    
    void Sprite2D::setHidden(Node *node, bool hidden)
    {
        s64 index = node->getGeometryIndex();
        
        if(m_Sprite2D)
        {
            m_Sprite2D[index].bl.hidden = (hidden)?1.0f:0.0f;
            m_Sprite2D[index].br.hidden = (hidden)?1.0f:0.0f;
            m_Sprite2D[index].tl.hidden = (hidden)?1.0f:0.0f;
            m_Sprite2D[index].tr.hidden = (hidden)?1.0f:0.0f;
            
            enableBufferModified();
        }
    }
    
    bool Sprite2D::isHidden(Node *node)const
    {
        s64 index = node->getGeometryIndex();
        
        if(m_Sprite2D)
        {
            return ((m_Sprite2D[index].bl.hidden == 1.0f) &&
                    (m_Sprite2D[index].br.hidden == 1.0f) &&
                    (m_Sprite2D[index].tl.hidden == 1.0f) &&
                    (m_Sprite2D[index].tr.hidden == 1.0f));
        }
        return false;
    }
    
    void Sprite2D::transformVertices(Node *node, const btTransform &transfrom)
    {
        btVector2 bottomLeft, bottomRight, topLeft, topRight;
        s64 index = node->getGeometryIndex();
        
        getVertexPositions(index, bottomLeft, bottomRight, topLeft, topRight);
        btVector3 _bottomLeft(bottomLeft.x(), bottomLeft.y(), 0.0f),
                    _bottomRight(bottomRight.x(), bottomRight.y(), 0.0f),
                    _topLeft(topLeft.x(), topLeft.y(), 0.0f),
                    _topRight(topRight.x(), topRight.y(), 0.0f);
        
        
        _bottomLeft += transfrom.getOrigin();
        _bottomLeft = _bottomLeft * transfrom.getBasis();
        
        _bottomRight += transfrom.getOrigin();
        _bottomRight = _bottomRight * transfrom.getBasis();
        
        _topLeft += transfrom.getOrigin();
        _topLeft = _topLeft * transfrom.getBasis();
        
        _topRight += transfrom.getOrigin();
        _topRight = _topRight * transfrom.getBasis();
        
        bottomLeft.setX(_bottomLeft.x());
        bottomLeft.setY(_bottomLeft.y());
        
        bottomRight.setX(_bottomRight.x());
        bottomRight.setY(_bottomRight.y());
        
        topLeft.setX(_topLeft.x());
        topLeft.setY(_topLeft.y());
        
        topRight.setX(_topRight.x());
        topRight.setY(_topRight.y());
        
        setVertexPositions(index, bottomLeft, bottomRight, topLeft, topRight);
    }
    
    void Sprite2D::transformVertexColors(Node *node, const btTransform &transform)
    {
        
    }
    
    void Sprite2D::transformTextureCoordinates(Node *node, const btTransform &transform)
    {
        
    }
    
    void Sprite2D::applyShape(Node *node, PhysicsShape *physicsShape)
    {
        btVector2 halfExtends(getDimensions(node) * 0.5f);
        
//        if(NULL != (shape2d  = dynamic_cast<PhysicsShapeBox2D*>(physicsShape)))
        if(strcmp(physicsShape->getClassName(), "PhysicsShapeBox2D") == 0)
        {
            PhysicsShapeBox2D *shape2d  = dynamic_cast<PhysicsShapeBox2D*>(physicsShape);
            shape2d->setHalfExtends(halfExtends);
        }
//        else if(NULL != (shape3d  = dynamic_cast<PhysicsShapeBox*>(physicsShape)))
        else if(strcmp(physicsShape->getClassName(), "PhysicsShapeBox") == 0)
        {
            PhysicsShapeBox *shape3d  = dynamic_cast<PhysicsShapeBox*>(physicsShape);
            btVector3 halfExtends3d(halfExtends.x(), halfExtends.y(), 1.0f);
            shape3d->setHalfExtends(halfExtends3d);
        }
    }
    
    void Sprite2D::setSpriteAtlasFrame(Node *node,
                                       const f32 &xoffset, const f32 &yoffset,
                                       const f32 &xdim, const f32 &ydim)
    {
        setTextureOffsets(node, btVector2(xoffset, yoffset), btVector2(xdim, ydim));
    }
    
    void Sprite2D::setSpriteAtlasFrame(Node *node, const btVector2 &offset, const btVector2 &dimension)
    {
//        setSpriteAtlasFrame(node, offset.x() + 1, offset.y() + 1, dimension.x() - 2, dimension.y() - 2);
        setSpriteAtlasFrame(node, offset.x(), offset.y(), dimension.x(), dimension.y());
    }
    
    void Sprite2D::setSpriteAtlasFrame(Node *node, const Rect &rect)
    {
//        setSpriteAtlasFrame(node, rect.getOffset() - rect.getSource(), rect.getDimension());
        setSpriteAtlasFrame(node, rect.getOffset(), rect.getDimension());
    }
    
    void Sprite2D::setSpriteAtlasFrame(Node *node, SpriteFrameAtlas *atlas, const char *frameName, bool matchDimension)
    {
        DEBUG_ASSERT(atlas);
        DEBUG_ASSERT(frameName);
        
        setSpriteAtlasFrame(node, atlas->getFrame(frameName));
        
        Rect rect = atlas->getFrame(frameName);
        if(matchDimension)
            setDimensions(node, rect.getDimension());
        setSpriteAtlasFrame(node, rect);
    }
    
    void Sprite2D::setSpriteAtlasFrame(Node *node, SpriteFrameAtlas *atlas, int frameIndex, bool matchDimension)
    {
        DEBUG_ASSERT(atlas);
        
        Rect rect = atlas->getFrame(frameIndex);
        if(matchDimension)
            setDimensions(node, rect.getDimension());
        setSpriteAtlasFrame(node, rect);
    }
    
    void Sprite2D::setDimensions(Node *node,
                                 const btVector2 &dimensions,
                                 const btVector2 &spritePivotPoint)
    {
        DEBUG_ASSERT(spritePivotPoint.x() >= 0 && spritePivotPoint.x() <= 1);
        DEBUG_ASSERT(spritePivotPoint.y() >= 0 && spritePivotPoint.y() <= 1);
        
        s64 spriteIndex = node->getGeometryIndex();
        

        
        if(spriteIndex >= 0)
        {
            f32 left_half_width = (dimensions.x() * spritePivotPoint.x());
            f32 right_half_width = (dimensions.x() * (1.0f - spritePivotPoint.x()));
            
            f32 bottom_half_height = (dimensions.y() * spritePivotPoint.y());
            f32 top_half_height = (dimensions.y() * (1.0f - spritePivotPoint.y()));
            
            btVector2 bottomLeft(BL_VERTEX.x() * left_half_width, BL_VERTEX.y() * bottom_half_height);
            btVector2 bottomRight(BR_VERTEX.x() * right_half_width, BR_VERTEX.y() * bottom_half_height);
            btVector2 topLeft(TL_VERTEX.x() * left_half_width, TL_VERTEX.y() * top_half_height);
            btVector2 topRight(TR_VERTEX.x() * right_half_width, TR_VERTEX.y() * top_half_height);
            
            setVertexPositions(spriteIndex, bottomLeft, bottomRight, topLeft, topRight);
            m_SpritePivots[spriteIndex] = spritePivotPoint;
        }
    }
    
    btVector2 Sprite2D::getDimensions(Node *node)const
    {
        btVector2 dimensions(0,0);
        
        s64 spriteIndex = node->getGeometryIndex();
        
        if(spriteIndex >= 0)
        {
            btVector2 bottomLeft;
            btVector2 bottomRight;
            btVector2 topLeft;
            btVector2 topRight;
            
            getVertexPositions(spriteIndex, bottomLeft, bottomRight, topLeft, topRight);
            
            f32 left = btMax<btScalar>(bottomLeft.x(), topLeft.x());
            f32 right = btMax<btScalar>(bottomRight.x(), topRight.x());
            f32 top = btMax<btScalar>(topLeft.y(), topRight.y());
            f32 bottom = btMax<btScalar>(bottomLeft.y(), bottomRight.y());
            
            dimensions.setX((right - left) );
            dimensions.setY((top - bottom) );
        }
        
        return dimensions;
    }
    
    void Sprite2D::getAabb(Node *node, btVector3& aabbMin,btVector3& aabbMax) const
    {
        btVector2 d(getDimensions(node) * 0.5f);
        aabbMin = btVector3(d.x(),d.y(),0) * -1.f;
        aabbMax = btVector3(d.x(),d.y(),0);
    }
    
    btVector2 Sprite2D::getPivotPoint(Node *node)const
    {
        btVector2 spritePivotPoint(0,0);
        
        s64 spriteIndex = node->getGeometryIndex();
        
        if(spriteIndex >= 0)
        {
            spritePivotPoint = m_SpritePivots[spriteIndex];
        }
        return spritePivotPoint;
    }
    
    void Sprite2D::setTextureOffsets(Node *node,
                                     const btVector2 &textureCoordOffset,
                                     const btVector2 &textureCoordDimensions)
    {
        s64 spriteIndex = node->getGeometryIndex();
        
        if(spriteIndex >= 0)
        {
            f32 width = getMaterial()->getDiffuse()->getWidth();
            f32 height = getMaterial()->getDiffuse()->getHeight();
            
            f32 left = textureCoordOffset.x() / width;
            f32 right = (textureCoordOffset.x() + textureCoordDimensions.x()) / width;
            f32 top = (height - textureCoordOffset.y()) / height;
            f32 bottom = 1.0f - (((textureCoordOffset.y()) + textureCoordDimensions.y()) / height);
            
            btVector2 bottomLeft(left, bottom);
            btVector2 bottomRight(right, bottom);
            btVector2 topLeft(left, top);
            btVector2 topRight(right, top);
            
            /*
             static const btVector2 BL_TEXTURECOORD = { 0, 0 };
             static const btVector2 BR_TEXTURECOORD = { 1, 0 };
             static const btVector2 TL_TEXTURECOORD = { 0, 1 };
             static const btVector2 TR_TEXTURECOORD = { 1, 1 };
             
             (0, 1)                                   (1, 1)
             ___________________________________
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
             |___________________________________|
             (0, 0)                                   (1, 0)
             */
            
            setVertexTextureCoordinates(spriteIndex, bottomLeft, bottomRight, topLeft, topRight);
        }
    }
    
    btVector2 Sprite2D::getTextureCoordinateOffsets(Node *node)const
    {
        return btVector2(0,0);
    }
    btVector2 Sprite2D::getTextureCoordinateDimensions(Node *node)const
    {
        return btVector2(0,0);
    }
    
    void Sprite2D::setColors(Node *node,
                             const btVector4 &bottomLeft,
                             const btVector4 &bottomRight,
                             const btVector4 &topLeft,
                             const btVector4 &topRight)
    {
        s64 spriteIndex = node->getGeometryIndex();
        
        if(spriteIndex >= 0)
        {
            setVertexColors(spriteIndex, bottomLeft, bottomRight, topLeft, topRight);
        }
    }
    
    void Sprite2D::setColors(Node *node, const btVector4 &color)
    {
        setColors(node, color, color, color, color);
    }

    btVector4 Sprite2D::getColorBottomLeft(Node *node)const
    {
        s64 spriteIndex = node->getGeometryIndex();
        btVector4 ret(0,0,0,0);
        
        if(spriteIndex >= 0)
        {
            btVector4 dummy;
            getVertexColors(spriteIndex, ret, dummy, dummy, dummy);
        }
        
        return ret;
    }
    btVector4 Sprite2D::getColorBottomRight(Node *node)const
    {
        s64 spriteIndex = node->getGeometryIndex();
        btVector4 ret(0,0,0,0);
        
        if(spriteIndex >= 0)
        {
            btVector4 dummy;
            getVertexColors(spriteIndex, dummy, ret, dummy, dummy);
        }
        
        return ret;
    }
    btVector4 Sprite2D::getColorTopLeft(Node *node)const
    {
        s64 spriteIndex = node->getGeometryIndex();
        btVector4 ret(0,0,0,0);
        
        if(spriteIndex >= 0)
        {
            btVector4 dummy;
            getVertexColors(spriteIndex, dummy, dummy, ret, dummy);
        }
        
        return ret;
    }
    btVector4 Sprite2D::getColorTopRight(Node *node)const
    {
        s64 spriteIndex = node->getGeometryIndex();
        btVector4 ret(0,0,0,0);
        
        if(spriteIndex >= 0)
        {
            btVector4 dummy;
            getVertexColors(spriteIndex, dummy, dummy, dummy, ret);
        }
        
        return ret;
    }
    
    s32 Sprite2D::numberOfVertices()const
    {
        return 4;
    }
    s32 Sprite2D::numberOfIndices()const
    {
        return 6;
    }
    
    void Sprite2D::setVertexPositions(Node *node,
                            const btVector2 &bottomLeft,
                            const btVector2 &bottomRight,
                            const btVector2 &topLeft,
                            const btVector2 &topRight)
    {
        s64 spriteIndex = node->getGeometryIndex();
        
        if(spriteIndex >= 0)
        {
            setVertexPositions(spriteIndex, bottomLeft, bottomRight, topLeft, topRight);
        }
    }
    
    void Sprite2D::setVertexPositions(const u64 spriteIndex,
                                      const btVector2 &bottomLeft,
                                      const btVector2 &bottomRight,
                                      const btVector2 &topLeft,
                                      const btVector2 &topRight)
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        m_Sprite2D[spriteIndex].bl.vertex = bottomLeft;
        m_Sprite2D[spriteIndex].br.vertex = bottomRight;
        m_Sprite2D[spriteIndex].tl.vertex = topLeft;
        m_Sprite2D[spriteIndex].tr.vertex = topRight;
        
        enableBufferModified();
        
//        Node *node = getParent();
//        if(node)
////            node->m_ApplyPhysicsShape = true;
//            node->applyPhysicsShape();
    }
    
    void Sprite2D::getVertexPositions(const u64 spriteIndex,
                                      btVector2 &bottomLeft,
                                      btVector2 &bottomRight,
                                      btVector2 &topLeft,
                                      btVector2 &topRight)const
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        bottomLeft = m_Sprite2D[spriteIndex].bl.vertex;
        bottomRight = m_Sprite2D[spriteIndex].br.vertex;
        topLeft = m_Sprite2D[spriteIndex].tl.vertex;
        topRight = m_Sprite2D[spriteIndex].tr.vertex;
    }
    
    void Sprite2D::setVertexTextureCoordinates(const u64 spriteIndex,
                                               const btVector2 &bottomLeft,
                                               const btVector2 &bottomRight,
                                               const btVector2 &topLeft,
                                               const btVector2 &topRight)
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        m_Sprite2D[spriteIndex].bl.texture = bottomLeft;
        m_Sprite2D[spriteIndex].br.texture = bottomRight;
        m_Sprite2D[spriteIndex].tl.texture = topLeft;
        m_Sprite2D[spriteIndex].tr.texture = topRight;
        
        enableBufferModified();
    }
    
    void Sprite2D::getVertexTextureCoordinates(const u64 spriteIndex,
                                               btVector2 &bottomLeft,
                                               btVector2 &bottomRight,
                                               btVector2 &topLeft,
                                               btVector2 &topRight)const
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        bottomLeft = m_Sprite2D[spriteIndex].bl.texture;
        bottomRight = m_Sprite2D[spriteIndex].br.texture;
        topLeft = m_Sprite2D[spriteIndex].tl.texture;
        topRight = m_Sprite2D[spriteIndex].tr.texture;
    }
    
    void Sprite2D::setVertexColors(const u64 spriteIndex,
                                   const btVector4 &bottomLeft,
                                   const btVector4 &bottomRight,
                                   const btVector4 &topLeft,
                                   const btVector4 &topRight)
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        m_Sprite2D[spriteIndex].bl.color = bottomLeft;
        m_Sprite2D[spriteIndex].br.color = bottomRight;
        m_Sprite2D[spriteIndex].tl.color = topLeft;
        m_Sprite2D[spriteIndex].tr.color = topRight;
        
        enableBufferModified();
    }
    
    void Sprite2D::getVertexColors(const u64 spriteIndex,
                                   btVector4 &bottomLeft,
                                   btVector4 &bottomRight,
                                   btVector4 &topLeft,
                                   btVector4 &topRight)const
    {
        DEBUG_ASSERT(spriteIndex < getMaxMeshes());
        
        bottomLeft = m_Sprite2D[spriteIndex].bl.color;
        bottomRight = m_Sprite2D[spriteIndex].br.color;
        topLeft = m_Sprite2D[spriteIndex].tl.color;
        topRight = m_Sprite2D[spriteIndex].tr.color;
    }
    
    void Sprite2D::load()
    {
        Geometry::load();
        
        m_Sprite2D = new SpriteQuad[getMaxMeshes()];
        
        // Set up texture coordinates for all particles as these will not change.
        for(int i=0; i<getMaxMeshes(); i++)
        {
            m_Sprite2D[i].bl.vertex = BL_VERTEX;
            m_Sprite2D[i].br.vertex = BR_VERTEX;
            m_Sprite2D[i].tl.vertex = TL_VERTEX;
            m_Sprite2D[i].tr.vertex = TR_VERTEX;
            
            m_Sprite2D[i].bl.texture = BL_TEXTURECOORD;
            m_Sprite2D[i].br.texture = BR_TEXTURECOORD;
            m_Sprite2D[i].tl.texture = TL_TEXTURECOORD;
            m_Sprite2D[i].tr.texture = TR_TEXTURECOORD;
            
            m_Sprite2D[i].bl.color = DEFAULTCOLOR;
            m_Sprite2D[i].br.color = DEFAULTCOLOR;
            m_Sprite2D[i].tl.color = DEFAULTCOLOR;
            m_Sprite2D[i].tr.color = DEFAULTCOLOR;
            
            m_Sprite2D[i].bl.opacity = 1.0f;
            m_Sprite2D[i].br.opacity = 1.0f;
            m_Sprite2D[i].tl.opacity = 1.0f;
            m_Sprite2D[i].tr.opacity = 1.0f;
            
            m_Sprite2D[i].bl.hidden = 0;
            m_Sprite2D[i].br.hidden = 0;
            m_Sprite2D[i].tl.hidden = 0;
            m_Sprite2D[i].tr.hidden = 0;
        }
        
        m_Indexes = new GLushort[getMaxMeshes() * numberOfIndices()];
        for( int i=0;i< getMaxMeshes();i++)
        {
            m_Indexes[i*numberOfIndices()+0] = i*4+0;
            m_Indexes[i*numberOfIndices()+1] = i*4+1;
            m_Indexes[i*numberOfIndices()+2] = i*4+2;
            
            m_Indexes[i*numberOfIndices()+5] = i*4+2;
            m_Indexes[i*numberOfIndices()+4] = i*4+3;
            m_Indexes[i*numberOfIndices()+3] = i*4+1;
        }
        
        enableBufferModified();
    }
    
    void Sprite2D::unLoad()
    {
        
        
        if(m_Indexes)
            delete [] m_Indexes;
        m_Indexes = NULL;
        
        if(m_Sprite2D)
            delete [] m_Sprite2D;
        m_Sprite2D=NULL;
        
        Geometry::unLoad();
    }
    
    void Sprite2D::swapVertexData(const size_t idx1, const size_t idx2)
    {
        
    }
    
    const void *Sprite2D::getArrayBuffer()const
    {
        return (const void *)m_Sprite2D;
    }
    s64 Sprite2D::getArrayBufferSize()const
    {
        return sizeof(SpriteQuad) * getMaxMeshes();
    }
    
    const void *Sprite2D::getElementArrayBuffer()const
    {
        return (const void *)m_Indexes;
    }
    s64 Sprite2D::getElementArrayBufferSize()const
    {
        return sizeof(GLushort) * getMaxMeshes() * numberOfIndices();
    }
    
    void Sprite2D::setSize(Node*node, const btVector3 &position, const f32 halfSize)
    {
        //TODO: implement
        btVector2 bottomLeft(position.x() - halfSize, position.y() - halfSize);
        btVector2 bottomRight(position.x() + halfSize, position.y() - halfSize);
        btVector2 topLeft(position.x() - halfSize, position.y() + halfSize);
        btVector2 topRight(position.x() + halfSize, position.y() + halfSize);
        
        setVertexPositions(node, bottomLeft, bottomRight, topLeft, topRight);
    }
    
    void Sprite2D::setColor(Node*node, const btVector4 &color)
    {
        setColors(node, color);
    }
    
    void Sprite2D::hideGeometry(Node*node)
    {
        s64 i = node->getGeometryIndex();
        
        m_Sprite2D[i].bl.vertex = BL_VERTEX;
        m_Sprite2D[i].br.vertex = BR_VERTEX;
        m_Sprite2D[i].tl.vertex = TL_VERTEX;
        m_Sprite2D[i].tr.vertex = TR_VERTEX;
        
        m_Sprite2D[i].bl.texture = BL_TEXTURECOORD;
        m_Sprite2D[i].br.texture = BL_TEXTURECOORD;
        m_Sprite2D[i].tl.texture = BL_TEXTURECOORD;
        m_Sprite2D[i].tr.texture = BL_TEXTURECOORD;
        
        m_Sprite2D[i].bl.color = DEFAULTCOLOR;
        m_Sprite2D[i].br.color = DEFAULTCOLOR;
        m_Sprite2D[i].tl.color = DEFAULTCOLOR;
        m_Sprite2D[i].tr.color = DEFAULTCOLOR;
        
        m_Sprite2D[i].bl.opacity = 1.0f;
        m_Sprite2D[i].br.opacity = 1.0f;
        m_Sprite2D[i].tl.opacity = 1.0f;
        m_Sprite2D[i].tr.opacity = 1.0f;
        
        enableBufferModified();
        
//        f32 m = std::numeric_limits<f32>::min();
//        s64 index = node->getGeometryIndex();
//        btVector2 p(m,m);
//        
//        setVertexPositions(index, p, p, p, p);
    }
}
