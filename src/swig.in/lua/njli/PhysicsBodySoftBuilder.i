//Factory
%newobject njli::PhysicsBodySoftBuilder::create;
%delobject njli::PhysicsBodySoftBuilder::destroy;
%factory(njli::PhysicsBodySoftBuilder *njli::PhysicsBodySoftBuilder::create, njli::PhysicsBodySoftBuilder /*Add the children to the njli::PhysicsBodySoftBuilder class*/);
%factory(njli::PhysicsBodySoftBuilder *njli::PhysicsBodySoftBuilder::clone, njli::PhysicsBodySoftBuilder /*Add the children to the njli::PhysicsBodySoftBuilder class*/);
%factory(njli::PhysicsBodySoftBuilder *njli::PhysicsBodySoftBuilder::copy, njli::PhysicsBodySoftBuilder /*Add the children to the njli::PhysicsBodySoftBuilder class*/);

//Extend
%extend njli::PhysicsBodySoftBuilder
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
