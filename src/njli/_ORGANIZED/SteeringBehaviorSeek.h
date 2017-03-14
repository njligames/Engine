//
//  SteeringBehaviorSeek.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehaviorSeek_hpp
#define SteeringBehaviorSeek_hpp

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "btVector3.h"
#include "SteeringBehavior.h"

namespace njli
{
    class SteeringBehaviorSeekBuilder;
    class Node;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) SteeringBehaviorSeek:
    public SteeringBehavior
    {
        friend class WorldFactory;
    protected:
        SteeringBehaviorSeek();
        SteeringBehaviorSeek(const AbstractBuilder&);
        SteeringBehaviorSeek(const SteeringBehaviorSeek &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SteeringBehaviorSeek();
        SteeringBehaviorSeek &operator=(const SteeringBehaviorSeek &);
    public:
        
        /*
        *  @section ex1 Lua example
        *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static SteeringBehaviorSeek** createArray(const u32 size);
        
        /**
         *  @author James Folk, 16-02-10 21:02:13
         *
         *  @brief <#Description#>
         *
         *  @param array <#array description#>
         *  @param size  <#size description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static void destroyArray(SteeringBehaviorSeek * *array, const u32 size = 0);
        
        /**
         *  @author James Folk, 16-02-10 21:02:21
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static SteeringBehaviorSeek* create();
        
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static SteeringBehaviorSeek* create(const SteeringBehaviorSeekBuilder& builder);
        
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static SteeringBehaviorSeek* clone(const SteeringBehaviorSeek& object);
        
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static SteeringBehaviorSeek* copy(const SteeringBehaviorSeek& object);
        
        /**
         *  @author James Folk, 16-02-10 21:02:41
         *
         *  @brief <#Description#>
         *
         *  @param object               <#object description#>
         *  @param destroyChildrenNodes <#destroyChildrenNodes description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static void destroy(SteeringBehaviorSeek * object);
        
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
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static void load(SteeringBehaviorSeek & object, lua_State * L, int stack_index);
        
        /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorSeek.lua SteeringBehaviorSeek_calculateSerializeBufferSize_
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for SteeringBehaviorSeek
        
        virtual const btVector3 &calculateForce();
    protected:
        
    private:
        btVector3 *m_CurrentForce;
        std::vector<Node*> m_TargetList;
    };
}

#endif /* SteeringBehaviorSeek_hpp */
