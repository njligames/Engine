//Factory
%newobject njli::PhysicsShapeBox2DBuilder::create;
%delobject njli::PhysicsShapeBox2DBuilder::destroy;
%factory(njli::PhysicsShapeBox2DBuilder *njli::PhysicsShapeBox2DBuilder::create, njli::PhysicsShapeBox2DBuilder /*Add the children to the njli::PhysicsShapeBox2DBuilder class*/);
%factory(njli::PhysicsShapeBox2DBuilder *njli::PhysicsShapeBox2DBuilder::clone, njli::PhysicsShapeBox2DBuilder /*Add the children to the njli::PhysicsShapeBox2DBuilder class*/);
%factory(njli::PhysicsShapeBox2DBuilder *njli::PhysicsShapeBox2DBuilder::copy, njli::PhysicsShapeBox2DBuilder /*Add the children to the njli::PhysicsShapeBox2DBuilder class*/);

//Extend
%extend njli::PhysicsShapeBox2DBuilder
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
