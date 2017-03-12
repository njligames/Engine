//Factory
%newobject njli::SceneState::create;
%delobject njli::SceneState::destroy;
%factory(njli::SceneState *njli::SceneState::create, njli::SceneState /*Add the children to the njli::SceneState class*/);
%factory(njli::SceneState *njli::SceneState::clone, njli::SceneState /*Add the children to the njli::SceneState class*/);
%factory(njli::SceneState *njli::SceneState::copy, njli::SceneState /*Add the children to the njli::SceneState class*/);

//Extend
%extend njli::SceneState
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
