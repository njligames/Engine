//Factory
%newobject njli::ActionBuilder::create;
%delobject njli::ActionBuilder::destroy;
%factory(njli::ActionBuilder *njli::ActionBuilder::create, njli::ActionBuilder /*Add the children to the njli::ActionBuilder class*/);
%factory(njli::ActionBuilder *njli::ActionBuilder::clone, njli::ActionBuilder /*Add the children to the njli::ActionBuilder class*/);
%factory(njli::ActionBuilder *njli::ActionBuilder::copy, njli::ActionBuilder /*Add the children to the njli::ActionBuilder class*/);

//Extend
%extend njli::ActionBuilder
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

