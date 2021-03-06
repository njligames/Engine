//Factory
%newobject njli::Image::create;
%newobject njli::Image::createSubImage;
%delobject njli::Image::destroy;
%factory(njli::Image *njli::Image::create, njli::Image /*Add the children to the njli::Image class*/);
%factory(njli::Image *njli::Image::createSubImage, njli::Image /*Add the children to the njli::Image class*/);
%factory(njli::Image *njli::Image::clone, njli::Image /*Add the children to the njli::Image class*/);
%factory(njli::Image *njli::Image::copy, njli::Image /*Add the children to the njli::Image class*/);

//Extend
%extend njli::Image
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
