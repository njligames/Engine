//
//  WorldHUD.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/28/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldHUD__
#define __JLIGameEngineTest__WorldHUD__

#include "AbstractObject.h"
#include "File.h"
#include "Util.h"
#include "nanovg.h"
//#include "nanovg_gl_utils.h"
#include "AbstractFrameBufferObject.h"
#include "JLIFactoryTypes.h"
#include "btAlignedObjectArray.h"

class btVector2;
class btVector4;
class btMatrix3x3;

#include <vector>

namespace njli {
class Image;
class Rect;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(struct)
JLIPaint
{
    f32 xform[6];
    f32 extent[2];
    f32 radius;
    f32 feather;
    btVector4 innerColor;
    btVector4 outerColor;
    s32 image;
};

/**
 *  <#Description#>
 */
ATTRIBUTE_ALIGNED16(struct)
JLIGlyphPosition
{
private:
//    const s8* str; // Position of the glyph in the input string.
    f32 x; // The x-coordinate of the logical glyph position.
    f32 minx, maxx; // The bounds of the glyph shape.
public:
    friend bool operator<(const JLIGlyphPosition& lhs, const JLIGlyphPosition& rhs) { return ((lhs.x < rhs.x) && (lhs.minx < rhs.minx) && (lhs.maxx < rhs.maxx)); }
    friend bool operator>(const JLIGlyphPosition& lhs, const JLIGlyphPosition& rhs) { return ((lhs.x > rhs.x) && (lhs.minx > rhs.minx) && (lhs.maxx > rhs.maxx)); }
    friend bool operator<=(const JLIGlyphPosition& lhs, const JLIGlyphPosition& rhs) { return ((lhs.x <= rhs.x) && (lhs.minx <= rhs.minx) && (lhs.maxx <= rhs.maxx)); }
    friend bool operator>=(const JLIGlyphPosition& lhs, const JLIGlyphPosition& rhs) { return ((lhs.x >= rhs.x) && (lhs.minx >= rhs.minx) && (lhs.maxx >= rhs.maxx)); }
    friend bool operator==(const JLIGlyphPosition& lhs, const JLIGlyphPosition& rhs) { return ((lhs.x == rhs.x) && (lhs.minx == rhs.minx) && (lhs.maxx == rhs.maxx)); }
    friend bool operator!=(const JLIGlyphPosition& lhs, const JLIGlyphPosition& rhs) { return ((lhs.x != rhs.x) && (lhs.minx != rhs.minx) && (lhs.maxx != rhs.maxx)); }
};

/**
 *  <#Description#>
 */
ATTRIBUTE_ALIGNED16(struct)
JLITextRow
{
private:
//    const s8* row_start; // Pointer to the input text where the row starts.
//    const s8* row_end; // Pointer to the input text where the row ends (one past the last character).
//    const s8* next; // Pointer to the beginning of the next row.
    f32 width; // Logical width of the row.
    f32 minx, maxx; // Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
public:
    friend bool operator<(const JLITextRow& lhs, const JLITextRow& rhs) { return ((lhs.width < rhs.width) && (lhs.minx < rhs.minx) && (lhs.maxx < rhs.maxx)); }
    friend bool operator>(const JLITextRow& lhs, const JLITextRow& rhs) { return ((lhs.width > rhs.width) && (lhs.minx > rhs.minx) && (lhs.maxx > rhs.maxx)); }
    friend bool operator<=(const JLITextRow& lhs, const JLITextRow& rhs) { return ((lhs.width <= rhs.width) && (lhs.minx <= rhs.minx) && (lhs.maxx <= rhs.maxx)); }
    friend bool operator>=(const JLITextRow& lhs, const JLITextRow& rhs) { return ((lhs.width >= rhs.width) && (lhs.minx >= rhs.minx) && (lhs.maxx >= rhs.maxx)); }
    friend bool operator==(const JLITextRow& lhs, const JLITextRow& rhs) { return ((lhs.width == rhs.width) && (lhs.minx == rhs.minx) && (lhs.maxx == rhs.maxx)); }
    friend bool operator!=(const JLITextRow& lhs, const JLITextRow& rhs) { return ((lhs.width != rhs.width) && (lhs.minx != rhs.minx) && (lhs.maxx != rhs.maxx)); }
};

/// <#Description#>
class WorldHUD : public AbstractObject {
    friend class World;
    friend class ButtonHUD;
    friend class CheckboxHUD;
    friend class DropdownHUD;
    friend class LabelHUD;
    friend class SliderHUD;
    friend class TextboxHUD;
    friend class AbstractFrameBufferObject;

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    /**
         *  <#Description#>
         */
    WorldHUD();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~WorldHUD();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const s8* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const;

public:
    //TODO: fill in specific methods for WorldHUD
    /**
         *  <#Description#>
         *
         *  @param cp <#cp description#>
         *
         *  @return <#return value description#>
         */
    static s8* cpToUTF8(s32 cp);
    /**
         *  <#Description#>
         *
         *  @param r <#r description#>
         *  @param g <#g description#>
         *  @param b <#b description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 rgb(u8 r, u8 g, u8 b);
    /**
         *  <#Description#>
         *
         *  @param r <#r description#>
         *  @param g <#g description#>
         *  @param b <#b description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 rgbf(f32 r, f32 g, f32 b);
    /**
         *  <#Description#>
         *
         *  @param r <#r description#>
         *  @param g <#g description#>
         *  @param b <#b description#>
         *  @param a <#a description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 rgba(u8 r, u8 g, u8 b, u8 a);
    /**
         *  <#Description#>
         *
         *  @param r <#r description#>
         *  @param g <#g description#>
         *  @param b <#b description#>
         *  @param a <#a description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 rgbaf(f32 r, f32 g, f32 b, f32 a);
    /**
         *  <#Description#>
         *
         *  @param c0 <#c0 description#>
         *  @param c1 <#c1 description#>
         *  @param u  <#u description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 lerpRGBA(const btVector4& c0, const btVector4& c1, f32 u);
    /**
         *  <#Description#>
         *
         *  @param c0 <#c0 description#>
         *  @param a  <#a description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 transRGBA(const btVector4& c0, u8 a);
    /**
         *  <#Description#>
         *
         *  @param c0 <#c0 description#>
         *  @param a  <#a description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 transRGBAf(const btVector4& c0, f32 a);
    /**
         *  <#Description#>
         *
         *  @param h <#h description#>
         *  @param s <#s description#>
         *  @param l <#l description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 hsl(f32 h, f32 s, f32 l);
    /**
         *  <#Description#>
         *
         *  @param h <#h description#>
         *  @param s <#s description#>
         *  @param l <#l description#>
         *  @param a <#a description#>
         *
         *  @return <#return value description#>
         */
    static btVector4 hsla(f32 h, f32 s, f32 l, u8 a);

    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         */
    static void transformIdentity(btMatrix3x3& floats);
    /**
         *  <#Description#>
         *
         *  @param floats       <#floats description#>
         *  @param translatePos <#translatePos description#>
         */
    static void transformTranslate(btMatrix3x3& floats, const btVector2& translatePos);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param scale  <#scale description#>
         */
    static void transformScale(btMatrix3x3& floats, const btVector2& scale);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param a      <#a description#>
         */
    static void transformRotate(btMatrix3x3& floats, f32 a);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param a      <#a description#>
         */
    static void transformSkewX(btMatrix3x3& floats, f32 a);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param a      <#a description#>
         */
    static void transformSkewY(btMatrix3x3& floats, f32 a);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param src    <#src description#>
         */
    static void transformMultiply(btMatrix3x3& floats, const btMatrix3x3& src);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param src    <#src description#>
         */
    static void transformPremultiply(btMatrix3x3& floats, const btMatrix3x3& src);
    /**
         *  <#Description#>
         *
         *  @param dstx      <#dstx description#>
         *  @param dsty      <#dsty description#>
         *  @param xform     <#xform description#>
         *  @param sourcePos <#sourcePos description#>
         */
    static void transformPoint(btMatrix3x3& dstx, btMatrix3x3& dsty, btMatrix3x3& xform, const btVector2& sourcePos);

    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         */
    static void transformIdentity(f32* floats);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param tx     <#tx description#>
         *  @param ty     <#ty description#>
         */
    static void transformTranslate(f32* floats, f32 tx, f32 ty);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param sx     <#sx description#>
         *  @param sy     <#sy description#>
         */
    static void transformScale(f32* floats, f32 sx, f32 sy);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param a      <#a description#>
         */
    static void transformRotate(f32* floats, f32 a);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param a      <#a description#>
         */
    static void transformSkewX(f32* floats, f32 a);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param a      <#a description#>
         */
    static void transformSkewY(f32* floats, f32 a);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param src    <#src description#>
         */
    static void transformMultiply(f32* floats, f32* src);
    /**
         *  <#Description#>
         *
         *  @param floats <#floats description#>
         *  @param src    <#src description#>
         */
    static void transformPremultiply(f32* floats, f32* src);
    /**
         *  <#Description#>
         *
         *  @param dstx  <#dstx description#>
         *  @param dsty  <#dsty description#>
         *  @param xform <#xform description#>
         *  @param srcx  <#srcx description#>
         *  @param srcy  <#srcy description#>
         */
    static void transformPoint(f32* dstx, f32* dsty, f32* xform, f32 srcx, f32 srcy);
    /**
         *  <#Description#>
         *
         *  @param deg <#deg description#>
         *
         *  @return <#return value description#>
         */
    static f32 degToRad(f32 deg);
    /**
         *  <#Description#>
         *
         *  @param rad <#rad description#>
         *
         *  @return <#return value description#>
         */
    static f32 radToDeg(f32 rad);

    /**
         *  <#Description#>
         */
    void save();
    /**
         *  <#Description#>
         */
    void restore();
    /**
         *  <#Description#>
         */
    void reset();
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void strokeColor(const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @param paint <#paint description#>
         */
    void strokePaint(JLIPaint paint);
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void fillColor(const btVector4& color);
    /**
         *  <#Description#>
         *
         *  @param paint <#paint description#>
         */
    void fillPaint(JLIPaint paint);
    /**
         *  <#Description#>
         *
         *  @param limit <#limit description#>
         */
    void miterLimit(f32 limit);
    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         */
    void strokeWidth(f32 size);
    /**
         *  <#Description#>
         *
         *  @param cap <#cap description#>
         */
    void lineCap(njliHUDLineCap cap);
    /**
         *  <#Description#>
         *
         *  @param join <#join description#>
         */
    void lineJoin(njliHUDLineCap join);
    /**
         *  <#Description#>
         *
         *  @param alpha <#alpha description#>
         */
    void globalAlpha(f32 alpha);
    /**
         *  <#Description#>
         */
    void resetTransform();
    /**
         *  <#Description#>
         *
         *  @param mtx <#mtx description#>
         */
    void transform(const btMatrix3x3& mtx);
    /**
         *  <#Description#>
         *
         *  @param pos <#pos description#>
         */
    void translate(const btVector2& pos);
    /**
         *  <#Description#>
         *
         *  @param angle <#angle description#>
         */
    void rotate(f32 angle);
    /**
         *  <#Description#>
         *
         *  @param angle <#angle description#>
         */
    void skewX(f32 angle);
    /**
         *  <#Description#>
         *
         *  @param angle <#angle description#>
         */
    void skewY(f32 angle);
    /**
         *  <#Description#>
         *
         *  @param scale <#scale description#>
         */
    void scale(const btVector2& scale);
    /**
         *  <#Description#>
         *
         *  @param xform <#xform description#>
         */
    void getTransform(btMatrix3x3& xform);
    /**
         *  <#Description#>
         *
         *  @param filename   <#filename description#>
         *  @param imageFlags <#imageFlags description#>
         *
         *  @return <#return value description#>
         */
    s32 createImage(const s8* filename, njliHUDImageFlags imageFlags);
    /**
         *  <#Description#>
         *
         *  @param image      <#image description#>
         *  @param imageFlags <#imageFlags description#>
         *
         *  @return <#return value description#>
         */
    s32 createImageRGBA(const Image& image, njliHUDImageFlags imageFlags);
    /**
         *  <#Description#>
         *
         *  @param imageHandle <#imageHandle description#>
         *  @param image       <#image description#>
         */
    void updateImage(s32 imageHandle, const Image& image);
    /**
         *  <#Description#>
         *
         *  @param imageHandle <#imageHandle description#>
         *  @param w           <#w description#>
         *  @param h           <#h description#>
         */
    void imageSize(s32 imageHandle, s32& w, s32& h);
    /**
         *  <#Description#>
         *
         *  @param imageHandle <#imageHandle description#>
         */
    void deleteImage(s32 imageHandle);
    /**
         *  <#Description#>
         *
         *  @param startPos   <#startPos description#>
         *  @param endPos     <#endPos description#>
         *  @param startColor <#startColor description#>
         *  @param endColor   <#endColor description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint linearGradient(const btVector2& startPos, const btVector2& endPos, const btVector4& startColor, const btVector4& endColor);
    /**
         *  <#Description#>
         *
         *  @param rect       <#rect description#>
         *  @param radius     <#radius description#>
         *  @param feather    <#feather description#>
         *  @param startColor <#startColor description#>
         *  @param endColor   <#endColor description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint boxGradient(const Rect& rect, f32 radius, f32 feather, const btVector4& startColor, const btVector4& endColor);
    /**
         *  <#Description#>
         *
         *  @param center      <#center description#>
         *  @param innerRadius <#innerRadius description#>
         *  @param outerRadius <#outerRadius description#>
         *  @param startColor  <#startColor description#>
         *  @param endColor    <#endColor description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint radialGradient(const btVector2& center, f32 innerRadius, f32 outerRadius, const btVector4& startColor, const btVector4& endColor);
    /**
         *  <#Description#>
         *
         *  @param startPos    <#startPos description#>
         *  @param endPos      <#endPos description#>
         *  @param angle       <#angle description#>
         *  @param imageHandle <#imageHandle description#>
         *  @param alpha       <#alpha description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint imagePattern(const btVector2& startPos, const btVector2& endPos, f32 angle, s32 imageHandle, f32 alpha);
    /**
         *  <#Description#>
         *
         *  @param rect <#rect description#>
         */
    void scissor(const Rect& rect);
    /**
         *  <#Description#>
         *
         *  @param rect <#rect description#>
         */
    void intersectScissor(const Rect& rect);
    /**
         *  <#Description#>
         */
    void resetScissor();
    /**
         *  <#Description#>
         */
    void beginPath();
    /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         */
    void moveTo(const btVector2& position);
    /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         */
    void lineTo(const btVector2& position);
    /**
         *  <#Description#>
         *
         *  @param controlPoint1 <#controlPoint1 description#>
         *  @param controlPoint2 <#controlPoint2 description#>
         *  @param pos           <#pos description#>
         */
    void bezierTo(const btVector2& controlPoint1, const btVector2& controlPoint2, const btVector2& pos);
    /**
         *  <#Description#>
         *
         *  @param controlPoint <#controlPoint description#>
         *  @param pos          <#pos description#>
         */
    void quadTo(const btVector2& controlPoint, const btVector2& pos);
    /**
         *  <#Description#>
         *
         *  @param pos1   <#pos1 description#>
         *  @param pos2   <#pos2 description#>
         *  @param radius <#radius description#>
         */
    void arcTo(const btVector2& pos1, const btVector2& pos2, f32 radius);
    /**
         *  <#Description#>
         */
    void closePath();
    /**
         *  <#Description#>
         *
         *  @param dir <#dir description#>
         */
    void pathWinding(njliHUDWinding dir);
    /**
         *  <#Description#>
         *
         *  @param center    <#center description#>
         *  @param radius    <#radius description#>
         *  @param fromAngle <#fromAngle description#>
         *  @param toAngle   <#toAngle description#>
         *  @param dir       <#dir description#>
         */
    void arc(const btVector2& center, f32 radius, f32 fromAngle, f32 toAngle, njliHUDWinding dir);
    /**
         *  <#Description#>
         *
         *  @param rect <#rect description#>
         */
    void rect(const Rect& rect);
    /**
         *  <#Description#>
         *
         *  @param rect   <#rect description#>
         *  @param radius <#radius description#>
         */
    void roundedRect(const Rect& rect, f32 radius);
    /**
         *  <#Description#>
         *
         *  @param center <#center description#>
         *  @param radius <#radius description#>
         */
    void ellipse(const btVector2& center, const btVector2& radius);
    /**
         *  <#Description#>
         *
         *  @param center <#center description#>
         *  @param radius <#radius description#>
         */
    void circle(const btVector2& center, f32 radius);
    /**
         *  <#Description#>
         */
    void fill();
    /**
         *  <#Description#>
         */
    void stroke();
    /**
         *  <#Description#>
         *
         *  @param name     <#name description#>
         *  @param filename <#filename description#>
         *
         *  @return <#return value description#>
         */
    s32 createFont(const s8* name, const s8* filename);
    /**
         *  <#Description#>
         *
         *  @param name <#name description#>
         *
         *  @return <#return value description#>
         */
    s32 findFont(const s8* name);
    /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         */
    void fontSize(f32 size);
    /**
         *  <#Description#>
         *
         *  @param blur <#blur description#>
         */
    void fontBlur(f32 blur);
    /**
         *  <#Description#>
         *
         *  @param spacing <#spacing description#>
         */
    void textLetterSpacing(f32 spacing);
    /**
         *  <#Description#>
         *
         *  @param lineHeight <#lineHeight description#>
         */
    void textLineHeight(f32 lineHeight);

    /**
         *  <#Description#>
         *
         *  @param align <#align description#>
         */
    void textAlign(njliHUDAlign align);

    /**
         *  <#Description#>
         *
         *  @param fontHandle <#fontHandle description#>
         */
    void fontFaceId(s32 fontHandle);
    /**
         *  <#Description#>
         *
         *  @param font <#font description#>
         */
    void fontFace(const s8* font);
    /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         *  @param string   <#string description#>
         *  @param end      <#end description#>
         *
         *  @return <#return value description#>
         */
    f32 text(const btVector2& position, const s8* string, const s8* end = NULL);
    /**
         *  <#Description#>
         *
         *  @param position      <#position description#>
         *  @param breakRowWidth <#breakRowWidth description#>
         *  @param string        <#string description#>
         *  @param end           <#end description#>
         */
    void textBox(const btVector2& position, f32 breakRowWidth, const s8* string, const s8* end = NULL);
    /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         *  @param bounds   <#bounds description#>
         *  @param string   <#string description#>
         *  @param end      <#end description#>
         *
         *  @return <#return value description#>
         */
    f32 textBounds(const btVector2& position, Rect& bounds, const s8* string, const s8* end = NULL);
    /**
         *  <#Description#>
         *
         *  @param position      <#position description#>
         *  @param breakRowWidth <#breakRowWidth description#>
         *  @param bounds        <#bounds description#>
         *  @param string        <#string description#>
         *  @param end           <#end description#>
         */
    void textBoxBounds(const btVector2& position, f32 breakRowWidth, Rect& bounds, const s8* string, const s8* end);
    /**
         *  <#Description#>
         *
         *  @param position       <#position description#>
         *  @param string         <#string description#>
         *  @param end            <#end description#>
         *  @param glyphPositions <#glyphPositions description#>
         */
    void textGlyphPositions(const btVector2& position, const s8* string, const s8* end, btAlignedObjectArray<JLIGlyphPosition>& glyphPositions);
    /**
         *  <#Description#>
         *
         *  @param ascender  <#ascender description#>
         *  @param descender <#descender description#>
         *  @param lineh     <#lineh description#>
         */
    void textMetrics(btMatrix3x3& ascender, btMatrix3x3& descender, btMatrix3x3& lineh);
    /**
         *  <#Description#>
         *
         *  @param string        <#string description#>
         *  @param end           <#end description#>
         *  @param breakRowWidth <#breakRowWidth description#>
         *
         *  @return <#return value description#>
         */
    btAlignedObjectArray<JLITextRow> textBreakLines(const s8* string, const s8* end, f32 breakRowWidth);

    /**
         *  <#Description#>
         *
         *  @param scaleX <#scaleX description#>
         *  @param skewY  <#skewY description#>
         *  @param skewX  <#skewX description#>
         *  @param scaleY <#scaleY description#>
         *  @param x      <#x description#>
         *  @param y      <#y description#>
         */
    void transform(f32 scaleX, f32 skewY, f32 skewX, f32 scaleY, f32 x, f32 y);
    /**
         *  <#Description#>
         *
         *  @param x <#x description#>
         *  @param y <#y description#>
         */
    void translate(f32 x, f32 y);
    /**
         *  <#Description#>
         *
         *  @param scalex <#scalex description#>
         *  @param scaley <#scaley description#>
         */
    void scale(f32 scalex, f32 scaley);
    /**
         *  <#Description#>
         *
         *  @param startx     <#startx description#>
         *  @param starty     <#starty description#>
         *  @param endx       <#endx description#>
         *  @param endy       <#endy description#>
         *  @param startColor <#startColor description#>
         *  @param endColor   <#endColor description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint linearGradient(f32 startx, f32 starty, f32 endx, f32 endy, const btVector4& startColor, const btVector4& endColor);
    /**
         *  <#Description#>
         *
         *  @param x          <#x description#>
         *  @param y          <#y description#>
         *  @param width      <#width description#>
         *  @param height     <#height description#>
         *  @param radius     <#radius description#>
         *  @param feather    <#feather description#>
         *  @param startColor <#startColor description#>
         *  @param endColor   <#endColor description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint boxGradient(f32 x, f32 y, f32 width, f32 height, f32 radius, f32 feather, const btVector4& startColor, const btVector4& endColor);
    /**
         *  <#Description#>
         *
         *  @param centerx     <#centerx description#>
         *  @param centery     <#centery description#>
         *  @param innerRadius <#innerRadius description#>
         *  @param outerRadius <#outerRadius description#>
         *  @param startColor  <#startColor description#>
         *  @param endColor    <#endColor description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint radialGradient(f32 centerx, f32 centery, f32 innerRadius, f32 outerRadius, const btVector4& startColor, const btVector4& endColor);
    /**
         *  <#Description#>
         *
         *  @param startx      <#startx description#>
         *  @param starty      <#starty description#>
         *  @param endx        <#endx description#>
         *  @param endy        <#endy description#>
         *  @param angle       <#angle description#>
         *  @param imageHandle <#imageHandle description#>
         *  @param alpha       <#alpha description#>
         *
         *  @return <#return value description#>
         */
    JLIPaint imagePattern(f32 startx, f32 starty, f32 endx, f32 endy, f32 angle, s32 imageHandle, f32 alpha);
    /**
         *  <#Description#>
         *
         *  @param x      <#x description#>
         *  @param y      <#y description#>
         *  @param width  <#width description#>
         *  @param height <#height description#>
         */
    void scissor(f32 x, f32 y, f32 width, f32 height);
    /**
         *  <#Description#>
         *
         *  @param x      <#x description#>
         *  @param y      <#y description#>
         *  @param width  <#width description#>
         *  @param height <#height description#>
         */
    void intersectScissor(f32 x, f32 y, f32 width, f32 height);
    /**
         *  <#Description#>
         *
         *  @param x <#x description#>
         *  @param y <#y description#>
         */
    void moveTo(f32 x, f32 y);
    /**
         *  <#Description#>
         *
         *  @param x <#x description#>
         *  @param y <#y description#>
         */
    void lineTo(f32 x, f32 y);
    /**
         *  <#Description#>
         *
         *  @param controlPoint1x <#controlPoint1x description#>
         *  @param controlPoint1y <#controlPoint1y description#>
         *  @param controlPoint2x <#controlPoint2x description#>
         *  @param controlPoint2y <#controlPoint2y description#>
         *  @param x              <#x description#>
         *  @param y              <#y description#>
         */
    void bezierTo(f32 controlPoint1x, f32 controlPoint1y, f32 controlPoint2x, f32 controlPoint2y, f32 x, f32 y);
    /**
         *  <#Description#>
         *
         *  @param controlPointx <#controlPointx description#>
         *  @param controlPointy <#controlPointy description#>
         *  @param x             <#x description#>
         *  @param y             <#y description#>
         */
    void quadTo(f32 controlPointx, f32 controlPointy, f32 x, f32 y);
    /**
         *  <#Description#>
         *
         *  @param pos1x  <#pos1x description#>
         *  @param pos1y  <#pos1y description#>
         *  @param pos2x  <#pos2x description#>
         *  @param pos2y  <#pos2y description#>
         *  @param radius <#radius description#>
         */
    void arcTo(f32 pos1x, f32 pos1y, f32 pos2x, f32 pos2y, f32 radius);
    /**
         *  <#Description#>
         *
         *  @param centerx   <#centerx description#>
         *  @param centery   <#centery description#>
         *  @param radius    <#radius description#>
         *  @param fromAngle <#fromAngle description#>
         *  @param toAngle   <#toAngle description#>
         *  @param dir       <#dir description#>
         */
    void arc(f32 centerx, f32 centery, f32 radius, f32 fromAngle, f32 toAngle, njliHUDWinding dir);
    /**
         *  <#Description#>
         *
         *  @param x      <#x description#>
         *  @param y      <#y description#>
         *  @param width  <#width description#>
         *  @param height <#height description#>
         */
    void rect(f32 x, f32 y, f32 width, f32 height);
    /**
         *  <#Description#>
         *
         *  @param x      <#x description#>
         *  @param y      <#y description#>
         *  @param width  <#width description#>
         *  @param height <#height description#>
         *  @param radius <#radius description#>
         */
    void roundedRect(f32 x, f32 y, f32 width, f32 height, f32 radius);
    /**
         *  <#Description#>
         *
         *  @param centerx <#centerx description#>
         *  @param centery <#centery description#>
         *  @param radiusx <#radiusx description#>
         *  @param radiusy <#radiusy description#>
         */
    void ellipse(f32 centerx, f32 centery, f32 radiusx, f32 radiusy);
    /**
         *  <#Description#>
         *
         *  @param centerx <#centerx description#>
         *  @param centery <#centery description#>
         *  @param radius  <#radius description#>
         */
    void circle(f32 centerx, f32 centery, f32 radius);
    /**
         *  <#Description#>
         *
         *  @param x      <#x description#>
         *  @param y      <#y description#>
         *  @param string <#string description#>
         *  @param end    <#end description#>
         *
         *  @return <#return value description#>
         */
    f32 text(f32 x, f32 y, const s8* string, const s8* end = NULL);
    /**
         *  <#Description#>
         *
         *  @param x             <#x description#>
         *  @param y             <#y description#>
         *  @param breakRowWidth <#breakRowWidth description#>
         *  @param string        <#string description#>
         *  @param end           <#end description#>
         */
    void textBox(f32 x, f32 y, f32 breakRowWidth, const s8* string, const s8* end = NULL);
    /**
         *  <#Description#>
         *
         *  @param x      <#x description#>
         *  @param y      <#y description#>
         *  @param bounds <#bounds description#>
         *  @param string <#string description#>
         *  @param end    <#end description#>
         *
         *  @return <#return value description#>
         */
    f32 textBounds(f32 x, f32 y, Rect& bounds, const s8* string, const s8* end = NULL);
    /**
         *  <#Description#>
         *
         *  @param x             <#x description#>
         *  @param y             <#y description#>
         *  @param breakRowWidth <#breakRowWidth description#>
         *  @param bounds        <#bounds description#>
         *  @param string        <#string description#>
         *  @param end           <#end description#>
         */
    void textBoxBounds(f32 x, f32 y, f32 breakRowWidth, Rect& bounds, const s8* string, const s8* end = NULL);
    /**
         *  <#Description#>
         *
         *  @param x              <#x description#>
         *  @param y              <#y description#>
         *  @param string         <#string description#>
         *  @param end            <#end description#>
         *  @param glyphPositions <#glyphPositions description#>
         */
    void textGlyphPositions(f32 x, f32 y, const s8* string, const s8* end, btAlignedObjectArray<JLIGlyphPosition>& glyphPositions);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Camera* getCamera();

protected:
    static void btVector4ToNVGcolor(NVGcolor& color, const btVector4& vColor);
    static void NVGcolorTobtVector4(btVector4& color, const NVGcolor& vColor);

    static void JLIPaintToNVGPaint(NVGpaint& nvgPaint, const JLIPaint& njliPaint);
    static void NVGPaintToJLIPaint(JLIPaint& njliPaint, const NVGpaint& nvgPaint);

    static void JLIGlyphPositionToNVGglyphPosition(NVGglyphPosition& nvgGlyphPos, const JLIGlyphPosition& njliGlyphPos);
    static void NVGglyphPositionToJLIGlyphPosition(JLIGlyphPosition& njliGlyphPos, const NVGglyphPosition& nvgGlyphPos);

    static void JLITextRowToNVGtextRow(NVGtextRow& nvgTextRow, const JLITextRow& njliTextRow);
    static void NVGtextRowToJLITextRow(JLITextRow& njliTextRow, const NVGtextRow& nvgTextRow);

    static void NVGaffineTobtMatrix3x3(btMatrix3x3& mtx, f32* floats);
    static void btMatrix3x3ToNVGaffine(f32* floats, const btMatrix3x3& mtx);

    void renderFBOs();
    void render();

    NVGcontext* getContext();
    void addFBO(AbstractFrameBufferObject* fbo);
    void removeFBO(AbstractFrameBufferObject* fbo);

private:
    WorldHUD(const WorldHUD&);
    WorldHUD& operator=(const WorldHUD&);

    NVGcontext* m_NVGContext;
    f32* m_matrixBuffer;

    std::vector<s32> m_images;
    std::vector<AbstractFrameBufferObject*> m_FBOvector;

    Camera* m_Camera;

    //        std::vector<NVGLUframebuffer*> m_NVGLUfb;
};
}

#endif /* defined(__JLIGameEngineTest__WorldHUD__) */
