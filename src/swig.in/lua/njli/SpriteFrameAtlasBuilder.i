//Factory
%newobject njli::SpriteFrameAtlasBuilder::create;
%delobject njli::SpriteFrameAtlasBuilder::destroy;
%factory(njli::SpriteFrameAtlasBuilder *njli::SpriteFrameAtlasBuilder::create, njli::SpriteFrameAtlasBuilder /*Add the children to the njli::SpriteFrameAtlasBuilder class*/);
%factory(njli::SpriteFrameAtlasBuilder *njli::SpriteFrameAtlasBuilder::clone, njli::SpriteFrameAtlasBuilder /*Add the children to the njli::SpriteFrameAtlasBuilder class*/);
%factory(njli::SpriteFrameAtlasBuilder *njli::SpriteFrameAtlasBuilder::copy, njli::SpriteFrameAtlasBuilder /*Add the children to the njli::SpriteFrameAtlasBuilder class*/);

//Extend
%extend njli::SpriteFrameAtlasBuilder
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
