//Factory
%newobject njli::PhysicsCloseContact::create;
%delobject njli::PhysicsCloseContact::destroy;
%factory(njli::PhysicsCloseContact *njli::PhysicsCloseContact::create, njli::PhysicsCloseContact /*Add the children to the njli::PhysicsCloseContact class*/);
%factory(njli::PhysicsCloseContact *njli::PhysicsCloseContact::clone, njli::PhysicsCloseContact /*Add the children to the njli::PhysicsCloseContact class*/);
%factory(njli::PhysicsCloseContact *njli::PhysicsCloseContact::copy, njli::PhysicsCloseContact /*Add the children to the njli::PhysicsCloseContact class*/);

//Extend
%extend njli::PhysicsCloseContact
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
