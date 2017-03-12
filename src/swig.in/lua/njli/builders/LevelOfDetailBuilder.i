//Factory
%newobject njli::LevelOfDetailBuilder::create;
%delobject njli::LevelOfDetailBuilder::destroy;
%factory(njli::LevelOfDetailBuilder *njli::LevelOfDetailBuilder::create, njli::LevelOfDetailBuilder /*Add the children to the njli::LevelOfDetailBuilder class*/);
%factory(njli::LevelOfDetailBuilder *njli::LevelOfDetailBuilder::clone, njli::LevelOfDetailBuilder /*Add the children to the njli::LevelOfDetailBuilder class*/);
%factory(njli::LevelOfDetailBuilder *njli::LevelOfDetailBuilder::copy, njli::LevelOfDetailBuilder /*Add the children to the njli::LevelOfDetailBuilder class*/);

//Extend
%extend njli::LevelOfDetailBuilder
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
