//Factory
%newobject njli::WorldStateMachine::create;
%delobject njli::WorldStateMachine::destroy;
%factory(njli::WorldStateMachine *njli::WorldStateMachine::create, njli::WorldStateMachine /*Add the children to the njli::WorldStateMachine class*/);
%factory(njli::WorldStateMachine *njli::WorldStateMachine::clone, njli::WorldStateMachine /*Add the children to the njli::WorldStateMachine class*/);
%factory(njli::WorldStateMachine *njli::WorldStateMachine::copy, njli::WorldStateMachine /*Add the children to the njli::WorldStateMachine class*/);

//Extend
%extend njli::WorldStateMachine
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
