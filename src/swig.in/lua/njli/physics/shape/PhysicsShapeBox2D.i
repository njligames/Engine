//Factory
%newobject njli::PhysicsShapeBox2D::create;
%delobject njli::PhysicsShapeBox2D::destroy;
%factory(njli::PhysicsShapeBox2D *njli::PhysicsShapeBox2D::create, njli::PhysicsShapeBox2D /*Add the children to the njli::PhysicsShapeBox2D class*/);
%factory(njli::PhysicsShapeBox2D *njli::PhysicsShapeBox2D::clone, njli::PhysicsShapeBox2D /*Add the children to the njli::PhysicsShapeBox2D class*/);
%factory(njli::PhysicsShapeBox2D *njli::PhysicsShapeBox2D::copy, njli::PhysicsShapeBox2D /*Add the children to the njli::PhysicsShapeBox2D class*/);

//Extend
%extend njli::PhysicsShapeBox2D
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
