//Factory
%newobject njli::Xml::create;
%delobject njli::Xml::destroy;
%factory(njli::Xml *njli::Xml::create, njli::Xml /*Add the children to the njli::Xml class*/);
%factory(njli::Xml *njli::Xml::clone, njli::Xml /*Add the children to the njli::Xml class*/);
%factory(njli::Xml *njli::Xml::copy, njli::Xml /*Add the children to the njli::Xml class*/);

//Extend
%extend njli::Xml
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
