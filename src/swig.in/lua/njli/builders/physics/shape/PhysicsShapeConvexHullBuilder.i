//Factory
%newobject njli::PhysicsShapeConvexHullBuilder::create;
%delobject njli::PhysicsShapeConvexHullBuilder::destroy;
%factory(njli::PhysicsShapeConvexHullBuilder *njli::PhysicsShapeConvexHullBuilder::create, njli::PhysicsShapeConvexHullBuilder /*Add the children to the njli::PhysicsShapeConvexHullBuilder class */);
%factory(njli::PhysicsShapeConvexHullBuilder *njli::PhysicsShapeConvexHullBuilder::clone, njli::PhysicsShapeConvexHullBuilder /*Add the children to the njli::PhysicsShapeConvexHullBuilder class */);
%factory(njli::PhysicsShapeConvexHullBuilder *njli::PhysicsShapeConvexHullBuilder::copy, njli::PhysicsShapeConvexHullBuilder /*Add the children to the njli::PhysicsShapeConvexHullBuilder class */);

//Extend
%extend njli::PhysicsShapeConvexHullBuilder
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
