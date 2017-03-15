//Factory
%newobject njli::SteeringBehaviorOffsetPursuitBuilder::create;
%delobject njli::SteeringBehaviorOffsetPursuitBuilder::destroy;
%factory(njli::SteeringBehaviorOffsetPursuitBuilder *njli::SteeringBehaviorOffsetPursuitBuilder::create, njli::SteeringBehaviorOffsetPursuitBuilder /*Add the children to the njli::SteeringBehaviorOffsetPursuitBuilder class*/);
%factory(njli::SteeringBehaviorOffsetPursuitBuilder *njli::SteeringBehaviorOffsetPursuitBuilder::clone, njli::SteeringBehaviorOffsetPursuitBuilder /*Add the children to the njli::SteeringBehaviorOffsetPursuitBuilder class*/);
%factory(njli::SteeringBehaviorOffsetPursuitBuilder *njli::SteeringBehaviorOffsetPursuitBuilder::copy, njli::SteeringBehaviorOffsetPursuitBuilder /*Add the children to the njli::SteeringBehaviorOffsetPursuitBuilder class*/);

//Extend
%extend njli::SteeringBehaviorOffsetPursuitBuilder
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
