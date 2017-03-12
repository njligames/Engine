//Factory
%newobject njli::CollisionResponse::create;
%delobject njli::CollisionResponse::destroy;
%factory(njli::CollisionResponse *njli::CollisionResponse::create, njli::CollisionResponse /*Add the children to the njli::CollisionResponse class*/);
%factory(njli::CollisionResponse *njli::CollisionResponse::clone, njli::CollisionResponse /*Add the children to the njli::CollisionResponse class*/);
%factory(njli::CollisionResponse *njli::CollisionResponse::copy, njli::CollisionResponse /*Add the children to the njli::CollisionResponse class*/);

//Extend
%extend njli::CollisionResponse
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
