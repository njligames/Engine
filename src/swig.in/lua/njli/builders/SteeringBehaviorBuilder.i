//Factory
%newobject njli::SteeringBehaviorBuilder::create;
%delobject njli::SteeringBehaviorBuilder::destroy;
/*Add the children to the njli::SteeringBehavior class*/
%factory(njli::SteeringBehaviorBuilder *njli::SteeringBehaviorBuilder::create,
         njli::SteeringBehaviorBuilder,
         njli::SteeringBehaviorAlignmentBuilder,
         njli::SteeringBehaviorArriveBuilder,
         njli::SteeringBehaviorCohesionBuilder,
         njli::SteeringBehaviorEvadeBuilder,
         njli::SteeringBehaviorFleeBuilder,
         njli::SteeringBehaviorFollowPathBuilder,
         njli::SteeringBehaviorHideBuilder,
         njli::SteeringBehaviorInterposeBuilder,
         njli::SteeringBehaviorObstacleAvoidance,
         njli::SteeringBehaviorOffsetPursuit,
         njli::SteeringBehaviorPursuit,
         njli::SteeringBehaviorSeek,
         njli::SteeringBehaviorSeparation,
         njli::SteeringBehaviorWallAvoidance,
         njli::SteeringBehaviorWander);

//Array

//Extend
%extend njli::SteeringBehaviorBuilder
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