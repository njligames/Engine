//
//  Geometry.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Geometry.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "LevelOfDetail.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "MaterialProperty.h"
#include "GLPlatform.h"
#include "Node.h"

#include "Log.h"
#define TAG "Geometry.cpp"
#define FORMATSTRING "{\"njli::Geometry\":[]}"
#include "btPrint.h"
#include "Image.h"

static const u32 MAX_SPRITES = NUMBER_OF_MESHES;

static const GLfloat IDENTITYMATRIX[] =
{
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
};

namespace njli
{
    f32 Geometry::s_PointSize = 1;
    f32 Geometry::s_LineWidth = 1;
    
    Geometry::Geometry():
    AbstractFactoryObject(this),
//    m_Name("MyGeometry"),
    m_Material(NULL),
    m_ShaderProgram(NULL),
    m_projectionMatrixUniform(-1),
    m_modelViewMatrixUniform(-1),
    m_ModelviewTransform(NULL),
    modelviewBufferID(-1),
    m_InTransformAttrib(-1),
//    m_CurrentMeshCount(-1),
    verticesID(-1),
    indexBufferID(-1),
    vertexArrayID(-1),
    m_InPositionAttrib(-1),
    m_InTexCoordAttrib(-1),
    m_InColorAttrib(-1),
    m_blendFuncSource(GL_SRC_ALPHA),
    m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
    _opacityModifyRGB(false),
    m_enableBlend(true),
    m_enableDepthTest(true),
    m_enableStencilTest(false),
    m_TransformDirty(true),
//    m_StartCopyTransform(std::numeric_limits<u64>::max()),
    m_LoadGPU(false),
    m_setupOpacity_Material(NULL),
    m_setupOpacity_Image(NULL),
    m_setupOpacity(false),
    m_UnLoadGPU(false),
//    m_setupShader(false),
    m_bufferModified(true),
    m_vertexAttribChanged(false),
    m_MatrixBuffer(new float[16])
    {
        enableRenderObject();
    }
    
    Geometry::Geometry(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
//    m_Name("MyGeometry"),
    m_Material(NULL),
    m_ShaderProgram(NULL),
    m_projectionMatrixUniform(-1),
    m_modelViewMatrixUniform(-1),
    m_ModelviewTransform(NULL),
    modelviewBufferID(-1),
    m_InTransformAttrib(-1),
//    m_CurrentMeshCount(-1),
    verticesID(-1),
    indexBufferID(-1),
    vertexArrayID(-1),
    m_InPositionAttrib(-1),
    m_InTexCoordAttrib(-1),
    m_InColorAttrib(-1),
    m_blendFuncSource(GL_SRC_ALPHA),
    m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
    _opacityModifyRGB(false),
    m_enableBlend(true),
    m_enableDepthTest(true),
    m_enableStencilTest(false),
    m_TransformDirty(true),
//    m_StartCopyTransform(std::numeric_limits<u64>::max()),
    m_LoadGPU(false),
    m_setupOpacity_Material(NULL),
    m_setupOpacity_Image(NULL),
    m_setupOpacity(false),
    m_UnLoadGPU(false),
//    m_setupShader(false),
    m_bufferModified(true),
    m_vertexAttribChanged(false),
    m_MatrixBuffer(new float[16])
    {
        enableRenderObject();
    }
    
    Geometry::Geometry(const Geometry &copy):
    AbstractFactoryObject(this),
//    m_Name("MyGeometry"),
    m_Material(NULL),
    m_ShaderProgram(NULL),
    m_projectionMatrixUniform(-1),
    m_modelViewMatrixUniform(-1),
    m_ModelviewTransform(NULL),
    modelviewBufferID(-1),
    m_InTransformAttrib(-1),
//    m_CurrentMeshCount(-1),
    verticesID(-1),
    indexBufferID(-1),
    vertexArrayID(-1),
    m_InPositionAttrib(-1),
    m_InTexCoordAttrib(-1),
    m_InColorAttrib(-1),
    m_InOpacityAttrib(-1),
    m_InHiddenAttrib(-1),
    m_blendFuncSource(GL_SRC_ALPHA),
    m_blendFuncDestination(GL_ONE_MINUS_SRC_ALPHA),
    _opacityModifyRGB(false),
    m_enableBlend(true),
    m_enableDepthTest(true),
    m_enableStencilTest(false),
    m_TransformDirty(true),
//    m_StartCopyTransform(std::numeric_limits<u64>::max()),
    m_LoadGPU(false),
    m_setupOpacity_Material(NULL),
    m_setupOpacity_Image(NULL),
    m_setupOpacity(false),
    m_UnLoadGPU(false),
//    m_setupShader(false),
    m_bufferModified(true),
    m_vertexAttribChanged(false),
    m_MatrixBuffer(new float[16])
    {
        enableRenderObject();
    }
    
    Geometry::~Geometry()
    {
        delete [] m_MatrixBuffer; m_MatrixBuffer = NULL;
        
        unLoadGPU_Internal();
    }
    
    Geometry &Geometry::operator=(const Geometry &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	Geometry::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Geometry::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Geometry::getClassName()const
    {
        return "Geometry";
    }
    
    s32 Geometry::getType()const
    {
        return Geometry::type();
    }
    
    Geometry::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }
    
    Geometry *Geometry::create(u32 type)
    {
        DEBUG_ASSERT(type == JLI_OBJECT_TYPE_Plane);
        
        return dynamic_cast<Geometry*>(World::getInstance()->getWorldFactory()->create(type));
    }
    
    void Geometry::destroy(Geometry *object)
    {
        if(object)
        {
            object->removeMaterial();
            object->removeShaderProgram();
            object->removeAllLevelOfDetails();
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Geometry::load(Geometry &object, lua_State *L, int index)
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
                Geometry::load(object, L, -2);
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
    
    u32 Geometry::type()
    {
        return JLI_OBJECT_TYPE_Geometry;
    }
    
    void Geometry::addLevelOfDetail(LevelOfDetail *lod)
    {
        DEBUG_ASSERT(NULL != lod);
        
        std::vector<LevelOfDetail*>::const_iterator iter = std::find(m_LevelOfDetailList.begin(), m_LevelOfDetailList.end(), lod);
        
        if(iter == m_LevelOfDetailList.end())
        {
            std::vector<LevelOfDetail*>::iterator iter = std::find(m_LevelOfDetailList.begin(), m_LevelOfDetailList.end(), lod);
            
            if(iter != m_LevelOfDetailList.end())
                removeLevelOfDetail(lod);
            
            m_LevelOfDetailList.push_back(lod);
            
            addChild(lod);
        }
    }
    
    bool Geometry::removeLevelOfDetail(LevelOfDetail *lod)
    {DEBUG_ASSERT(NULL != lod);
        
        std::vector<LevelOfDetail*>::iterator iter = std::find(m_LevelOfDetailList.begin(), m_LevelOfDetailList.end(), lod);
        
        if(iter != m_LevelOfDetailList.end())
        {
            removeChild(*iter);
            m_LevelOfDetailList.erase(iter);
            return true;
        }
        return false;
    }
    
    void Geometry::removeAllLevelOfDetails()
    {
        for(std::vector<LevelOfDetail*>::iterator iter = m_LevelOfDetailList.begin();
            iter != m_LevelOfDetailList.end();
            ++iter)
        {
            removeChild(*iter);
        }
        m_LevelOfDetailList.clear();
    }
    
    void Geometry::getLevelOfDetails(std::vector<LevelOfDetail*> &particleEmitters)const
    {
        for(std::vector<LevelOfDetail*>::const_iterator iter = m_LevelOfDetailList.begin();
            iter != m_LevelOfDetailList.end();
            ++iter)
        {
            if(getChildIndex(*iter) != -1)
                particleEmitters.push_back(*iter);
        }
    }
    
    LevelOfDetail *Geometry::getLevelOfDetail(const u32 index)
    {
        if (index < m_LevelOfDetailList.size())
        {
            s32 idx = getChildIndex(m_LevelOfDetailList.at(index));
            if(idx != -1)
                return dynamic_cast<LevelOfDetail*>(getChild(idx));
        }
        return NULL;
    }
    
    const LevelOfDetail *Geometry::getLevelOfDetail(const u32 index)const
    {
        if (index < m_LevelOfDetailList.size())
        {
            s32 idx = getChildIndex(m_LevelOfDetailList.at(index));
            if(idx != -1)
                return dynamic_cast<const LevelOfDetail*>(getChild(idx));
        }
        return NULL;
    }
    
    void Geometry::addMaterial(Material *material, Image *img)
    {
        DEBUG_ASSERT(material != NULL);
        
        removeMaterial();
        
        m_Material = material;
        
        addChild(m_Material);
        
        if(img)
        {
            bool hasAlpha = img->getNumberOfComponents() == 4 || img->getNumberOfComponents() == 2;
            bool premultiplied = img->getNumberOfComponents() != 1 && hasAlpha;
            
            _opacityModifyRGB = false;
            if (m_blendFuncSource == GL_ONE && m_blendFuncDestination == GL_ONE_MINUS_SRC_ALPHA)
            {
                if (premultiplied)
                    _opacityModifyRGB = true;
                else {
                    m_blendFuncSource = GL_SRC_ALPHA;
                    m_blendFuncDestination = GL_ONE_MINUS_SRC_ALPHA;
                }
            }
            
            if(premultiplied)
                img->preMultiplyAlpha();
        }
    }
    
    void Geometry::removeMaterial()
    {
        if(getMaterial())
        {
            removeChild(getMaterial());
        }
        
        m_Material = NULL;
    }
    
    Material *Geometry::getMaterial()
    {
        s32 idx = getChildIndex(m_Material);
        if(idx != -1)
            return dynamic_cast<Material*>(getChild(idx));
        return NULL;
    }
    const Material *Geometry::getMaterial() const
    {
        s32 idx = getChildIndex(m_Material);
        if(idx != -1)
            return dynamic_cast<const Material*>(getChild(idx));
        return NULL;
    }
    
    void Geometry::addShaderProgram(ShaderProgram *shader)
    {
        DEBUG_ASSERT(shader != NULL);
        
        removeShaderProgram();
        
        m_ShaderProgram = shader;
        
        addChild(m_ShaderProgram);
        
        
//        setupShader();
        setupShader_Internal();
    }
    
    void Geometry::removeShaderProgram()
    {
        ShaderProgram *shader = getShaderProgram();
        if(NULL != shader)
        {
            removeChild(shader);
        }
        
        m_ShaderProgram = NULL;
    }
    
    ShaderProgram *Geometry::getShaderProgram()
    {
        s32 idx = getChildIndex(m_ShaderProgram);
        if(idx != -1)
            return dynamic_cast<ShaderProgram*>(getChild(idx));
        return NULL;
    }
    
    const ShaderProgram *Geometry::getShaderProgram() const
    {
        s32 idx = getChildIndex(m_ShaderProgram);
        if(idx != -1)
            return dynamic_cast<const ShaderProgram*>(getChild(idx));
        return NULL;
    }
    
    u32 Geometry::getMaxMeshes()const
    {
        return MAX_SPRITES;
    }
    
    void Geometry::setBlendSource(s32 source)
    {
        m_blendFuncSource = source;
    }
    
    void Geometry::setBlendDestination(s32 dest)
    {
        m_blendFuncDestination = dest;
    }
    
    void Geometry::setupOpacity(Material *material, Image *img)
    {
        m_setupOpacity_Material = material;
        m_setupOpacity_Image = img;
        m_setupOpacity = true;
    }
    
    void Geometry::loadGPU()
    {
        m_LoadGPU = true;
    }
    
    void Geometry::unLoadGPU()
    {
        m_UnLoadGPU = true;
    }
    
    bool Geometry::isLoadedGPU()const
    {
        return (verticesID != -1);
    }
    
    void Geometry::setTransform(const u64 index, const btTransform &transform)
    {
        if (index < getMaxMeshes())
        {
            const GLuint STRIDE = 64;
//            static GLfloat m[16];
//            GLfloat *m = new GLfloat[16];
            transform.getOpenGLMatrix(m_MatrixBuffer);
            
//            m_StartCopyTransform = btMin<u64>(m_StartCopyTransform, (index * STRIDE));
            m_TransformDirty = true;
            for (int currentVertex = 0; currentVertex < numberOfVertices(); currentVertex++)
            {
                memcpy(m_ModelviewTransform + ((index * STRIDE) + (16 * currentVertex)), m_MatrixBuffer, sizeof(f32) * 16);
            }
        }
    }

    void Geometry::sort(const btVector3 &cameraOrigin)
    {
        quickSort(0, m_maxindice, cameraOrigin);
    }
    
    void Geometry::quickSort(signed long left, signed long right, const btVector3 &cameraOrigin)
    {
        DEBUG_ASSERT(left >= 0 && left < getMaxMeshes());
        DEBUG_ASSERT(right >= 0 && right < getMaxMeshes());
        
        signed long i = left, j = right;
        signed long pivot = (left + right) / 2;
        
        while (i <= j)
        {
            while (lessThan(i, pivot, cameraOrigin))
                ++i;
            while(greaterThan(j, pivot, cameraOrigin))
                --j;
            if (i <= j)
            {
                swapTransformData(i, j);
//                swapVertexData(i, j);
                
                ++i;
                --j;
            }
        }
        
        if (left < j)
            quickSort(left, j, cameraOrigin);
        if (i < right)
            quickSort(i, right, cameraOrigin);
    }
    
    void Geometry::swapTransformData(const size_t idx1, const size_t idx2)
    {
        btTransform temp(getTransform(idx1));
        setTransform(idx1, getTransform(idx2));
        setTransform(idx2, temp);
        
    }
    bool Geometry::lessThan(const size_t idx1, const size_t idx2, const btVector3 &cameraOrigin)
    {
        btVector3 object1(getTransform(idx1).getOrigin());
        btVector3 object2(getTransform(idx2).getOrigin());
        
        return cameraOrigin.distance2(object1) < cameraOrigin.distance2(object2);
    }
    
    bool Geometry::greaterThan(const size_t idx1, const size_t idx2, const btVector3 &cameraOrigin)
    {
        btVector3 object1(getTransform(idx1).getOrigin());
        btVector3 object2(getTransform(idx2).getOrigin());
        
        return cameraOrigin.distance2(object1) > cameraOrigin.distance2(object2);
    }
    
    btTransform Geometry::getTransform(const u64 index)
    {
        btTransform transform(btTransform::getIdentity());
        if (index < getMaxMeshes())
        {
            const GLuint STRIDE = 64;
//            static GLfloat m[16];
//            GLfloat *m = new GLfloat[16];
            
            for (int currentVertex = 0; currentVertex < numberOfVertices(); currentVertex++)
            {
                memcpy(m_MatrixBuffer, m_ModelviewTransform + ((index * STRIDE) + (16 * currentVertex)), sizeof(f32) * 16);
            }
            
            transform.setFromOpenGLMatrix(m_MatrixBuffer);
            
//            delete [] m;m=NULL;
        }
        return transform;
    }
    
    void Geometry::getAabb(Node *node, btVector3& aabbMin,btVector3& aabbMax) const
    {
        aabbMin = btVector3(0,0,0);
        aabbMax = btVector3(0,0,0);
    }
    
    void Geometry::enableBlend(const bool enable)
    {
        m_enableBlend = enable;
    }
    
    void Geometry::enableDepthTest(const bool enable)
    {
        m_enableDepthTest = enable;
    }
    
    void Geometry::enableStencilTest(const bool enable)
    {
        m_enableStencilTest = enable;
    }
    
    void Geometry::load()
    {
        unLoad();
        
        m_ModelviewTransform = new f32[MAX_SPRITES * numberOfVertices() * 16];
        memset(m_ModelviewTransform, 0, sizeof(f32) * MAX_SPRITES * numberOfVertices() * 16);
        m_TransformDirty = true;
//        m_StartCopyTransform = 0;
        
        for (int i = 0; i < MAX_SPRITES * numberOfVertices() * 16; i += 16)
        {
            memcpy(m_ModelviewTransform + i, IDENTITYMATRIX, sizeof(IDENTITYMATRIX));
        }
        
        m_References.reset();
//        std::string ids = m_References.to_string();
//        DEBUG_LOG_V("", "reset\t%s", ids.c_str());
    }
    void Geometry::unLoad()
    {
        if(m_ModelviewTransform)
            delete [] m_ModelviewTransform;
        m_ModelviewTransform=NULL;
    }
    
    void Geometry::render(Camera *camera, s32 mode)
    {
        Material *material = getMaterial();
        ShaderProgram *shader = getShaderProgram();
        
        if (m_UnLoadGPU)
            unLoadGPU_Internal();
        
        if (m_setupOpacity)
            setupOpacity_Internal(m_setupOpacity_Material, m_setupOpacity_Image);
        
        glLineWidth(s_LineWidth);
        
        if (m_LoadGPU)
            loadGPU_Internal();
        
//        if(m_setupShader)
//            setupShader_Internal();
        
        if (m_enableBlend)
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);
        
        if (m_enableDepthTest)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
        
        if (m_enableStencilTest)
            glEnable(GL_STENCIL_TEST);
        else
            glDisable(GL_STENCIL_TEST);
        
        glBlendFunc(m_blendFuncSource, m_blendFuncDestination);
        
        if(NULL != shader)
            shader->use();

        if(NULL != material && NULL != shader)
            material->bind(shader);
            
        glUniformMatrix4fv(m_modelViewMatrixUniform, 1, 0, camera->getModelViewMatrixArray());
        glUniformMatrix4fv(m_projectionMatrixUniform, 1, 0, camera->getProjectionMatrixArray());
        glUniform1i(u_opacityModifyRGB, _opacityModifyRGB);
        
        glBindVertexArrayAPPLE(vertexArrayID);
        
        if(!isLoadedGPU())
        {
            m_LoadGPU = true;
            loadGPU_Internal();
        }
        
        bindTransform();
        
        glBindBuffer(GL_ARRAY_BUFFER, verticesID);
        
        if(isBufferModified())
        {
            glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)getArrayBufferSize(), getArrayBuffer());
            m_bufferModified = false;
//            printf("buffer");
        }
        
        if (m_vertexAttribChanged)
        {
//            m_vertexAttribChanged = false;
            
            glEnableVertexAttribArray(m_InPositionAttrib);
            glVertexAttribPointer(m_InPositionAttrib,
                                  3,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(TexturedColoredVertex),
                                  (const GLvoid*) offsetof(TexturedColoredVertex, vertex));
            
            glEnableVertexAttribArray(m_InTexCoordAttrib);
            glVertexAttribPointer(m_InTexCoordAttrib,
                                  2,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(TexturedColoredVertex),
                                  (const GLvoid*) offsetof(TexturedColoredVertex, texture));
            
            glEnableVertexAttribArray(m_InColorAttrib);
            glVertexAttribPointer(m_InColorAttrib,
                                  4,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(TexturedColoredVertex),
                                  (const GLvoid*) offsetof(TexturedColoredVertex, color));
            
            glEnableVertexAttribArray(m_InOpacityAttrib);
            glVertexAttribPointer(m_InOpacityAttrib,
                                  1,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(TexturedColoredVertex),
                                  (const GLvoid*)offsetof(TexturedColoredVertex, opacity));
            
            glEnableVertexAttribArray(m_InHiddenAttrib);
            glVertexAttribPointer(m_InHiddenAttrib,
                                  1,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  sizeof(TexturedColoredVertex),
                                  (const GLvoid*)offsetof(TexturedColoredVertex, hidden));
        }
        
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
        
        glDrawElements(mode, static_cast<GLsizei>((getMaxMeshes()) * numberOfIndices()), GL_UNSIGNED_SHORT, (const GLvoid*)0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        if(material)
            material->unBind();
    }
    
//    void Geometry::setupShader()
//    {
//        m_setupShader = true;
//        
//    }
    
    void Geometry::bindTransform()
    {
        if(m_TransformDirty)
        {
            const GLuint STRIDE = 64;
            
            glBindBuffer(GL_ARRAY_BUFFER, modelviewBufferID);
            
            GLsizei size = sizeof(GLfloat) * getMaxMeshes() * numberOfVertices() * 16;
            
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_ModelviewTransform);
            
            if (m_vertexAttribChanged)
            {
                glEnableVertexAttribArray(m_InTransformAttrib + 0);
                glEnableVertexAttribArray(m_InTransformAttrib + 1);
                glEnableVertexAttribArray(m_InTransformAttrib + 2);
                glEnableVertexAttribArray(m_InTransformAttrib + 3);
                glVertexAttribPointer(m_InTransformAttrib + 0, 4, GL_FLOAT, 0, STRIDE, (GLvoid*)0);
                glVertexAttribPointer(m_InTransformAttrib + 1, 4, GL_FLOAT, 0, STRIDE, (GLvoid*)16);
                glVertexAttribPointer(m_InTransformAttrib + 2, 4, GL_FLOAT, 0, STRIDE, (GLvoid*)32);
                glVertexAttribPointer(m_InTransformAttrib + 3, 4, GL_FLOAT, 0, STRIDE, (GLvoid*)48);
            }
            
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            m_TransformDirty = false;
            
//            DEBUG_LOG_V(TAG, "%llu\n", m_StartCopyTransform);
            
//            m_StartCopyTransform = std::numeric_limits<u64>::max();
        }
    }
    
//    void Geometry::resetMeshCount()
//    {
//        m_CurrentMeshCount = -1;
//    }
    
    Node *Geometry::getParent()
    {
        return dynamic_cast<Node*>(AbstractDecorator::getParent());
    }
    
    const Node *Geometry::getParent()const
    {
        return dynamic_cast<const Node*>(AbstractDecorator::getParent());
    }
    
    void Geometry::addReference(Node *node)
    {
        for (s32 i = 0; i < m_References.size(); ++i)
        {
            if (!m_References[i])
            {
                m_References[i] = 1;
                
//                std::string ids = m_References.to_string();
//                DEBUG_LOG_V("", "add\t%s", ids.c_str());
                
                node->setGeometryIndex(i);
                return;
            }
        }
    }
    void Geometry::removeReference(Node *node)
    {
        size_t index = node->getGeometryIndex();
        if(index < m_References.size())
        {
            m_References[index] = 0;
            
//            std::string ids = m_References.to_string();
//            DEBUG_LOG_V("", "remove\t%s", ids.c_str());
            
            hideGeometry(node);
        }
    }
    
    void Geometry::enableBufferModified(bool modified)
    {
        m_bufferModified = modified;
    }
    
    bool Geometry::isBufferModified()const
    {
        return m_bufferModified;
    }
    
    void Geometry::setPointSize(const f32 s)
    {
        s_PointSize = s;
    }
    
    f32 Geometry::getPointSize()
    {
        return s_PointSize;
    }
    
    void Geometry::setLineWidth(const f32 s)
    {
        DEBUG_ASSERT(s >= 0.0);
        s_LineWidth = s;
    }
    
    f32 Geometry::getLineWidth()
    {
        return s_LineWidth;
    }
    
    s32 Geometry::numberOfReferences()const
    {
        return m_References.size();
    }
    
    void Geometry::loadGPU_Internal()
    {
        DEBUG_ASSERT(m_LoadGPU);
        
        
        DEBUG_ASSERT(vertexArrayID == -1);
        glGenVertexArraysAPPLE(1, &vertexArrayID);
        glBindVertexArrayAPPLE(vertexArrayID);
        
        DEBUG_ASSERT(modelviewBufferID == -1);
        glGenBuffers(1, &modelviewBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, modelviewBufferID);
        
        GLsizei size = sizeof(GLfloat) * getMaxMeshes() * numberOfVertices() * 16;
        glBufferData(GL_ARRAY_BUFFER, size, m_ModelviewTransform, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        DEBUG_ASSERT(verticesID == -1);
        glGenBuffers(1, &verticesID);
        glBindBuffer(GL_ARRAY_BUFFER, verticesID);
        glBufferData(GL_ARRAY_BUFFER, (long)getArrayBufferSize(), getArrayBuffer(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        DEBUG_ASSERT(indexBufferID == -1);
        glGenBuffers(1, &indexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long)getElementArrayBufferSize(), getElementArrayBuffer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glBindVertexArrayAPPLE(0);
        
        m_LoadGPU = false;
    }
    
    void Geometry::setupOpacity_Internal(Material *material, Image *img)
    {
        DEBUG_ASSERT(m_setupOpacity);
        
        bool hasAlpha = img->getNumberOfComponents() == 4 || img->getNumberOfComponents() == 2;
        bool premultiplied = img->getNumberOfComponents() != 1 && hasAlpha;
        
        _opacityModifyRGB = false;
        if (m_blendFuncSource == GL_ONE && m_blendFuncDestination == GL_ONE_MINUS_SRC_ALPHA)
        {
            if (premultiplied)
                _opacityModifyRGB = true;
            else {
                m_blendFuncSource = GL_SRC_ALPHA;
                m_blendFuncDestination = GL_ONE_MINUS_SRC_ALPHA;
            }
        }
        
        if(premultiplied)
            img->preMultiplyAlpha();
        
        material->getDiffuse()->loadGPU(*img);
        
        m_setupOpacity = false;
    }
    
    void Geometry::unLoadGPU_Internal()
    {
        DEBUG_ASSERT(m_UnLoadGPU);
        
        if(modelviewBufferID == -1)
        {
            glDeleteBuffers(1, &modelviewBufferID);
            modelviewBufferID = -1;
        }
        
        if(indexBufferID == -1)
        {
            glDeleteBuffers(1, &indexBufferID);
            indexBufferID = -1;
        }
        
        if(verticesID == -1)
        {
            glDeleteBuffers(1, &verticesID);
            verticesID = -1;
        }
        
        if(vertexArrayID == -1)
        {
            glDeleteVertexArraysAPPLE(1, &vertexArrayID);
            vertexArrayID = -1;
        }
        
        m_UnLoadGPU = false;
    }
    
    void Geometry::setupShader_Internal()
    {
//        DEBUG_ASSERT(m_setupShader);
        
        ShaderProgram *shader = getShaderProgram();
        
        DEBUG_ASSERT(shader);
        
        
        if (!shader->isLinked())
        {
            if(!shader->link())
            {
                DEBUG_LOG_PRINT_E(TAG, "%s", "Linking failed");
                DEBUG_LOG_PRINT_E(TAG, "Program log: %s", shader->programLog());
                DEBUG_LOG_PRINT_E(TAG, "Vertex log: %s", shader->vertexShaderLog());
                DEBUG_LOG_PRINT_E(TAG, "Fragment log: %s", shader->fragmentShaderLog());
            }
        }
        // ... and add the attributes the shader needs for the vertex position, color and texture st information
        shader->bindAttribute("inPosition");
        shader->bindAttribute("inTexCoord");
        shader->bindAttribute("inColor");
        shader->bindAttribute("inOpacity");
        shader->bindAttribute("inHidden");
        
        shader->bindAttribute("inTransform");
        
        // Setup the index pointers into the shader for our attributes
        m_InPositionAttrib = shader->getAttributeIndex("inPosition");
        m_InTexCoordAttrib = shader->getAttributeIndex("inTexCoord");
        m_InColorAttrib = shader->getAttributeIndex("inColor");
        m_InOpacityAttrib = shader->getAttributeIndex("inOpacity");
        m_InHiddenAttrib = shader->getAttributeIndex("inHidden");
        
        
        
        shader->use();
        
        m_InTransformAttrib = shader->getAttributeIndex("inTransform");
        
        m_modelViewMatrixUniform = shader->getUniformIndex("modelView");
        m_projectionMatrixUniform = shader->getUniformIndex("projection");
        u_opacityModifyRGB = shader->getUniformIndex("u_opacityModifyRGB");
        //        u_pointSize = shader->getUniformIndex("u_pointSize");
        
//        m_setupShader = false;
        m_vertexAttribChanged = true;
    }
    
}
