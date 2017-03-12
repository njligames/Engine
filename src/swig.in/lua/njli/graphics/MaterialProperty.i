//Factory
%newobject njli::MaterialProperty::create;
%delobject njli::MaterialProperty::destroy;
%factory(njli::MaterialProperty *njli::MaterialProperty::create, njli::MaterialProperty /*Add the children to the njli::MaterialProperty class*/);
%factory(njli::MaterialProperty *njli::MaterialProperty::clone, njli::MaterialProperty /*Add the children to the njli::MaterialProperty class*/);
%factory(njli::MaterialProperty *njli::MaterialProperty::copy, njli::MaterialProperty /*Add the children to the njli::MaterialProperty class*/);

//Extend
%extend njli::MaterialProperty
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
