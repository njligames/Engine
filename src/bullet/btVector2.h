//
//  btVector2.h
//  GameAsteroids
//
//  Created by James Folk on 5/13/13.
//  Copyright (c) 2013 James Folk. All rights reserved.
//

#ifndef __GameAsteroids__btVector2__
#define __GameAsteroids__btVector2__

#include "LinearMath/btScalar.h"
#include "LinearMath/btVector3.h"

#ifdef BT_USE_DOUBLE_PRECISION
#define btVector2Data btVector2DoubleData
#define btVector2DataName "btVector2DoubleData"
#else
#define btVector2Data btVector2FloatData
#define btVector2DataName "btVector2FloatData"
#endif //BT_USE_DOUBLE_PRECISION

/** @name 2D points and vectors
 *
 * Available functions are similar to btVector3 ones.
 * Values are stored in public x and y attributes for convenience.
 */
//@{
ATTRIBUTE_ALIGNED16(class) btVector2
{
public:
    
	BT_DECLARE_ALIGNED_ALLOCATOR();
public:
//    btScalar xy_[4];
    btScalar xy_[2];
    
public:
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2() { xy_[0] = 0; xy_[1] = 0; }
/**
 *  <#Description#>
 *
 *  @param x <#x description#>
 *  @param y <#y description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2(const btScalar& x, const btScalar& y) { xy_[0] = x; xy_[1] = y; }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2(const btVector2& v)
    {
        xy_[0] = v.xy_[0];
        xy_[1] = v.xy_[1];
    }
/**
 *  <#Description#>
 *
 *  @param v3 <#v3 description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2(const btVector3& v3)
    {
        xy_[0] = v3.x();
        xy_[1] = v3.y();
    }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE operator btVector3() const { return btVector3(xy_[0], xy_[1], 0); }

/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE operator const btScalar* () const { return xy_; }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE const btScalar& x() const { return xy_[0]; }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE const btScalar& y() const { return xy_[1]; }
/**
 *  <#Description#>
 *
 *  @param x <#x description#>
 */
    SIMD_FORCE_INLINE void setX(const btScalar& x) { xy_[0] = x; }
/**
 *  <#Description#>
 *
 *  @param y <#y description#>
 */
    SIMD_FORCE_INLINE void setY(const btScalar& y) { xy_[1] = y; }

/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& operator=(const btVector2& v) { if(this != &v){xy_[0] = v.xy_[0]; xy_[1] = v.xy_[1];} return *this; }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& operator+=(const btVector2& v) { xy_[0] += v.xy_[0]; xy_[1] += v.xy_[1]; return *this; }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& operator-=(const btVector2& v) { xy_[0] -= v.xy_[0]; xy_[1] -= v.xy_[1]; return *this; }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& operator*=(const btVector2& v) { xy_[0] *= v.xy_[0]; xy_[1] *= v.xy_[1]; return *this; }
/**
 *  <#Description#>
 *
 *  @param s <#s description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& operator*=(const btScalar& s) { xy_[0] *= s; xy_[1] *= s; return *this; }
/**
 *  <#Description#>
 *
 *  @param s <#s description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& operator/=(const btScalar& s) { btFullAssert(s != btScalar(0.0)); return *this *= btScalar(1.0) / s; }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btScalar dot(const btVector2& v) const { return xy_[0] * v.xy_[0] + xy_[1] * v.xy_[1]; }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btScalar length2() const { return dot(*this); }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btScalar length () const { return btSqrt(length2()); }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btScalar distance2(const btVector2& v) const;
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btScalar distance (const btVector2& v) const;
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& normalize() { return *this /= length(); }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2 normalized() const;

/**
 *  <#Description#>
 *
 *  @param angle <#angle description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2& rotate(const btScalar angle);
/**
 *  <#Description#>
 *
 *  @param angle <#angle description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2 rotated(const btScalar angle) const;
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btVector2 absolute() const { return btVector2( btFabs(xy_[0]), btFabs(xy_[1]) ); }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
    SIMD_FORCE_INLINE btScalar angle() const { return btAtan2(xy_[1], xy_[0]); }
/**
 *  <#Description#>
 *
 *  @param dataOut <#dataOut description#>
 */
    SIMD_FORCE_INLINE	void	serializeFloat(struct	btVector2FloatData& dataOut) const;
/**
 *  <#Description#>
 *
 *  @param dataIn <#dataIn description#>
 */
    SIMD_FORCE_INLINE void	deSerializeFloat(const struct	btVector2FloatData& dataIn);
/**
 *  <#Description#>
 *
 *  @param dataOut <#dataOut description#>
 */
    SIMD_FORCE_INLINE	void	serializeDouble(struct	btVector2DoubleData& dataOut) const;
/**
 *  <#Description#>
 *
 *  @param dataIn <#dataIn description#>
 */
    SIMD_FORCE_INLINE void	deSerializeDouble(const struct	btVector2DoubleData& dataIn);
/**
 *  <#Description#>
 *
 *  @param dataOut <#dataOut description#>
 */
    SIMD_FORCE_INLINE	void	serialize(struct	btVector2Data& dataOut) const;
/**
 *  <#Description#>
 *
 *  @param dataIn <#dataIn description#>
 */
    SIMD_FORCE_INLINE void	deSerialize(const struct	btVector2Data& dataIn);
/**
 *  <#Description#>
 */


};

/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 operator+(const btVector2& v1, const btVector2& v2) { return btVector2(v1.xy_[0]+v2.xy_[0], v1.xy_[1]+v2.xy_[1]); }
/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 operator-(const btVector2& v1, const btVector2& v2) { return btVector2(v1.xy_[0]-v2.xy_[0], v1.xy_[1]-v2.xy_[1]); }
/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 operator*(const btVector2& v1, const btVector2& v2) { return btVector2(v1.xy_[0]*v2.xy_[0], v1.xy_[1]*v2.xy_[1]); }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 operator-(const btVector2& v) { return btVector2(-v.xy_[0], -v.xy_[1]); }
/**
 *  <#Description#>
 *
 *  @param s <#s description#>
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 operator*(const btScalar& s, const btVector2& v) { return btVector2(s*v.xy_[0], s*v.xy_[1]); }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *  @param s <#s description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 operator*(const btVector2& v, const btScalar& s) { return s*v; }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *  @param s <#s description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 operator/(const btVector2& v, const btScalar& s) { btFullAssert(s != btScalar(0.0)); return v * (btScalar(1.0)/s); }
/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE bool operator==(const btVector2& v1, const btVector2& v2) { return v1.xy_[0] == v2.xy_[0] && v1.xy_[1] == v2.xy_[1]; }
/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE bool operator!=(const btVector2& v1, const btVector2& v2) { return !(v1 == v2); }

/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btScalar btVector2::distance2(const btVector2& v) const { return (v - *this).length2(); }
/**
 *  <#Description#>
 *
 *  @param v <#v description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btScalar btVector2::distance (const btVector2& v) const { return (v - *this).length(); }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 btVector2::normalized() const { return *this / length(); }
/**
 *  <#Description#>
 *
 *  @param angle <#angle description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2& btVector2::rotate(const btScalar angle)
{
    btVector2 v(-xy_[1], xy_[0]);
    return *this = ( *this * btCos(angle) + v * btSin(angle) );
}
/**
 *  <#Description#>
 *
 *  @param angle <#angle description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btVector2 btVector2::rotated(const btScalar angle) const
{
    btVector2 v(-xy_[1], xy_[0]);
    return ( *this * btCos(angle) + v * btSin(angle) );
}

/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btScalar dot(const btVector2& v1, const btVector2& v2) { return v1.dot(v2); }
/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btScalar distance2(const btVector2& v1, const btVector2& v2) { return v1.distance2(v2); }
/**
 *  <#Description#>
 *
 *  @param v1 <#v1 description#>
 *  @param v2 <#v2 description#>
 *
 *  @return <#return value description#>
 */
SIMD_FORCE_INLINE btScalar distance (const btVector2& v1, const btVector2& v2) { return v1.distance(v2); }
//@}

struct	btVector2FloatData
{
	float	xy_[2];
};

struct	btVector2DoubleData
{
	double	xy_[2];
    
};

/**
 *  <#Description#>
 *
 *  @param dataOut <#dataOut description#>
 */
SIMD_FORCE_INLINE	void	btVector2::serializeFloat(struct	btVector2FloatData& dataOut) const
{
	///could also do a memcpy, check if it is worth it
	for (int i=0;i<2;i++)
		dataOut.xy_[i] = float(xy_[i]);
}

/**
 *  <#Description#>
 *
 *  @param dataIn <#dataIn description#>
 */
SIMD_FORCE_INLINE void	btVector2::deSerializeFloat(const struct	btVector2FloatData& dataIn)
{
	for (int i=0;i<2;i++)
		xy_[i] = btScalar(dataIn.xy_[i]);
}

/**
 *  <#Description#>
 *
 *  @param dataOut <#dataOut description#>
 */
SIMD_FORCE_INLINE	void	btVector2::serializeDouble(struct	btVector2DoubleData& dataOut) const
{
	///could also do a memcpy, check if it is worth it
	for (int i=0;i<2;i++)
		dataOut.xy_[i] = double(xy_[i]);
}

/**
 *  <#Description#>
 *
 *  @param dataIn <#dataIn description#>
 */
SIMD_FORCE_INLINE void	btVector2::deSerializeDouble(const struct	btVector2DoubleData& dataIn)
{
	for (int i=0;i<2;i++)
		xy_[i] = btScalar(dataIn.xy_[i]);
}

/**
 *  <#Description#>
 *
 *  @param dataOut <#dataOut description#>
 */
SIMD_FORCE_INLINE	void	btVector2::serialize(struct	btVector2Data& dataOut) const
{
	///could also do a memcpy, check if it is worth it
	for (int i=0;i<2;i++)
		dataOut.xy_[i] = xy_[i];
}

/**
 *  <#Description#>
 *
 *  @param dataIn <#dataIn description#>
 */
SIMD_FORCE_INLINE void	btVector2::deSerialize(const struct	btVector2Data& dataIn)
{
	for (int i=0;i<2;i++)
		xy_[i] = dataIn.xy_[i];
}

#endif /* defined(__GameAsteroids__btVector2__) */
