//Factory
%newobject njli::SteeringBehavior::create;
%delobject njli::SteeringBehavior::destroy;
/*Add the children to the njli::SteeringBehavior class*/
%factory(njli::SteeringBehavior *njli::SteeringBehavior::create,
         njli::SteeringBehavior,
         njli::SteeringBehaviorAlignment,
         njli::SteeringBehaviorArrive,
         njli::SteeringBehaviorCohesion,
         njli::SteeringBehaviorEvade,
         njli::SteeringBehaviorFlee,
         njli::SteeringBehaviorFollowPath,
         njli::SteeringBehaviorHide,
         njli::SteeringBehaviorInterpose,
         njli::SteeringBehaviorMachine,
         njli::SteeringBehaviorMachineDithered,
         njli::SteeringBehaviorMachinePrioritized,
         njli::SteeringBehaviorMachineWeighted,
         njli::SteeringBehaviorObstacleAvoidance,
         njli::SteeringBehaviorOffsetPursuit,
         njli::SteeringBehaviorPursuit,
         njli::SteeringBehaviorSeek,
         njli::SteeringBehaviorSeparation,
         njli::SteeringBehaviorWallAvoidance,
         njli::SteeringBehaviorWander);

//Array

//Extend
%extend njli::SteeringBehavior
{
    const char *__concat__(const char *s) {
        static std::string temp;
        std::string t1(*self);
        std::string t2(s);
        
        temp = (t1 + t2);
        return temp.c_str();
    }
    
    const char *__str__()
    {
        std::string s(*self);
        static char tmp[1024];
        sprintf(tmp, "%s", s.c_str());
        return tmp;
    }
};

//Typemap