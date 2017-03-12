//Factory
%newobject njli::SteeringBehaviorSeek::create;
%delobject njli::SteeringBehaviorSeek::destroy;
%factory(njli::SteeringBehaviorSeek *njli::SteeringBehaviorSeek::create, njli::SteeringBehaviorSeek /*Add the children to the njli::SteeringBehaviorSeek class*/);
%factory(njli::SteeringBehaviorSeek *njli::SteeringBehaviorSeek::clone, njli::SteeringBehaviorSeek /*Add the children to the njli::SteeringBehaviorSeek class*/);
%factory(njli::SteeringBehaviorSeek *njli::SteeringBehaviorSeek::copy, njli::SteeringBehaviorSeek /*Add the children to the njli::SteeringBehaviorSeek class*/);

//Extend
%extend njli::SteeringBehaviorSeek
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
