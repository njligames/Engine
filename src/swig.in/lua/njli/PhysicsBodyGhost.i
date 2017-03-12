//Factory
%newobject njli::PhysicsBodyGhost::create;
%delobject njli::PhysicsBodyGhost::destroy;
%factory(njli::PhysicsBodyGhost *njli::PhysicsBodyGhost::create, njli::PhysicsBodyGhost /*Add the children to the njli::PhysicsBodyGhost class*/);
%factory(njli::PhysicsBodyGhost *njli::PhysicsBodyGhost::clone, njli::PhysicsBodyGhost /*Add the children to the njli::PhysicsBodyGhost class*/);
%factory(njli::PhysicsBodyGhost *njli::PhysicsBodyGhost::copy, njli::PhysicsBodyGhost /*Add the children to the njli::PhysicsBodyGhost class*/);

//Extend
%extend njli::PhysicsBodyGhost
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
