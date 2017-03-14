//Factory
%newobject njli::Sprite2DBuilder::create;
%delobject njli::Sprite2DBuilder::destroy;
%factory(njli::Sprite2DBuilder *njli::Sprite2DBuilder::create, njli::Sprite2DBuilder /*Add the children to the njli::Sprite2DBuilder class*/);
%factory(njli::Sprite2DBuilder *njli::Sprite2DBuilder::clone, njli::Sprite2DBuilder /*Add the children to the njli::Sprite2DBuilder class*/);
%factory(njli::Sprite2DBuilder *njli::Sprite2DBuilder::copy, njli::Sprite2DBuilder /*Add the children to the njli::Sprite2DBuilder class*/);

//Extend
%extend njli::Sprite2DBuilder
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
