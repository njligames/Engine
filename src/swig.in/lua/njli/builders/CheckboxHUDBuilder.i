//Factory
%newobject njli::CheckboxHUDBuilder::create;
%delobject njli::CheckboxHUDBuilder::destroy;
%factory(njli::CheckboxHUDBuilder *njli::CheckboxHUDBuilder::create, njli::CheckboxHUDBuilder /*Add the children to the CheckboxHUDBuilder class*/);
%factory(njli::CheckboxHUDBuilder *njli::CheckboxHUDBuilder::clone, njli::CheckboxHUDBuilder /*Add the children to the CheckboxHUDBuilder class*/);
%factory(njli::CheckboxHUDBuilder *njli::CheckboxHUDBuilder::copy, njli::CheckboxHUDBuilder /*Add the children to the CheckboxHUDBuilder class*/);

//Extend
%extend njli::CheckboxHUDBuilder
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
