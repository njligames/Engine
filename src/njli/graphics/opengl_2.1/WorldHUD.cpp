//
//  WorldHUD.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/28/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldHUD.h"
#include "JLIFactoryTypes.h"

#include "btVector2.h"
#include "btVector3.h"
#include "btMatrix3x3.h"

#include "Image.h"
#include "SpriteFrameAtlas.h"

#include "GLPlatform.h"
//#include "nanovg.h"

#ifdef __MACOSX__
#define NANOVG_GL2_IMPLEMENTATION
#else
#define NANOVG_GLES2_IMPLEMENTATION
#endif
#include "nanovg_gl.h"
//#include "nanovg_gl_utils.h"

#include "World.h"

#include "Util.h"

#define FORMATSTRING "{\"njli::WorldHUD\":[]}"
#include "btPrint.h"

namespace njli
{
    WorldHUD::WorldHUD() :
    m_NVGContext(NULL),
    m_matrixBuffer(new f32[9]),
    m_Camera(NULL)
    {
#if defined NANOVG_GL2
        m_NVGContext = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#elif defined NANOVG_GL3
        m_NVGContext = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#elif defined NANOVG_GLES2
        m_NVGContext = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#elif defined NANOVG_GLES3
        m_NVGContext = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#endif
    }

    WorldHUD::~WorldHUD()
    {
        if(m_Camera)
            Camera::destroy(m_Camera);
        m_Camera = NULL;
        
        delete [] m_matrixBuffer;
        m_matrixBuffer=NULL;
        
        for (std::vector<s32>::iterator i = m_images.begin(); i != m_images.end(); ++i)
            nvgDeleteImage(m_NVGContext, *i);
        
#if defined NANOVG_GL2
        nvgDeleteGL2(m_NVGContext);
#elif defined NANOVG_GL3
        nvgDeleteGL3(m_NVGContext);
#elif defined NANOVG_GLES2
        nvgDeleteGLES2(m_NVGContext);
#elif defined NANOVG_GLES3
        nvgDeleteGLES3(m_NVGContext);
#endif
        
    }

    const s8 *WorldHUD::getClassName()const
    {
        return "WorldHUD";
    }

    s32 WorldHUD::getType()const
    {
        return JLI_OBJECT_TYPE_WorldHUD;
    }

    WorldHUD::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING).c_str());
    }


    s8* WorldHUD::cpToUTF8(s32 cp)
    {
        static s8 str[256];
        
        s32 n = 0;
        if (cp < 0x80) n = 1;
        else if (cp < 0x800) n = 2;
        else if (cp < 0x10000) n = 3;
        else if (cp < 0x200000) n = 4;
        else if (cp < 0x4000000) n = 5;
        else if (cp <= 0x7fffffff) n = 6;
        str[n] = '\0';
        switch (n) {
            case 6: str[5] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x4000000;
            case 5: str[4] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x200000;
            case 4: str[3] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x10000;
            case 3: str[2] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x800;
            case 2: str[1] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0xc0;
            case 1: str[0] = cp;
        }
        return str;
    }
    
    btVector4 WorldHUD::rgb(u8 r, u8 g, u8 b)
    {
        NVGcolor color = nvgRGB(r, g, b);
        return btVector4(color.r, color.g, color.b, 1.0f);
    }

    btVector4 WorldHUD::rgbf(f32 r, f32 g, f32 b)
    {
        NVGcolor color = nvgRGBf(r, g, b);
        return btVector4(color.r, color.g, color.b, 1.0f);
    }

    btVector4 WorldHUD::rgba(u8 r, u8 g, u8 b, u8 a)
    {
        NVGcolor color = nvgRGBA(r, g, b, a);
        return btVector4(color.r, color.g, color.b, color.a);
    }

    btVector4 WorldHUD::rgbaf(f32 r, f32 g, f32 b, f32 a)
    {
        NVGcolor color = nvgRGBAf(r, g, b, a);
        return btVector4(color.r, color.g, color.b, color.a);
    }

    btVector4 WorldHUD::lerpRGBA(const btVector4 &c0, const btVector4 &c1, f32 u)
    {
        
        NVGcolor color0;
        WorldHUD::btVector4ToNVGcolor(color0, c0);
        
        NVGcolor color1;
        WorldHUD::btVector4ToNVGcolor(color1, c1);
        
        NVGcolor color = nvgLerpRGBA(color0, color1, u);
        return btVector4(color.r, color.g, color.b, color.a);
    }

    btVector4 WorldHUD::transRGBA(const btVector4 &c0, u8 a)
    {
        NVGcolor color0;
        WorldHUD::btVector4ToNVGcolor(color0, c0);
        
        NVGcolor color = nvgTransRGBA(color0, a);
        return btVector4(color.r, color.g, color.b, color.a);
    }

    btVector4 WorldHUD::transRGBAf(const btVector4 &c0, f32 a)
    {
        NVGcolor color0;
        WorldHUD::btVector4ToNVGcolor(color0, c0);
        
        NVGcolor color = nvgTransRGBAf(color0, a);
        return btVector4(color.r, color.g, color.b, color.a);
    }

    btVector4 WorldHUD::hsl(f32 h, f32 s, f32 l)
    {
        NVGcolor color = nvgHSL(h, s, l);
        return btVector4(color.r, color.g, color.b, color.a);
    }

    btVector4 WorldHUD::hsla(f32 h, f32 s, f32 l, u8 a)
    {
        NVGcolor color = nvgHSLA(h, s, l, a);
        return btVector4(color.r, color.g, color.b, color.a);
    }
    
    
    
    
    
    
    
    void WorldHUD::transformIdentity(btMatrix3x3 &dst)
    {
        f32 *floats = new f32[9];
        
        btMatrix3x3ToNVGaffine(floats, dst);
        WorldHUD::transformIdentity(floats);
        NVGaffineTobtMatrix3x3(dst, floats);
        
        delete [] floats;
        floats=NULL;
    }
    
    void WorldHUD::transformTranslate(btMatrix3x3 &dst, const btVector2 &translatePos)
    {
        f32 *floats = new f32[9];
        
        btMatrix3x3ToNVGaffine(floats, dst);
        WorldHUD::transformTranslate(floats, translatePos.x(), translatePos.y());
        NVGaffineTobtMatrix3x3(dst, floats);
        
        delete [] floats;
        floats=NULL;
    }
    
    void WorldHUD::transformScale(btMatrix3x3 &dst, const btVector2 &scale)
    {
        f32 *floats = new f32[9];
        
        btMatrix3x3ToNVGaffine(floats, dst);
        WorldHUD::transformScale(floats, scale.x(), scale.y());
        NVGaffineTobtMatrix3x3(dst, floats);
        
        delete [] floats;
        floats=NULL;
    }
    
    void WorldHUD::transformRotate(btMatrix3x3 &dst, f32 a)
    {
        f32 *floats = new f32[9];
        
        btMatrix3x3ToNVGaffine(floats, dst);
        WorldHUD::transformRotate(floats, a);
        NVGaffineTobtMatrix3x3(dst, floats);
        
        delete [] floats;
        floats=NULL;
    }
    
    void WorldHUD::transformSkewX(btMatrix3x3 &dst, f32 a)
    {
        f32 *floats = new f32[9];
        
        btMatrix3x3ToNVGaffine(floats, dst);
        WorldHUD::transformSkewX(floats, a);
        NVGaffineTobtMatrix3x3(dst, floats);
        
        delete [] floats;floats=NULL;
    }
    
    void WorldHUD::transformSkewY(btMatrix3x3 &dst, f32 a)
    {
        f32 *floats = new f32[9];
        
        btMatrix3x3ToNVGaffine(floats, dst);
        WorldHUD::transformSkewY(floats, a);
        NVGaffineTobtMatrix3x3(dst, floats);
        
        delete [] floats;floats=NULL;
    }
    
    void WorldHUD::transformMultiply(btMatrix3x3 &dst, const btMatrix3x3 &src)
    {
        f32 *_dst = new f32[9];
        f32 *_src = new f32[9];
        
        btMatrix3x3ToNVGaffine(_dst, dst);
        btMatrix3x3ToNVGaffine(_src, src);
        
        WorldHUD::transformMultiply(_dst, _src);
        
        NVGaffineTobtMatrix3x3(dst, _dst);
        
        delete [] _src;_src=NULL;
        delete [] _dst;_dst=NULL;
    }
    
    void WorldHUD::transformPremultiply(btMatrix3x3 &dst, const btMatrix3x3 &src)
    {
        f32 *_dst = new f32[9];
        f32 *_src = new f32[9];
        
        btMatrix3x3ToNVGaffine(_dst, dst);
        btMatrix3x3ToNVGaffine(_src, src);
        
        WorldHUD::transformPremultiply(_dst, _src);
        
        NVGaffineTobtMatrix3x3(dst, _dst);
        
        delete [] _src;_src=NULL;
        delete [] _dst;_dst=NULL;
    }
    
    void WorldHUD::transformPoint(btMatrix3x3& dstx, btMatrix3x3 &dsty, btMatrix3x3 &xform, const btVector2 &sourcePos)
    {
        f32 *_dstx = new f32[9];
        f32 *_dsty = new f32[9];
        f32 *_xform = new f32[9];
        
        btMatrix3x3ToNVGaffine(_dstx, dstx);
        btMatrix3x3ToNVGaffine(_dsty, dsty);
        btMatrix3x3ToNVGaffine(_xform, xform);
        
        WorldHUD::transformPoint(_dstx, _dsty, _xform, sourcePos.x(), sourcePos.y());
        
        NVGaffineTobtMatrix3x3(dstx, _dstx);
        NVGaffineTobtMatrix3x3(dsty, _dsty);
        NVGaffineTobtMatrix3x3(xform, _xform);
        
        delete [] _xform;_xform=NULL;
        delete [] _dsty;_dsty=NULL;
        delete [] _dstx;_dstx=NULL;
    }
    
    void WorldHUD::transformIdentity(f32 *floats)
    {
        nvgTransformIdentity(floats);
    }
    
    void WorldHUD::transformTranslate(f32 *floats, f32 tx, f32 ty)
    {
        nvgTransformTranslate(floats, tx, ty);
    }
    
    void WorldHUD::transformScale(f32 *floats, f32 sx, f32 sy)
    {
        nvgTransformScale(floats, sx, sy);
    }
    
    void WorldHUD::transformRotate(f32 *floats, f32 a)
    {
        nvgTransformRotate(floats, a);
    }
    
    void WorldHUD::transformSkewX(f32 *floats, f32 a)
    {
        nvgTransformSkewX(floats, a);
    }
    
    void WorldHUD::transformSkewY(f32 *floats, f32 a)
    {
        nvgTransformSkewY(floats, a);
    }
    
    void WorldHUD::transformMultiply(f32 *floats, f32 *src)
    {
        nvgTransformMultiply(floats, src);
    }
    
    void WorldHUD::transformPremultiply(f32 *floats, f32 *src)
    {
        nvgTransformPremultiply(floats, src);
    }
    
    void WorldHUD::transformPoint(f32 *dstx, f32 *dsty, f32 *xform, f32 srcx, f32 srcy)
    {
        nvgTransformPoint(dstx, dsty, xform, srcx, srcy);
    }
    
    f32 WorldHUD::degToRad(f32 deg)
    {
        return nvgDegToRad(deg);
    }
    
    f32 WorldHUD::radToDeg(f32 rad)
    {
        return nvgRadToDeg(rad);
    }

    void WorldHUD::save()
    {
        nvgSave(m_NVGContext);
    }

    void WorldHUD::restore()
    {
        nvgRestore(m_NVGContext);
    }

    void WorldHUD::reset()
    {
        nvgReset(m_NVGContext);
    }

    void WorldHUD::strokeColor(const btVector4 & color)
    {
        NVGcolor nvgcolor;
        btVector4ToNVGcolor(nvgcolor, color);
        nvgStrokeColor(m_NVGContext, nvgcolor);
    }

    void WorldHUD::strokePaint(JLIPaint paint)
    {
        NVGpaint _paint;
        JLIPaintToNVGPaint(_paint, paint);
        nvgStrokePaint(m_NVGContext, _paint);
    }

    void WorldHUD::fillColor(const btVector4 & color)
    {
        NVGcolor nvgcolor;
        btVector4ToNVGcolor(nvgcolor, color);
        nvgFillColor(m_NVGContext, nvgcolor);
    }

    void WorldHUD::fillPaint(JLIPaint paint)
    {
        NVGpaint _paint;
        JLIPaintToNVGPaint(_paint, paint);
        nvgFillPaint(m_NVGContext, _paint);
    }

    void WorldHUD::miterLimit(f32 limit)
    {
        nvgMiterLimit(m_NVGContext, limit);
    }

    void WorldHUD::strokeWidth(f32 size)
    {
        nvgStrokeWidth(m_NVGContext, size);
    }

    void WorldHUD::lineCap(njliHUDLineCap cap)
    {
        nvgLineCap(m_NVGContext, (s32)cap);
    }

    void WorldHUD::lineJoin(njliHUDLineCap join)
    {
        nvgLineJoin(m_NVGContext, join);
    }

    void WorldHUD::globalAlpha(f32 alpha)
    {
        nvgGlobalAlpha(m_NVGContext, alpha);
    }

    void WorldHUD::resetTransform()
    {
        nvgResetTransform(m_NVGContext);
    }

    //
    // Transforms
    //
    // The paths, gradients, patterns and scissor region are transformed by an transformation
    // matrix at the time when they are passed to the API.
    // The current transformation matrix is a affine matrix:
    //   [sx kx tx]
    //   [ky sy ty]
    //   [ 0  0  1]
    // Where: sx,sy define scaling, kx,ky skewing, and tx,ty translation.
    // The last row is assumed to be 0,0,1 and is not stored.
    //
    // Apart from nvgResetTransform(), each transformation function first creates
    // specific transformation matrix and pre-multiplies the current transformation by it.
    //
    // Current coordinate system (transformation) can be saved and restored using nvgSave() and nvgRestore().
    
    void WorldHUD::transform(const btMatrix3x3 &mtx)
    {
        mtx.getOpenGLSubMatrix(m_matrixBuffer);
        
        this->transform(m_matrixBuffer[0], m_matrixBuffer[3], m_matrixBuffer[1], m_matrixBuffer[4], m_matrixBuffer[2], m_matrixBuffer[5]);
    }

    void WorldHUD::translate(const btVector2 &pos)
    {
        nvgTranslate(m_NVGContext, pos.x(), pos.y());
        this->translate(pos.x(), pos.y());
    }

    void WorldHUD::rotate(f32 angle)
    {
        nvgRotate(m_NVGContext, angle);
    }

    void WorldHUD::skewX(f32 angle)
    {
        nvgSkewX(m_NVGContext, angle);
    }

    void WorldHUD::skewY(f32 angle)
    {
        nvgSkewY(m_NVGContext, angle);
    }

    void WorldHUD::scale(const btVector2 &scale)
    {
        this->scale(scale.x(), scale.y());
    }

    void WorldHUD::getTransform(btMatrix3x3 & xform)
    {
        nvgCurrentTransform(m_NVGContext, m_matrixBuffer);
    }

    s32 WorldHUD::createImage(const s8* filename, njliHUDImageFlags imageFlags)
    {
        s32 image = nvgCreateImage(m_NVGContext, ASSET_PATH(filename), imageFlags);
        m_images.push_back(image);
        return image;
    }

    s32 WorldHUD::createImageRGBA(const Image &image, njliHUDImageFlags imageFlags)
    {
        s32 img = nvgCreateImageRGBA(m_NVGContext, image.getWidth(), image.getHeight(), imageFlags, image.getDataRaw());
        m_images.push_back(img);
        return img;
    }

    void WorldHUD::updateImage(s32 imageHandle, const Image &image)
    {
        nvgUpdateImage(m_NVGContext, imageHandle, image.getDataRaw());
    }

    void WorldHUD::imageSize(s32 imageHandle, s32 &w, s32 &h)
    {
        nvgImageSize(m_NVGContext, imageHandle, &w, &h);
    }

    void WorldHUD::deleteImage(s32 imageHandle)
    {
        m_images.erase(std::remove(m_images.begin(), m_images.end(), imageHandle), m_images.end());
        nvgDeleteImage(m_NVGContext, imageHandle);
    }

    JLIPaint WorldHUD::linearGradient(const btVector2 &startPos, const btVector2 &endPos, const btVector4 &startColor, const btVector4 &endColor)
    {
        return this->linearGradient(startPos.x(), startPos.y(), endPos.x(), endPos.y(), startColor, endColor);
    }

    JLIPaint WorldHUD::boxGradient(const Rect &rect, f32 radius, f32 feather, const btVector4 &startColor, const btVector4 &endColor)
    {
        return this->boxGradient(rect.getOffset().x(), rect.getOffset().y(), rect.getDimension().x(), rect.getDimension().y(), radius, feather, startColor, endColor);
    }

    JLIPaint WorldHUD::radialGradient(const btVector2 &center, f32 innerRadius, f32 outerRadius, const btVector4 &startColor, const btVector4 &endColor)
    {
        return this->radialGradient(center.x(), center.y(), innerRadius, outerRadius, startColor, endColor);
    }

    JLIPaint WorldHUD::imagePattern(const btVector2 &startPos, const btVector2 &endPos, f32 angle, s32 imageHandle, f32 alpha)
    {
        return this->imagePattern(startPos.x(), startPos.y(), endPos.x(), endPos.y(), angle, imageHandle, alpha);
    }

    void WorldHUD::scissor(const Rect &rect)
    {
        this->scissor(rect.getOffset().x(), rect.getOffset().y(), rect.getDimension().x(), rect.getDimension().y());
    }

    void WorldHUD::intersectScissor(const Rect &rect)
    {
        this->intersectScissor(rect.getOffset().x(), rect.getOffset().y(), rect.getDimension().x(), rect.getDimension().y());
    }

    void WorldHUD::resetScissor()
    {
        nvgResetScissor(m_NVGContext);
    }

    void WorldHUD::beginPath()
    {
        nvgBeginPath(m_NVGContext);
    }

    void WorldHUD::moveTo(const btVector2 &position)
    {
        this->moveTo(position.x(), position.y());
    }

    void WorldHUD::lineTo(const btVector2 &position)
    {
        this->lineTo(position.x(), position.y());
    }

    void WorldHUD::bezierTo(const btVector2 &controlPoint1, const btVector2 &controlPoint2, const btVector2 &pos)
    {
        this->bezierTo(controlPoint1.x(), controlPoint1.y(), controlPoint2.x(), controlPoint2.y(), pos.x(), pos.y());
    }

    void WorldHUD::quadTo(const btVector2 &controlPoint, const btVector2 &pos)
    {
        this->quadTo(controlPoint.x(), controlPoint.y(), pos.x(), pos.y());
    }

    void WorldHUD::arcTo(const btVector2 &pos1, const btVector2 &pos2, f32 radius)
    {
        this->arcTo(pos1.x(), pos1.y(), pos2.x(), pos2.y(), radius);
    }

    void WorldHUD::closePath()
    {
        nvgClosePath(m_NVGContext);
    }

    void WorldHUD::pathWinding(njliHUDWinding dir)
    {
        nvgPathWinding(m_NVGContext, dir);
    }

    void WorldHUD::arc(const btVector2 &center, f32 radius, f32 fromAngle, f32 toAngle, njliHUDWinding dir)
    {
        this->arc(center.x(), center.y(), radius, fromAngle, toAngle, dir);
    }

    void WorldHUD::rect(const Rect &rect)
    {
        this->rect(rect.getOffset().x(), rect.getOffset().y(), rect.getDimension().x(), rect.getDimension().y());
    }

    void WorldHUD::roundedRect(const Rect &rect, f32 r)
    {
        this->roundedRect(rect.getOffset().x(), rect.getOffset().y(), rect.getDimension().x(), rect.getDimension().y(), r);
    }

    void WorldHUD::ellipse(const btVector2 &center, const btVector2 &radius)
    {
        this->ellipse(center.x(), center.y(), radius.x(), radius.y());
    }

    void WorldHUD::circle(const btVector2 &center, f32 r)
    {
        this->circle(center.x(), center.y(), r);
    }

    void WorldHUD::fill()
    {
        nvgFill(m_NVGContext);
    }

    void WorldHUD::stroke()
    {
        nvgStroke(m_NVGContext);
    }

    s32 WorldHUD::createFont(const s8* name, const s8* filename)
    {
        return nvgCreateFont(m_NVGContext, name, ASSET_PATH(filename));
    }

//    s32 WorldHUD::createFontMem(const s8* name, u8* data, s32 ndata, s32 freeData)
//    {
////        nvgCreateFontMem(m_NVGContext, <#const s8 *name#>, <#u8 *data#>, <#s32 ndata#>, <#s32 freeData#>)
//    }

    s32 WorldHUD::findFont(const s8* name)
    {
        return nvgFindFont(m_NVGContext, name);
    }

    void WorldHUD::fontSize(f32 size)
    {
        nvgFontSize(m_NVGContext, size);
    }

    void WorldHUD::fontBlur(f32 blur)
    {
        nvgFontBlur(m_NVGContext, blur);
    }

    void WorldHUD::textLetterSpacing(f32 spacing)
    {
        nvgTextLetterSpacing(m_NVGContext, spacing);
    }

    void WorldHUD::textLineHeight(f32 lineHeight)
    {
        nvgTextLineHeight(m_NVGContext, lineHeight);
    }
    
    void WorldHUD::textAlign(njliHUDAlign align)
    {
        nvgTextAlign(m_NVGContext, align);
    }

//    void WorldHUD::textAlign(njliHUDAlign align)
//    {
//        this->textAlign(align, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE);
//    }
//
//    void WorldHUD::textAlign(njliHUDAlign align1, njliHUDAlign align2)
//    {
//        this->textAlign(align1, align2, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE);
//    }
//    
//    void WorldHUD::textAlign(njliHUDAlign align1, njliHUDAlign align2, njliHUDAlign align3)
//    {
//        this->textAlign(align1, align2, align3, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE);
//    }
//    void WorldHUD::textAlign(njliHUDAlign align1, njliHUDAlign align2, njliHUDAlign align3, njliHUDAlign align4)
//    {
//        this->textAlign(align1, align2, align3, align4, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE);
//    }
//    void WorldHUD::textAlign(njliHUDAlign align1, njliHUDAlign align2, njliHUDAlign align3, njliHUDAlign align4, njliHUDAlign align5)
//    {
//        this->textAlign(align1, align2, align3, align4, align5, JLI_HUD_ALIGN_NONE, JLI_HUD_ALIGN_NONE);
//    }
//    
//    void WorldHUD::textAlign(njliHUDAlign align1, njliHUDAlign align2, njliHUDAlign align3, njliHUDAlign align4, njliHUDAlign align5, njliHUDAlign align6)
//    {
//        this->textAlign(align1, align2, align3, align4, align5, align6, JLI_HUD_ALIGN_NONE);
//    }
//    
//    void WorldHUD::textAlign(njliHUDAlign align1, njliHUDAlign align2, njliHUDAlign align3, njliHUDAlign align4, njliHUDAlign align5, njliHUDAlign align6, njliHUDAlign align7)
//    {
//        nvgTextAlign(m_NVGContext, align1 | align2 | align3 | align4 | align5 | align6 | align7);
//    }
    
    void WorldHUD::fontFaceId(s32 fontHandle)
    {
        nvgFontFaceId(m_NVGContext, fontHandle);
    }

    void WorldHUD::fontFace(const s8* font)
    {
        nvgFontFace(m_NVGContext, font);
    }

    f32 WorldHUD::text(const btVector2 &position, const s8* string, const s8* end)
    {
        return this->text(position.x(), position.y(), string, end);
    }

    void WorldHUD::textBox(const btVector2 &position, f32 breakRowWidth, const s8* string, const s8* end)
    {
        this->textBox(position.x(), position.y(), breakRowWidth, string, end);
    }

    f32 WorldHUD::textBounds(const btVector2 &position, Rect &bounds, const s8* string, const s8* end)
    {
        return this->textBounds(position.x(), position.y(), bounds, string, end);
    }
    void WorldHUD::textBoxBounds(const btVector2 &position, f32 breakRowWidth, Rect &bounds, const s8* string, const s8* end)
    {
        this->textBoxBounds(position.x(), position.y(), breakRowWidth, bounds, string, end);
    }

    void WorldHUD::textGlyphPositions(const btVector2 &position, const s8* string, const s8* end, btAlignedObjectArray<JLIGlyphPosition> &glyphPositions)
    {
        this->textGlyphPositions(position.x(), position.y(), string, end, glyphPositions);
    }

    void WorldHUD::textMetrics(btMatrix3x3 &ascender, btMatrix3x3 &descender, btMatrix3x3 &lineh)
    {
        f32 *_ascender = new f32[9];
        f32 *_descender = new f32[9];
        f32 *_lineh = new f32[9];
        
        btMatrix3x3ToNVGaffine(_ascender, ascender);
        btMatrix3x3ToNVGaffine(_descender, descender);
        btMatrix3x3ToNVGaffine(_lineh, lineh);
        
        nvgTextMetrics(m_NVGContext, _ascender, _descender, _lineh);
        
        delete [] _lineh;_lineh=NULL;
        delete [] _descender;_descender=NULL;
        delete [] _ascender;_ascender=NULL;
    }
    
    btAlignedObjectArray<JLITextRow> WorldHUD::textBreakLines(const s8* string, const s8* end, f32 breakRowWidth)
    {
        btAlignedObjectArray<JLITextRow> textRows;
        NVGtextRow *positions = new NVGtextRow[100];
        
        s32 numRows = nvgTextBreakLines(m_NVGContext, string, end, breakRowWidth, positions, 100);
        
        for(s32 i = 0; i < numRows; ++i)
        {
            JLITextRow row;
            NVGtextRowToJLITextRow(row, positions[i]);
            textRows.push_back(row);
        }
        
        delete [] positions;positions=NULL;
        return textRows;
    }
    
    // Premultiplies current coordinate system by specified matrix.
    // The parameters are interpreted as matrix as follows:
    //   [a c e]
    //   [b d f]
    //   [0 0 1]
    
    // The paths, gradients, patterns and scissor region are transformed by an transformation
    // matrix at the time when they are passed to the API.
    // The current transformation matrix is a affine matrix:
    //   [sx kx tx]
    //   [ky sy ty]
    //   [ 0  0  1]
    
    void WorldHUD::transform(f32 scaleX, f32 skewY, f32 skewX, f32 scaleY, f32 x, f32 y)
    {
        nvgTransform(m_NVGContext, scaleX, skewY, skewX, scaleY, x, y);
    }
    
    void WorldHUD::translate(f32 x, f32 y)
    {
        nvgTranslate(m_NVGContext, x, y);
    }
    
    void WorldHUD::scale(f32 scalex, f32 scaley)
    {
        nvgScale(m_NVGContext, scalex, scaley);
    }
    
    JLIPaint WorldHUD::linearGradient(f32 startx, f32 starty, f32 endx, f32 endy, const btVector4 &startColor, const btVector4 &endColor)
    {
        NVGcolor icol, ocol;
        WorldHUD::btVector4ToNVGcolor(icol, startColor);
        WorldHUD::btVector4ToNVGcolor(ocol, endColor);
        
        JLIPaint ret;
        NVGPaintToJLIPaint(ret, nvgLinearGradient(m_NVGContext, startx, starty, endx, endy, icol, ocol));
        return ret;
    }
    
    JLIPaint WorldHUD::boxGradient(f32 x, f32 y, f32 width, f32 height, f32 radius, f32 feather, const btVector4 &startColor, const btVector4 &endColor)
    {
        NVGcolor icol, ocol;
        WorldHUD::btVector4ToNVGcolor(icol, startColor);
        WorldHUD::btVector4ToNVGcolor(ocol, endColor);
        
        JLIPaint ret;
        NVGPaintToJLIPaint(ret, nvgBoxGradient(m_NVGContext, x, y, width, height, radius, feather, icol, ocol));
        return ret;
    }
    
    JLIPaint WorldHUD::radialGradient(f32 centerx, f32 centery, f32 innerRadius, f32 outerRadius, const btVector4 &startColor, const btVector4 &endColor)
    {
        NVGcolor icol, ocol;
        WorldHUD::btVector4ToNVGcolor(icol, startColor);
        WorldHUD::btVector4ToNVGcolor(ocol, endColor);
        
        JLIPaint ret;
        NVGPaintToJLIPaint(ret, nvgRadialGradient(m_NVGContext, centerx, centery, innerRadius, outerRadius, icol, ocol));
        return ret;
    }
    
    JLIPaint WorldHUD::imagePattern(f32 startx, f32 starty, f32 endx, f32 endy, f32 angle, s32 imageHandle, f32 alpha)
    {
        JLIPaint ret;
        NVGPaintToJLIPaint(ret, nvgImagePattern(m_NVGContext, startx, starty, endx, endy, angle, imageHandle, alpha));
        return ret;
    }
    
    void WorldHUD::scissor(f32 x, f32 y, f32 width, f32 height)
    {
        nvgScissor(m_NVGContext, x, y, width, height);
    }
    
    void WorldHUD::intersectScissor(f32 x, f32 y, f32 width, f32 height)
    {
        nvgIntersectScissor(m_NVGContext, x, y, width, height);
    }
    
    void WorldHUD::moveTo(f32 x, f32 y)
    {
        nvgMoveTo(m_NVGContext, x, y);
    }
    
    void WorldHUD::lineTo(f32 x, f32 y)
    {
        nvgLineTo(m_NVGContext, x, y);
    }
    
    void WorldHUD::bezierTo(f32 controlPoint1x, f32 controlPoint1y, f32 controlPoint2x, f32 controlPoint2y, f32 x, f32 y)
    {
        nvgBezierTo(m_NVGContext, controlPoint1x, controlPoint1y, controlPoint2x, controlPoint2y, x, y);
    }
    
    void WorldHUD::quadTo(f32 controlPointx, f32 controlPointy, f32 x, f32 y)
    {
        nvgQuadTo(m_NVGContext, controlPointx, controlPointy, x, y);
    }
    
    void WorldHUD::arcTo(f32 pos1x, f32 pos1y, f32 pos2x, f32 pos2y, f32 radius)
    {
        nvgArcTo(m_NVGContext, pos1x, pos1x, pos2x, pos2y, radius);
    }
    
    void WorldHUD::arc(f32 centerx, f32 centery, f32 radius, f32 fromAngle, f32 toAngle, njliHUDWinding dir)
    {
        nvgArc(m_NVGContext, centerx, centery, radius, fromAngle, toAngle, dir);
    }
    
    void WorldHUD::rect(f32 x, f32 y, f32 width, f32 height)
    {
        nvgRect(m_NVGContext, x, y, width, height);
    }
    
    void WorldHUD::roundedRect(f32 x, f32 y, f32 width, f32 height, f32 radius)
    {
        nvgRoundedRect(m_NVGContext, x, y, width, height, radius);
    }
    
    void WorldHUD::ellipse(f32 centerx, f32 centery, f32 radiusx, f32 radiusy)
    {
        nvgEllipse(m_NVGContext, centerx, centery, radiusx, radiusy);
    }
    
    void WorldHUD::circle(f32 centerx, f32 centery, f32 radius)
    {
        nvgCircle(m_NVGContext, centerx, centery, radius);
    }
    
    f32 WorldHUD::text(f32 x, f32 y, const s8* string, const s8* end)
    {
        if(!string)
            string = "<NULL>";
        return nvgText(m_NVGContext, x, y, string, end);
    }
    
    void WorldHUD::textBox(f32 x, f32 y, f32 breakRowWidth, const s8* string, const s8* end)
    {
        if(!string)
            string = "<NULL>";
        nvgTextBox(m_NVGContext, x, y, breakRowWidth, string, end);
    }
    
    
    
    
    f32 WorldHUD::textBounds(f32 x, f32 y, Rect &bounds, const s8* string, const s8* end)
    {
        f32 *_bounds = new f32[4];
        
        f32 ret = nvgTextBounds(m_NVGContext, x, y, string, end, _bounds);
        bounds.setOffset(btVector2(_bounds[0], _bounds[1]));
        bounds.setDimension(btVector2(_bounds[2], _bounds[3]));
        
        delete [] _bounds;_bounds=NULL;
        return ret;
    }
    
    void WorldHUD::textBoxBounds(f32 x, f32 y, f32 breakRowWidth, Rect &bounds, const s8* string, const s8* end)
    {
        f32 *_bounds = new f32[4];
        
        nvgTextBoxBounds(m_NVGContext, x, y, breakRowWidth, string, end, _bounds);
        bounds.setOffset(btVector2(_bounds[0], _bounds[1]));
        bounds.setDimension(btVector2(_bounds[2], _bounds[3]));
        
        delete [] _bounds;_bounds=NULL;
    }
    
    
//    f32 WorldHUD::textBounds(f32 x, f32 y, const s8* string, const s8* end, const btMatrix3x3 &bounds)
//    {
//        if(!string)
//            string = "<NULL>";
//        btMatrix3x3ToNVGaffine(m_matrixBuffer, bounds);
//        return nvgTextBounds(m_NVGContext, x, y, string, end, m_matrixBuffer);
//    }
//    
//    void WorldHUD::textBoxBounds(f32 x, f32 y, f32 breakRowWidth, const s8* string, const s8* end, const btMatrix3x3 & bounds)
//    {
//        if(!string)
//            string = "<NULL>";
//        btMatrix3x3ToNVGaffine(m_matrixBuffer, bounds);
//        nvgTextBoxBounds(m_NVGContext, x, y, breakRowWidth, string, end, m_matrixBuffer);
//    }
    
    void WorldHUD::textGlyphPositions(f32 x, f32 y, const s8* string, const s8* end, btAlignedObjectArray<JLIGlyphPosition> &glyphPositions)
    {
        NVGglyphPosition *positions = new NVGglyphPosition[100];
        
        s32 numGlyphs = nvgTextGlyphPositions(m_NVGContext, x, y, string, end, positions, 100);
        
        for(s32 i = 0; i < numGlyphs; ++i)
        {
            JLIGlyphPosition pos;
            NVGglyphPositionToJLIGlyphPosition(pos, positions[i]);
            glyphPositions.push_back(pos);
        }
        
        delete [] positions;positions=NULL;
    }
    
    Camera *WorldHUD::getCamera()
    {
        if(!m_Camera)
        {
            m_Camera = Camera::create();
            m_Camera->enableOrthographic();
        }
        return m_Camera;
    }
    
//    NVGLUframebuffer *WorldHUD::createFBO(int w, int h, int imageFlags)
//    {
//        NVGLUframebuffer *fb;
//        
//        fb = nvgluCreateFramebuffer(m_NVGContext, w, h, imageFlags);
//        
//        m_NVGLUfb.push_back(fb);
//        
//        return fb;
//    }
//    bool WorldHUD::destroyFBO(NVGLUframebuffer *fb)
//    {
//        std::vector<NVGLUframebuffer*>::iterator iter = std::find(m_NVGLUfb.begin(), m_NVGLUfb.end(), fb);
//        if(iter != m_NVGLUfb.end())
//        {
//            m_NVGLUfb.erase(iter);
//            return true;
//        }
//        return false;
//    }
    
    void WorldHUD::btVector4ToNVGcolor(NVGcolor &color, const btVector4 &vColor)
    {
        color.r = vColor.x();
        color.g = vColor.y();
        color.b = vColor.z();
        color.a = vColor.w();
    }
    
    void WorldHUD::NVGcolorTobtVector4(btVector4 &color, const NVGcolor &vColor)
    {
        color.setX(vColor.r);
        color.setY(vColor.g);
        color.setZ(vColor.b);
        color.setW(vColor.a);
    }
    
    /*
     struct NVGpaint {
     f32 xform[6];
     f32 extent[2];
     f32 radius;
     f32 feather;
     NVGcolor innerColor;
     NVGcolor outerColor;
     s32 image;
     };
     */
    
    void WorldHUD::JLIPaintToNVGPaint(NVGpaint &nvgPaint, const JLIPaint &njliPaint)
    {
        for (s32 i = 0; i < 6; ++i)
            nvgPaint.xform[i] = njliPaint.xform[i];
        
        nvgPaint.extent[0] = njliPaint.extent[0];
        nvgPaint.extent[1] = njliPaint.extent[1];
        
        nvgPaint.radius = njliPaint.radius;
        nvgPaint.feather = njliPaint.feather;
        
        btVector4ToNVGcolor(nvgPaint.innerColor, njliPaint.innerColor);
        btVector4ToNVGcolor(nvgPaint.outerColor, njliPaint.outerColor);
        
        nvgPaint.image = njliPaint.image;
    }
    
    void WorldHUD::NVGPaintToJLIPaint(JLIPaint &njliPaint, const NVGpaint &nvgPaint)
    {
        for (s32 i = 0; i < 6; ++i)
            njliPaint.xform[i] = nvgPaint.xform[i];
        
        njliPaint.extent[0] = nvgPaint.extent[0];
        njliPaint.extent[1] = nvgPaint.extent[1];
        
        njliPaint.radius = nvgPaint.radius;
        njliPaint.feather = nvgPaint.feather;
        
        NVGcolorTobtVector4(njliPaint.innerColor, nvgPaint.innerColor);
        NVGcolorTobtVector4(njliPaint.outerColor, nvgPaint.outerColor);
        
        njliPaint.image = nvgPaint.image;
    }
    
    
    
    
    
    
    
    
    void WorldHUD::JLIGlyphPositionToNVGglyphPosition(NVGglyphPosition &nvgGlyphPos, const JLIGlyphPosition &njliGlyphPos)
    {
//        nvgGlyphPos.str = njliGlyphPos.str;
//        nvgGlyphPos.x = njliGlyphPos.x;
//        nvgGlyphPos.minx = njliGlyphPos.minx;
//        nvgGlyphPos.maxx = njliGlyphPos.maxx;
    }
    
    void WorldHUD::NVGglyphPositionToJLIGlyphPosition(JLIGlyphPosition &njliGlyphPos, const NVGglyphPosition &nvgGlyphPos)
    {
//        njliGlyphPos.str = nvgGlyphPos.str;
//        njliGlyphPos.x = nvgGlyphPos.x;
//        njliGlyphPos.minx = nvgGlyphPos.minx;
//        njliGlyphPos.maxx = nvgGlyphPos.maxx;
    }
    
    void WorldHUD::JLITextRowToNVGtextRow(NVGtextRow &nvgTextRow, const JLITextRow &njliTextRow)
    {
//        nvgTextRow.start = njliTextRow.row_start;
//        nvgTextRow.end = njliTextRow.row_end;
//        nvgTextRow.next = njliTextRow.next;
//        nvgTextRow.width = njliTextRow.width;
//        nvgTextRow.minx = njliTextRow.minx;
//        nvgTextRow.maxx = njliTextRow.maxx;
    }
    
    void WorldHUD::NVGtextRowToJLITextRow(JLITextRow &njliTextRow, const NVGtextRow &nvgTextRow)
    {
//        njliTextRow.row_start = nvgTextRow.start;
//        njliTextRow.row_end = nvgTextRow.end;
//        njliTextRow.next = nvgTextRow.next;
//        njliTextRow.width = nvgTextRow.width;
//        njliTextRow.minx = nvgTextRow.minx;
//        njliTextRow.maxx = nvgTextRow.maxx;
    }
    
    
    // Premultiplies current coordinate system by specified matrix.
    // The parameters are interpreted as matrix as follows:
    //   [a c e]
    //   [b d f]
    //   [0 0 1]
    
    // The paths, gradients, patterns and scissor region are transformed by an transformation
    // matrix at the time when they are passed to the API.
    // The current transformation matrix is a affine matrix:
    //   [sx kx tx]
    //   [ky sy ty]
    //   [ 0  0  1]
    
    /*
     void setValue(const btScalar& xx, const btScalar& xy, const btScalar& xz,
     const btScalar& yx, const btScalar& yy, const btScalar& yz,
     const btScalar& zx, const btScalar& zy, const btScalar& zz)
     {
     m_el[0].setValue(xx,xy,xz);
     m_el[1].setValue(yx,yy,yz);
     m_el[2].setValue(zx,zy,zz);
     }
     */
    
    void WorldHUD::NVGaffineTobtMatrix3x3(btMatrix3x3 &mtx, f32 *floats)
    {
        mtx = btMatrix3x3(floats[0], floats[1], floats[2], floats[3], floats[4], floats[5], floats[6], floats[7], floats[8]);
    }
    void WorldHUD::btMatrix3x3ToNVGaffine(f32 *floats, const btMatrix3x3 &mtx)
    {
        mtx.getOpenGLSubMatrix(floats);
    }
    
    void WorldHUD::renderFBOs()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        for (std::vector<AbstractFrameBufferObject*>::iterator i = m_FBOvector.begin(); i != m_FBOvector.end(); ++i)
        {
            if (!(*i)->isHidden())
            {
                (*i)->render(NULL);
            }
        }
        glDisable(GL_BLEND);
    }
    void WorldHUD::render()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_DEPTH_TEST);
        
        nvgBeginFrame(m_NVGContext,
                      njli::World::getInstance()->getViewportDimensions().x(),
                      njli::World::getInstance()->getViewportDimensions().y(),
                      njli::World::getInstance()->getAspectRatio());
        
        s8 buffer[BUFFER_SIZE];
        sprintf(buffer, "%s", "WorldRenderHUD");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->renderHUD();
        
        nvgEndFrame(m_NVGContext);
        
        glDisable(GL_BLEND);
    }
    
    NVGcontext *WorldHUD::getContext()
    {
        return m_NVGContext;
    }
    
    void WorldHUD::addFBO(AbstractFrameBufferObject *fbo)
    {
        std::vector<AbstractFrameBufferObject*>::iterator iter = std::find(m_FBOvector.begin(), m_FBOvector.end(), fbo);
        DEBUG_ASSERT(iter == m_FBOvector.end());
        
        m_FBOvector.push_back(fbo);
    }
    
    void WorldHUD::removeFBO(AbstractFrameBufferObject *fbo)
    {
        std::vector<AbstractFrameBufferObject*>::iterator iter = std::find(m_FBOvector.begin(), m_FBOvector.end(), fbo);
        DEBUG_ASSERT(iter != m_FBOvector.end());
        
        m_FBOvector.erase(iter);
    }
}
