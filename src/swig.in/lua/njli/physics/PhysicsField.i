//Factory
%newobject njli::PhysicsField::create;
%delobject njli::PhysicsField::destroy;
%factory(njli::PhysicsField *njli::PhysicsField::create, njli::PhysicsField /*Add the children to the njli::PhysicsField class*/);
%factory(njli::PhysicsField *njli::PhysicsField::clone, njli::PhysicsField /*Add the children to the njli::PhysicsField class*/);
%factory(njli::PhysicsField *njli::PhysicsField::copy, njli::PhysicsField /*Add the children to the njli::PhysicsField class*/);

//Extend
%extend njli::PhysicsField
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
