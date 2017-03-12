//Factory
%newobject njli::PhysicsShapeBvhTriangleMeshBuilder::create;
%delobject njli::PhysicsShapeBvhTriangleMeshBuilder::destroy;
%factory(njli::PhysicsShapeBvhTriangleMeshBuilder *njli::PhysicsShapeBvhTriangleMeshBuilder::create, njli::PhysicsShapeBvhTriangleMeshBuilder /*Add the children to the njli::PhysicsShapeBvhTriangleMeshBuilder class */);
%factory(njli::PhysicsShapeBvhTriangleMeshBuilder *njli::PhysicsShapeBvhTriangleMeshBuilder::clone, njli::PhysicsShapeBvhTriangleMeshBuilder /*Add the children to the njli::PhysicsShapeBvhTriangleMeshBuilder class */);
%factory(njli::PhysicsShapeBvhTriangleMeshBuilder *njli::PhysicsShapeBvhTriangleMeshBuilder::copy, njli::PhysicsShapeBvhTriangleMeshBuilder /*Add the children to the njli::PhysicsShapeBvhTriangleMeshBuilder class */);

//Extend
%extend njli::PhysicsShapeBvhTriangleMeshBuilder
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
