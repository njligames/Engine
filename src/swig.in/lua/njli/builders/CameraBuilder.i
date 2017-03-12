//Factory
%newobject njli::CameraBuilder::create;
%delobject njli::CameraBuilder::destroy;
%factory(njli::CameraBuilder *njli::CameraBuilder::create, njli::CameraBuilder /*Add the children to the njli::CameraBuilder class*/);
%factory(njli::CameraBuilder *njli::CameraBuilder::clone, njli::CameraBuilder /*Add the children to the njli::CameraBuilder class*/);
%factory(njli::CameraBuilder *njli::CameraBuilder::copy, njli::CameraBuilder /*Add the children to the njli::CameraBuilder class*/);

//Extend
%extend njli::CameraBuilder
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
