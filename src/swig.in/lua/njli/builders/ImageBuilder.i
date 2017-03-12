//Factory
%newobject njli::ImageBuilder::create;
%delobject njli::ImageBuilder::destroy;
%factory(njli::ImageBuilder *njli::ImageBuilder::create, njli::ImageBuilder /*Add the children to the njli::ImageBuilder class*/);
%factory(njli::ImageBuilder *njli::ImageBuilder::clone, njli::ImageBuilder /*Add the children to the njli::ImageBuilder class*/);
%factory(njli::ImageBuilder *njli::ImageBuilder::copy, njli::ImageBuilder /*Add the children to the njli::ImageBuilder class*/);

//Extend
%extend njli::ImageBuilder
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
