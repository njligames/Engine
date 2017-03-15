//Factory
%newobject njli::PhysicsShapeBvhTriangleMesh::create;
%delobject njli::PhysicsShapeBvhTriangleMesh::destroy;
%factory(njli::PhysicsShapeBvhTriangleMesh *njli::PhysicsShapeBvhTriangleMesh::create, njli::PhysicsShapeBvhTriangleMesh /*Add the children to the njli::PhysicsShapeBvhTriangleMesh class */);
%factory(njli::PhysicsShapeBvhTriangleMesh *njli::PhysicsShapeBvhTriangleMesh::clone, njli::PhysicsShapeBvhTriangleMesh /*Add the children to the njli::PhysicsShapeBvhTriangleMesh class */);
%factory(njli::PhysicsShapeBvhTriangleMesh *njli::PhysicsShapeBvhTriangleMesh::copy, njli::PhysicsShapeBvhTriangleMesh /*Add the children to the njli::PhysicsShapeBvhTriangleMesh class */);

//Extend
%extend njli::PhysicsShapeBvhTriangleMesh
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
