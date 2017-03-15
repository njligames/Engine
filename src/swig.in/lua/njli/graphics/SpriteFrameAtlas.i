//Factory
%newobject njli::SpriteFrameAtlas::create;
%delobject njli::SpriteFrameAtlas::destroy;
%factory(njli::SpriteFrameAtlas *njli::SpriteFrameAtlas::create, njli::SpriteFrameAtlas /*Add the children to the njli::SpriteFrameAtlas class*/);
%factory(njli::SpriteFrameAtlas *njli::SpriteFrameAtlas::clone, njli::SpriteFrameAtlas /*Add the children to the njli::SpriteFrameAtlas class*/);
%factory(njli::SpriteFrameAtlas *njli::SpriteFrameAtlas::copy, njli::SpriteFrameAtlas /*Add the children to the njli::SpriteFrameAtlas class*/);

//Extend
%extend njli::SpriteFrameAtlas
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
