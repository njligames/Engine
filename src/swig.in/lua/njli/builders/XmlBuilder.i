//Factory
%newobject njli::XmlBuilder::create;
%delobject njli::XmlBuilder::destroy;
%factory(njli::XmlBuilder *njli::XmlBuilder::create, njli::XmlBuilder /*Add the children to the njli::XmlBuilder class*/);
%factory(njli::XmlBuilder *njli::XmlBuilder::clone, njli::XmlBuilder /*Add the children to the njli::XmlBuilder class*/);
%factory(njli::XmlBuilder *njli::XmlBuilder::copy, njli::XmlBuilder /*Add the children to the njli::XmlBuilder class*/);

//Extend
%extend njli::XmlBuilder
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
