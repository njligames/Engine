//Factory
%newobject njli::StopWatch::create;
%delobject njli::StopWatch::destroy;
%factory(njli::StopWatch *njli::StopWatch::create, njli::StopWatch /*Add the children to the njli::StopWatch class*/);
%factory(njli::StopWatch *njli::StopWatch::clone, njli::StopWatch /*Add the children to the njli::StopWatch class*/);
%factory(njli::StopWatch *njli::StopWatch::copy, njli::StopWatch /*Add the children to the njli::StopWatch class*/);

//Extend
%extend njli::StopWatch
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
