//Factory
%newobject njli::PhysicsBodySoft::create;
%delobject njli::PhysicsBodySoft::destroy;
%factory(njli::PhysicsBodySoft *njli::PhysicsBodySoft::create, njli::PhysicsBodySoft /*Add the children to the njli::PhysicsBodySoft class*/);
%factory(njli::PhysicsBodySoft *njli::PhysicsBodySoft::clone, njli::PhysicsBodySoft /*Add the children to the njli::PhysicsBodySoft class*/);
%factory(njli::PhysicsBodySoft *njli::PhysicsBodySoft::copy, njli::PhysicsBodySoft /*Add the children to the njli::PhysicsBodySoft class*/);

//Extend
%extend njli::PhysicsBodySoft
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
