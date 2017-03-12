//Factory
%newobject njli::PhysicsConstraintFixedBuilder::create;
%delobject njli::PhysicsConstraintFixedBuilder::destroy;
%factory(njli::PhysicsConstraintFixedBuilder *njli::PhysicsConstraintFixedBuilder::create, njli::PhysicsConstraintFixedBuilder /*Add the children to the njli::PhysicsConstraintFixedBuilder class*/);
%factory(njli::PhysicsConstraintFixedBuilder *njli::PhysicsConstraintFixedBuilder::close, njli::PhysicsConstraintFixedBuilder /*Add the children to the njli::PhysicsConstraintFixedBuilder class*/);
%factory(njli::PhysicsConstraintFixedBuilder *njli::PhysicsConstraintFixedBuilder::copy, njli::PhysicsConstraintFixedBuilder /*Add the children to the njli::PhysicsConstraintFixedBuilder class*/);

//Extend
%extend njli::PhysicsConstraintFixedBuilder
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

