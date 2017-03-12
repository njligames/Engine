//Factory
%newobject njli::NodeState::create;
%delobject njli::NodeState::destroy;
%factory(njli::NodeState *njli::NodeState::create, njli::NodeState /*Add the children to the njli::NodeState class*/);
%factory(njli::NodeState *njli::NodeState::clone, njli::NodeState /*Add the children to the njli::NodeState class*/);
%factory(njli::NodeState *njli::NodeState::copy, njli::NodeState /*Add the children to the njli::NodeState class*/);

//Extend
%extend njli::NodeState
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
