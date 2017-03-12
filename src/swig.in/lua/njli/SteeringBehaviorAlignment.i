//Factory
%newobject njli::SteeringBehaviorAlignment::create;
%delobject njli::SteeringBehaviorAlignment::destroy;
%factory(njli::SteeringBehaviorAlignment *njli::SteeringBehaviorAlignment::create, njli::SteeringBehaviorAlignment /*Add the children to the njli::SteeringBehaviorAlignment class*/);
%factory(njli::SteeringBehaviorAlignment *njli::SteeringBehaviorAlignment::clone, njli::SteeringBehaviorAlignment /*Add the children to the njli::SteeringBehaviorAlignment class*/);
%factory(njli::SteeringBehaviorAlignment *njli::SteeringBehaviorAlignment::copy, njli::SteeringBehaviorAlignment /*Add the children to the njli::SteeringBehaviorAlignment class*/);

//Extend
%extend njli::SteeringBehaviorAlignment
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
