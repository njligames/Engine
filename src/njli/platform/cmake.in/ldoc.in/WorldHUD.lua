
----
-- @file WorldHUD


---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:WorldHUD()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:getClassName()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:getType()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:save()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:restore()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:reset()
end

---- Brief description.
-- <#Description#>
-- @param color <#color description#>
-- @return <#return value description#>
function WorldHUD:strokeColor(color)
end

---- Brief description.
-- <#Description#>
-- @param paint <#paint description#>
-- @return <#return value description#>
function WorldHUD:strokePaint(paint)
end

---- Brief description.
-- <#Description#>
-- @param color <#color description#>
-- @return <#return value description#>
function WorldHUD:fillColor(color)
end

---- Brief description.
-- <#Description#>
-- @param paint <#paint description#>
-- @return <#return value description#>
function WorldHUD:fillPaint(paint)
end

---- Brief description.
-- <#Description#>
-- @param limit <#limit description#>
-- @return <#return value description#>
function WorldHUD:miterLimit(limit)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function WorldHUD:strokeWidth(size)
end

---- Brief description.
-- <#Description#>
-- @param cap <#cap description#>
-- @return <#return value description#>
function WorldHUD:lineCap(cap)
end

---- Brief description.
-- <#Description#>
-- @param join <#join description#>
-- @return <#return value description#>
function WorldHUD:lineJoin(join)
end

---- Brief description.
-- <#Description#>
-- @param alpha <#alpha description#>
-- @return <#return value description#>
function WorldHUD:globalAlpha(alpha)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:resetTransform()
end

---- Brief description.
-- <#Description#>
-- @param mtx <#mtx description#>
-- @return <#return value description#>
function WorldHUD:transform(mtx)
end

---- Brief description.
-- <#Description#>
-- @param pos <#pos description#>
-- @return <#return value description#>
function WorldHUD:translate(pos)
end

---- Brief description.
-- <#Description#>
-- @param angle <#angle description#>
-- @return <#return value description#>
function WorldHUD:rotate(angle)
end

---- Brief description.
-- <#Description#>
-- @param angle <#angle description#>
-- @return <#return value description#>
function WorldHUD:skewX(angle)
end

---- Brief description.
-- <#Description#>
-- @param angle <#angle description#>
-- @return <#return value description#>
function WorldHUD:skewY(angle)
end

---- Brief description.
-- <#Description#>
-- @param scale <
-- @return <#return value description#>
function WorldHUD:scale(scale)
end

---- Brief description.
-- <#Description#>
-- @param xform <#xform description#>
-- @return <#return value description#>
function WorldHUD:getTransform(xform)
end

---- Brief description.
-- <#Description#>
-- @param filename <#filename description#>
-- @param imageFlags <#imageFlags description#>
-- @return <#return value description#>
function WorldHUD:createImage(filename, imageFlags)
end

---- Brief description.
-- <#Description#>
-- @param image <#image description#>
-- @param imageFlags <#imageFlags description#>
-- @return <#return value description#>
function WorldHUD:createImageRGBA(image, imageFlags)
end

---- Brief description.
-- <#Description#>
-- @param imageHandle <#imageHandle description#>
-- @param image <#image description#>
-- @return <#return value description#>
function WorldHUD:updateImage(imageHandle, image)
end

---- Brief description.
-- <#Description#>
-- @param imageHandle <#imageHandle description#>
-- @param w <#w description#>
-- @param h <#h description#>
-- @return <#return value description#>
function WorldHUD:imageSize(imageHandle, w, h)
end

---- Brief description.
-- <#Description#>
-- @param imageHandle <#imageHandle description#>
-- @return <#return value description#>
function WorldHUD:deleteImage(imageHandle)
end

---- Brief description.
-- <#Description#>
-- @param startPos <#startPos description#>
-- @param endPos <#endPos description#>
-- @param startColor <#startColor description#>
-- @param endColor <#endColor description#>
-- @return <#return value description#>
function WorldHUD:linearGradient(startPos, endPos, startColor, endColor)
end

---- Brief description.
-- <#Description#>
-- @param rect <
-- @param radius <#radius description#>
-- @param feather <#feather description#>
-- @param startColor <#startColor description#>
-- @param endColor <#endColor description#>
-- @return <#return value description#>
function WorldHUD:boxGradient(rect, radius, feather, startColor, endColor)
end

---- Brief description.
-- <#Description#>
-- @param center <#center description#>
-- @param innerRadius <#innerRadius description#>
-- @param outerRadius <#outerRadius description#>
-- @param startColor <#startColor description#>
-- @param endColor <#endColor description#>
-- @return <#return value description#>
function WorldHUD:radialGradient(center, innerRadius, outerRadius, startColor, endColor)
end

---- Brief description.
-- <#Description#>
-- @param startPos <#startPos description#>
-- @param endPos <#endPos description#>
-- @param angle <#angle description#>
-- @param imageHandle <#imageHandle description#>
-- @param alpha <#alpha description#>
-- @return <#return value description#>
function WorldHUD:imagePattern(startPos, endPos, angle, imageHandle, alpha)
end

---- Brief description.
-- <#Description#>
-- @param rect <
-- @return <#return value description#>
function WorldHUD:scissor(rect)
end

---- Brief description.
-- <#Description#>
-- @param rect <
-- @return <#return value description#>
function WorldHUD:intersectScissor(rect)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:resetScissor()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:beginPath()
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @return <#return value description#>
function WorldHUD:moveTo(position)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @return <#return value description#>
function WorldHUD:lineTo(position)
end

---- Brief description.
-- <#Description#>
-- @param controlPoint1 <#controlPoint1 description#>
-- @param controlPoint2 <#controlPoint2 description#>
-- @param pos <#pos description#>
-- @return <#return value description#>
function WorldHUD:bezierTo(controlPoint1, controlPoint2, pos)
end

---- Brief description.
-- <#Description#>
-- @param controlPoint <#controlPoint description#>
-- @param pos <#pos description#>
-- @return <#return value description#>
function WorldHUD:quadTo(controlPoint, pos)
end

---- Brief description.
-- <#Description#>
-- @param pos1 <#pos1 description#>
-- @param pos2 <#pos2 description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function WorldHUD:arcTo(pos1, pos2, radius)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:closePath()
end

---- Brief description.
-- <#Description#>
-- @param dir <#dir description#>
-- @return <#return value description#>
function WorldHUD:pathWinding(dir)
end

---- Brief description.
-- <#Description#>
-- @param center <#center description#>
-- @param radius <#radius description#>
-- @param fromAngle <#fromAngle description#>
-- @param toAngle <#toAngle description#>
-- @param dir <#dir description#>
-- @return <#return value description#>
function WorldHUD:arc(center, radius, fromAngle, toAngle, dir)
end

---- Brief description.
-- <#Description#>
-- @param rect <
-- @return <#return value description#>
function WorldHUD:rect(rect)
end

---- Brief description.
-- <#Description#>
-- @param rect <
-- @param radius <#radius description#>
-- @return <#return value description#>
function WorldHUD:roundedRect(rect, radius)
end

---- Brief description.
-- <#Description#>
-- @param center <#center description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function WorldHUD:ellipse(center, radius)
end

---- Brief description.
-- <#Description#>
-- @param center <#center description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function WorldHUD:circle(center, radius)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:fill()
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:stroke()
end

---- Brief description.
-- <#Description#>
-- @param name <#name description#>
-- @param filename <#filename description#>
-- @return <#return value description#>
function WorldHUD:createFont(name, filename)
end

---- Brief description.
-- <#Description#>
-- @param name <#name description#>
-- @return <#return value description#>
function WorldHUD:findFont(name)
end

---- Brief description.
-- <#Description#>
-- @param size <#size description#>
-- @return <#return value description#>
function WorldHUD:fontSize(size)
end

---- Brief description.
-- <#Description#>
-- @param blur <#blur description#>
-- @return <#return value description#>
function WorldHUD:fontBlur(blur)
end

---- Brief description.
-- <#Description#>
-- @param spacing <#spacing description#>
-- @return <#return value description#>
function WorldHUD:textLetterSpacing(spacing)
end

---- Brief description.
-- <#Description#>
-- @param lineHeight <#lineHeight description#>
-- @return <#return value description#>
function WorldHUD:textLineHeight(lineHeight)
end

---- Brief description.
-- <#Description#>
-- @param align <#align description#>
-- @return <#return value description#>
function WorldHUD:textAlign(align)
end

---- Brief description.
-- <#Description#>
-- @param fontHandle <#fontHandle description#>
-- @return <#return value description#>
function WorldHUD:fontFaceId(fontHandle)
end

---- Brief description.
-- <#Description#>
-- @param font <#font description#>
-- @return <#return value description#>
function WorldHUD:fontFace(font)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:text(position, string, end)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param breakRowWidth <#breakRowWidth description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:textBox(position, breakRowWidth, string, end)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param bounds <#bounds description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:textBounds(position, bounds, string, end)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param breakRowWidth <#breakRowWidth description#>
-- @param bounds <#bounds description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:textBoxBounds(position, breakRowWidth, bounds, string, end)
end

---- Brief description.
-- <#Description#>
-- @param position <#position description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @param glyphPositions <#glyphPositions description#>
-- @return <#return value description#>
function WorldHUD:textGlyphPositions(position, string, end, glyphPositions)
end

---- Brief description.
-- <#Description#>
-- @param ascender <#ascender description#>
-- @param descender <#descender description#>
-- @param lineh <#lineh description#>
-- @return <#return value description#>
function WorldHUD:textMetrics(ascender, descender, lineh)
end

---- Brief description.
-- <#Description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @param breakRowWidth <#breakRowWidth description#>
-- @return <#return value description#>
function WorldHUD:textBreakLines(string, end, breakRowWidth)
end

---- Brief description.
-- <#Description#>
-- @param scaleX <#scaleX description#>
-- @param skewY <
-- @param skewX <
-- @param scaleY <#scaleY description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @return <#return value description#>
function WorldHUD:transform(scaleX, skewY, skewX, scaleY, x, y)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @return <#return value description#>
function WorldHUD:translate(x, y)
end

---- Brief description.
-- <#Description#>
-- @param scalex <#scalex description#>
-- @param scaley <#scaley description#>
-- @return <#return value description#>
function WorldHUD:scale(scalex, scaley)
end

---- Brief description.
-- <#Description#>
-- @param startx <#startx description#>
-- @param starty <#starty description#>
-- @param endx <#endx description#>
-- @param endy <#endy description#>
-- @param startColor <#startColor description#>
-- @param endColor <#endColor description#>
-- @return <#return value description#>
function WorldHUD:linearGradient(startx, starty, endx, endy, startColor, endColor)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param width <#width description#>
-- @param height <#height description#>
-- @param radius <#radius description#>
-- @param feather <#feather description#>
-- @param startColor <#startColor description#>
-- @param endColor <#endColor description#>
-- @return <#return value description#>
function WorldHUD:boxGradient(x, y, width, height, radius, feather, startColor, endColor)
end

---- Brief description.
-- <#Description#>
-- @param centerx <#centerx description#>
-- @param centery <#centery description#>
-- @param innerRadius <#innerRadius description#>
-- @param outerRadius <#outerRadius description#>
-- @param startColor <#startColor description#>
-- @param endColor <#endColor description#>
-- @return <#return value description#>
function WorldHUD:radialGradient(centerx, centery, innerRadius, outerRadius, startColor, endColor)
end

---- Brief description.
-- <#Description#>
-- @param startx <#startx description#>
-- @param starty <#starty description#>
-- @param endx <#endx description#>
-- @param endy <#endy description#>
-- @param angle <#angle description#>
-- @param imageHandle <#imageHandle description#>
-- @param alpha <#alpha description#>
-- @return <#return value description#>
function WorldHUD:imagePattern(startx, starty, endx, endy, angle, imageHandle, alpha)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param width <#width description#>
-- @param height <#height description#>
-- @return <#return value description#>
function WorldHUD:scissor(x, y, width, height)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param width <#width description#>
-- @param height <#height description#>
-- @return <#return value description#>
function WorldHUD:intersectScissor(x, y, width, height)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @return <#return value description#>
function WorldHUD:moveTo(x, y)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @return <#return value description#>
function WorldHUD:lineTo(x, y)
end

---- Brief description.
-- <#Description#>
-- @param controlPoint1x <#controlPoint1x description#>
-- @param controlPoint1y <#controlPoint1y description#>
-- @param controlPoint2x <#controlPoint2x description#>
-- @param controlPoint2y <#controlPoint2y description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @return <#return value description#>
function WorldHUD:bezierTo(controlPoint1x, controlPoint1y, controlPoint2x, controlPoint2y, x, y)
end

---- Brief description.
-- <#Description#>
-- @param controlPointx <#controlPointx description#>
-- @param controlPointy <#controlPointy description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @return <#return value description#>
function WorldHUD:quadTo(controlPointx, controlPointy, x, y)
end

---- Brief description.
-- <#Description#>
-- @param pos1x <#pos1x description#>
-- @param pos1y <#pos1y description#>
-- @param pos2x <#pos2x description#>
-- @param pos2y <#pos2y description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function WorldHUD:arcTo(pos1x, pos1y, pos2x, pos2y, radius)
end

---- Brief description.
-- <#Description#>
-- @param centerx <#centerx description#>
-- @param centery <#centery description#>
-- @param radius <#radius description#>
-- @param fromAngle <#fromAngle description#>
-- @param toAngle <#toAngle description#>
-- @param dir <#dir description#>
-- @return <#return value description#>
function WorldHUD:arc(centerx, centery, radius, fromAngle, toAngle, dir)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param width <#width description#>
-- @param height <#height description#>
-- @return <#return value description#>
function WorldHUD:rect(x, y, width, height)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param width <#width description#>
-- @param height <#height description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function WorldHUD:roundedRect(x, y, width, height, radius)
end

---- Brief description.
-- <#Description#>
-- @param centerx <#centerx description#>
-- @param centery <#centery description#>
-- @param radiusx <#radiusx description#>
-- @param radiusy <#radiusy description#>
-- @return <#return value description#>
function WorldHUD:ellipse(centerx, centery, radiusx, radiusy)
end

---- Brief description.
-- <#Description#>
-- @param centerx <#centerx description#>
-- @param centery <#centery description#>
-- @param radius <#radius description#>
-- @return <#return value description#>
function WorldHUD:circle(centerx, centery, radius)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:text(x, y, string, end)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param breakRowWidth <#breakRowWidth description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:textBox(x, y, breakRowWidth, string, end)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param bounds <#bounds description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:textBounds(x, y, bounds, string, end)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param breakRowWidth <#breakRowWidth description#>
-- @param bounds <#bounds description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @return <#return value description#>
function WorldHUD:textBoxBounds(x, y, breakRowWidth, bounds, string, end)
end

---- Brief description.
-- <#Description#>
-- @param x <#x description#>
-- @param y <#y description#>
-- @param string <#string description#>
-- @param end <#end description#>
-- @param glyphPositions <#glyphPositions description#>
-- @return <#return value description#>
function WorldHUD:textGlyphPositions(x, y, string, end, glyphPositions)
end

---- Brief description.
-- <#Description#>
-- @return <#return value description#>
function WorldHUD:getCamera()
end

---- Brief description.
-- <#Description#>
-- @param cp <#cp description#>
-- @return <#return value description#>
function NJLI.WorldHUD.cpToUTF8(cp)
end

---- Brief description.
-- <#Description#>
-- @param r <#r description#>
-- @param g <#g description#>
-- @param b <#b description#>
-- @return <#return value description#>
function NJLI.WorldHUD.rgb(r, g, b)
end

---- Brief description.
-- <#Description#>
-- @param r <#r description#>
-- @param g <#g description#>
-- @param b <#b description#>
-- @return <#return value description#>
function NJLI.WorldHUD.rgbf(r, g, b)
end

---- Brief description.
-- <#Description#>
-- @param r <#r description#>
-- @param g <#g description#>
-- @param b <#b description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.rgba(r, g, b, a)
end

---- Brief description.
-- <#Description#>
-- @param r <#r description#>
-- @param g <#g description#>
-- @param b <#b description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.rgbaf(r, g, b, a)
end

---- Brief description.
-- <#Description#>
-- @param c0 <#c0 description#>
-- @param c1 <#c1 description#>
-- @param u <#u description#>
-- @return <#return value description#>
function NJLI.WorldHUD.lerpRGBA(c0, c1, u)
end

---- Brief description.
-- <#Description#>
-- @param c0 <#c0 description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transRGBA(c0, a)
end

---- Brief description.
-- <#Description#>
-- @param c0 <#c0 description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transRGBAf(c0, a)
end

---- Brief description.
-- <#Description#>
-- @param h <#h description#>
-- @param s <#s description#>
-- @param l <#l description#>
-- @return <#return value description#>
function NJLI.WorldHUD.hsl(h, s, l)
end

---- Brief description.
-- <#Description#>
-- @param h <#h description#>
-- @param s <#s description#>
-- @param l <#l description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.hsla(h, s, l, a)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformIdentity(floats)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param translatePos <#translatePos description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformTranslate(floats, translatePos)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param scale <
-- @return <#return value description#>
function NJLI.WorldHUD.transformScale(floats, scale)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformRotate(floats, a)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformSkewX(floats, a)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformSkewY(floats, a)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param src <#src description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformMultiply(floats, src)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param src <#src description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformPremultiply(floats, src)
end

---- Brief description.
-- <#Description#>
-- @param dstx <#dstx description#>
-- @param dsty <#dsty description#>
-- @param xform <#xform description#>
-- @param sourcePos <#sourcePos description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformPoint(dstx, dsty, xform, sourcePos)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformIdentity(floats)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param tx <#tx description#>
-- @param ty <#ty description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformTranslate(floats, tx, ty)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param sx <#sx description#>
-- @param sy <#sy description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformScale(floats, sx, sy)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformRotate(floats, a)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformSkewX(floats, a)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param a <#a description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformSkewY(floats, a)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param src <#src description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformMultiply(floats, src)
end

---- Brief description.
-- <#Description#>
-- @param floats <#floats description#>
-- @param src <#src description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformPremultiply(floats, src)
end

---- Brief description.
-- <#Description#>
-- @param dstx <#dstx description#>
-- @param dsty <#dsty description#>
-- @param xform <#xform description#>
-- @param srcx <#srcx description#>
-- @param srcy <#srcy description#>
-- @return <#return value description#>
function NJLI.WorldHUD.transformPoint(dstx, dsty, xform, srcx, srcy)
end

---- Brief description.
-- <#Description#>
-- @param deg <#deg description#>
-- @return <#return value description#>
function NJLI.WorldHUD.degToRad(deg)
end

---- Brief description.
-- <#Description#>
-- @param rad <#rad description#>
-- @return <#return value description#>
function NJLI.WorldHUD.radToDeg(rad)
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.btVector4ToNVGcolor()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.NVGcolorTobtVector4()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.JLIPaintToNVGPaint()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.NVGPaintToJLIPaint()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.JLIGlyphPositionToNVGglyphPosition()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.NVGglyphPositionToJLIGlyphPosition()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.JLITextRowToNVGtextRow()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.NVGtextRowToJLITextRow()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.NVGaffineTobtMatrix3x3()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.btMatrix3x3ToNVGaffine()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.renderFBOs()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.render()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.getContext()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.addFBO()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.removeFBO()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.WorldHUD()
end

---- Brief description.
-- @return <#return value description#>
function NJLI.WorldHUD.operator=()
end

