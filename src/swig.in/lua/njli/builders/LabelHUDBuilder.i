//Factory
%newobject njli::LabelHUDBuilder::create;
%delobject njli::LabelHUDBuilder::destroy;
%factory(njli::LabelHUDBuilder *njli::LabelHUDBuilder::create, njli::LabelHUDBuilder /*Add the children to the LabelHUDBuilder class*/);
%factory(njli::LabelHUDBuilder *njli::LabelHUDBuilder::clone, njli::LabelHUDBuilder /*Add the children to the LabelHUDBuilder class*/);
%factory(njli::LabelHUDBuilder *njli::LabelHUDBuilder::copy, njli::LabelHUDBuilder /*Add the children to the LabelHUDBuilder class*/);

//Extend
%extend njli::LabelHUDBuilder
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
