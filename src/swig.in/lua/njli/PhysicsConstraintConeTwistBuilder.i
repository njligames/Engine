//Factory
%newobject njli::PhysicsConstraintConeTwistBuilder::create;
%delobject njli::PhysicsConstraintConeTwistBuilder::destroy;
%factory(njli::PhysicsConstraintConeTwistBuilder *njli::PhysicsConstraintConeTwistBuilder::create, njli::PhysicsConstraintConeTwistBuilder /*Add the children to the njli::PhysicsConstraintConeTwistBuilder class*/);
%factory(njli::PhysicsConstraintConeTwistBuilder *njli::PhysicsConstraintConeTwistBuilder::close, njli::PhysicsConstraintConeTwistBuilder /*Add the children to the njli::PhysicsConstraintConeTwistBuilder class*/);
%factory(njli::PhysicsConstraintConeTwistBuilder *njli::PhysicsConstraintConeTwistBuilder::copy, njli::PhysicsConstraintConeTwistBuilder /*Add the children to the njli::PhysicsConstraintConeTwistBuilder class*/);

//Extend
%extend njli::PhysicsConstraintConeTwistBuilder
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
