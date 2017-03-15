//Factory
%newobject njli::LightBuilder::create;
%delobject njli::LightBuilder::destroy;
%factory(njli::LightBuilder *njli::LightBuilder::create, njli::LightBuilder /*Add the children to the njli::LightBuilder class*/);
%factory(njli::LightBuilder *njli::LightBuilder::clone, njli::LightBuilder /*Add the children to the njli::LightBuilder class*/);
%factory(njli::LightBuilder *njli::LightBuilder::copy, njli::LightBuilder /*Add the children to the njli::LightBuilder class*/);

//Extend
%extend njli::LightBuilder
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
