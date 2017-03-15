//Factory
%newobject njli::PhysicsShapeConvexHull::create;
%delobject njli::PhysicsShapeConvexHull::destroy;
%factory(njli::PhysicsShapeConvexHull *njli::PhysicsShapeConvexHull::create, njli::PhysicsShapeConvexHull /*Add the children to the njli::PhysicsShapeConvexHull class */);
%factory(njli::PhysicsShapeConvexHull *njli::PhysicsShapeConvexHull::clone, njli::PhysicsShapeConvexHull /*Add the children to the njli::PhysicsShapeConvexHull class */);
%factory(njli::PhysicsShapeConvexHull *njli::PhysicsShapeConvexHull::copy, njli::PhysicsShapeConvexHull /*Add the children to the njli::PhysicsShapeConvexHull class */);

//Extend
%extend njli::PhysicsShapeConvexHull
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
