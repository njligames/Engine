//Factory
%newobject njli::SteeringBehaviorFollowPathBuilder::create;
%delobject njli::SteeringBehaviorFollowPathBuilder::destroy;
%factory(njli::SteeringBehaviorFollowPathBuilder *njli::SteeringBehaviorFollowPathBuilder::create, njli::SteeringBehaviorFollowPathBuilder /*Add the children to the njli::SteeringBehaviorFollowPathBuilder class*/);
%factory(njli::SteeringBehaviorFollowPathBuilder *njli::SteeringBehaviorFollowPathBuilder::clone, njli::SteeringBehaviorFollowPathBuilder /*Add the children to the njli::SteeringBehaviorFollowPathBuilder class*/);
%factory(njli::SteeringBehaviorFollowPathBuilder *njli::SteeringBehaviorFollowPathBuilder::copy, njli::SteeringBehaviorFollowPathBuilder /*Add the children to the njli::SteeringBehaviorFollowPathBuilder class*/);

//Extend
%extend njli::SteeringBehaviorFollowPathBuilder
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
