//Factory
%newobject njli::PhysicsBodyGhostBuilder::create;
%delobject njli::PhysicsBodyGhostBuilder::destroy;
%factory(njli::PhysicsBodyGhostBuilder *njli::PhysicsBodyGhostBuilder::create, njli::PhysicsBodyGhostBuilder /*Add the children to the njli::PhysicsBodyGhostBuilder class*/);
%factory(njli::PhysicsBodyGhostBuilder *njli::PhysicsBodyGhostBuilder::clone, njli::PhysicsBodyGhostBuilder /*Add the children to the njli::PhysicsBodyGhostBuilder class*/);
%factory(njli::PhysicsBodyGhostBuilder *njli::PhysicsBodyGhostBuilder::copy, njli::PhysicsBodyGhostBuilder /*Add the children to the njli::PhysicsBodyGhostBuilder class*/);

//Extend
%extend njli::PhysicsBodyGhostBuilder
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
