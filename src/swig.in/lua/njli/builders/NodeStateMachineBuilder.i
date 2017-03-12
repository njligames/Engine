//Factory
%newobject njli::NodeStateMachineBuilder::create;
%delobject njli::NodeStateMachineBuilder::destroy;
%factory(njli::NodeStateMachineBuilder *njli::NodeStateMachineBuilder::create, njli::NodeStateMachineBuilder /*Add the children to the njli::NodeStateMachineBuilder class*/);
%factory(njli::NodeStateMachineBuilder *njli::NodeStateMachineBuilder::clone, njli::NodeStateMachineBuilder /*Add the children to the njli::NodeStateMachineBuilder class*/);
%factory(njli::NodeStateMachineBuilder *njli::NodeStateMachineBuilder::copy, njli::NodeStateMachineBuilder /*Add the children to the njli::NodeStateMachineBuilder class*/);

//Extend
%extend njli::NodeStateMachineBuilder
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
