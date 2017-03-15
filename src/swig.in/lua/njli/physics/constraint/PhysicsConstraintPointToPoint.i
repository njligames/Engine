//Factory
%newobject njli::PhysicsConstraintPointToPoint::create;
%delobject njli::PhysicsConstraintPointToPoint::destroy;
%factory(njli::PhysicsConstraintPointToPoint *njli::PhysicsConstraintPointToPoint::create, njli::PhysicsConstraintPointToPoint /*Add the children to the njli::PhysicsConstraintPointToPoint class*/);
%factory(njli::PhysicsConstraintPointToPoint *njli::PhysicsConstraintPointToPoint::clone, njli::PhysicsConstraintPointToPoint /*Add the children to the njli::PhysicsConstraintPointToPoint class*/);
%factory(njli::PhysicsConstraintPointToPoint *njli::PhysicsConstraintPointToPoint::copy, njli::PhysicsConstraintPointToPoint /*Add the children to the njli::PhysicsConstraintPointToPoint class*/);

//Extend
%extend njli::PhysicsConstraintPointToPoint
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
