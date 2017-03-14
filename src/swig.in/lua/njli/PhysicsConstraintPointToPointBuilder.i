//Factory
%newobject njli::PhysicsConstraintPointToPointBuilder::create;
%delobject njli::PhysicsConstraintPointToPointBuilder::destroy;
%factory(njli::PhysicsConstraintPointToPointBuilder *njli::PhysicsConstraintPointToPointBuilder::create, njli::PhysicsConstraintPointToPointBuilder /*Add the children to the njli::PhysicsConstraintPointToPointBuilder class*/);
%factory(njli::PhysicsConstraintPointToPointBuilder *njli::PhysicsConstraintPointToPointBuilder::clone, njli::PhysicsConstraintPointToPointBuilder /*Add the children to the njli::PhysicsConstraintPointToPointBuilder class*/);
%factory(njli::PhysicsConstraintPointToPointBuilder *njli::PhysicsConstraintPointToPointBuilder::copy, njli::PhysicsConstraintPointToPointBuilder /*Add the children to the njli::PhysicsConstraintPointToPointBuilder class*/);

//Extend
%extend njli::PhysicsConstraintPointToPointBuilder
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
