//Factory
%newobject njli::WorldStateBuilder::create;
%delobject njli::WorldStateBuilder::destroy;
%factory(njli::WorldStateBuilder *njli::WorldStateBuilder::create, njli::WorldStateBuilder /*Add the children to the njli::WorldStateBuilder class*/);
%factory(njli::WorldStateBuilder *njli::WorldStateBuilder::clone, njli::WorldStateBuilder /*Add the children to the njli::WorldStateBuilder class*/);
%factory(njli::WorldStateBuilder *njli::WorldStateBuilder::copy, njli::WorldStateBuilder /*Add the children to the njli::WorldStateBuilder class*/);

//Extend
%extend njli::WorldStateBuilder
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
