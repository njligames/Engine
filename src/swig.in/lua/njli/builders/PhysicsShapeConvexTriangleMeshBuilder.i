//Factory
%newobject njli::PhysicsShapeConvexTriangleMeshBuilder::create;
%delobject njli::PhysicsShapeConvexTriangleMeshBuilder::destroy;
%factory(njli::PhysicsShapeConvexTriangleMeshBuilder *njli::PhysicsShapeConvexTriangleMeshBuilder::create, njli::PhysicsShapeConvexTriangleMeshBuilder /*Add the children to the njli::PhysicsShapeConvexTriangleMeshBuilder class */);
%factory(njli::PhysicsShapeConvexTriangleMeshBuilder *njli::PhysicsShapeConvexTriangleMeshBuilder::clone, njli::PhysicsShapeConvexTriangleMeshBuilder /*Add the children to the njli::PhysicsShapeConvexTriangleMeshBuilder class */);
%factory(njli::PhysicsShapeConvexTriangleMeshBuilder *njli::PhysicsShapeConvexTriangleMeshBuilder::copy, njli::PhysicsShapeConvexTriangleMeshBuilder /*Add the children to the njli::PhysicsShapeConvexTriangleMeshBuilder class */);

//Extend
%extend njli::PhysicsShapeConvexTriangleMeshBuilder
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
