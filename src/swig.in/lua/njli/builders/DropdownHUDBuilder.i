//Factory
%newobject njli::DropdownHUDBuilder::create;
%delobject njli::DropdownHUDBuilder::destroy;
%factory(njli::DropdownHUDBuilder *njli::DropdownHUDBuilder::create, njli::DropdownHUDBuilder /*Add the children to the DropdownHUDBuilder class*/);
%factory(njli::DropdownHUDBuilder *njli::DropdownHUDBuilder::clone, njli::DropdownHUDBuilder /*Add the children to the DropdownHUDBuilder class*/);
%factory(njli::DropdownHUDBuilder *njli::DropdownHUDBuilder::copy, njli::DropdownHUDBuilder /*Add the children to the DropdownHUDBuilder class*/);

//Extend
%extend njli::DropdownHUDBuilder
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
