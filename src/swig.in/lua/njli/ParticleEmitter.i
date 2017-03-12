//Factory
%newobject njli::ParticleEmitter::create;
%delobject njli::ParticleEmitter::destroy;
%factory(njli::ParticleEmitter *njli::ParticleEmitter::create, njli::ParticleEmitter /*Add the children to the njli::ParticleEmitter class*/);
%factory(njli::ParticleEmitter *njli::ParticleEmitter::clone, njli::ParticleEmitter /*Add the children to the njli::ParticleEmitter class*/);
%factory(njli::ParticleEmitter *njli::ParticleEmitter::copy, njli::ParticleEmitter /*Add the children to the njli::ParticleEmitter class*/);
%convert(njli::ShaderProgram* njli::ParticleEmitter::getShaderProgram, njli::ShaderProgram);

//Extend
%extend njli::ParticleEmitter
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
