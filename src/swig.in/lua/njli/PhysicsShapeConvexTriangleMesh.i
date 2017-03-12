//Factory
%newobject njli::PhysicsShapeConvexTriangleMesh::create;
%delobject njli::PhysicsShapeConvexTriangleMesh::destroy;
%factory(njli::PhysicsShapeConvexTriangleMesh *njli::PhysicsShapeConvexTriangleMesh::create, njli::PhysicsShapeConvexTriangleMesh /*Add the children to the njli::PhysicsShapeConvexTriangleMesh class */);
%factory(njli::PhysicsShapeConvexTriangleMesh *njli::PhysicsShapeConvexTriangleMesh::clone, njli::PhysicsShapeConvexTriangleMesh /*Add the children to the njli::PhysicsShapeConvexTriangleMesh class */);
%factory(njli::PhysicsShapeConvexTriangleMesh *njli::PhysicsShapeConvexTriangleMesh::copy, njli::PhysicsShapeConvexTriangleMesh /*Add the children to the njli::PhysicsShapeConvexTriangleMesh class */);

//Extend
%extend njli::PhysicsShapeConvexTriangleMesh
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
