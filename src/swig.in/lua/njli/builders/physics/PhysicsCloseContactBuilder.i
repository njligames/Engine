//Factory
%newobject njli::PhysicsCloseContactBuilder::create;
%delobject njli::PhysicsCloseContactBuilder::destroy;
%factory(njli::PhysicsCloseContactBuilder *njli::PhysicsCloseContactBuilder::create, njli::PhysicsCloseContactBuilder /*Add the children to the njli::PhysicsCloseContactBuilder class*/);
%factory(njli::PhysicsCloseContactBuilder *njli::PhysicsCloseContactBuilder::clone, njli::PhysicsCloseContactBuilder /*Add the children to the njli::PhysicsCloseContactBuilder class*/);
%factory(njli::PhysicsCloseContactBuilder *njli::PhysicsCloseContactBuilder::copy, njli::PhysicsCloseContactBuilder /*Add the children to the njli::PhysicsCloseContactBuilder class*/);

//Extend
%extend njli::PhysicsCloseContactBuilder
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
