//Factory
%newobject njli::SteeringBehaviorMachineWeighted::create;
%delobject njli::SteeringBehaviorMachineWeighted::destroy;
%factory(njli::SteeringBehaviorMachineWeighted *njli::SteeringBehaviorMachineWeighted::create, njli::SteeringBehaviorMachineWeighted /*Add the children to the njli::SteeringBehaviorMachineWeighted class*/);
%factory(njli::SteeringBehaviorMachineWeighted *njli::SteeringBehaviorMachineWeighted::clone, njli::SteeringBehaviorMachineWeighted /*Add the children to the njli::SteeringBehaviorMachineWeighted class*/);
%factory(njli::SteeringBehaviorMachineWeighted *njli::SteeringBehaviorMachineWeighted::copy, njli::SteeringBehaviorMachineWeighted /*Add the children to the njli::SteeringBehaviorMachineWeighted class*/);

//Extend
%extend njli::SteeringBehaviorMachineWeighted
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
