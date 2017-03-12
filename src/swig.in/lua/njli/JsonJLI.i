//Factory
%newobject njli::JsonJLI::create;
%delobject njli::JsonJLI::destroy;
%factory(njli::JsonJLI *njli::JsonJLI::create, njli::JsonJLI /*Add the children to the njli::JsonJLI class*/);
%factory(njli::JsonJLI *njli::JsonJLI::clone, njli::JsonJLI /*Add the children to the njli::JsonJLI class*/);
%factory(njli::JsonJLI *njli::JsonJLI::copy, njli::JsonJLI /*Add the children to the njli::JsonJLI class*/);

//Extend
%extend njli::JsonJLI
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
