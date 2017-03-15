//Factory
%newobject njli::Plane::create;
%delobject njli::Plane::destroy;
%factory(njli::Plane *njli::Plane::create, njli::Plane /*Add the children to the njli::Plane class*/);
%factory(njli::Plane *njli::Plane::clone, njli::Plane /*Add the children to the njli::Plane class*/);
%factory(njli::Plane *njli::Plane::copy, njli::Plane /*Add the children to the njli::Plane class*/);

//Extend
%extend njli::Plane
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
