//Factory
%newobject njli::PhysicsShapeMultiSphereBuilder::create;
%delobject njli::PhysicsShapeMultiSphereBuilder::destroy;
%factory(njli::PhysicsShapeMultiSphereBuilder *njli::PhysicsShapeMultiSphereBuilder::create, njli::PhysicsShapeMultiSphereBuilder /*Add the children to the njli::PhysicsShapeMultiSphereBuilder class */);
%factory(njli::PhysicsShapeMultiSphereBuilder *njli::PhysicsShapeMultiSphereBuilder::clone, njli::PhysicsShapeMultiSphereBuilder /*Add the children to the njli::PhysicsShapeMultiSphereBuilder class */);
%factory(njli::PhysicsShapeMultiSphereBuilder *njli::PhysicsShapeMultiSphereBuilder::copy, njli::PhysicsShapeMultiSphereBuilder /*Add the children to the njli::PhysicsShapeMultiSphereBuilder class */);

//Extend
%extend njli::PhysicsShapeMultiSphereBuilder
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
