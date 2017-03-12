//Factory
%newobject njli::PhysicsBodyRigid::create;
%delobject njli::PhysicsBodyRigid::destroy;
%factory(njli::PhysicsBodyRigid *njli::PhysicsBodyRigid::create, njli::PhysicsBodyRigid /*Add the children to the njli::PhysicsBodyRigid class*/);
%factory(njli::PhysicsBodyRigid *njli::PhysicsBodyRigid::clone, njli::PhysicsBodyRigid /*Add the children to the njli::PhysicsBodyRigid class*/);
%factory(njli::PhysicsBodyRigid *njli::PhysicsBodyRigid::copy, njli::PhysicsBodyRigid /*Add the children to the njli::PhysicsBodyRigid class*/);

//Extend
%extend njli::PhysicsBodyRigid
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
