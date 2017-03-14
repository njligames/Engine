//Factory
%newobject njli::PhysicsBodyRigidBuilder::create;
%delobject njli::PhysicsBodyRigidBuilder::destroy;
%factory(njli::PhysicsBodyRigidBuilder *njli::PhysicsBodyRigidBuilder::create, njli::PhysicsBodyRigidBuilder /*Add the children to the njli::PhysicsBodyRigidBuilder class*/);
%factory(njli::PhysicsBodyRigidBuilder *njli::PhysicsBodyRigidBuilder::clone, njli::PhysicsBodyRigidBuilder /*Add the children to the njli::PhysicsBodyRigidBuilder class*/);
%factory(njli::PhysicsBodyRigidBuilder *njli::PhysicsBodyRigidBuilder::copy, njli::PhysicsBodyRigidBuilder /*Add the children to the njli::PhysicsBodyRigidBuilder class*/);

//Extend
%extend njli::PhysicsBodyRigidBuilder
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
