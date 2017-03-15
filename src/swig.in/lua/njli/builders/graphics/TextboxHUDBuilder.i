//Factory
%newobject njli::TextHUDBuilder::create;
%delobject njli::TextHUDBuilder::destroy;
%factory(njli::TextHUDBuilder *njli::TextHUDBuilder::create, njli::TextHUDBuilder /*Add the children to the TextHUDBuilder class*/);
%factory(njli::TextHUDBuilder *njli::TextHUDBuilder::clone, njli::TextHUDBuilder /*Add the children to the TextHUDBuilder class*/);
%factory(njli::TextHUDBuilder *njli::TextHUDBuilder::copy, njli::TextHUDBuilder /*Add the children to the TextHUDBuilder class*/);

//Extend
%extend njli::TextboxHUDBuilder
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
