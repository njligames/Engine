//Factory
%newobject njli::ClockBuilder::create;
%delobject njli::ClockBuilder::destroy;
%factory(njli::ClockBuilder *njli::ClockBuilder::create, njli::ClockBuilder /*Add the children to the njli::ClockBuilder class*/);
%factory(njli::ClockBuilder *njli::ClockBuilder::clone, njli::ClockBuilder /*Add the children to the njli::ClockBuilder class*/);
%factory(njli::ClockBuilder *njli::ClockBuilder::copy, njli::ClockBuilder /*Add the children to the njli::ClockBuilder class*/);

//Extend
%extend njli::ClockBuilder
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
