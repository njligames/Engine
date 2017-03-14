//Factory
%newobject njli::Geometry::create;
%delobject njli::Geometry::destroy;
%factory(njli::Geometry *njli::Geometry::create, njli::Geometry, njli::Sprite2D, njli::Cube, njli::Plane /*Add the children to the njli::Geometry class*/);
%convert(njli::Material *njli::Geometry::getMaterial, njli::Material);
%convert(njli::ShaderProgram *njli::Geometry::getShaderProgram, njli::ShaderProgram);
%downcast(jli::Geometry,jli::Sprite2D,jli::Plane,jli::Geometry);

//Extend
%extend njli::Geometry
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
    
//    njli::LevelOfDetail **getLevelOfDetails()const
//    {
//        std::vector<njli::LevelOfDetail*> items;
//        self->getLevelOfDetails(items);
//        size_t nelements = items.size();
//        
////        njli::LevelOfDetail **ret = (njli::LevelOfDetail**)(njli::World::getInstance()->getWorldFactory()->createArray(njli::LevelOfDetail::type(), nelements));
//        njli::LevelOfDetail **ret = (njli::LevelOfDetail**)njli::LevelOfDetail::createArray(nelements);
//        for (s32 i = 0; i < nelements; i++)
//            ret[i] = items[i];
//        
//        return ret;
//    }
}
