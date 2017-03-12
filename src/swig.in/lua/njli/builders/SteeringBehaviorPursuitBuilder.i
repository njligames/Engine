//Factory
%newobject njli::SteeringBehaviorPursuitBuilder::create;
%delobject njli::SteeringBehaviorPursuitBuilder::destroy;
%factory(njli::SteeringBehaviorPursuitBuilder *njli::SteeringBehaviorPursuitBuilder::create, njli::SteeringBehaviorPursuitBuilder /*Add the children to the njli::SteeringBehaviorPursuitBuilder class*/);
%factory(njli::SteeringBehaviorPursuitBuilder *njli::SteeringBehaviorPursuitBuilder::clone, njli::SteeringBehaviorPursuitBuilder /*Add the children to the njli::SteeringBehaviorPursuitBuilder class*/);
%factory(njli::SteeringBehaviorPursuitBuilder *njli::SteeringBehaviorPursuitBuilder::copy, njli::SteeringBehaviorPursuitBuilder /*Add the children to the njli::SteeringBehaviorPursuitBuilder class*/);

//Extend
%extend njli::SteeringBehaviorPursuitBuilder
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
