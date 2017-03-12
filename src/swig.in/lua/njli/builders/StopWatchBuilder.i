//Factory
%newobject njli::StopWatchBuilder::create;
%delobject njli::StopWatchBuilder::destroy;
%factory(njli::StopWatchBuilder *njli::StopWatchBuilder::create, njli::StopWatchBuilder /*Add the children to the njli::StopWatchBuilder class*/);
%factory(njli::StopWatchBuilder *njli::StopWatchBuilder::clone, njli::StopWatchBuilder /*Add the children to the njli::StopWatchBuilder class*/);
%factory(njli::StopWatchBuilder *njli::StopWatchBuilder::copy, njli::StopWatchBuilder /*Add the children to the njli::StopWatchBuilder class*/);

//Extend
%extend njli::StopWatchBuilder
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
