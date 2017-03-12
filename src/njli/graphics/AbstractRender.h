//
//  AbstractRender.h
//  JLIGameEngineTest
//
//  Created by James Folk on 5/10/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractRender_h
#define JLIGameEngineTest_AbstractRender_h

/**
 <#Description#>
 
 :returns: <#return value description#>
 */
void initGL();

/**
 *  <#Description#>
 */
void renderGL();

/**
 *  <#Description#>
 */
void printGLInfo();

/**
 *  <#Description#>
 *
 *  @param red   <#red description#>
 *  @param green <#green description#>
 *  @param blue  <#blue description#>
 *  @param alpha <#alpha description#>
 */
void setGLBackgroundColor(float red, float green, float blue, float alpha);

/**
 *  <#Description#>
 *
 *  @param x      <#x description#>
 *  @param y      <#y description#>
 *  @param width  <#width description#>
 *  @param height <#height description#>
 */
void setGLViewSize(int x, int y, int width, int height);

#endif
