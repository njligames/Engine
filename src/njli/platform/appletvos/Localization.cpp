//
//  Localization.m
//  JLIGameEngineTest
//
//  Created by James Folk on 2/27/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "Localization.h"
#import <Foundation/Foundation.h>

std::string LOCALIZED_TEXT(const char *key, const char *default_value, const char *comment)
{
    /*
     #define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
	    [bundle localizedStringForKey:(key) value:(val) table:(tbl)]
     */
    
    //    NSString *value = NSLocalizedStringWithDefaultValue(@"window.greeting" // Unique key of your choice
    //                                      , @"Localizable", // .strings file name
    //                                      , [NSBundle mainBundle] // Default bundle
    //                                      , @"Hello, world" // Default (English) text
    //                                      , @"Window title" // comment for translator
    //                                      );
    
    NSString *_key = [[NSString alloc] initWithCString:key encoding:NSASCIIStringEncoding];
    NSString *_val = [[NSString alloc] initWithCString:default_value encoding:NSASCIIStringEncoding];
    NSString *_tbl = @"Localizable";
    
//    NSString *value = NSLocalizedString(_key, nil);
    NSString *value = [NSBundle.mainBundle localizedStringForKey:(_key) value:(_val) table:(_tbl)];
    
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
