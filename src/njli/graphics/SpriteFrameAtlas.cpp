//
//  SpriteFrameAtlas.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/25/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "SpriteFrameAtlas.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SpriteFrameAtlasBuilder.h"
#include <string>
#include "Log.h"
#define TAG "SpriteFrameAtlas.cpp"
#define FORMATSTRING "{\"njli::SpriteFrameAtlas\":[]}"
#define RECT_FORMATSTRING "{\"njli::Rect\":[%s,%s,%s,%s,%s,%s,%s]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include <string>

#define ASDF (2)

namespace njli
{
    Rect::Rect():
    offset(new btVector2()),
    dimension(new btVector2()),
    dimensionFile(new btVector2()),
    pivotPoint(new btVector2()),
    trimmedname(""),
    sourcePosition(new btVector2()),
    sourceDimension(new btVector2()),
    populationCount(0)
    {
        
    }
    Rect::Rect(const Rect &copy):
    offset(new btVector2(*(copy.offset))),
    dimension(new btVector2(*(copy.dimension))),
    dimensionFile(new btVector2(*(copy.dimensionFile))),
    pivotPoint(new btVector2(*(copy.pivotPoint))),
    trimmedname(copy.trimmedname),
    sourcePosition(new btVector2(*(copy.sourcePosition))),
    sourceDimension(new btVector2(*(copy.sourceDimension))),
    populationCount(0)
    {
    }
    Rect &Rect::operator=(const Rect &rhs)
    {
        if(this != &rhs)
        {
            *offset = *(rhs.offset);
            *dimension = *(rhs.dimension);
            *dimensionFile = *(rhs.dimensionFile);
            *pivotPoint = *(rhs.pivotPoint);
            trimmedname = rhs.trimmedname;
            
            *sourcePosition = *(rhs.sourcePosition);
            *sourceDimension = *(rhs.sourceDimension);
        }
        return *this;
    }
    Rect::~Rect()
    {
        delete pivotPoint;pivotPoint=NULL;
        delete dimensionFile;dimensionFile=NULL;
        delete dimension;dimension=NULL;
        delete offset;offset=NULL;
        delete sourcePosition;sourcePosition = NULL;
        delete sourceDimension;sourceDimension = NULL;
    }
    void Rect::setX(const f32 x)
    {
        DEBUG_ASSERT(x >= 0);
        offset->setX(x);
        populationCount++;
    }
    void Rect::setY(const f32 y)
    {
        DEBUG_ASSERT(y >= 0);
        offset->setY(y);
        populationCount++;
    }
    void Rect::setWidth(const f32 width)
    {
        DEBUG_ASSERT(width >= 0);
        dimension->setX(width);
        populationCount++;
    }
    void Rect::setHeight(const f32 height)
    {
        DEBUG_ASSERT(height >= 0);
        dimension->setY(height);
        populationCount++;
    }
    
    void Rect::setWidthFile(const f32 width)
    {
        DEBUG_ASSERT(width >= 0);
        dimensionFile->setX(width);
        populationCount++;
    }
    void Rect::setHeightFile(const f32 height)
    {
        DEBUG_ASSERT(height >= 0);
        dimensionFile->setY(height);
        populationCount++;
    }
    
    void Rect::setPivotX(const f32 x)
    {
        DEBUG_ASSERT(x >= 0);
        pivotPoint->setX(x);
        populationCount++;
    }
    
    void Rect::setPivotY(const f32 y)
    {
        DEBUG_ASSERT(y >= 0);
        pivotPoint->setY(y);
        populationCount++;
    }
    
    void Rect::setOffset(const btVector2 &offset)
    {
        *(this->offset) = offset;
    }
    void Rect::setDimension(const btVector2 &dimension)
    {
        *(this->dimension) = dimension;
    }
    void Rect::setDimensionFile(const btVector2 &dimension)
    {
        *(this->dimensionFile) = dimension;
    }
    void Rect::setPivotPoint(const btVector2 &pivotPoint)
    {
        *(this->pivotPoint) = pivotPoint;
    }
    
    void Rect::setTrimmedName(const char *trimmedname)
    {
        DEBUG_ASSERT(trimmedname);
        
        this->trimmedname = trimmedname;
        populationCount++;
    }
    
    bool Rect::finishedPopulating()const
    {
        DEBUG_ASSERT(populationCount <= 9 + 4);
        return (populationCount >= 9 + 4);
    }
    
    void Rect::resetPopulation()
    {
        populationCount = 0;
    }
    
    const btVector2 &Rect::getOffset()const
    {
        return *offset;
    }
    const btVector2 &Rect::getDimension()const
    {
        return *dimension;
    }
    const btVector2 &Rect::getDimensionFile()const
    {
        return *dimensionFile;
    }
    const btVector2 &Rect::getPivotPoint()const
    {
        return *pivotPoint;
    }
    
    const std::string &Rect::getTrimmedName()const
    {
        return this->trimmedname;
    }
    
    Rect::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
//        std::string _offset = createJsonKeyValue("offset", toJsonString(getOffset()));
//        std::string _dimension = createJsonKeyValue("dimension", toJsonString(getDimension()));
//        std::string _dimensionFile = createJsonKeyValue("dimensionFile", toJsonString(getDimensionFile()));
//        std::string _pivotPoint = createJsonKeyValue("pivotPoint", toJsonString(getPivotPoint()));
//        std::string _trimmedname = createJsonKeyValue("trimmedName", toJsonString(getTrimmedName()));
//        std::string _sourcePosition = createJsonKeyValue("sourcePosition", toJsonString(getSource()));
//        std::string _sourceDimension = createJsonKeyValue("sourceDimension", toJsonString(getSourceDimension()));
//        
//        
//        std::string ret = string_format(RECT_FORMATSTRING,
//                                        _offset.c_str(),
//                                        _dimension.c_str(),
//                                        _dimensionFile.c_str(),
//                                        _pivotPoint.c_str(),
//                                        _trimmedname.c_str(),
//                                        _sourcePosition.c_str(),
//                                        _sourceDimension.c_str());
//        
//        ret = njli::JsonJLI::parse(ret.c_str());
//        
//        return ret;
    }
    
    void Rect::setSouceX(const f32 x)
    {
        sourcePosition->setX(x);populationCount++;
    }
    void Rect::setSourceY(const f32 y)
    {
        sourcePosition->setY(y);populationCount++;
    }
    void Rect::setSourceWidth(const f32 width)
    {
        sourceDimension->setX(width);populationCount++;
    }
    void Rect::setSourceHeight(const f32 height)
    {
        sourceDimension->setY(height);populationCount++;
    }
    
    const btVector2 &Rect::getSource()const
    {
        return *sourcePosition;
    }
    
    const btVector2 &Rect::getSourceDimension()const
    {
        return *sourceDimension;
    }
    
    SpriteFrameAtlas::SpriteFrameAtlas():
    AbstractFactoryObject(this),
    m_ContentDimension(new btVector2())
    {
        
    }
    
    SpriteFrameAtlas::SpriteFrameAtlas(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_ContentDimension(new btVector2())
    {
        
    }
    
    SpriteFrameAtlas::SpriteFrameAtlas(const SpriteFrameAtlas &copy):
    AbstractFactoryObject(this),
    m_ContentDimension(new btVector2())
    {
        
    }
    
    SpriteFrameAtlas::~SpriteFrameAtlas()
    {
        
    }
    
    SpriteFrameAtlas &SpriteFrameAtlas::operator=(const SpriteFrameAtlas &rhs)
    {
        if(this != &rhs)
        {
            //TODO: implement...
        }
        return *this;
    }
    
    s32	SpriteFrameAtlas::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void SpriteFrameAtlas::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *SpriteFrameAtlas::getClassName()const
    {
        return "SpriteFrameAtlas";
    }
    
    s32 SpriteFrameAtlas::getType()const
    {
        return SpriteFrameAtlas::type();
    }
    
    SpriteFrameAtlas::operator std::string() const
    {
//        std::string json_ = createJsonKeyValue("Source Filename", getSourceFilename());
//        std::string json_dimension = toJsonString(contentDimension());
//        
//        for (s32 i = 0; i < m_Frames.size(); ++i)
//        {
//            std::string frame = m_Frames[i];
//        }
        
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    SpriteFrameAtlas **SpriteFrameAtlas::createArray(const u32 size)
    {
        return (SpriteFrameAtlas**)World::getInstance()->getWorldFactory()->createArray(SpriteFrameAtlas::type(), size);
    }
    
    void SpriteFrameAtlas::destroyArray(SpriteFrameAtlas **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SpriteFrameAtlas *SpriteFrameAtlas::create()
    {
        return dynamic_cast<SpriteFrameAtlas*>(World::getInstance()->getWorldFactory()->create(SpriteFrameAtlas::type()));
    }
    
    SpriteFrameAtlas *SpriteFrameAtlas::create(const SpriteFrameAtlasBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<SpriteFrameAtlas*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    SpriteFrameAtlas *SpriteFrameAtlas::clone(const SpriteFrameAtlas &object)
    {
        return dynamic_cast<SpriteFrameAtlas*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    SpriteFrameAtlas *SpriteFrameAtlas::copy(const SpriteFrameAtlas &object)
    {
        return dynamic_cast<SpriteFrameAtlas*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void SpriteFrameAtlas::destroy(SpriteFrameAtlas *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
//    s32 SpriteFrameAtlas::countParameters = 0;
    njli::Rect SpriteFrameAtlas::rect;
    void SpriteFrameAtlas::load(SpriteFrameAtlas &object, lua_State *L, int index)
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
//            const char *key = lua_tostring(L, -1);
//            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
//                DEBUG_ASSERT(countParameters == 0 || countParameters == 7 || countParameters == 11);
//
                if(rect.finishedPopulating())
                {
                    object.addFrame(rect);
                    rect.resetPopulation();
                }
//                if(countParameters == 7)// || countParameters == 11)
//                    object.addFrame(rect);
//                countParameters = 0;
                
                SpriteFrameAtlas::load(object, L, -2);
            }
            else
            {
                std::string key(lua_tostring(L, -1));
                std::transform(key.begin(), key.end(), key.begin(), ::tolower);
                
                if(strcmp(key.c_str(), "sheetcontentwidth") == 0)
                {
                    double number = lua_tonumber(L, index);
                    object.setSheetContentWidth(number);
                }
                else if(strcmp(key.c_str(), "sheetcontentheight") == 0)
                {
                    double number = lua_tonumber(L, index);
                    object.setSheetContentHeight(number);
                }
                else if(strcmp(key.c_str(), "filename") == 0)
                {
                    const char *value = lua_tostring(L, index);
                    object.setSourceFilename(value);
                }
                
                else if(strcmp(key.c_str(), "scale") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "shapepadding") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "borderpadding") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "commondivisorx") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "commondivisory") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "extrude") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "basefactor") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "maxtexturesizewidth") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "maxtexturesizeheight") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "fixedtexturesizewidth") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                else if(strcmp(key.c_str(), "fixedtexturesizeheight") == 0)
                {
                    //TODO: implement...
                    double number = lua_tonumber(L, index);
//                    DEBUG_LOG_W(TAG, "TODO - %s => %f\n", key.c_str(), number);
                }
                
                else
                {
//                    ++countParameters;
                    
                    if(strcmp(key.c_str(), "x") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setX(number);
                    }
                    else if(strcmp(key.c_str(), "y") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setY(number);
                    }
                    else if(strcmp(key.c_str(), "width") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setWidth(number);
                    }
                    else if(strcmp(key.c_str(), "height") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setHeight(number);
                    }
                    else if(strcmp(key.c_str(), "widthfile") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setWidthFile(number);
                    }
                    else if(strcmp(key.c_str(), "heightfile") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setHeightFile(number);
                    }
                    else if(strcmp(key.c_str(), "pivotx") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setPivotX(number);
                    }
                    else if(strcmp(key.c_str(), "pivoty") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setPivotY(number);
                    }
                    else if(strcmp(key.c_str(), "trimmedname") == 0)
                    {
                        const char *value = lua_tostring(L, index);
                        rect.setTrimmedName(value);
                    }
                    else if(strcmp(key.c_str(), "sourcex") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setSouceX(number);
//                        rect.setTrimmedName(value);
                    }
                    else if(strcmp(key.c_str(), "sourcey") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setSourceY(number);
//                        rect.setTrimmedName(value);
                    }
                    else if(strcmp(key.c_str(), "sourcewidth") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setSourceWidth(number);
//                        rect.setTrimmedName(value);
                    }
                    else if(strcmp(key.c_str(), "sourceheight") == 0)
                    {
                        double number = lua_tonumber(L, index);
                        rect.setSourceHeight(number);
//                        rect.setTrimmedName(value);
                    }
                    else
                    {
                        DEBUG_LOG_PRINT_E(TAG, "invalid key: %s\n", key.c_str());
                        DEBUG_ASSERT(false);
                    }
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            
//            if(countParameters == 11)
//            {
//                object.addFrame(rect);
//                countParameters = 0;
//            }
            // stack now contains: -1 => key; -2 => table
            
            if(rect.finishedPopulating())
            {
                object.addFrame(rect);
                rect.resetPopulation();
            }
            
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 SpriteFrameAtlas::type()
    {
        return JLI_OBJECT_TYPE_SpriteFrameAtlas;
    }
    
    void SpriteFrameAtlas::setSourceFilename(const char *filename)
    {
        DEBUG_ASSERT(filename);
        
        m_SourceFilename = std::string(filename);
    }
    
    void SpriteFrameAtlas::setSheetContentWidth(const u32 width)
    {
        m_ContentDimension->setX(width);
    }
    
    void SpriteFrameAtlas::setSheetContentHeight(const u32 height)
    {
        m_ContentDimension->setY(height);
    }
    
    void SpriteFrameAtlas::addFrame(Rect rect)
    {
        m_Frames.push_back(rect);
//        m_FrameNames.insert(btHashString(rect.getTrimmedName().c_str()), rect);
    }
    
    const Rect &SpriteFrameAtlas::getFrame(const char *name)const
    {
        DEBUG_ASSERT(name);
        
        for (s32 i = 0; i < m_Frames.size(); ++i)
        {
            const char *s = m_Frames.at(i).getTrimmedName().c_str();
            if (std::strcmp(s, name) == 0)
            {
                return m_Frames.at(i);
            }
        }
        
        DEBUG_LOG_PRINT_W(TAG, "Unable to find frame name (%s)", name);
        return m_Frames.at(0);
    }
    
    const Rect &SpriteFrameAtlas::getFrame(int index)const
    {
        DEBUG_ASSERT(index >= 0 && index < m_Frames.size());
        return m_Frames.at(index);
    }
    
    const std::string &SpriteFrameAtlas::getSourceFilename()const
    {
        return m_SourceFilename;
    }
    
    u32 SpriteFrameAtlas::numberOfFrames()const
    {
        return m_Frames.size();
    }
    
    const btVector2 &SpriteFrameAtlas::contentDimension()const
    {
        return *m_ContentDimension;
    }
}
