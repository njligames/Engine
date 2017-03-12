//Factory
%newobject njli::ParticleEmitterBuilder::create;
%delobject njli::ParticleEmitterBuilder::destroy;
%factory(njli::ParticleEmitterBuilder *njli::ParticleEmitterBuilder::create, njli::ParticleEmitterBuilder /*Add the children to the njli::ParticleEmitterBuilder class*/);
%factory(njli::ParticleEmitterBuilder *njli::ParticleEmitterBuilder::clone, njli::ParticleEmitterBuilder /*Add the children to the njli::ParticleEmitterBuilder class*/);
%factory(njli::ParticleEmitterBuilder *njli::ParticleEmitterBuilder::copy, njli::ParticleEmitterBuilder /*Add the children to the njli::ParticleEmitterBuilder class*/);

//Extend
%extend njli::ParticleEmitterBuilder
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

//Typemap
