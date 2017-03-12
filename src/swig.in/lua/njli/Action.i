//Factory
%newobject njli::Action::create;
%delobject njli::Action::destroy;
%factory(njli::Action *njli::Action::create, njli::Action /*Add the children to the Action class*/);
%factory(njli::Action *njli::Action::clone, njli::Action /*Add the children to the Action class*/);
%factory(njli::Action *njli::Action::copy, njli::Action /*Add the children to the Action class*/);

//Extend
%extend njli::Action
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
