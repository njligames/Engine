//Factory
%newobject njli::NodeStateMachine::create;
%delobject njli::NodeStateMachine::destroy;
%factory(njli::NodeStateMachine *njli::NodeStateMachine::create, njli::NodeStateMachine /*Add the children to the njli::NodeStateMachine class*/);
%factory(njli::NodeStateMachine *njli::NodeStateMachine::clone, njli::NodeStateMachine /*Add the children to the njli::NodeStateMachine class*/);
%factory(njli::NodeStateMachine *njli::NodeStateMachine::copy, njli::NodeStateMachine /*Add the children to the njli::NodeStateMachine class*/);

//Extend
%extend njli::NodeStateMachine
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
