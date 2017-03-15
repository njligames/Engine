//Factory
%newobject njli::PhysicsConstraintGeneric6Dof::create;
%delobject njli::PhysicsConstraintGeneric6Dof::destroy;
%factory(njli::PhysicsConstraintGeneric6Dof *njli::PhysicsConstraintGeneric6Dof::create, njli::PhysicsConstraintGeneric6Dof /*Add the children to the njli::PhysicsConstraintGeneric6Dof class*/);
%factory(njli::PhysicsConstraintGeneric6Dof *njli::PhysicsConstraintGeneric6Dof::close, njli::PhysicsConstraintGeneric6Dof /*Add the children to the njli::PhysicsConstraintGeneric6Dof class*/);
%factory(njli::PhysicsConstraintGeneric6Dof *njli::PhysicsConstraintGeneric6Dof::copy, njli::PhysicsConstraintGeneric6Dof /*Add the children to the njli::PhysicsConstraintGeneric6Dof class*/);

//Extend
%extend njli::PhysicsConstraintGeneric6Dof
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
