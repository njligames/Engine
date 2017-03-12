//Factory
%newobject njli::PhysicsConstraintFixed::create;
%delobject njli::PhysicsConstraintFixed::destroy;
%factory(njli::PhysicsConstraintFixed *njli::PhysicsConstraintFixed::create, njli::PhysicsConstraintFixed /*Add the children to the njli::PhysicsConstraintFixed class*/);
%factory(njli::PhysicsConstraintFixed *njli::PhysicsConstraintFixed::close, njli::PhysicsConstraintFixed /*Add the children to the njli::PhysicsConstraintFixed class*/);
%factory(njli::PhysicsConstraintFixed *njli::PhysicsConstraintFixed::copy, njli::PhysicsConstraintFixed /*Add the children to the njli::PhysicsConstraintFixed class*/);

//Extend
%extend njli::PhysicsConstraintFixed
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
