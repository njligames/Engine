//Factory
%newobject njli::PhysicsConstraintGeneric6DofSpringBuilder::create;
%delobject njli::PhysicsConstraintGeneric6DofSpringBuilder::destroy;
%factory(njli::PhysicsConstraintGeneric6DofSpringBuilder *njli::PhysicsConstraintGeneric6DofSpringBuilder::create, njli::PhysicsConstraintGeneric6DofSpringBuilder /*Add the children to the njli::PhysicsConstraintGeneric6DofSpringBuilder class*/);
%factory(njli::PhysicsConstraintGeneric6DofSpringBuilder *njli::PhysicsConstraintGeneric6DofSpringBuilder::close, njli::PhysicsConstraintGeneric6DofSpringBuilder /*Add the children to the njli::PhysicsConstraintGeneric6DofSpringBuilder class*/);
%factory(njli::PhysicsConstraintGeneric6DofSpringBuilder *njli::PhysicsConstraintGeneric6DofSpringBuilder::copy, njli::PhysicsConstraintGeneric6DofSpringBuilder /*Add the children to the njli::PhysicsConstraintGeneric6DofSpringBuilder class*/);

//Extend
%extend njli::PhysicsConstraintGeneric6DofSpringBuilder
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
