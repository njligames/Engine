//Factory
%newobject njli::LabelHUD::create;
%delobject njli::LabelHUD::destroy;
%factory(njli::LabelHUD *njli::LabelHUD::create, njli::LabelHUD /*Add the children to the LabelHUD class*/);
%factory(njli::LabelHUD *njli::LabelHUD::clone, njli::LabelHUD /*Add the children to the LabelHUD class*/);
%factory(njli::LabelHUD *njli::LabelHUD::copy, njli::LabelHUD /*Add the children to the LabelHUD class*/);

//Extend
%extend njli::LabelHUD
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

