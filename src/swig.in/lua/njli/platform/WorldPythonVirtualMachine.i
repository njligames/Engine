//Factory

//Extend
%extend njli::WorldPythonVirtualMachine
{
    const char *__str__()
    {
        std::string s(*self);
        static char tmp[1024];
        sprintf(tmp, "%s", s.c_str());
        return tmp;
    }
}
