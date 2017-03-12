//Factory
%newobject njli::Camera::create;
%delobject njli::Camera::destroy;
%factory(njli::Camera *njli::Camera::create, njli::Camera /*Add the children to the njli::Camera class*/);
%factory(njli::Camera *njli::Camera::clone, njli::Camera /*Add the children to the njli::Camera class*/);
%factory(njli::Camera *njli::Camera::copy, njli::Camera /*Add the children to the njli::Camera class*/);

//Extend
%extend njli::Camera
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
