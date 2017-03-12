//Factory
%newobject njli::SoundBuilder::create;
%delobject njli::SoundBuilder::destroy;
%factory(njli::SoundBuilder *njli::SoundBuilder::create, njli::SoundBuilder /*Add the children to the njli::SoundBuilder class*/);
%factory(njli::SoundBuilder *njli::SoundBuilder::clone, njli::SoundBuilder /*Add the children to the njli::SoundBuilder class*/);
%factory(njli::SoundBuilder *njli::SoundBuilder::copy, njli::SoundBuilder /*Add the children to the njli::SoundBuilder class*/);

//Extend
%extend njli::SoundBuilder
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
