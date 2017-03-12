//Factory
%newobject njli::PhysicsShapeStaticPlaneBuilder::create;
%delobject njli::PhysicsShapeStaticPlaneBuilder::destroy;
%factory(njli::PhysicsShapeStaticPlaneBuilder *njli::PhysicsShapeStaticPlaneBuilder::create, njli::PhysicsShapeStaticPlaneBuilder /*Add the children to the njli::PhysicsShapeStaticPlaneBuilder class */);
%factory(njli::PhysicsShapeStaticPlaneBuilder *njli::PhysicsShapeStaticPlaneBuilder::clone, njli::PhysicsShapeStaticPlaneBuilder /*Add the children to the njli::PhysicsShapeStaticPlaneBuilder class */);
%factory(njli::PhysicsShapeStaticPlaneBuilder *njli::PhysicsShapeStaticPlaneBuilder::copy, njli::PhysicsShapeStaticPlaneBuilder /*Add the children to the njli::PhysicsShapeStaticPlaneBuilder class */);

//Extend
%extend njli::PhysicsShapeStaticPlaneBuilder
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
