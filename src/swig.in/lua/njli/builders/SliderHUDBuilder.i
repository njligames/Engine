//Factory
%newobject njli::SliderHUDBuilder::create;
%delobject njli::SliderHUDBuilder::destroy;
%factory(njli::SliderHUDBuilder *njli::SliderHUDBuilder::create, njli::SliderHUDBuilder /*Add the children to the SliderHUDBuilder class*/);
%factory(njli::SliderHUDBuilder *njli::SliderHUDBuilder::clone, njli::SliderHUDBuilder /*Add the children to the SliderHUDBuilder class*/);
%factory(njli::SliderHUDBuilder *njli::SliderHUDBuilder::copy, njli::SliderHUDBuilder /*Add the children to the SliderHUDBuilder class*/);

//Extend
%extend njli::SliderHUDBuilder
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
