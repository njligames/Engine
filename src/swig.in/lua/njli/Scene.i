//Factory
%newobject njli::Scene::create;
%delobject njli::Scene::destroy;
%factory(njli::Scene *njli::Scene::create, njli::Scene /*Add the children to the njli::Scene class*/);
%factory(njli::Scene *njli::Scene::clone, njli::Scene /*Add the children to the njli::Scene class*/);
%factory(njli::Scene *njli::Scene::copy, njli::Scene /*Add the children to the njli::Scene class*/);
%convert(njli::Node *njli::Scene::getRootNode, njli::Node);
%convert(njli::Camera *njli::Scene::getCamera, njli::Camera);
%convert(njli::Light *njli::Scene::getLight, njli::Light);
%convert(njli::SceneStateMachine *njli::Scene::getStateMachine, njli::SceneStateMachine);
%convert(njli::PhysicsWorld *njli::Scene::getPhysicsWorld, njli::PhysicsWorld);

//Extend
%extend njli::Scene
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
        /*WILL FARRELL*/
        sprintf(tmp, "%s", s.c_str());
        return tmp;
    }
    
//    njli::ParticleEmitter **getParticleEmitters()const
//    {
//        std::vector<njli::ParticleEmitter*> items;
//        self->getParticleEmitters(items);
//        size_t nelements = items.size();
//        
//        njli::ParticleEmitter **ret = (njli::ParticleEmitter**)(njli::World::getInstance()->getWorldFactory()->createArray(njli::ParticleEmitter::type(), nelements));
//        
//        for (s32 i = 0; i < nelements; i++)
//            ret[i] = items[i];
//        
//        return ret;
//    }
    
    njli::Clock **getClocks()const
    {
        std::vector<njli::Clock*> items;
        self->getClocks(items);
        size_t nelements = items.size();
        
//        njli::Clock **ret = (njli::Clock**)(njli::World::getInstance()->getWorldFactory()->createArray(njli::Clock::type(), nelements));
        njli::Clock **ret = (njli::Clock**)njli::Clock::createArray(nelements);
        
        for (u32 i = 0; i < nelements; i++)
            ret[i] = items[i];
        
        return ret;
    }
}
