//Factory
%newobject njli::Skinner::create;
%delobject njli::Skinner::destroy;
%factory(njli::Skinner *njli::Skinner::create, njli::Skinner /*Add the children to the njli::Skinner class*/);
%factory(njli::Skinner *njli::Skinner::clone, njli::Skinner /*Add the children to the njli::Skinner class*/);
%factory(njli::Skinner *njli::Skinner::copy, njli::Skinner /*Add the children to the njli::Skinner class*/);


//Extend
%extend njli::Skinner
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
