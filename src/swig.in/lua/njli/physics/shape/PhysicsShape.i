//Factory
%newobject njli::PhysicsShape::create;
%delobject njli::PhysicsShape::destroy;
%factory(njli::PhysicsShape *njli::PhysicsShape::create,
         njli::PhysicsShapeBox,
         njli::PhysicsShapeBox2D,
         njli::PhysicsShapeSphere,
         njli::PhysicsShapeCylinder,
         njli::PhysicsShapeCapsule,
         njli::PhysicsShapeCone,
         njli::PhysicsShapeMultiSphere,
         njli::PhysicsShapeConvexHull,
         njli::PhysicsShapeConvexTriangleMesh,
         njli::PhysicsShapeBvhTriangleMesh,
         njli::PhysicsShapeHeightfieldTerrain,
         njli::PhysicsShapeStaticPlane
/*Add the children to the njli::PhysicsShape class*/);

//Array

//Extend
%extend njli::PhysicsShape
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

//Typemap