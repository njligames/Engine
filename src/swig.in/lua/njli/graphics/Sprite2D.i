//Factory
%newobject njli::Sprite2D::create;
%delobject njli::Sprite2D::destroy;
%factory(njli::Sprite2D *njli::Sprite2D::create, njli::Sprite2D /*Add the children to the njli::Sprite2D class*/);
%factory(njli::Sprite2D *njli::Sprite2D::clone, njli::Sprite2D /*Add the children to the njli::Sprite2D class*/);
%factory(njli::Sprite2D *njli::Sprite2D::copy, njli::Sprite2D /*Add the children to the njli::Sprite2D class*/);

//Extend
%extend njli::Sprite2D
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
