//
//  SteeringBehaviorMachine.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehaviorMachine_hpp
#define SteeringBehaviorMachine_hpp

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "btVector3.h"

#include <map>

namespace njli
{
    class SteeringBehaviorMachineBuilder;
    class Node;
    class SteeringBehavior;
    
    
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) SteeringBehaviorMachine:
    public AbstractFactoryObject
    {
        friend class WorldFactory;
        friend class Node;
        
    protected:
        SteeringBehaviorMachine();
        SteeringBehaviorMachine(const AbstractBuilder&);
        SteeringBehaviorMachine(const SteeringBehaviorMachine &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~SteeringBehaviorMachine();
        SteeringBehaviorMachine &operator=(const SteeringBehaviorMachine &);
    public:
        
        /**
         *  Calculate the buffer size of this object.
         *
         *  @return The buffer size.
         */
        virtual	s32	calculateSerializeBufferSize() const;
        /**
         *  Serialize this object.
         *
         *  @param btSerializer the serializer which does the serialize.
         */
        virtual	void serialize(void*, btSerializer*) const;
        
        /**
         *  The name of this class.
         *
         *  @return The name of this class.
         */
        virtual const char *getClassName()const;
        /**
         *  Get the type of ::jliObjectEnumType enum value.
         *
         *  @return The ::jliObjectEnumType enum value.
         */
        virtual s32 getType()const;
        /**
         *  The string value for this object, which can be used for debugging.
         *
         *  @return "The string value for this object.
         */
        operator std::string() const;
        
        /**
         *  Create an Array of instances of this class.
         *
         *  @param size The amount of elements in the array.
         *
         *  @return Pointer to the newly created array.
         */
        static SteeringBehaviorMachine **createArray(const u32 size);
        /**
         *  Destroy an Array of this class type.
         *
         *  @param array The Pointer to the array to delete.
         */
        static void destroyArray(SteeringBehaviorMachine **array, const u32 size = 0);
        /**
         *  Create an instance of this class.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachine *create();
        /**
         *  Create an instance of this class using a builder.
         *
         *  @param builder The builder to use for construction
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachine *create(const SteeringBehaviorMachineBuilder &builder);
        /**
         *  Create a shallow copy of an instance of this class (sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachine *clone(const SteeringBehaviorMachine &object);
        /**
         *  Create a deep copy of an instance of this class (NOT sharing pointers).
         *
         *  @param object The object to clone.
         *
         *  @return Pointer to the newly created instance.
         */
        static SteeringBehaviorMachine *copy(const SteeringBehaviorMachine &object);
        /**
         *  Destroy an instance of this class.
         *
         *  @param object The object to destroy.
         */
        static void destroy(SteeringBehaviorMachine *object);
        /**
         *  Load a lua table representation of this class. This is used for JLIM.create(object).
         *
         *  @param object      The object to load.
         *  @param L           The current lua state.
         *  @param stack_index The stack index of the lua stack.
         */
        static void load(SteeringBehaviorMachine &object, lua_State *L, int stack_index);
        /**
         *  Get the type of ::jliObjectEnumType enum value.
         *
         *  @return The ::jliObjectEnumType enum value.
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for SteeringBehaviorMachine
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
        
        virtual const btVector3 &calculateSteeringForce() = 0;
        
        
        const btVector3 &getCalculatedForce()const;
        
        
        bool setHeuristic(SteeringBehavior *steeringBehavior, f32 heuristic);
        f32 getHeuristic(SteeringBehavior *steeringBehavior)const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:01
         *
         *  @brief <#Description#>
         *
         *  @param steeringBehavior <#emitter description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorMachine.lua SteeringBehaviorMachine_addSteeringBehavior_
         */
        bool addSteeringBehavior(SteeringBehavior *steeringBehavior, f32 heuristic);
        
        /**
         *  @author James Folk, 16-02-10 21:02:05
         *
         *  @brief <#Description#>
         *
         *  @param steeringBehavior <#emitter description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorMachine.lua SteeringBehaviorMachine_removeSteeringBehavior_
         */
        bool removeSteeringBehavior(SteeringBehavior * steeringBehavior);
        
        /**
         *  @author James Folk, 16-02-10 21:02:09
         *
         *  @brief <#Description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorMachine.lua SteeringBehaviorMachine_removeAllSteeringBehaviors_
         */
        void removeAllSteeringBehaviors();
        
        /**
         *  @author James Folk, 16-02-10 21:02:14
         *
         *  @brief <#Description#>
         *
         *  @return <#return value description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorMachine.lua SteeringBehaviorMachine_numberOfSteeringBehaviors_
         */
        u64 numberOfSteeringBehaviors() const;
        
        /**
         *  @author James Folk, 16-02-10 21:02:19
         *
         *  @brief <#Description#>
         *
         *  @param particleEmitters <#particleEmitters description#>
         *
         *  @section ex1 Lua example
         *  @snippet SteeringBehaviorMachine.lua SteeringBehaviorMachine_getSteeringBehaviors
         */
        virtual void getSteeringBehaviors(std::vector<SteeringBehavior*> & steeringBehaviors) const;
        
        void setMaxSpeed(const f32 speed);
        f32 getMaxSpeed()const;
        
        void setMaxForce(const f32 speed);
        f32 getMaxForce()const;
        
        const btVector3 &getHeadingVector()const;
    protected:
        f32 getMaxForce2()const;
        
        void setCalculatedForce(const btVector3 &force);
        typedef std::pair<SteeringBehavior*, f32> SteeringPair;
        typedef std::map<SteeringBehavior*, f32> SteeringMap;
        
        SteeringMap m_SteeringBehaviorMap;
    private:
        virtual const btVector3 &calculate(f32 timestep);
        
        btVector3 *m_CurrentForce;
        
        
//        std::vector<SteeringPair> m_SteeringBehaviorList;
        btVector3 *m_CurrentVelocity;
        btVector3 *m_HeadingVector;
        f32 m_MaxSpeed;
        f32 m_MaxForce;
        f32 m_MaxForce2;
        
    };
}

#endif /* SteeringBehaviorMachine_hpp */
