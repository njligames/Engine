//Factory
%newobject njli::PhysicsFieldBuilder::create;
%delobject njli::PhysicsFieldBuilder::destroy;
%factory(njli::PhysicsFieldBuilder *njli::PhysicsFieldBuilder::create, njli::PhysicsFieldBuilder /*Add the children to the njli::PhysicsFieldBuilder class*/);
%factory(njli::PhysicsFieldBuilder *njli::PhysicsFieldBuilder::clone, njli::PhysicsFieldBuilder /*Add the children to the njli::PhysicsFieldBuilder class*/);
%factory(njli::PhysicsFieldBuilder *njli::PhysicsFieldBuilder::copy, njli::PhysicsFieldBuilder /*Add the children to the njli::PhysicsFieldBuilder class*/);

//Extend
%extend njli::PhysicsFieldBuilder
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
