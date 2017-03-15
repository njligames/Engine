//Factory
%newobject njli::FontBuilder::create;
%delobject njli::FontBuilder::destroy;
%factory(njli::FontBuilder *njli::FontBuilder::create, njli::FontBuilder /*Add the children to the njli::FontBuilder class*/);
%factory(njli::FontBuilder *njli::FontBuilder::clone, njli::FontBuilder /*Add the children to the njli::FontBuilder class*/);
%factory(njli::FontBuilder *njli::FontBuilder::copy, njli::FontBuilder /*Add the children to the njli::FontBuilder class*/);

//Extend
%extend njli::FontBuilder
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
