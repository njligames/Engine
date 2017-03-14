//
//  Localization.m
//  JLIGameEngineTest
//
//  Created by James Folk on 2/27/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "Localization.h"
#import <Foundation/Foundation.h>

std::string LOCALIZED_TEXT(const char *key)
{
    NSString *_key = [[NSString alloc] initWithCString:key encoding:NSASCIIStringEncoding];
    NSString *value = NSLocalizedString(_key, nil);
    const char *_value = [value cStringUsingEncoding:NSUTF8StringEncoding];
    return std::string(_value);
    
}

std::string LOCALIZED_LANGUAGE()
{
    NSUserDefaults* defs = [NSUserDefaults standardUserDefaults];
    NSArray* languages = [defs objectForKey:@"AppleLanguages"];
    NSString* preferredLang = [languages objectAtIndex:0];
    const char *_value = [preferredLang cStringUsingEncoding:NSUTF8StringEncoding];
    return std::string(_value);
}