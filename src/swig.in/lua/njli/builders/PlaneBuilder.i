//Factory
%newobject njli::PlaneBuilder::create;
%delobject njli::PlaneBuilder::destroy;
%factory(njli::PlaneBuilder *njli::PlaneBuilder::create, njli::PlaneBuilder /*Add the children to the njli::PlaneBuilder class*/);
%factory(njli::PlaneBuilder *njli::PlaneBuilder::clone, njli::PlaneBuilder /*Add the children to the njli::PlaneBuilder class*/);
%factory(njli::PlaneBuilder *njli::PlaneBuilder::copy, njli::PlaneBuilder /*Add the children to the njli::PlaneBuilder class*/);

//Extend
%extend njli::PlaneBuilder
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
