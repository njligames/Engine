//Factory
%newobject njli::PhysicsShapeHeightfieldTerrain::create;
%delobject njli::PhysicsShapeHeightfieldTerrain::destroy;
%factory(njli::PhysicsShapeHeightfieldTerrain *njli::PhysicsShapeHeightfieldTerrain::create, njli::PhysicsShapeHeightfieldTerrain /*Add the children to the njli::PhysicsShapeHeightfieldTerrain class */);
%factory(njli::PhysicsShapeHeightfieldTerrain *njli::PhysicsShapeHeightfieldTerrain::clone, njli::PhysicsShapeHeightfieldTerrain /*Add the children to the njli::PhysicsShapeHeightfieldTerrain class */);
%factory(njli::PhysicsShapeHeightfieldTerrain *njli::PhysicsShapeHeightfieldTerrain::copy, njli::PhysicsShapeHeightfieldTerrain /*Add the children to the njli::PhysicsShapeHeightfieldTerrain class */);

//Extend
%extend njli::PhysicsShapeHeightfieldTerrain
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
