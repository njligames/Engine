//Factory
%newobject njli::SkinnerBuilder::create;
%delobject njli::SkinnerBuilder::destroy;
%factory(njli::SkinnerBuilder *njli::SkinnerBuilder::create, njli::SkinnerBuilder /*Add the children to the njli::SkinnerBuilder class*/);
%factory(njli::SkinnerBuilder *njli::SkinnerBuilder::clone, njli::SkinnerBuilder /*Add the children to the njli::SkinnerBuilder class*/);
%factory(njli::SkinnerBuilder *njli::SkinnerBuilder::copy, njli::SkinnerBuilder /*Add the children to the njli::SkinnerBuilder class*/);

//Extend
%extend njli::SkinnerBuilder
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
