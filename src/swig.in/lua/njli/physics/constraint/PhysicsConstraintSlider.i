//Factory
%newobject njli::PhysicsConstraintSlider::create;
%delobject njli::PhysicsConstraintSlider::destroy;
%factory(njli::PhysicsConstraintSlider *njli::PhysicsConstraintSlider::create, njli::PhysicsConstraintSlider /*Add the children to the njli::PhysicsConstraintSlider class*/);
%factory(njli::PhysicsConstraintSlider *njli::PhysicsConstraintSlider::close, njli::PhysicsConstraintSlider /*Add the children to the njli::PhysicsConstraintSlider class*/);
%factory(njli::PhysicsConstraintSlider *njli::PhysicsConstraintSlider::copy, njli::PhysicsConstraintSlider /*Add the children to the njli::PhysicsConstraintSlider class*/);

//Extend
%extend njli::PhysicsConstraintSlider
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
