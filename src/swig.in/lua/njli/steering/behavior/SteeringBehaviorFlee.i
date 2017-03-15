//Factory
%newobject njli::SteeringBehaviorFlee::create;
%delobject njli::SteeringBehaviorFlee::destroy;
%factory(njli::SteeringBehaviorFlee *njli::SteeringBehaviorFlee::create, njli::SteeringBehaviorFlee /*Add the children to the njli::SteeringBehaviorFlee class*/);
%factory(njli::SteeringBehaviorFlee *njli::SteeringBehaviorFlee::clone, njli::SteeringBehaviorFlee /*Add the children to the njli::SteeringBehaviorFlee class*/);
%factory(njli::SteeringBehaviorFlee *njli::SteeringBehaviorFlee::copy, njli::SteeringBehaviorFlee /*Add the children to the njli::SteeringBehaviorFlee class*/);

//Extend
%extend njli::SteeringBehaviorFlee
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
