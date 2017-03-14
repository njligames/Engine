//Factory
%newobject njli::ShaderProgramBuilder::create;
%delobject njli::ShaderProgramBuilder::destroy;
%factory(njli::ShaderProgramBuilder *njli::ShaderProgramBuilder::create, njli::ShaderProgramBuilder /*Add the children to the njli::ShaderProgramBuilder class*/);
%factory(njli::ShaderProgramBuilder *njli::ShaderProgramBuilder::clone, njli::ShaderProgramBuilder /*Add the children to the njli::ShaderProgramBuilder class*/);
%factory(njli::ShaderProgramBuilder *njli::ShaderProgramBuilder::copy, njli::ShaderProgramBuilder /*Add the children to the njli::ShaderProgramBuilder class*/);

//Extend
%extend njli::ShaderProgramBuilder
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
