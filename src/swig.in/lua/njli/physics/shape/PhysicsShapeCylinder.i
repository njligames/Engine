//Factory
%newobject njli::PhysicsShapeCylinder::create;
%delobject njli::PhysicsShapeCylinder::destroy;
%factory(njli::PhysicsShapeCylinder *njli::PhysicsShapeCylinder::create, njli::PhysicsShapeCylinder /*Add the children to the njli::PhysicsShapeCylinder class */);
%factory(njli::PhysicsShapeCylinder *njli::PhysicsShapeCylinder::clone, njli::PhysicsShapeCylinder /*Add the children to the njli::PhysicsShapeCylinder class */);
%factory(njli::PhysicsShapeCylinder *njli::PhysicsShapeCylinder::copy, njli::PhysicsShapeCylinder /*Add the children to the njli::PhysicsShapeCylinder class */);

//Extend
%extend njli::PhysicsShapeCylinder
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
