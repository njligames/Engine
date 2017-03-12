//Factory
%newobject njli::WorldState::create;
%delobject njli::WorldState::destroy;
%factory(njli::WorldState *njli::WorldState::create, njli::WorldState /*Add the children to the njli::WorldState class*/);
%factory(njli::WorldState *njli::WorldState::clone, njli::WorldState /*Add the children to the njli::WorldState class*/);
%factory(njli::WorldState *njli::WorldState::copy, njli::WorldState /*Add the children to the njli::WorldState class*/);

//Extend
%extend njli::WorldState
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
