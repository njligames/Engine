//
//  DeviceTouch.mm
//  JLIGameEngineTest
//
//  Created by James Folk on 12/8/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "DeviceTouch.h"
#include <UIKit/UIKit.h>
#include "JLIFactoryTypes.h"
#include "World.h"

namespace njli
{
    const u8 DeviceTouch::MAX_TOUCHES = 5;
    
//    -(CGPoint) pixelPointFromViewPoint:(CGPoint)touch
//    CGPoint pixelPointFromViewPoint(CGPoint touch, UIView *view)
//    {
//        // Sanity check to see whether the touch is actually in the view
//        if(touch.x >= 0.0 && touch.x <= view.frame.size.width && touch.y >= 0.0 && touch.y <= view.frame.size.height)
//        {
//            UIViewContentMode m = view.contentMode;
////            NSLog(@"%ld", (long)m);
//            // http://developer.apple.com/library/ios/#DOCUMENTATION/UIKit/Reference/UIView_Class/UIView/UIView.html#//apple_ref/occ/cl/UIView
////            switch(view.contentMode)
////            {
////                    // Simply scale the image size by the size of the frame
////                case UIViewContentModeScaleToFill:
////                    // Redraw is basically the same as scale to fill but redraws itself in the drawRect call (so when bounds change)
////                case UIViewContentModeRedraw:
////                    return CGPointMake(floor(touch.x/(view.frame.size.width/view.image.size.width)),floor(touch.y/(view.frame.size.height/view.image.size.height)));
////                    // Although the documentation doesn't state it, we will assume a centered image. This mode makes the image fit into the view with its aspect ratio
////                case UIViewContentModeScaleAspectFit:
////                {
////                    // If the aspect ratio favours width over height in relation to the images aspect ratio
////                    if(view.frame.size.width/view.frame.size.height > view.image.size.width/view.image.size.height)
////                    {
////                        // Checking whether the touch coordinate is not in a 'blank' spot on the view
////                        if(touch.x >= (view.frame.size.width/2.0)-(((view.frame.size.height/view.image.size.height)*view.image.size.width)/2.0)
////                           && touch.x <= (view.frame.size.width/2.0)+(((view.frame.size.height/view.image.size.height)*view.image.size.width)/2.0))
////                        {
////                            // Scaling by using the height ratio as a reference, and minusing the blank x coordiantes on the view
////                            return CGPointMake(floor((touch.x-((view.frame.size.width/2.0)-(((view.frame.size.height/view.image.size.height)*view.image.size.width)/2.0)))/(view.frame.size.height/view.image.size.height)),floor(touch.y/(view.frame.size.height/view.image.size.height)));
////                        }
////                        break;
////                    }
////                    // Or if the aspect ratio favours height over width in relation to the images aspect ratio
////                    else if(view.frame.size.width/view.frame.size.height < view.image.size.width/view.image.size.height)
////                    {
////                        // Obtaining half of the view that is taken up by the aspect ratio
////                        CGFloat halfAspectFit = ((view.frame.size.width/view.image.size.width)*view.image.size.height)/2.0;
////                        // Checking whether the touch coordinate is not in a 'blank' spot on the view
////                        if(touch.y >= (view.frame.size.height/2.0)-halfAspectFit
////                           && touch.y <= (view.frame.size.height/2.0)+halfAspectFit)
////                        {
////                            // Scaling by using the width ratio as a reference, and minusing the blank y coordinates on the view
////                            return CGPointMake(floor(touch.x/(view.frame.size.width/view.image.size.width)),floor((touch.y-((view.frame.size.width/2.0)-halfAspectFit))/(view.frame.size.height/view.image.size.height)));
////                        }
////                    }
////                    // This is just the same as a scale to fill mode if the aspect ratios from the view and the image are the same
////                    else return CGPointMake(floor(touch.x/(view.frame.size.width/view.image.size.width)),floor(touch.y/(view.frame.size.width/view.image.size.height)));
////                        break;
////                }
////                    // This fills the view with the image in its aspect ratio, meaning that it could get cut off in either axis
////                case UIViewContentModeScaleAspectFill:
////                {
////                    // If the aspect ratio favours width over height in relation to the images aspect ratio
////                    if(view.frame.size.width/view.frame.size.height > view.image.size.width/view.image.size.height)
////                    {
////                        // Scaling by using the width ratio, this will cut off some height
////                        return CGPointMake(floor(touch.x/(view.frame.size.width/view.image.size.width)),floor(touch.y/(view.frame.size.width/view.image.size.width)));
////                    }
////                    // If the aspect ratio favours height over width in relation to the images aspect ratio
////                    else if(view.frame.size.width/view.frame.size.height < view.image.size.width/view.image.size.height)
////                    {
////                        // Scaling by using the height ratio, this will cut off some width
////                        return CGPointMake(floor(touch.x/(view.frame.size.height/view.image.size.height)),floor(touch.y/(view.frame.size.height/view.image.size.height)));
////                    }
////                    // Again if the aspect ratios are the same, then it will just be another copy of scale to fill mode
////                    else return CGPointMake(floor(touch.x/(view.frame.size.width/view.image.size.width)),floor(touch.y/(view.frame.size.width/view.image.size.height)));
////                        break;
////                }
////                    // This centers the image in the view both vertically and horizontally
////                case UIViewContentModeCenter:
////                {
////                    // Check whether our touch is on the image centered vertically and horizontally
////                    if(touch.x >= (view.frame.size.width/2.0)-(view.image.size.width/2.0)
////                       && touch.x <= (view.frame.size.width/2.0)+(view.image.size.width/2.0)
////                       && touch.y >= (view.frame.size.height/2.0)-(view.image.size.height/2.0)
////                       && touch.y <= (view.frame.size.height/2.0)+(view.image.size.height/2.0))
////                        // Just return the touch coordinates and minus the offset
////                        return CGPointMake(floor(touch.x-((view.frame.size.width/2.0)-(view.image.size.width/2.0))),floor(touch.y-((view.frame.size.height/2.0)-(view.image.size.height/2.0))));
////                        break;
////                }
////                    // This centers the image horizontally and moves it up to the top
////                case UIViewContentModeTop:
////                {
////                    // Check whether our touch is on the image centered horizontally and put at the vertical start
////                    if(touch.x >= (view.frame.size.width/2.0)-(view.image.size.width/2.0)
////                       && touch.x <= (view.frame.size.width/2.0)+(view.image.size.width/2.0)
////                       && touch.y <= view.image.size.height)
////                        // Just return the touch coordinates and minus the offset
////                        return CGPointMake(floor(touch.x-((view.frame.size.width/2.0)-(view.image.size.width/2.0))),floor(touch.y));
////                        break;
////                }
////                    // This centers the image horizontally and moves it down to the bottom
////                case UIViewContentModeBottom:
////                {
////                    // Check whether our touch is on the image centered horizontally and put at the vertical end
////                    if(touch.x >= (view.frame.size.width/2.0)-(view.image.size.width/2.0)
////                       && touch.x <= (view.frame.size.width/2.0)+(view.image.size.width/2.0)
////                       && touch.y >= view.frame.size.height-view.image.size.height)
////                        // Just return the touch coordinates and minus the offset
////                        return CGPointMake(floor(touch.x-((view.frame.size.width/2.0)-(view.image.size.width/2.0))),floor(touch.y-(view.frame.size.height-view.image.size.height)));
////                        break;
////                }
////                    // This moves the image to the horizontal start and centers it vertically
////                case UIViewContentModeLeft:
////                {
////                    // Check whether our touch is on the image at the horizontal start and centered vertically
////                    if(touch.x <= view.image.size.width
////                       && touch.y >= (view.frame.size.height/2.0)-(view.image.size.height/2.0)
////                       && touch.y <= (view.frame.size.height/2.0)+(view.image.size.height/2.0))
////                        return CGPointMake(floor(touch.x),floor(touch.y-((view.frame.size.height/2.0)-(view.image.size.height/2.0))));
////                        break;
////                }
////                    // This moves the image to the horizontal end and centers it vertically
////                case UIViewContentModeRight:
////                {
////                    if(touch.x >= view.frame.size.width-view.image.size.width
////                       && touch.y >= (view.frame.size.height/2.0)-(view.image.size.height/2.0)
////                       && touch.y <= (view.frame.size.height/2.0)+(view.image.size.height/2.0))
////                        return CGPointMake(floor(touch.x-(view.frame.size.width-view.image.size.width)),floor(touch.y-((view.frame.size.height/2.0)-(view.image.size.height/2.0))));
////                        break;
////                }
////                    // This simply moves the image to the horizontal and vertical start
////                case UIViewContentModeTopLeft:
////                {
////                    if(touch.x <= view.image.size.width
////                       && touch.x <= view.image.size.height)
////                        // My favourite
////                        return CGPointMake(floor(touch.x),floor(touch.y));
////                        break;
////                }
////                    // This moves the image to the horizontal end and vertical start
////                case UIViewContentModeTopRight:
////                {
////                    if(touch.x >= view.frame.size.width-view.image.size.width
////                       && touch.y <= view.image.size.height)
////                        return CGPointMake(floor(touch.x-(view.frame.size.width-view.image.size.width)),floor(touch.y));
////                        break;
////                }
////                    // This moves the image to the horizontal start and vertical end
////                case UIViewContentModeBottomLeft:
////                {
////                    if(touch.x <= view.image.size.width
////                       && touch.y <= view.frame.size.height-view.image.size.height)
////                        return CGPointMake(floor(touch.x),floor(touch.y-(view.frame.size.height-view.image.size.height)));
////                        break;
////                }
////                    // This moves the image to the horizontal and vertical end
////                case UIViewContentModeBottomRight:
////                {
////                    if(touch.x <= view.frame.size.width-view.image.size.width
////                       && touch.y <= view.frame.size.height-view.image.size.height)
////                        return CGPointMake(floor(touch.x-(view.frame.size.width-view.image.size.width)),floor(touch.y-(view.frame.size.height-view.image.size.height)));
////                        break;
////                }
////                default: break;
////            }
//        }
//        return CGPointZero;
//    }
    
    void DeviceTouch::convert(DeviceTouch &t, const void *_touch)
    {
        if(_touch)
        {
            UITouch *touch = (__bridge UITouch*)_touch;
            
            float height = njli::World::getInstance()->getViewportDimensions().y();
            
            m_scale = touch.view.contentScaleFactor;
            
            CGPoint touchPoint = [touch locationInView:touch.view];
            CGPoint previousTouchPoint = [touch previousLocationInView:touch.view];
            
            t.setTimeStampFrame(touch.timestamp);
            t.m_address = [touch hash];
            t.m_tapCount = [touch tapCount];
            
            t.m_xpos = (touchPoint.x * m_scale);
            t.m_ypos = height - (touchPoint.y * m_scale);
            
            t.m_prev_xpos = (previousTouchPoint.x * m_scale);
            t.m_prev_ypos = height - (previousTouchPoint.y * m_scale);
            
//            DEBUG_LOG_V("devictouch", "%s", ((std::string)t).c_str());
        }
    }
}
