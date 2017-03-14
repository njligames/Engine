//Factory
%newobject njli::Sound::create;
%delobject njli::Sound::destroy;
%factory(njli::Sound *njli::Sound::create, njli::Sound /*Add the children to the njli::Sound class*/);
%factory(njli::Sound *njli::Sound::clone, njli::Sound /*Add the children to the njli::Sound class*/);
%factory(njli::Sound *njli::Sound::copy, njli::Sound /*Add the children to the njli::Sound class*/);



//Extend
%extend njli::Sound
{
    const char *__str__()
    {
        std::string s(*self);
        static char tmp[1024];
        sprintf(tmp, "%s", s.c_str());
        return tmp;
    }
}
