//Factory
%newobject njli::SteeringBehaviorEvadeBuilder::create;
%delobject njli::SteeringBehaviorEvadeBuilder::destroy;
%factory(njli::SteeringBehaviorEvadeBuilder *njli::SteeringBehaviorEvadeBuilder::create, njli::SteeringBehaviorEvadeBuilder /*Add the children to the njli::SteeringBehaviorEvadeBuilder class*/);
%factory(njli::SteeringBehaviorEvadeBuilder *njli::SteeringBehaviorEvadeBuilder::clone, njli::SteeringBehaviorEvadeBuilder /*Add the children to the njli::SteeringBehaviorEvadeBuilder class*/);
%factory(njli::SteeringBehaviorEvadeBuilder *njli::SteeringBehaviorEvadeBuilder::copy, njli::SteeringBehaviorEvadeBuilder /*Add the children to the njli::SteeringBehaviorEvadeBuilder class*/);

//Extend
%extend njli::SteeringBehaviorEvadeBuilder
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
