//Factory
%newobject njli::SteeringBehaviorFleeBuilder::create;
%delobject njli::SteeringBehaviorFleeBuilder::destroy;
%factory(njli::SteeringBehaviorFleeBuilder *njli::SteeringBehaviorFleeBuilder::create, njli::SteeringBehaviorFleeBuilder /*Add the children to the njli::SteeringBehaviorFleeBuilder class*/);
%factory(njli::SteeringBehaviorFleeBuilder *njli::SteeringBehaviorFleeBuilder::clone, njli::SteeringBehaviorFleeBuilder /*Add the children to the njli::SteeringBehaviorFleeBuilder class*/);
%factory(njli::SteeringBehaviorFleeBuilder *njli::SteeringBehaviorFleeBuilder::copy, njli::SteeringBehaviorFleeBuilder /*Add the children to the njli::SteeringBehaviorFleeBuilder class*/);

//Extend
%extend njli::SteeringBehaviorFleeBuilder
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
