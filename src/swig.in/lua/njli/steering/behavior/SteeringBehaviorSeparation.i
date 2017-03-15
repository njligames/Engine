//Factory
%newobject njli::SteeringBehaviorSeparation::create;
%delobject njli::SteeringBehaviorSeparation::destroy;
%factory(njli::SteeringBehaviorSeparation *njli::SteeringBehaviorSeparation::create, njli::SteeringBehaviorSeparation /*Add the children to the njli::SteeringBehaviorSeparation class*/);
%factory(njli::SteeringBehaviorSeparation *njli::SteeringBehaviorSeparation::clone, njli::SteeringBehaviorSeparation /*Add the children to the njli::SteeringBehaviorSeparation class*/);
%factory(njli::SteeringBehaviorSeparation *njli::SteeringBehaviorSeparation::copy, njli::SteeringBehaviorSeparation /*Add the children to the njli::SteeringBehaviorSeparation class*/);

//Extend
%extend njli::SteeringBehaviorSeparation
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
