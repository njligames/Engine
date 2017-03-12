//
//  WorldFacebook.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 7/6/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "JLIFactoryTypes.h"
#include "WorldFacebook.h"

#include "World.h"

//#import <Foundation/Foundation.h>
//
//#import <FBSDKCoreKit/FBSDKCoreKit.h>
//#import <FBSDKLoginKit/FBSDKLoginKit.h>
//#import "AppDelegate.h"

namespace njli {

WorldFacebook::WorldFacebook()
{
}

WorldFacebook::~WorldFacebook()
{
}

const char* WorldFacebook::getClassName() const
{
    return "WorldFacebook";
}

s32 WorldFacebook::getType() const
{
    return JLI_OBJECT_TYPE_WorldFacebook;
}

WorldFacebook::operator std::string() const
{
    return "TODO";
}

void WorldFacebook::login()
{
    //        FBSDKLoginManager *login = [[FBSDKLoginManager alloc] init];
    //        [login logInWithReadPermissions:@[@"email"]
    //                                handler:^(FBSDKLoginManagerLoginResult *result, NSError *error)
    //         {
    //         char buffer[256];
    //         sprintf(buffer, "%s", "FacebookResponse");
    //
    //         if (error)
    //         {
    //         // Process error
    //                                    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, 0);
    //         }
    //         else if (result.isCancelled)
    //         {
    //         // Handle cancellations
    //                                    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, 1);
    //         }
    //         else
    //         {
    //         // If you ask for multiple permissions at once, you
    //         // should check if specific permissions missing
    //         if ([result.grantedPermissions containsObject:@"email"])
    //         {
    //         // Do work
    //
    //                                    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, 2);
    //         }
    //         }
    //         }];
}

void WorldFacebook::logout()
{
}

void WorldFacebook::inviteToApp()
{
    //        AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    //        [appDelegate inviteAppFacebook];
}
}