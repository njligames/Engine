//Factory
%newobject njli::PhysicsContact::create;
%delobject njli::PhysicsContact::destroy;
%factory(njli::PhysicsContact *njli::PhysicsContact::create, njli::PhysicsContact /*Add the children to the njli::PhysicsContact class*/);
%factory(njli::PhysicsContact *njli::PhysicsContact::clone, njli::PhysicsContact /*Add the children to the njli::PhysicsContact class*/);
%factory(njli::PhysicsContact *njli::PhysicsContact::copy, njli::PhysicsContact /*Add the children to the njli::PhysicsContact class*/);

//Extend
%extend njli::PhysicsContact
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
