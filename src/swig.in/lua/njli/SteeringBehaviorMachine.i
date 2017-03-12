//Factory
%newobject njli::SteeringBehaviorMachine::create;
%delobject njli::SteeringBehaviorMachine::destroy;
/*Add the children to the njli::SteeringBehavior class*/
%factory(njli::SteeringBehaviorMachine *njli::SteeringBehaviorMachine::create,
         njli::SteeringBehaviorMachine,
         njli::SteeringBehaviorMachineDithered,
         njli::SteeringBehaviorMachinePrioritized,
         njli::SteeringBehaviorMachineWeighted);

//Array

//Extend
%extend njli::SteeringBehaviorMachine
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