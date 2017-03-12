//
//  SteeringBehaviorFollowPath.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehaviorFollowPath_hpp
#define SteeringBehaviorFollowPath_hpp

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "btVector3.h"
#include "SteeringBehavior.h"

namespace njli
{
    class SteeringBehaviorFollowPathBuilder;
    class Node;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) SteeringBehaviorFollowPath:
    public SteeringBehavior
    {
        friend class WorldFactory;
    protected:
        SteeringBehaviorFollowPath();
        SteeringBehaviorFollowPath(const AbstractBuilder&);
        SteeringBehaviorFollowPath(const SteeringBehaviorFollowPath &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SteeringBehaviorFollowPath();
        SteeringBehaviorFollowPath &operator=(const SteeringBehaviorFollowPath &);
    public:
        
        /*
        *  @section ex1 Lua example
        *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
        */
        virtual s32 calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:45
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        virtual void serialize(void* dataBuffer, btSerializer*) const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        virtual const char* getClassName() const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:54
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        virtual s32 getType() const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:59
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        operator std::string() const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:09
         *
         *  @brief <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static SteeringBehaviorFollowPath** createArray(const u32 size);
        
        /**
         *  @author James Folk, 16-02-10 21:02:13
         *
         *  @brief <#Description#>
         *
         *  @param array <#array description#>
         *  @param size  <#size description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static void destroyArray(SteeringBehaviorFollowPath * *array, const u32 size = 0);
        
        /**
         *  @author James Folk, 16-02-10 21:02:21
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static SteeringBehaviorFollowPath* create();
        
        /**
         *  @author James Folk, 16-02-10 21:02:23
         *
         *  @brief <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static SteeringBehaviorFollowPath* create(const SteeringBehaviorFollowPathBuilder& builder);
        
        /**
         *  @author James Folk, 16-02-10 21:02:31
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static SteeringBehaviorFollowPath* clone(const SteeringBehaviorFollowPath& object);
        
        /**
         *  @author James Folk, 16-02-10 21:02:36
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static SteeringBehaviorFollowPath* copy(const SteeringBehaviorFollowPath& object);
        
        /**
         *  @author James Folk, 16-02-10 21:02:41
         *
         *  @brief <#Description#>
         *
         *  @param object               <#object description#>
         *  @param destroyChildrenNodes <#destroyChildrenNodes description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static void destroy(SteeringBehaviorFollowPath * object);
        
        /**
         *  @author James Folk, 16-02-10 21:02:46
         *
         *  @brief <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static void load(SteeringBehaviorFollowPath & object, lua_State * L, int stack_index);
        
        /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorFollowPath.lua SteeringBehaviorFollowPath_calculateSerializeBufferSize_
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for SteeringBehaviorFollowPath
        
        virtual const btVector3 &calculateForce();
    protected:
        
    private:
        btVector3 *m_CurrentForce;
        std::vector<Node*> m_TargetList;
    };
}

#endif /* SteeringBehaviorFollowPath_hpp */
