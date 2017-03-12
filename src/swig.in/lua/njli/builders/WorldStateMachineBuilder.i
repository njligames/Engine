//Factory
%newobject njli::WorldStateMachineBuilder::create;
%delobject njli::WorldStateMachineBuilder::destroy;
%factory(njli::WorldStateMachineBuilder *njli::WorldStateMachineBuilder::create, njli::WorldStateMachineBuilder /*Add the children to the njli::WorldStateMachineBuilder class*/);
%factory(njli::WorldStateMachineBuilder *njli::WorldStateMachineBuilder::clone, njli::WorldStateMachineBuilder /*Add the children to the njli::WorldStateMachineBuilder class*/);
%factory(njli::WorldStateMachineBuilder *njli::WorldStateMachineBuilder::copy, njli::WorldStateMachineBuilder /*Add the children to the njli::WorldStateMachineBuilder class*/);

//Extend
%extend njli::WorldStateMachineBuilder
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
