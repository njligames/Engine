//Factory
%newobject njli::SteeringBehaviorPursuit::create;
%delobject njli::SteeringBehaviorPursuit::destroy;
%factory(njli::SteeringBehaviorPursuit *njli::SteeringBehaviorPursuit::create, njli::SteeringBehaviorPursuit /*Add the children to the njli::SteeringBehaviorPursuit class*/);
%factory(njli::SteeringBehaviorPursuit *njli::SteeringBehaviorPursuit::clone, njli::SteeringBehaviorPursuit /*Add the children to the njli::SteeringBehaviorPursuit class*/);
%factory(njli::SteeringBehaviorPursuit *njli::SteeringBehaviorPursuit::copy, njli::SteeringBehaviorPursuit /*Add the children to the njli::SteeringBehaviorPursuit class*/);

//Extend
%extend njli::SteeringBehaviorPursuit
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
