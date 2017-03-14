//Factory
%newobject njli::SceneStateMachineBuilder::create;
%delobject njli::SceneStateMachineBuilder::destroy;
%factory(njli::SceneStateMachineBuilder *njli::SceneStateMachineBuilder::create, njli::SceneStateMachineBuilder /*Add the children to the njli::SceneStateMachineBuilder class*/);
%factory(njli::SceneStateMachineBuilder *njli::SceneStateMachineBuilder::clone, njli::SceneStateMachineBuilder /*Add the children to the njli::SceneStateMachineBuilder class*/);
%factory(njli::SceneStateMachineBuilder *njli::SceneStateMachineBuilder::copy, njli::SceneStateMachineBuilder /*Add the children to the njli::SceneStateMachineBuilder class*/);

//Extend
%extend njli::SceneStateMachineBuilder
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
