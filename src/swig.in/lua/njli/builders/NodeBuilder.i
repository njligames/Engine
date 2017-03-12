//Factory
%newobject njli::NodeBuilder::create;
%delobject njli::NodeBuilder::destroy;
%factory(njli::NodeBuilder *njli::NodeBuilder::create, njli::NodeBuilder /*Add the children to the njli::NodeBuilder class*/);
%factory(njli::NodeBuilder *njli::NodeBuilder::clone, njli::NodeBuilder /*Add the children to the njli::NodeBuilder class*/);
%factory(njli::NodeBuilder *njli::NodeBuilder::copy, njli::NodeBuilder /*Add the children to the njli::NodeBuilder class*/);

//Extend
%extend njli::NodeBuilder
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
