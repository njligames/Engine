//Factory
%newobject njli::PhysicsShapeCylinderBuilder::create;
%delobject njli::PhysicsShapeCylinderBuilder::destroy;
%factory(njli::PhysicsShapeCylinderBuilder *njli::PhysicsShapeCylinderBuilder::create, njli::PhysicsShapeCylinderBuilder /*Add the children to the njli::PhysicsShapeCylinderBuilder class */);
%factory(njli::PhysicsShapeCylinderBuilder *njli::PhysicsShapeCylinderBuilder::clone, njli::PhysicsShapeCylinderBuilder /*Add the children to the njli::PhysicsShapeCylinderBuilder class */);
%factory(njli::PhysicsShapeCylinderBuilder *njli::PhysicsShapeCylinderBuilder::copy, njli::PhysicsShapeCylinderBuilder /*Add the children to the njli::PhysicsShapeCylinderBuilder class */);

//Extend
%extend njli::PhysicsShapeCylinderBuilder
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
