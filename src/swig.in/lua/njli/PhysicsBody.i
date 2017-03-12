//Factory
%newobject njli::PhysicsBody::create;
%delobject njli::PhysicsBody::destroy;
%factory(njli::PhysicsBody *njli::PhysicsBody::create, njli::PhysicsBodyRigid, njli::PhysicsBodyGhost, njli::PhysicsBodySoft /*Add the children to the njli::PhysicsBody class*/);

//Array

//Extend
%extend njli::PhysicsBody
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
};

//Typemap