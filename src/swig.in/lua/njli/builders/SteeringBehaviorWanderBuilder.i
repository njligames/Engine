//Factory
%newobject njli::SteeringBehaviorWanderBuilder::create;
%delobject njli::SteeringBehaviorWanderBuilder::destroy;
%factory(njli::SteeringBehaviorWanderBuilder *njli::SteeringBehaviorWanderBuilder::create, njli::SteeringBehaviorWanderBuilder /*Add the children to the njli::SteeringBehaviorWanderBuilder class*/);
%factory(njli::SteeringBehaviorWanderBuilder *njli::SteeringBehaviorWanderBuilder::clone, njli::SteeringBehaviorWanderBuilder /*Add the children to the njli::SteeringBehaviorWanderBuilder class*/);
%factory(njli::SteeringBehaviorWanderBuilder *njli::SteeringBehaviorWanderBuilder::copy, njli::SteeringBehaviorWanderBuilder /*Add the children to the njli::SteeringBehaviorWanderBuilder class*/);

//Extend
%extend njli::SteeringBehaviorWanderBuilder
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
