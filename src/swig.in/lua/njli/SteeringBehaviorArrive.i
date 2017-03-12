//Factory
%newobject njli::SteeringBehaviorArrive::create;
%delobject njli::SteeringBehaviorArrive::destroy;
%factory(njli::SteeringBehaviorArrive *njli::SteeringBehaviorArrive::create, njli::SteeringBehaviorArrive /*Add the children to the njli::SteeringBehaviorArrive class*/);
%factory(njli::SteeringBehaviorArrive *njli::SteeringBehaviorArrive::clone, njli::SteeringBehaviorArrive /*Add the children to the njli::SteeringBehaviorArrive class*/);
%factory(njli::SteeringBehaviorArrive *njli::SteeringBehaviorArrive::copy, njli::SteeringBehaviorArrive /*Add the children to the njli::SteeringBehaviorArrive class*/);

//Extend
%extend njli::SteeringBehaviorArrive
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
