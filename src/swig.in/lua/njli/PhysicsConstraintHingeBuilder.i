//Factory
%newobject njli::PhysicsConstraintHingeBuilder::create;
%delobject njli::PhysicsConstraintHingeBuilder::destroy;
%factory(njli::PhysicsConstraintHingeBuilder *njli::PhysicsConstraintHingeBuilder::create, njli::PhysicsConstraintHingeBuilder /*Add the children to the njli::PhysicsConstraintHingeBuilder class*/);
%factory(njli::PhysicsConstraintHingeBuilder *njli::PhysicsConstraintHingeBuilder::clone, njli::PhysicsConstraintHingeBuilder /*Add the children to the njli::PhysicsConstraintHingeBuilder class*/);
%factory(njli::PhysicsConstraintHingeBuilder *njli::PhysicsConstraintHingeBuilder::copy, njli::PhysicsConstraintHingeBuilder /*Add the children to the njli::PhysicsConstraintHingeBuilder class*/);

//Extend
%extend njli::PhysicsConstraintHingeBuilder
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
