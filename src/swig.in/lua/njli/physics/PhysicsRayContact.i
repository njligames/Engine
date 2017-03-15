//Factory
%newobject njli::PhysicsRayContact::create;
%delobject njli::PhysicsRayContact::destroy;
%factory(njli::PhysicsRayContact *njli::PhysicsRayContact::create, njli::PhysicsRayContact /*Add the children to the njli::PhysicsRayContact class*/);
%factory(njli::PhysicsRayContact *njli::PhysicsRayContact::clone, njli::PhysicsRayContact /*Add the children to the njli::PhysicsRayContact class*/);
%factory(njli::PhysicsRayContact *njli::PhysicsRayContact::copy, njli::PhysicsRayContact /*Add the children to the njli::PhysicsRayContact class*/);

//Extend
%extend njli::PhysicsRayContact
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
