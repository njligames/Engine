//Factory
%newobject njli::SteeringBehaviorEvade::create;
%delobject njli::SteeringBehaviorEvade::destroy;
%factory(njli::SteeringBehaviorEvade *njli::SteeringBehaviorEvade::create, njli::SteeringBehaviorEvade /*Add the children to the njli::SteeringBehaviorEvade class*/);
%factory(njli::SteeringBehaviorEvade *njli::SteeringBehaviorEvade::clone, njli::SteeringBehaviorEvade /*Add the children to the njli::SteeringBehaviorEvade class*/);
%factory(njli::SteeringBehaviorEvade *njli::SteeringBehaviorEvade::copy, njli::SteeringBehaviorEvade /*Add the children to the njli::SteeringBehaviorEvade class*/);

//Extend
%extend njli::SteeringBehaviorEvade
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
