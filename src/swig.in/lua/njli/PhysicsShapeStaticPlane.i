//Factory
%newobject njli::PhysicsShapeStaticPlane::create;
%delobject njli::PhysicsShapeStaticPlane::destroy;
%factory(njli::PhysicsShapeStaticPlane *njli::PhysicsShapeStaticPlane::create, njli::PhysicsShapeStaticPlane /*Add the children to the njli::PhysicsShapeStaticPlane class */);
%factory(njli::PhysicsShapeStaticPlane *njli::PhysicsShapeStaticPlane::clone, njli::PhysicsShapeStaticPlane /*Add the children to the njli::PhysicsShapeStaticPlane class */);
%factory(njli::PhysicsShapeStaticPlane *njli::PhysicsShapeStaticPlane::copy, njli::PhysicsShapeStaticPlane /*Add the children to the njli::PhysicsShapeStaticPlane class */);

//Extend
%extend njli::PhysicsShapeStaticPlane
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
