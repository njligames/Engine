//Factory
%newobject njli::SteeringBehaviorObstacleAvoidanceBuilder::create;
%delobject njli::SteeringBehaviorObstacleAvoidanceBuilder::destroy;
%factory(njli::SteeringBehaviorObstacleAvoidanceBuilder *njli::SteeringBehaviorObstacleAvoidanceBuilder::create, njli::SteeringBehaviorObstacleAvoidanceBuilder /*Add the children to the njli::SteeringBehaviorObstacleAvoidanceBuilder class*/);
%factory(njli::SteeringBehaviorObstacleAvoidanceBuilder *njli::SteeringBehaviorObstacleAvoidanceBuilder::clone, njli::SteeringBehaviorObstacleAvoidanceBuilder /*Add the children to the njli::SteeringBehaviorObstacleAvoidanceBuilder class*/);
%factory(njli::SteeringBehaviorObstacleAvoidanceBuilder *njli::SteeringBehaviorObstacleAvoidanceBuilder::copy, njli::SteeringBehaviorObstacleAvoidanceBuilder /*Add the children to the njli::SteeringBehaviorObstacleAvoidanceBuilder class*/);

//Extend
%extend njli::SteeringBehaviorObstacleAvoidanceBuilder
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
}
