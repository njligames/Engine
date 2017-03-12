//Factory
%newobject njli::SteeringBehaviorHide::create;
%delobject njli::SteeringBehaviorHide::destroy;
%factory(njli::SteeringBehaviorHide *njli::SteeringBehaviorHide::create, njli::SteeringBehaviorHide /*Add the children to the njli::SteeringBehaviorHide class*/);
%factory(njli::SteeringBehaviorHide *njli::SteeringBehaviorHide::clone, njli::SteeringBehaviorHide /*Add the children to the njli::SteeringBehaviorHide class*/);
%factory(njli::SteeringBehaviorHide *njli::SteeringBehaviorHide::copy, njli::SteeringBehaviorHide /*Add the children to the njli::SteeringBehaviorHide class*/);

//Extend
%extend njli::SteeringBehaviorHide
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
