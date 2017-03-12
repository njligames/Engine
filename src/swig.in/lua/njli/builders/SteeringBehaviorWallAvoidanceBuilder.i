//Factory
%newobject njli::SteeringBehaviorWallAvoidanceBuilder::create;
%delobject njli::SteeringBehaviorWallAvoidanceBuilder::destroy;
%factory(njli::SteeringBehaviorWallAvoidanceBuilder *njli::SteeringBehaviorWallAvoidanceBuilder::create, njli::SteeringBehaviorWallAvoidanceBuilder /*Add the children to the njli::SteeringBehaviorWallAvoidanceBuilder class*/);
%factory(njli::SteeringBehaviorWallAvoidanceBuilder *njli::SteeringBehaviorWallAvoidanceBuilder::clone, njli::SteeringBehaviorWallAvoidanceBuilder /*Add the children to the njli::SteeringBehaviorWallAvoidanceBuilder class*/);
%factory(njli::SteeringBehaviorWallAvoidanceBuilder *njli::SteeringBehaviorWallAvoidanceBuilder::copy, njli::SteeringBehaviorWallAvoidanceBuilder /*Add the children to the njli::SteeringBehaviorWallAvoidanceBuilder class*/);

//Extend
%extend njli::SteeringBehaviorWallAvoidanceBuilder
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
