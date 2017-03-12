//Factory
%newobject njli::CheckboxHUD::create;
%delobject njli::CheckboxHUD::destroy;
%factory(njli::CheckboxHUD *njli::CheckboxHUD::create, njli::CheckboxHUD /*Add the children to the CheckboxHUD class*/);
%factory(njli::CheckboxHUD *njli::CheckboxHUD::clone, njli::CheckboxHUD /*Add the children to the CheckboxHUD class*/);
%factory(njli::CheckboxHUD *njli::CheckboxHUD::copy, njli::CheckboxHUD /*Add the children to the CheckboxHUD class*/);

//Extend
%extend njli::CheckboxHUD
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
