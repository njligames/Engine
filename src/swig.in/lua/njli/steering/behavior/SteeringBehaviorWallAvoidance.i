//Factory
%newobject njli::SteeringBehaviorWallAvoidance::create;
%delobject njli::SteeringBehaviorWallAvoidance::destroy;
%factory(njli::SteeringBehaviorWallAvoidance *njli::SteeringBehaviorWallAvoidance::create, njli::SteeringBehaviorWallAvoidance /*Add the children to the njli::SteeringBehaviorWallAvoidance class*/);
%factory(njli::SteeringBehaviorWallAvoidance *njli::SteeringBehaviorWallAvoidance::clone, njli::SteeringBehaviorWallAvoidance /*Add the children to the njli::SteeringBehaviorWallAvoidance class*/);
%factory(njli::SteeringBehaviorWallAvoidance *njli::SteeringBehaviorWallAvoidance::copy, njli::SteeringBehaviorWallAvoidance /*Add the children to the njli::SteeringBehaviorWallAvoidance class*/);

//Extend
%extend njli::SteeringBehaviorWallAvoidance
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
