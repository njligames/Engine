//Factory
%newobject njli::SteeringBehaviorHideBuilder::create;
%delobject njli::SteeringBehaviorHideBuilder::destroy;
%factory(njli::SteeringBehaviorHideBuilder *njli::SteeringBehaviorHideBuilder::create, njli::SteeringBehaviorHideBuilder /*Add the children to the njli::SteeringBehaviorHideBuilder class*/);
%factory(njli::SteeringBehaviorHideBuilder *njli::SteeringBehaviorHideBuilder::clone, njli::SteeringBehaviorHideBuilder /*Add the children to the njli::SteeringBehaviorHideBuilder class*/);
%factory(njli::SteeringBehaviorHideBuilder *njli::SteeringBehaviorHideBuilder::copy, njli::SteeringBehaviorHideBuilder /*Add the children to the njli::SteeringBehaviorHideBuilder class*/);

//Extend
%extend njli::SteeringBehaviorHideBuilder
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
