//Factory
%newobject njli::SceneBuilder::create;
%delobject njli::SceneBuilder::destroy;
%factory(njli::SceneBuilder *njli::SceneBuilder::create, njli::SceneBuilder /*Add the children to the njli::SceneBuilder class*/);
%factory(njli::SceneBuilder *njli::SceneBuilder::clone, njli::SceneBuilder /*Add the children to the njli::SceneBuilder class*/);
%factory(njli::SceneBuilder *njli::SceneBuilder::copy, njli::SceneBuilder /*Add the children to the njli::SceneBuilder class*/);

//Extend
%extend njli::SceneBuilder
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
