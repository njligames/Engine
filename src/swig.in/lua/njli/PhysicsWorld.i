//Factory
%newobject njli::PhysicsWorld::create;
%delobject njli::PhysicsWorld::destroy;
%factory(njli::PhysicsWorld *njli::PhysicsWorld::create, njli::PhysicsWorld /*Add the children to the njli::PhysicsWorld class*/);
%factory(njli::PhysicsWorld *njli::PhysicsWorld::clone, njli::PhysicsWorld /*Add the children to the njli::PhysicsWorld class*/);
%factory(njli::PhysicsWorld *njli::PhysicsWorld::copy, njli::PhysicsWorld /*Add the children to the njli::PhysicsWorld class*/);

//Extend
%extend njli::PhysicsWorld
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
