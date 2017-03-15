//Factory
%newobject njli::ShaderProgram::create;
%delobject njli::ShaderProgram::destroy;
%factory(njli::ShaderProgram *njli::ShaderProgram::create, njli::ShaderProgram /*Add the children to the njli::ShaderProgram class*/);
%factory(njli::ShaderProgram *njli::ShaderProgram::clone, njli::ShaderProgram /*Add the children to the njli::ShaderProgram class*/);
%factory(njli::ShaderProgram *njli::ShaderProgram::copy, njli::ShaderProgram /*Add the children to the njli::ShaderProgram class*/);

//Extend
%extend njli::ShaderProgram
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
