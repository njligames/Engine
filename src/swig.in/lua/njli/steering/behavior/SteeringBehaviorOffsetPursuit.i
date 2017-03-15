//Factory
%newobject njli::SteeringBehaviorOffsetPursuit::create;
%delobject njli::SteeringBehaviorOffsetPursuit::destroy;
%factory(njli::SteeringBehaviorOffsetPursuit *njli::SteeringBehaviorOffsetPursuit::create, njli::SteeringBehaviorOffsetPursuit /*Add the children to the njli::SteeringBehaviorOffsetPursuit class*/);
%factory(njli::SteeringBehaviorOffsetPursuit *njli::SteeringBehaviorOffsetPursuit::clone, njli::SteeringBehaviorOffsetPursuit /*Add the children to the njli::SteeringBehaviorOffsetPursuit class*/);
%factory(njli::SteeringBehaviorOffsetPursuit *njli::SteeringBehaviorOffsetPursuit::copy, njli::SteeringBehaviorOffsetPursuit /*Add the children to the njli::SteeringBehaviorOffsetPursuit class*/);

//Extend
%extend njli::SteeringBehaviorOffsetPursuit
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
