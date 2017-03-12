//Factory
%newobject njli::PhysicsShapeMultiSphere::create;
%delobject njli::PhysicsShapeMultiSphere::destroy;
%factory(njli::PhysicsShapeMultiSphere *njli::PhysicsShapeMultiSphere::create, njli::PhysicsShapeMultiSphere /*Add the children to the njli::PhysicsShapeMultiSphere class */);
%factory(njli::PhysicsShapeMultiSphere *njli::PhysicsShapeMultiSphere::clone, njli::PhysicsShapeMultiSphere /*Add the children to the njli::PhysicsShapeMultiSphere class */);
%factory(njli::PhysicsShapeMultiSphere *njli::PhysicsShapeMultiSphere::copy, njli::PhysicsShapeMultiSphere /*Add the children to the njli::PhysicsShapeMultiSphere class */);

//Extend
%extend njli::PhysicsShapeMultiSphere
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
