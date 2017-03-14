//
//  Geometry.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Geometry__
#define __JLIGameEngineTest__Geometry__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

#include <bitset>
#include <string>

#include "btVector2.h"
#include "btVector3.h"
#include "JLIFactoryTypes.h"

class btTransform;

#define NUMBER_OF_MESHES (100)

namespace njli {
class GeometryBuilder;
class LevelOfDetail;
class Material;
class ShaderProgram;
class Camera;
class PhysicsShape;
class Node;
class Image;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Geometry : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class Node;
    friend class Scene;
    friend class PhysicsBodyRigid;

protected:
    Geometry();
    Geometry(const AbstractBuilder&);
    Geometry(const Geometry&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Geometry();
    Geometry& operator=(const Geometry&);

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
         *  @author James Folk, 16-02-11 15:02:57
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

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
         *  @param type <#type description#>
         *
         *  @return <#return value description#>
         */
    static Geometry* create(u32 type);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Geometry * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Geometry & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for Geometry

    /**
         *  <#Description#>
         *
         *  @param geometry <#geometry description#>
         */
    void addLevelOfDetail(LevelOfDetail * geometry);
    /**
         *  <#Description#>
         *
         *  @param geometry <#geometry description#>
         *
         *  @return <#return value description#>
         */
    bool removeLevelOfDetail(LevelOfDetail * geometry);
    /**
         *  <#Description#>
         */
    void removeAllLevelOfDetails();
    /**
         *  <#Description#>
         *
         *  @param geometries <#geometries description#>
         */
    void getLevelOfDetails(std::vector<LevelOfDetail*> & geometries) const;
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    LevelOfDetail* getLevelOfDetail(const u32 index);
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    const LevelOfDetail* getLevelOfDetail(const u32 index) const;

    /**
         *  <#Description#>
         *
         *  @param material <#material description#>
         */
    void setMaterial(Material * material, Image* image = NULL);
    /**
         *  <#Description#>
         */
    void removeMaterial();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Material* getMaterial();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Material* getMaterial() const;

    /**
         *  <#Description#>
         *
         *  @param shader <#shader description#>
         */
    void setShaderProgram(ShaderProgram * shader);
    /**
         *  <#Description#>
         */
    void removeShaderProgram();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    ShaderProgram* getShaderProgram();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const ShaderProgram* getShaderProgram() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u32 getMaxMeshes() const;

    /**
         *  @author James Folk, 16-02-11 17:02:44
         *
         *  @brief <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param vertices <#vertices description#>
         *  @param node     <#node description#>
         */
    virtual void getVertices(LevelOfDetail * geometry, btVector3 * *vertices, Node * node) const = 0;

    /**
         *  @author James Folk, 16-02-11 17:02:49
         *
         *  @brief <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
    virtual u64 getNumberOfVertices(LevelOfDetail * geometry, Node * node) const = 0;

    /**
         *  @author James Folk, 16-02-11 17:02:56
         *
         *  @brief <#Description#>
         *
         *  @param geometry      <#geometry description#>
         *  @param colorVertices <#colorVertices description#>
         *  @param node          <#node description#>
         */
    virtual void getVertexColors(LevelOfDetail * geometry, btVector4 * *colorVertices, Node * node) const = 0;

    /**
         *  @author James Folk, 16-02-11 17:02:05
         *
         *  @brief <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
    virtual u64 getNumberOfVertexColors(LevelOfDetail * geometry, Node * node) const = 0;

    /**
         *  @author James Folk, 16-02-11 17:02:14
         *
         *  @brief <#Description#>
         *
         *  @param geometry           <#geometry description#>
         *  @param textureCoordinates <#textureCoordinates description#>
         *  @param node               <#node description#>
         */
    virtual void getTextureCoordinates(LevelOfDetail * geometry, btVector2 * *textureCoordinates, Node * node) const = 0;

    /**
         *  @author James Folk, 16-02-11 17:02:21
         *
         *  @brief <#Description#>
         *
         *  @param geometry <#geometry description#>
         *  @param node     <#node description#>
         *
         *  @return <#return value description#>
         */
    virtual u64 getNumberOfTextureCoordinates(LevelOfDetail * geometry, Node * node) const = 0;

    /**
         *  <#Description#>
         *
         *  @param node    <#node description#>
         *  @param opacity <#opacity description#>
         */
    virtual void setOpacity(Node * node, f32 opacity) = 0;
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
    virtual void setHidden(Node * node, bool hidden = true) = 0;

    /**
         *  <#Description#>
         *
         *  @param node    <#node description#>
         *  @param opacity <#opacity description#>
         */
    virtual bool isHidden(Node * node) const = 0;

    virtual void transformVertices(Node * node, const btTransform& transfrom) = 0;
    /**
         *  <#Description#>
         *
         *  @param node      <#node description#>
         *  @param transform <#transform description#>
         */
    virtual void transformVertexColors(Node * node, const btTransform& transform) = 0;
    /**
         *  <#Description#>
         *
         *  @param node      <#node description#>
         *  @param transform <#transform description#>
         */
    virtual void transformTextureCoordinates(Node * node, const btTransform& transform) = 0;
    /**
         *  <#Description#>
         *
         *  @param node         <#node description#>
         *  @param physicsShape <#physicsShape description#>
         */
    virtual void applyShape(Node * node, PhysicsShape * physicsShape) = 0;

    virtual bool shouldApplyShape(Node *node)const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 numberOfVertices() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 numberOfIndices() const = 0;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const void* getArrayBuffer() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s64 getArrayBufferSize() const = 0;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const void* getElementArrayBuffer() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s64 getElementArrayBufferSize() const = 0;

    virtual void setSize(Node * node, const btVector3& position, const f32 halfSize) = 0;
    virtual void setColor(Node * node, const btVector4& color) = 0;

    void setBlendSource(s32 source);
    void setBlendDestination(s32 dest);
    void setupOpacity(Material * material, Image * image);

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
    virtual bool isLoadedGPU() const;

    /**
         *  <#Description#>
         *
         *  @param index     <#index description#>
         *  @param transform <#transform description#>
         */
    virtual void setTransform(const u64 index, const btTransform& transform);
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    virtual btTransform getTransform(const u64 index);
    
    
    
    
    
    
    /**
     *  <#Description#>
     *
     *  @param index     <#index description#>
     *  @param transform <#transform description#>
     */
    virtual void setColorTransform(const u64 index, const btTransform& transform);
    /**
     *  <#Description#>
     *
     *  @param index <#index description#>
     *
     *  @return <#return value description#>
     */
    virtual btTransform getColorTransform(const u64 index);
    
    
    
    

    virtual void getAabb(Node * node, btVector3 & aabbMin, btVector3 & aabbMax) const;

    void enableBlend(const bool enable = true);
    void enableDepthTest(const bool enable = true);
    void enableStencilTest(const bool enable = true);

    void hide(Camera* camera);
    void show(Camera * camera);
    bool isHidden(Camera * camera) const;
protected:
    virtual void load();
    virtual void unLoad();
    virtual void render(Camera * camera, s32 mode = 0x0004);

    //        virtual void setupShader();

    Node* getParent();
    const Node* getParent() const;

    void addReference(Node*);
    void removeReference(Node*);
    virtual void hideGeometry(Node*) = 0;

    void enableBufferModified(bool modified = true);
    bool isBufferModified() const;
    
    

public:
    static void setPointSize(const f32 size);
    static f32 getPointSize();
    static void setLineWidth(const f32 size);
    static f32 getLineWidth();

    s32 numberOfReferences() const;
    ATTRIBUTE_ALIGNED16(struct)
    TexturedColoredVertex
    {
        TexturedColoredVertex()
            : vertex(0, 0, 0)
            , color(1, 1, 1, 1)
            , texture(0, 0)
            , opacity(1.0f)
            , hidden(0.0f)
        {
        }
        TexturedColoredVertex(const btVector3 vertex,
            const btVector4 color,
            const btVector2 texture,
            const f32 opacity,
            const f32 hidden)
            : vertex(vertex)
            , color(color)
            , texture(texture)
            , opacity(opacity)
            , hidden(hidden)
        {
        }
        btVector3 vertex;
        btVector4 color;
        btVector2 texture;
        f32 opacity;
        f32 hidden;

        operator std::string() const
        {
            char buffer[2048];
            sprintf(buffer, "{{%f, %f, %f}, {%f, %f}, {%f, %f, %f, %f}}", vertex.x(), vertex.y(), vertex.z(), texture.x(), texture.y(), color.x(), color.y(), color.z(), color.w());
            return std::string(buffer);
        }

        TexturedColoredVertex& operator=(const TexturedColoredVertex& rhs)
        {
            if (this != &rhs) {
                vertex = rhs.vertex;
                color = rhs.color;
                texture = rhs.texture;
                opacity = rhs.opacity;
                hidden = rhs.hidden;
            }
            return *this;
        }
    };

    ATTRIBUTE_ALIGNED16(struct)
    TexturedNormaledColoredVertex
    {
        btVector3 vertex;
        btVector3 normal;
        btVector2 texture;
        btVector4 color;

        operator std::string() const
        {
            char buffer[2048];
            sprintf(buffer, "{{%f, %f, %f}, {%f, %f, %f}, {%f, %f}, {%f, %f, %f, %f}}", vertex.x(), vertex.y(), vertex.z(), normal.x(), normal.y(), normal.z(), texture.x(), texture.y(), color.x(), color.y(), color.z(), color.w());
            return std::string(buffer);
        }
    };

    void sort(const btVector3& cameraOrigin);

void setupShader();
private:
    void quickSort(signed long left, signed long right, const btVector3& cameraOrigin);

    void swapTransformData(const size_t idx1, const size_t idx2);
    bool lessThan(const size_t idx1, const size_t idx2, const btVector3& cameraOrigin);
    bool greaterThan(const size_t idx1, const size_t idx2, const btVector3& cameraOrigin);

    virtual void swapVertexData(const size_t idx1, const size_t idx2) = 0;

    void bindTransform();
    void bindColorTransform();
    std::vector<LevelOfDetail*> m_LevelOfDetailList;

    Material* m_Material;
    ShaderProgram* m_ShaderProgram;
    u32 m_projectionMatrixUniform;
//    u32 m_modelViewMatrixUniform;
    u32 m_modelViewBufferID;
    u32 m_colorTransformBufferID;
    f32* m_ModelviewTransform;
    f32 *m_ColorTransform;

    u32 m_InTransformAttrib;
    u32 m_InColorTransform;
    u32 m_verticesBufferID;
    u32 indexBufferID;
    u32 m_vertexArrayID;

    u32 m_InPositionAttrib;
    u32 m_InTexCoordAttrib;
    u32 m_InColorAttrib;
    u32 m_InOpacityAttrib;
    u32 m_InHiddenAttrib;

    std::bitset<NUMBER_OF_MESHES> m_References;

    static f32 s_PointSize;

    s32 m_blendFuncSource;
    s32 m_blendFuncDestination;
    bool _opacityModifyRGB;
//    u32 u_opacityModifyRGB;
    u32 u_pointSize;

    bool m_enableBlend;
    bool m_enableDepthTest;
    bool m_enableStencilTest;

    bool m_TransformDirty;
    bool m_ColorTransformDirty;
    //u64 m_StartCopyTransform;

    bool m_LoadGPU;
    void loadGPU_Internal();

    static f32 s_LineWidth;

    void setupOpacity_Internal(Material * material, Image * image);
    Material* m_setupOpacity_Material;
    Image* m_setupOpacity_Image;
    bool m_setupOpacity;

    bool m_UnLoadGPU;
    void unLoadGPU_Internal();

    //bool m_setupShader;


    bool m_bufferModified;
    bool m_vertexAttribChanged;

    float* m_MatrixBuffer;
    u64 m_maxindice;
    njliBitCategories m_RenderCategory;
};
}

#endif /* defined(__JLIGameEngineTest__Geometry__) */
