//Factory
%newobject njli::PhysicsShapeSphere::create;
%delobject njli::PhysicsShapeSphere::destroy;
%factory(njli::PhysicsShapeSphere *njli::PhysicsShapeSphere::create, njli::PhysicsShapeSphere /*Add the children to the njli::PhysicsShapeSphere class */);
%factory(njli::PhysicsShapeSphere *njli::PhysicsShapeSphere::clone, njli::PhysicsShapeSphere /*Add the children to the njli::PhysicsShapeSphere class */);
%factory(njli::PhysicsShapeSphere *njli::PhysicsShapeSphere::copy, njli::PhysicsShapeSphere /*Add the children to the njli::PhysicsShapeSphere class */);

//Extend
%extend njli::PhysicsShapeSphere
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
