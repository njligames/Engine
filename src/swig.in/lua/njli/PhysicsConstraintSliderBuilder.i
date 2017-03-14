//Factory
%newobject njli::PhysicsConstraintSliderBuilder::create;
%delobject njli::PhysicsConstraintSliderBuilder::destroy;
%factory(njli::PhysicsConstraintSliderBuilder *njli::PhysicsConstraintSliderBuilder::create, njli::PhysicsConstraintSliderBuilder /*Add the children to the njli::PhysicsConstraintSliderBuilder class*/);
%factory(njli::PhysicsConstraintSliderBuilder *njli::PhysicsConstraintSliderBuilder::close, njli::PhysicsConstraintSliderBuilder /*Add the children to the njli::PhysicsConstraintSliderBuilder class*/);
%factory(njli::PhysicsConstraintSliderBuilder *njli::PhysicsConstraintSliderBuilder::copy, njli::PhysicsConstraintSliderBuilder /*Add the children to the njli::PhysicsConstraintSliderBuilder class*/);

//Extend
%extend njli::PhysicsConstraintSliderBuilder
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
