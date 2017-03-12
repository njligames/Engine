//Factory
%newobject njli::SceneStateMachine::create;
%delobject njli::SceneStateMachine::destroy;
%factory(njli::SceneStateMachine *njli::SceneStateMachine::create, njli::SceneStateMachine /*Add the children to the njli::SceneStateMachine class*/);
%factory(njli::SceneStateMachine *njli::SceneStateMachine::clone, njli::SceneStateMachine /*Add the children to the njli::SceneStateMachine class*/);
%factory(njli::SceneStateMachine *njli::SceneStateMachine::copy, njli::SceneStateMachine /*Add the children to the njli::SceneStateMachine class*/);

//Extend
%extend njli::SceneStateMachine
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
