//Factory
%newobject njli::CollisionResponseBuilder::create;
%delobject njli::CollisionResponseBuilder::destroy;
%factory(njli::CollisionResponseBuilder *njli::CollisionResponseBuilder::create, njli::CollisionResponseBuilder /*Add the children to the njli::CollisionResponseBuilder class*/);
%factory(njli::CollisionResponseBuilder *njli::CollisionResponseBuilder::clone, njli::CollisionResponseBuilder /*Add the children to the njli::CollisionResponseBuilder class*/);
%factory(njli::CollisionResponseBuilder *njli::CollisionResponseBuilder::copy, njli::CollisionResponseBuilder /*Add the children to the njli::CollisionResponseBuilder class*/);

//Extend
%extend njli::CollisionResponseBuilder
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
