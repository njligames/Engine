//Factory
%newobject njli::PhysicsShapeBox::create;
%delobject njli::PhysicsShapeBox::destroy;
%factory(njli::PhysicsShapeBox *njli::PhysicsShapeBox::create, njli::PhysicsShapeBox /*Add the children to the njli::PhysicsShapeBox class*/);
%factory(njli::PhysicsShapeBox *njli::PhysicsShapeBox::clone, njli::PhysicsShapeBox /*Add the children to the njli::PhysicsShapeBox class*/);
%factory(njli::PhysicsShapeBox *njli::PhysicsShapeBox::copy, njli::PhysicsShapeBox /*Add the children to the njli::PhysicsShapeBox class*/);

//Extend
%extend njli::PhysicsShapeBox
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
