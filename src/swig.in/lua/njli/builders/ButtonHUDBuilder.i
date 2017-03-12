//Factory
%newobject njli::ButtonHUDBuilder::create;
%delobject njli::ButtonHUDBuilder::destroy;
%factory(njli::ButtonHUDBuilder *njli::ButtonHUDBuilder::create, njli::ButtonHUDBuilder /*Add the children to the ButtonHUDBuilder class*/);
%factory(njli::ButtonHUDBuilder *njli::ButtonHUDBuilder::clone, njli::ButtonHUDBuilder /*Add the children to the ButtonHUDBuilder class*/);
%factory(njli::ButtonHUDBuilder *njli::ButtonHUDBuilder::copy, njli::ButtonHUDBuilder /*Add the children to the ButtonHUDBuilder class*/);

//Extend
%extend njli::ButtonHUDBuilder
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
