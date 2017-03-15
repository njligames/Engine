//Factory
%newobject njli::SteeringBehaviorObstacleAvoidance::create;
%delobject njli::SteeringBehaviorObstacleAvoidance::destroy;
%factory(njli::SteeringBehaviorObstacleAvoidance *njli::SteeringBehaviorObstacleAvoidance::create, njli::SteeringBehaviorObstacleAvoidance /*Add the children to the njli::SteeringBehaviorObstacleAvoidance class*/);
%factory(njli::SteeringBehaviorObstacleAvoidance *njli::SteeringBehaviorObstacleAvoidance::clone, njli::SteeringBehaviorObstacleAvoidance /*Add the children to the njli::SteeringBehaviorObstacleAvoidance class*/);
%factory(njli::SteeringBehaviorObstacleAvoidance *njli::SteeringBehaviorObstacleAvoidance::copy, njli::SteeringBehaviorObstacleAvoidance /*Add the children to the njli::SteeringBehaviorObstacleAvoidance class*/);

//Extend
%extend njli::SteeringBehaviorObstacleAvoidance
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
