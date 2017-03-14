//Factory
%newobject njli::PhysicsConstraintGeneric6DofBuilder::create;
%delobject njli::PhysicsConstraintGeneric6DofBuilder::destroy;
%factory(njli::PhysicsConstraintGeneric6DofBuilder *njli::PhysicsConstraintGeneric6DofBuilder::create, njli::PhysicsConstraintGeneric6DofBuilder /*Add the children to the njli::PhysicsConstraintGeneric6DofBuilder class*/);
%factory(njli::PhysicsConstraintGeneric6DofBuilder *njli::PhysicsConstraintGeneric6DofBuilder::close, njli::PhysicsConstraintGeneric6DofBuilder /*Add the children to the njli::PhysicsConstraintGeneric6DofBuilder class*/);
%factory(njli::PhysicsConstraintGeneric6DofBuilder *njli::PhysicsConstraintGeneric6DofBuilder::copy, njli::PhysicsConstraintGeneric6DofBuilder /*Add the children to the njli::PhysicsConstraintGeneric6DofBuilder class*/);

//Extend
%extend njli::PhysicsConstraintGeneric6DofBuilder
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
