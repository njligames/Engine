//Factory
%newobject njli::SliderHUD::create;
%delobject njli::SliderHUD::destroy;
%factory(njli::SliderHUD *njli::SliderHUD::create, njli::SliderHUD /*Add the children to the SliderHUD class*/);
%factory(njli::SliderHUD *njli::SliderHUD::clone, njli::SliderHUD /*Add the children to the SliderHUD class*/);
%factory(njli::SliderHUD *njli::SliderHUD::copy, njli::SliderHUD /*Add the children to the SliderHUD class*/);

//Extend
%extend njli::SliderHUD
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
