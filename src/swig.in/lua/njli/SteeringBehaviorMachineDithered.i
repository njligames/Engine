//Factory
%newobject njli::SteeringBehaviorMachineDithered::create;
%delobject njli::SteeringBehaviorMachineDithered::destroy;
%factory(njli::SteeringBehaviorMachineDithered *njli::SteeringBehaviorMachineDithered::create, njli::SteeringBehaviorMachineDithered /*Add the children to the njli::SteeringBehaviorMachineDithered class*/);
%factory(njli::SteeringBehaviorMachineDithered *njli::SteeringBehaviorMachineDithered::clone, njli::SteeringBehaviorMachineDithered /*Add the children to the njli::SteeringBehaviorMachineDithered class*/);
%factory(njli::SteeringBehaviorMachineDithered *njli::SteeringBehaviorMachineDithered::copy, njli::SteeringBehaviorMachineDithered /*Add the children to the njli::SteeringBehaviorMachineDithered class*/);

//Extend
%extend njli::SteeringBehaviorMachineDithered
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
