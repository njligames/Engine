//Factory
%newobject njli::ButtonHUD::create;
%delobject njli::ButtonHUD::destroy;
%factory(njli::ButtonHUD *njli::ButtonHUD::create, njli::ButtonHUD /*Add the children to the ButtonHUD class*/);
%factory(njli::ButtonHUD *njli::ButtonHUD::clone, njli::ButtonHUD /*Add the children to the ButtonHUD class*/);
%factory(njli::ButtonHUD *njli::ButtonHUD::copy, njli::ButtonHUD /*Add the children to the ButtonHUD class*/);

//Extend
%extend njli::ButtonHUD
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
