//
//  GameViewController.m
//  iOS
//
//  Created by James Folk on 2/28/17.
//  Copyright © 2017 James Folk. All rights reserved.
//

#import "GameViewController.h"
#import <OpenGLES/ES2/glext.h>

#include "hello_public.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

@interface GameViewController ()
{
    lua_State* L;
}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation GameViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    [self loadModule];
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    float timeStep = self.timeSinceLastUpdate;
//    printf("%f\n", timeStep);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#pragma mark - Load Lua Module

- (void)loadModule
{
    L = luaL_newstate();
    luaL_checkversion(L);
    
    //    DEBUG_LOG_V(TAG, "Lua version: %s\n", LUA_VERSION);
    NSLog(@"%s", LUA_VERSION);
    
    luaL_openlibs(L);
    
    if(L)
    {
        NSString *bundlePath = [[NSBundle mainBundle] bundlePath];
        NSString *appPath = [NSString stringWithFormat:@"appPath = '%@/?.so'",bundlePath];
        
        [self runScript:appPath];
        
        NSString *s = @"\n\
        package.cpath = appPath\n\
        \n\
            hello=require('njli')\n\
            inst=hello.Hello(23)\n\
            inst:printHello()\n\
        \n\
        \n\
        \n";
        
        
        [self runScript:s];
    }
}

- (void)runScript:(NSString*)script
{
    NSLog(@"Running Script... %@", script);
    
    if(luaL_loadstring(L, [script UTF8String]) != LUA_OK)
        printf("%s", lua_tostring( L, -1 ));
    if(lua_pcall( L, 0, LUA_MULTRET, 0 ) != LUA_OK)
        printf("%s", lua_tostring( L, -1 ));
    
}

@end
