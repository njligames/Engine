//Factory
%newobject njli::PhysicsRayContactBuilder::create;
%delobject njli::PhysicsRayContactBuilder::destroy;
%factory(njli::PhysicsRayContactBuilder *njli::PhysicsRayContactBuilder::create, njli::PhysicsRayContactBuilder /*Add the children to the njli::PhysicsRayContactBuilder class*/);
%factory(njli::PhysicsRayContactBuilder *njli::PhysicsRayContactBuilder::clone, njli::PhysicsRayContactBuilder /*Add the children to the njli::PhysicsRayContactBuilder class*/);
%factory(njli::PhysicsRayContactBuilder *njli::PhysicsRayContactBuilder::copy, njli::PhysicsRayContactBuilder /*Add the children to the njli::PhysicsRayContactBuilder class*/);

//Extend
%extend njli::PhysicsRayContactBuilder
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
