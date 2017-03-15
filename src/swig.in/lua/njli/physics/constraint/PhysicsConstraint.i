//Factory
%newobject njli::PhysicsConstraint::create;
%delobject njli::PhysicsConstraint::destroy;
%factory(njli::PhysicsConstraint *njli::PhysicsConstraint::create, njli::PhysicsConstraintPointToPoint, njli::PhysicsConstraintHinge, njli::PhysicsConstraintSlider, njli::PhysicsConstraintConeTwist, njli::PhysicsConstraintFixed, njli::PhysicsConstraintGeneric6Dof, njli::PhysicsConstraintGeneric6DofSpring /*Add the children to the njli::PhysicsConstraint class*/);

//Extend
%extend njli::PhysicsConstraint
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
