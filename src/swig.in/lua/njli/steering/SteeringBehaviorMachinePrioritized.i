//Factory
%newobject njli::SteeringBehaviorMachinePrioritized::create;
%delobject njli::SteeringBehaviorMachinePrioritized::destroy;
%factory(njli::SteeringBehaviorMachinePrioritized *njli::SteeringBehaviorMachinePrioritized::create, njli::SteeringBehaviorMachinePrioritized /*Add the children to the njli::SteeringBehaviorMachinePrioritized class*/);
%factory(njli::SteeringBehaviorMachinePrioritized *njli::SteeringBehaviorMachinePrioritized::clone, njli::SteeringBehaviorMachinePrioritized /*Add the children to the njli::SteeringBehaviorMachinePrioritized class*/);
%factory(njli::SteeringBehaviorMachinePrioritized *njli::SteeringBehaviorMachinePrioritized::copy, njli::SteeringBehaviorMachinePrioritized /*Add the children to the njli::SteeringBehaviorMachinePrioritized class*/);

//Extend
%extend njli::SteeringBehaviorMachinePrioritized
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
