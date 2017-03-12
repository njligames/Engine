//Factory
%newobject njli::PhysicsConstraintHinge::create;
%delobject njli::PhysicsConstraintHinge::destroy;
%factory(njli::PhysicsConstraintHinge *njli::PhysicsConstraintHinge::create, njli::PhysicsConstraintHinge /*Add the children to the njli::PhysicsConstraintHinge class*/);
%factory(njli::PhysicsConstraintHinge *njli::PhysicsConstraintHinge::clone, njli::PhysicsConstraintHinge /*Add the children to the njli::PhysicsConstraintHinge class*/);
%factory(njli::PhysicsConstraintHinge *njli::PhysicsConstraintHinge::copy, njli::PhysicsConstraintHinge /*Add the children to the njli::PhysicsConstraintHinge class*/);

//Extend
%extend njli::PhysicsConstraintHinge
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
