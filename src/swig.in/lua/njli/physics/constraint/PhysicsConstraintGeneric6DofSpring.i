//Factory
%newobject njli::PhysicsConstraintGeneric6DofSpring::create;
%delobject njli::PhysicsConstraintGeneric6DofSpring::destroy;
%factory(njli::PhysicsConstraintGeneric6DofSpring *njli::PhysicsConstraintGeneric6DofSpring::create, njli::PhysicsConstraintGeneric6DofSpring /*Add the children to the njli::PhysicsConstraintGeneric6DofSpring class*/);
%factory(njli::PhysicsConstraintGeneric6DofSpring *njli::PhysicsConstraintGeneric6DofSpring::close, njli::PhysicsConstraintGeneric6DofSpring /*Add the children to the njli::PhysicsConstraintGeneric6DofSpring class*/);
%factory(njli::PhysicsConstraintGeneric6DofSpring *njli::PhysicsConstraintGeneric6DofSpring::copy, njli::PhysicsConstraintGeneric6DofSpring /*Add the children to the njli::PhysicsConstraintGeneric6DofSpring class*/);

//Extend
%extend njli::PhysicsConstraintGeneric6DofSpring
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
