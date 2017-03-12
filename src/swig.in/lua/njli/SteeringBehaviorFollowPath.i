//Factory
%newobject njli::SteeringBehaviorFollowPath::create;
%delobject njli::SteeringBehaviorFollowPath::destroy;
%factory(njli::SteeringBehaviorFollowPath *njli::SteeringBehaviorFollowPath::create, njli::SteeringBehaviorFollowPath /*Add the children to the njli::SteeringBehaviorFollowPath class*/);
%factory(njli::SteeringBehaviorFollowPath *njli::SteeringBehaviorFollowPath::clone, njli::SteeringBehaviorFollowPath /*Add the children to the njli::SteeringBehaviorFollowPath class*/);
%factory(njli::SteeringBehaviorFollowPath *njli::SteeringBehaviorFollowPath::copy, njli::SteeringBehaviorFollowPath /*Add the children to the njli::SteeringBehaviorFollowPath class*/);

//Extend
%extend njli::SteeringBehaviorFollowPath
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
