//Factory
%newobject njli::Font::create;
%delobject njli::Font::destroy;
%factory(njli::Font *njli::Font::create, njli::Font /*Add the children to the njli::Font class*/);
%factory(njli::Font *njli::Font::clone, njli::Font /*Add the children to the njli::Font class*/);
%factory(njli::Font *njli::Font::copy, njli::Font /*Add the children to the njli::Font class*/);

//Extend
%extend njli::Font
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
