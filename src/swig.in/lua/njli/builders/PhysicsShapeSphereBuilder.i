//Factory
%newobject njli::PhysicsShapeSphereBuilder::create;
%delobject njli::PhysicsShapeSphereBuilder::destroy;
%factory(njli::PhysicsShapeSphereBuilder *njli::PhysicsShapeSphereBuilder::create, njli::PhysicsShapeSphereBuilder /*Add the children to the njli::PhysicsShapeSphereBuilder class */);
%factory(njli::PhysicsShapeSphereBuilder *njli::PhysicsShapeSphereBuilder::clone, njli::PhysicsShapeSphereBuilder /*Add the children to the njli::PhysicsShapeSphereBuilder class */);
%factory(njli::PhysicsShapeSphereBuilder *njli::PhysicsShapeSphereBuilder::copy, njli::PhysicsShapeSphereBuilder /*Add the children to the njli::PhysicsShapeSphereBuilder class */);

//Extend
%extend njli::PhysicsShapeSphereBuilder
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
