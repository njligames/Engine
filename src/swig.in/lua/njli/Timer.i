//Factory
%newobject njli::Timer::create;
%delobject njli::Timer::destroy;
%factory(njli::Timer *njli::Timer::create, njli::Timer /*Add the children to the njli::Timer class*/);
%factory(njli::Timer *njli::Timer::clone, njli::Timer /*Add the children to the njli::Timer class*/);
%factory(njli::Timer *njli::Timer::copy, njli::Timer /*Add the children to the njli::Timer class*/);

//Extend
%extend njli::Timer
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
