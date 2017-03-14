//Factory
%newobject njli::JsonJLIBuilder::create;
%delobject njli::JsonJLIBuilder::destroy;
%factory(njli::JsonJLIBuilder *njli::JsonJLIBuilder::create, njli::JsonJLIBuilder /*Add the children to the njli::JsonJLIBuilder class*/);
%factory(njli::JsonJLIBuilder *njli::JsonJLIBuilder::clone, njli::JsonJLIBuilder /*Add the children to the njli::JsonJLIBuilder class*/);
%factory(njli::JsonJLIBuilder *njli::JsonJLIBuilder::copy, njli::JsonJLIBuilder /*Add the children to the njli::JsonJLIBuilder class*/);

//Extend
%extend njli::JsonJLIBuilder
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