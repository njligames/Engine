//Factory
%newobject njli::SteeringBehaviorInterpose::create;
%delobject njli::SteeringBehaviorInterpose::destroy;
%factory(njli::SteeringBehaviorInterpose *njli::SteeringBehaviorInterpose::create, njli::SteeringBehaviorInterpose /*Add the children to the njli::SteeringBehaviorInterpose class*/);
%factory(njli::SteeringBehaviorInterpose *njli::SteeringBehaviorInterpose::clone, njli::SteeringBehaviorInterpose /*Add the children to the njli::SteeringBehaviorInterpose class*/);
%factory(njli::SteeringBehaviorInterpose *njli::SteeringBehaviorInterpose::copy, njli::SteeringBehaviorInterpose /*Add the children to the njli::SteeringBehaviorInterpose class*/);

//Extend
%extend njli::SteeringBehaviorInterpose
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
