//Factory
%newobject njli::SteeringBehaviorCohesionBuilder::create;
%delobject njli::SteeringBehaviorCohesionBuilder::destroy;
%factory(njli::SteeringBehaviorCohesionBuilder *njli::SteeringBehaviorCohesionBuilder::create, njli::SteeringBehaviorCohesionBuilder /*Add the children to the njli::SteeringBehaviorCohesionBuilder class*/);
%factory(njli::SteeringBehaviorCohesionBuilder *njli::SteeringBehaviorCohesionBuilder::clone, njli::SteeringBehaviorCohesionBuilder /*Add the children to the njli::SteeringBehaviorCohesionBuilder class*/);
%factory(njli::SteeringBehaviorCohesionBuilder *njli::SteeringBehaviorCohesionBuilder::copy, njli::SteeringBehaviorCohesionBuilder /*Add the children to the njli::SteeringBehaviorCohesionBuilder class*/);

//Extend
%extend njli::SteeringBehaviorCohesionBuilder
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
