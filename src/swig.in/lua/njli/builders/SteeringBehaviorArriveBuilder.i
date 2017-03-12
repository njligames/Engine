//Factory
%newobject njli::SteeringBehaviorArriveBuilder::create;
%delobject njli::SteeringBehaviorArriveBuilder::destroy;
%factory(njli::SteeringBehaviorArriveBuilder *njli::SteeringBehaviorArriveBuilder::create, njli::SteeringBehaviorArriveBuilder /*Add the children to the njli::SteeringBehaviorArriveBuilder class*/);
%factory(njli::SteeringBehaviorArriveBuilder *njli::SteeringBehaviorArriveBuilder::clone, njli::SteeringBehaviorArriveBuilder /*Add the children to the njli::SteeringBehaviorArriveBuilder class*/);
%factory(njli::SteeringBehaviorArriveBuilder *njli::SteeringBehaviorArriveBuilder::copy, njli::SteeringBehaviorArriveBuilder /*Add the children to the njli::SteeringBehaviorArriveBuilder class*/);

//Extend
%extend njli::SteeringBehaviorArriveBuilder
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
