//Factory
%newobject njli::SteeringBehaviorWander::create;
%delobject njli::SteeringBehaviorWander::destroy;
%factory(njli::SteeringBehaviorWander *njli::SteeringBehaviorWander::create, njli::SteeringBehaviorWander /*Add the children to the njli::SteeringBehaviorWander class*/);
%factory(njli::SteeringBehaviorWander *njli::SteeringBehaviorWander::clone, njli::SteeringBehaviorWander /*Add the children to the njli::SteeringBehaviorWander class*/);
%factory(njli::SteeringBehaviorWander *njli::SteeringBehaviorWander::copy, njli::SteeringBehaviorWander /*Add the children to the njli::SteeringBehaviorWander class*/);

//Extend
%extend njli::SteeringBehaviorWander
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
