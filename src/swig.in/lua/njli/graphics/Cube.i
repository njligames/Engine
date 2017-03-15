//Factory
%newobject njli::Cube::create;
%delobject njli::Cube::destroy;
%factory(njli::Cube *njli::Cube::create, njli::Cube /*Add the children to the njli::Cube class*/);
%factory(njli::Cube *njli::Cube::clone, njli::Cube /*Add the children to the njli::Cube class*/);
%factory(njli::Cube *njli::Cube::copy, njli::Cube /*Add the children to the njli::Cube class*/);

//Extend
%extend njli::Cube
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
