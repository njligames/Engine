//Factory
%newobject njli::PhysicsShapeBoxBuilder::create;
%delobject njli::PhysicsShapeBoxBuilder::destroy;
%factory(njli::PhysicsShapeBoxBuilder *njli::PhysicsShapeBoxBuilder::create, njli::PhysicsShapeBoxBuilder /*Add the children to the njli::PhysicsShapeBoxBuilder class*/);
%factory(njli::PhysicsShapeBoxBuilder *njli::PhysicsShapeBoxBuilder::clone, njli::PhysicsShapeBoxBuilder /*Add the children to the njli::PhysicsShapeBoxBuilder class*/);
%factory(njli::PhysicsShapeBoxBuilder *njli::PhysicsShapeBoxBuilder::copy, njli::PhysicsShapeBoxBuilder /*Add the children to the njli::PhysicsShapeBoxBuilder class*/);

//Extend
%extend njli::PhysicsShapeBoxBuilder
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
