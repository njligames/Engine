//Factory
%newobject njli::DropdownHUD::create;
%delobject njli::DropdownHUD::destroy;
%factory(njli::DropdownHUD *njli::DropdownHUD::create, njli::DropdownHUD /*Add the children to the DropdownHUD class*/);
%factory(njli::DropdownHUD *njli::DropdownHUD::clone, njli::DropdownHUD /*Add the children to the DropdownHUD class*/);
%factory(njli::DropdownHUD *njli::DropdownHUD::copy, njli::DropdownHUD /*Add the children to the DropdownHUD class*/);

//Extend
%extend njli::DropdownHUD
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
