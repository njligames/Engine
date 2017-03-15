//Factory
%newobject njli::SteeringBehaviorSeparationBuilder::create;
%delobject njli::SteeringBehaviorSeparationBuilder::destroy;
%factory(njli::SteeringBehaviorSeparationBuilder *njli::SteeringBehaviorSeparationBuilder::create, njli::SteeringBehaviorSeparationBuilder /*Add the children to the njli::SteeringBehaviorSeparationBuilder class*/);
%factory(njli::SteeringBehaviorSeparationBuilder *njli::SteeringBehaviorSeparationBuilder::clone, njli::SteeringBehaviorSeparationBuilder /*Add the children to the njli::SteeringBehaviorSeparationBuilder class*/);
%factory(njli::SteeringBehaviorSeparationBuilder *njli::SteeringBehaviorSeparationBuilder::copy, njli::SteeringBehaviorSeparationBuilder /*Add the children to the njli::SteeringBehaviorSeparationBuilder class*/);

//Extend
%extend njli::SteeringBehaviorSeparationBuilder
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
