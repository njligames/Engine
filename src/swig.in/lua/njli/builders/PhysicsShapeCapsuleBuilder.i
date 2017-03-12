//Factory
%newobject njli::PhysicsShapeCapsuleBuilder::create;
%delobject njli::PhysicsShapeCapsuleBuilder::destroy;
%factory(njli::PhysicsShapeCapsuleBuilder *njli::PhysicsShapeCapsuleBuilder::create, njli::PhysicsShapeCapsuleBuilder /*Add the children to the njli::PhysicsShapeCapsuleBuilder class */);
%factory(njli::PhysicsShapeCapsuleBuilder *njli::PhysicsShapeCapsuleBuilder::clone, njli::PhysicsShapeCapsuleBuilder /*Add the children to the njli::PhysicsShapeCapsuleBuilder class */);
%factory(njli::PhysicsShapeCapsuleBuilder *njli::PhysicsShapeCapsuleBuilder::copy, njli::PhysicsShapeCapsuleBuilder /*Add the children to the njli::PhysicsShapeCapsuleBuilder class */);

//Extend
%extend njli::PhysicsShapeCapsuleBuilder
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
