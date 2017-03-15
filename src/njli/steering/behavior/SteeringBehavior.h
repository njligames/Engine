//
//  SteeringBehavior.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehavior_hpp
#define SteeringBehavior_hpp

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "btVector3.h"

namespace njli
{
    class SteeringBehaviorBuilder;
    class Node;
    class SteeringBehaviorMachine;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) SteeringBehavior:
    public AbstractFactoryObject
    {
        friend class WorldFactory;
        
    protected:
        SteeringBehavior();
        SteeringBehavior(const AbstractBuilder&);
        SteeringBehavior(const SteeringBehavior &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SteeringBehavior();
        SteeringBehavior &operator=(const SteeringBehavior &);
    public:
        
        /*
        *  @section ex1 Lua example
        *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static SteeringBehavior** createArray(const u32 size);
        
        /**
         *  @author James Folk, 16-02-10 21:02:13
         *
         *  @brief <#Description#>
         *
         *  @param array <#array description#>
         *  @param size  <#size description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static void destroyArray(SteeringBehavior * *array, const u32 size = 0);
        
        /**
         *  @author James Folk, 16-02-10 21:02:21
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static SteeringBehavior* create();
        
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static SteeringBehavior* create(const SteeringBehaviorBuilder& builder);
        
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static SteeringBehavior* clone(const SteeringBehavior& object);
        
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static SteeringBehavior* copy(const SteeringBehavior& object);
        
        /**
         *  @author James Folk, 16-02-10 21:02:41
         *
         *  @brief <#Description#>
         *
         *  @param object               <#object description#>
         *  @param destroyChildrenNodes <#destroyChildrenNodes description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static void destroy(SteeringBehavior * object);
        
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
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static void load(SteeringBehavior & object, lua_State * L, int stack_index);
        
        /**
         *  @author James Folk, 16-02-10 21:02:50
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_calculateSerializeBufferSize_
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for SteeringBehavior
        
        virtual const btVector3 &calculateForce() = 0;
        
        const btVector3 &getCurrentForce()const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:01
         *
         *  @brief <#Description#>
         *
         *  @param emitter <#emitter description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_addTarget_
         */
        s32 addTarget(Node *emitter);
        
        /**
         *  @author James Folk, 16-02-10 21:02:05
         *
         *  @brief <#Description#>
         *
         *  @param emitter <#emitter description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_removeTarget_
         */
        bool removeTarget(Node * target);
        
        /**
         *  @author James Folk, 16-02-10 21:02:09
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_removeAllTargets_
         */
        void removeAllTargets();
        
        /**
         *  @author James Folk, 16-02-10 21:02:14
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_numberOfTargets_
         */
        s32 numberOfTargets() const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:19
         *
         *  @brief <#Description#>
         *
         *  @param particleEmitters <#particleEmitters description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_getTargets
         */
        virtual void getTargets(std::vector<Node*> & targets) const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:22
         *
         *  @brief <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_getTargetIndex
         */
        virtual s32 getTargetIndex(Node * object) const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:27
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_getTarget
         */
        virtual Node* getTarget(const u32 index);
        
        /**
         *  @author James Folk, 16-02-10 21:02:30
         *
         *  @brief <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehavior.lua SteeringBehavior_getTarget
         */
        virtual const Node* getTarget(const u32 index) const;
        
     protected:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        SteeringBehaviorMachine* getParent();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const SteeringBehaviorMachine* getParent() const;
    
        void setCurrentForce(const btVector3 &force);
        
        bool hasOwner()const;
        btVector3 getOwnerPosition()const;
        
        btVector3 getAverageTargetPosition()const;
        
        typedef std::vector<Node*> TargetVector;
        TargetVector m_TargetList;
    private:
        btVector3 *m_CurrentForce;
        
        
    };
}

#endif /* SteeringBehavior_hpp */
