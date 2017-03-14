//Factory
%newobject njli::PhysicsWorldBuilder::create;
%delobject njli::PhysicsWorldBuilder::destroy;
%factory(njli::PhysicsWorldBuilder *njli::PhysicsWorldBuilder::create, njli::PhysicsWorldBuilder /*Add the children to the njli::PhysicsWorldBuilder class*/);
%factory(njli::PhysicsWorldBuilder *njli::PhysicsWorldBuilder::clone, njli::PhysicsWorldBuilder /*Add the children to the njli::PhysicsWorldBuilder class*/);
%factory(njli::PhysicsWorldBuilder *njli::PhysicsWorldBuilder::copy, njli::PhysicsWorldBuilder /*Add the children to the njli::PhysicsWorldBuilder class*/);

//Extend
%extend njli::PhysicsWorldBuilder
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
