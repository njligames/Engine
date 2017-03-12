//Factory
%newobject njli::SteeringBehaviorMachineBuilder::create;
%delobject njli::SteeringBehaviorMachineBuilder::destroy;
/*Add the children to the njli::SteeringBehavior class*/
%factory(njli::SteeringBehaviorMachineBuilder *njli::SteeringBehaviorMachineBuilder::create,
         njli::SteeringBehaviorMachineBuilder,
         njli::SteeringBehaviorMachineDitheredBuilder,
         njli::SteeringBehaviorMachinePrioritizedBuilder,
         njli::SteeringBehaviorMachineWeightedBuilder);

//Array

//Extend
%extend njli::SteeringBehaviorMachineBuilder
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
};

//Typemap