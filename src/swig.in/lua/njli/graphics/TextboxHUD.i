//Factory
%newobject njli::TextboxHUD::create;
%delobject njli::TextboxHUD::destroy;
%factory(njli::TextboxHUD *njli::TextboxHUD::create, njli::TextboxHUD /*Add the children to the TextboxHUD class*/);
%factory(njli::TextboxHUD *njli::TextboxHUD::clone, njli::TextboxHUD /*Add the children to the TextboxHUD class*/);
%factory(njli::TextboxHUD *njli::TextboxHUD::copy, njli::TextboxHUD /*Add the children to the TextboxHUD class*/);

//Extend
%extend njli::TextboxHUD
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
