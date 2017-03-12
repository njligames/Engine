//Factory
%newobject njli::SteeringBehaviorCohesion::create;
%delobject njli::SteeringBehaviorCohesion::destroy;
%factory(njli::SteeringBehaviorCohesion *njli::SteeringBehaviorCohesion::create, njli::SteeringBehaviorCohesion /*Add the children to the njli::SteeringBehaviorCohesion class*/);
%factory(njli::SteeringBehaviorCohesion *njli::SteeringBehaviorCohesion::clone, njli::SteeringBehaviorCohesion /*Add the children to the njli::SteeringBehaviorCohesion class*/);
%factory(njli::SteeringBehaviorCohesion *njli::SteeringBehaviorCohesion::copy, njli::SteeringBehaviorCohesion /*Add the children to the njli::SteeringBehaviorCohesion class*/);

//Extend
%extend njli::SteeringBehaviorCohesion
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
