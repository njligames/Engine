//
//  Camera.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Camera__
#define __JLIGameEngineTest__Camera__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "JLIFactoryTypes.h"
#include "btVector3.h"
//#include "AbstractTransform.h"
#include "lua.hpp"

struct btDbvtBroadphase;
struct btDbvtNode;
class btVector3;
class btVector2;
class btTransform;

namespace njli {
class CameraBuilder;
struct OcclusionBuffer;
class SceneRenderer;
class Node;
class PhysicsRayContact;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Camera : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class PhysicsWorld;
    friend struct OcclusionBuffer;
    friend class SceneRenderer;
    friend class Node;
    friend class Scene;
    friend class ParticleEmitter;
    friend class World;
    friend class Geometry;
    friend class WorldState;

protected:
    Camera();
    Camera(const AbstractBuilder&);
    Camera(const Camera&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Camera();
    Camera& operator=(const Camera&);

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
         *  @author James Folk, 16-02-11 15:02:17
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
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
    static Camera** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Camera * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Camera* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Camera* create(const CameraBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Camera* clone(const Camera& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Camera* copy(const Camera& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Camera * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Camera & object, lua_State * L, int stack_index);
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
         *  @param val <#val description#>
         */
    void setZNear(const f32 val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getZNear() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setZFar(const f32 val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getZFar() const;

    /**
         *  <#Description#>
         *
         *  @param val <#val description#>
         */
    void setFov(const f32 val);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getFov() const;

    /**
         *  <#Description#>
         *
         *  @param enable <#enable description#>
         */
    void enableOrthographic(const bool enable = true, const f32 near = 1000.0f, const f32 far = -1000.0f);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isOrthographic() const;

    /**
         *  <#Description#>
         *
         *  @param category <#category description#>
         */
    void setRenderCategory(const njliBitCategories category);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    njliBitCategories getRenderCategory() const;
    /**
         *  <#Description#>
         *
         *  @param category <#category description#>
         */
    void addRenderCategory(const njliBitCategories category);
    /**
         *  <#Description#>
         *
         *  @param category <#category description#>
         */
    void removeRenderCategory(const njliBitCategories category);
    /**
         *  <#Description#>
         *
         *  @param category <#category description#>
         *
         *  @return <#return value description#>
         */
    bool hasRenderCategory(const njliBitCategories category);

    /**
         *  <#Description#>
         *
         *  @param windowPosition <#windowPosition description#>
         *
         *  @return <#return value description#>
         */
    btVector3 unProject(const btVector2& windowPosition) const;
    /**
         *  <#Description#>
         *
         *  @param objectPosition <#objectPosition description#>
         *
         *  @return <#return value description#>
         */
    btVector2 project(const btVector3& objectPosition) const;
    /**
         *  <#Description#>
         *
         *  @param windowPosition <#windowPosition description#>
         *  @param from           <#from description#>
         *  @param to             <#to description#>
         */
    void getTouchRay(const btVector2& windowPosition, btVector3& from, btVector3& to);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getForwardVector() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getUpVector() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getSideVector() const;

    /**
         *  @author James Folk, 16-02-11 02:02:03
         *
         *  @brief <#Description#>
         *
         *  @param pos  <#pos description#>
         *  @param up    <#0 description#>
         */
    void lookAt(const btVector3& pos, const btVector3& up = btVector3(0, 1.0f, 0));

    /**
         *  <#Description#>
         *
         *  @param screenPosition <#screenPosition description#>
         *  @param rayContact     <#rayContact description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         */
    bool rayTestClosest(const btVector2& screenPosition,
        PhysicsRayContact& rayContact,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;

    /**
         *  <#Description#>
         *
         *  @param screenPosition <#screenPosition description#>
         *  @param rayContacts    <#rayContacts description#>
         *  @param numContacts    <#numContacts description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         */
    bool rayTestAll(const btVector2& screenPosition,
        btAlignedObjectArray<PhysicsRayContact*>& rayContacts,
        s32& numContacts,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node* getParent();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Node* getParent() const;

    
    /**
     <#Description#>
     */
    void updateViewSize();
protected:
    void cull(btDbvtBroadphase * pbp);

    const btTransform& getProjection() const;
    const f32* getProjectionMatrixArray();
//    const f32* getModelViewMatrixArray();
    btTransform getModelView() const;

    void getViewBounds(f32 & left, f32 & right, f32 & bottom, f32 & top, f32 & farLeft, f32 & farRight, f32 & farBottom, f32 & farTop) const;

    btVector3 getTopLeftVector() const;
    btVector3 getTopRightVector() const;
    btVector3 getBottomLeftVector() const;
    btVector3 getBottomRightVector() const;

    void render(const btDbvtNode* root1,
        const btDbvtNode* root2,
        const btVector3& sortaxis,
        const btVector3* eye = NULL);

private:
    f32 m_Near;
    f32 m_Far;
    f32 m_Fov;
    bool m_Orthographic;
    njliBitCategories m_RenderCategory;

    OcclusionBuffer* m_OcclusionBuffer;
    SceneRenderer* m_SceneRenderer;

    btTransform* m_projectionMatrix;
    f32* m_ProjectionMatrixArray;
    f32* m_ModelViewMatrixArray;

    s32* m_ViewPort;
    btScalar* m_ModelMatrix;
    btScalar* m_ProjectionMatrix;
};
}

#endif /* defined(__JLIGameEngineTest__Camera__) */
