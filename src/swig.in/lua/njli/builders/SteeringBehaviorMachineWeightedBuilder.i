//Factory
%newobject njli::SteeringBehaviorMachineWeightedBuilder::create;
%delobject njli::SteeringBehaviorMachineWeightedBuilder::destroy;
%factory(njli::SteeringBehaviorMachineWeightedBuilder *njli::SteeringBehaviorMachineWeightedBuilder::create, njli::SteeringBehaviorMachineWeightedBuilder /*Add the children to the njli::SteeringBehaviorMachineWeightedBuilder class*/);
%factory(njli::SteeringBehaviorMachineWeightedBuilder *njli::SteeringBehaviorMachineWeightedBuilder::clone, njli::SteeringBehaviorMachineWeightedBuilder /*Add the children to the njli::SteeringBehaviorMachineWeightedBuilder class*/);
%factory(njli::SteeringBehaviorMachineWeightedBuilder *njli::SteeringBehaviorMachineWeightedBuilder::copy, njli::SteeringBehaviorMachineWeightedBuilder /*Add the children to the njli::SteeringBehaviorMachineWeightedBuilder class*/);

//Extend
%extend njli::SteeringBehaviorMachineWeightedBuilder
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
