//
//  Camera.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Camera.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "CameraBuilder.h"
#include "btDbvtBroadphase.h"
#include "btVector2.h"
#include "btVector3.h"
#include <map>
#include "btDbvt.h"
#include "Geometry.h"
#include "Material.h"
#include "btCollisionObject.h"
#include "btCollisionShape.h"
#include "Node.h"

#define FORMATSTRING "{\"njli::Camera\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

static inline btTransform setFrom4x4Matrix(const btScalar *m)
{
    btMatrix3x3 basis;
    btVector3 origin;
    
    basis.setFromOpenGLSubMatrix(m);
    origin.setValue(m[12],m[13],m[14]);
    
    basis[0].setW(m[3]);
    basis[1].setW(m[7]);
    basis[2].setW(m[11]);
    origin.setW(m[15]);
    
    return btTransform(basis, origin);
}

static inline void getFrom4x4Matrix(const btTransform &t, btScalar *m)
{
    t.getBasis().getOpenGLSubMatrix(m);
    
    m[3] = t.getBasis()[0].w();
    m[7] = t.getBasis()[1].w();
    m[11] = t.getBasis()[2].w();
    
    m[12] = t.getOrigin().x();
    m[13] = t.getOrigin().y();
    m[14] = t.getOrigin().z();
    m[15] = t.getOrigin().w();
}

static inline btTransform makeLookAt(btScalar eyeX, btScalar eyeY, btScalar eyeZ,
                                     btScalar centerX, btScalar centerY, btScalar centerZ,
                                     btScalar upX, btScalar upY, btScalar upZ)
{
    btVector3 ev(eyeX, eyeY, eyeZ );
    btVector3 cv(centerX, centerY, centerZ );
    btVector3 uv( upX, upY, upZ );
    btVector3 n((ev + -cv).normalized());
    btVector3 u((uv.cross(n).normalized()));
    btVector3 v(n.cross(u));
    
    btScalar m[16] = { u.x(), v.x(), n.x(), 0.0f,
        u.y(), v.y(), n.y(), 0.0f,
        u.z(), v.z(), n.z(), 0.0f,
        (-u).dot(ev),
        (-v).dot(ev),
        (-n).dot(ev),
        1.0f };
    
    return setFrom4x4Matrix(m);
}

static inline btTransform makeFrustum(f32 *matrixBuffer, float fov, float aspect, float nearDist, float farDist, bool leftHanded = true )
{
    memset(matrixBuffer, 0, sizeof(f32) * 16);
    //
    // General form of the Projection Matrix
    //
    // uh = Cot( fov/2 ) == 1/Tan(fov/2)
    // uw / uh = 1/aspect
    //
    //   uw         0       0       0
    //    0        uh       0       0
    //    0         0      f/(f-n)  1
    //    0         0    -fn/(f-n)  0
    //
    // Make result to be identity first
    
    //    0         1       2       3
    //    4         5       6       7
    //    8         9      10      11
    //   12        13      14      15
    
    // check for bad parameters to avoid divide by zero:
    // if found, assert and return an identity matrix.
    if ( fov <= 0 || aspect == 0 )
    {
        DEBUG_ASSERT( fov > 0 && aspect != 0 );
        return btTransform::getIdentity();
    }
    
    float frustumDepth = farDist - nearDist;
    float oneOverDepth = 1.0f / frustumDepth;
    
    matrixBuffer[5] = 1.0f / tan(0.5f * btRadians(fov));
    matrixBuffer[0] = (leftHanded ? 1.0f : -1.0f ) * matrixBuffer[5] / aspect;
    matrixBuffer[10] = farDist * oneOverDepth;
    matrixBuffer[14] = (-farDist * nearDist) * oneOverDepth;
    matrixBuffer[11] = 1.0f;
    matrixBuffer[15] = 0;
    
    return setFrom4x4Matrix(matrixBuffer);
}
static inline btTransform makeFrustum(btScalar left, btScalar right,
                                      btScalar bottom, btScalar top,
                                      btScalar nearZ, btScalar farZ)
{
    btScalar ral = right + left;
    btScalar rsl = right - left;
    btScalar tsb = top - bottom;
    btScalar tab = top + bottom;
    btScalar fan = farZ + nearZ;
    btScalar fsn = farZ - nearZ;
    
    btScalar m[16] = { 2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
        ral / rsl, tab / tsb, -fan / fsn, -1.0f,
        0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f };
    
    return setFrom4x4Matrix(m);
}

static inline btTransform makeOrtho(btScalar left, btScalar right,
                             btScalar bottom, btScalar top,
                             btScalar nearZ, btScalar farZ)
{
    btScalar ral = right + left;
    btScalar rsl = right - left;
    btScalar tab = top + bottom;
    btScalar tsb = top - bottom;
    btScalar fan = farZ + nearZ;
    btScalar fsn = farZ - nearZ;
    
    btScalar m[16] = { 2.0f / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / tsb, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / fsn, 0.0f,
        -ral / rsl, -tab / tsb, -fan / fsn, 1.0f };
    
    return setFrom4x4Matrix(m);
}

static void __gluMultMatrixVecd(const f32 matrix[16], const f32 in[4],
                                f32 out[4])
{
    s32 i;
    
    for (i=0; i<4; i++) {
        out[i] =
        in[0] * matrix[0*4+i] +
        in[1] * matrix[1*4+i] +
        in[2] * matrix[2*4+i] +
        in[3] * matrix[3*4+i];
    }
}

/*
 ** Invert 4x4 matrix.
 ** Contributed by David Moore (See Mesa bug #6748)
 */
static s32 __gluInvertMatrixd(const f32 m[16], f32 invOut[16])
{
    f32 inv[16], det;
    s32 i;
    
    inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
    + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
    inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
    - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
    inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
    + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
    inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
    - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
    inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
    - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
    inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
    + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
    inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
    - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
    inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
    + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
    inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
    + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
    inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
    - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
    inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
    + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
    inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
    - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
    inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
    - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
    inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
    + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
    inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
    - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
    inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
    + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];
    
    det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
    if (det == 0)
        return 0;
    
    det = 1.0 / det;
    
    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;
    
    return 1;
}

static void __gluMultMatricesd(const f32 a[16], const f32 b[16],
                               f32 r[16])
{
    s32 i, j;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            r[i*4+j] =
            a[i*4+0]*b[0*4+j] +
            a[i*4+1]*b[1*4+j] +
            a[i*4+2]*b[2*4+j] +
            a[i*4+3]*b[3*4+j];
        }
    }
}

s32 gluProject(f32 objx, f32 objy, f32 objz,
                 const f32 modelMatrix[16],
                 const f32 projMatrix[16],
                 const s32 viewport[4],
                 f32 *winx, f32 *winy, f32 *winz)
{
    f32 in[4];
    f32 out[4];
    
    in[0]=objx;
    in[1]=objy;
    in[2]=objz;
    in[3]=1.0;
    __gluMultMatrixVecd(modelMatrix, in, out);
    __gluMultMatrixVecd(projMatrix, out, in);
    if (in[3] == 0.0) return(0);
    in[0] /= in[3];
    in[1] /= in[3];
    in[2] /= in[3];
    /* Map x, y and z to range 0-1 */
    in[0] = in[0] * 0.5 + 0.5;
    in[1] = in[1] * 0.5 + 0.5;
    in[2] = in[2] * 0.5 + 0.5;
    
    /* Map x,y to viewport */
    in[0] = in[0] * viewport[2] + viewport[0];
    in[1] = in[1] * viewport[3] + viewport[1];
    
    *winx=in[0];
    *winy=in[1];
    *winz=in[2];
    
    DEBUG_ASSERT(!isnan(*winx));
    DEBUG_ASSERT(!isnan(*winy));
    DEBUG_ASSERT(!isnan(*winz));
    
    return(1);
}

static s32
gluUnProject(f32 winx, f32 winy, f32 winz,
             const f32 modelMatrix[16],
             const f32 projMatrix[16],
             const s32 viewport[4],
             f32 *objx, f32 *objy, f32 *objz)
{
    f32 finalMatrix[16];
    f32 in[4];
    f32 out[4];
    
    __gluMultMatricesd(modelMatrix, projMatrix, finalMatrix);
    if (!__gluInvertMatrixd(finalMatrix, finalMatrix)) return(0);
    
    in[0]=winx;DEBUG_ASSERT(!isnan(in[0]));
    in[1]=winy;DEBUG_ASSERT(!isnan(in[1]));
    in[2]=winz;DEBUG_ASSERT(!isnan(in[2]));
    in[3]=1.0;
    
    /* Map x and y from window coordinates */
    in[0] = (in[0] - viewport[0]) / viewport[2];DEBUG_ASSERT(!isnan(in[0]));
    in[1] = (in[1] - viewport[1]) / viewport[3];DEBUG_ASSERT(!isnan(in[1]));
    
    /* Map to range -1 to 1 */
    in[0] = in[0] * 2 - 1;DEBUG_ASSERT(!isnan(in[0]));
    in[1] = in[1] * 2 - 1;DEBUG_ASSERT(!isnan(in[1]));
    in[2] = in[2] * 2 - 1;DEBUG_ASSERT(!isnan(in[2]));
    
    __gluMultMatrixVecd(finalMatrix, in, out);
    if (out[3] == 0.0) return(0);
    out[0] /= out[3];DEBUG_ASSERT(!isnan(in[0]));
    out[1] /= out[3];DEBUG_ASSERT(!isnan(in[1]));
    out[2] /= out[3];DEBUG_ASSERT(!isnan(in[2]));
    *objx = out[0];
    *objy = out[1];
    *objz = out[2];
    
    DEBUG_ASSERT(!isnan(*objx));
    DEBUG_ASSERT(!isnan(*objy));
    DEBUG_ASSERT(!isnan(*objz));
    return(1);
}

void MultiplyMatrices4by4OpenGL_FLOAT(float *result, float *matrix1, float *matrix2)
{
    result[0]=matrix1[0]*matrix2[0]+
    matrix1[4]*matrix2[1]+
    matrix1[8]*matrix2[2]+
    matrix1[12]*matrix2[3];
    result[4]=matrix1[0]*matrix2[4]+
    matrix1[4]*matrix2[5]+
    matrix1[8]*matrix2[6]+
    matrix1[12]*matrix2[7];
    result[8]=matrix1[0]*matrix2[8]+
    matrix1[4]*matrix2[9]+
    matrix1[8]*matrix2[10]+
    matrix1[12]*matrix2[11];
    result[12]=matrix1[0]*matrix2[12]+
    matrix1[4]*matrix2[13]+
    matrix1[8]*matrix2[14]+
    matrix1[12]*matrix2[15];
    result[1]=matrix1[1]*matrix2[0]+
    matrix1[5]*matrix2[1]+
    matrix1[9]*matrix2[2]+
    matrix1[13]*matrix2[3];
    result[5]=matrix1[1]*matrix2[4]+
    matrix1[5]*matrix2[5]+
    matrix1[9]*matrix2[6]+
    matrix1[13]*matrix2[7];
    result[9]=matrix1[1]*matrix2[8]+
    matrix1[5]*matrix2[9]+
    matrix1[9]*matrix2[10]+
    matrix1[13]*matrix2[11];
    result[13]=matrix1[1]*matrix2[12]+
    matrix1[5]*matrix2[13]+
    matrix1[9]*matrix2[14]+
    matrix1[13]*matrix2[15];
    result[2]=matrix1[2]*matrix2[0]+
    matrix1[6]*matrix2[1]+
    matrix1[10]*matrix2[2]+
    matrix1[14]*matrix2[3];
    result[6]=matrix1[2]*matrix2[4]+
    matrix1[6]*matrix2[5]+
    matrix1[10]*matrix2[6]+
    matrix1[14]*matrix2[7];
    result[10]=matrix1[2]*matrix2[8]+
    matrix1[6]*matrix2[9]+
    matrix1[10]*matrix2[10]+
    matrix1[14]*matrix2[11];
    result[14]=matrix1[2]*matrix2[12]+
    matrix1[6]*matrix2[13]+
    matrix1[10]*matrix2[14]+
    matrix1[14]*matrix2[15];
    result[3]=matrix1[3]*matrix2[0]+
    matrix1[7]*matrix2[1]+
    matrix1[11]*matrix2[2]+
    matrix1[15]*matrix2[3];
    result[7]=matrix1[3]*matrix2[4]+
    matrix1[7]*matrix2[5]+
    matrix1[11]*matrix2[6]+
    matrix1[15]*matrix2[7];
    result[11]=matrix1[3]*matrix2[8]+
    matrix1[7]*matrix2[9]+
    matrix1[11]*matrix2[10]+
    matrix1[15]*matrix2[11];
    result[15]=matrix1[3]*matrix2[12]+
    matrix1[7]*matrix2[13]+
    matrix1[11]*matrix2[14]+
    matrix1[15]*matrix2[15];
}

void MultiplyMatrixByVector4by4OpenGL_FLOAT(float *resultvector, const float *matrix, const float *pvector)
{
    resultvector[0]=matrix[0]*pvector[0]+matrix[4]*pvector[1]+matrix[8]*pvector[2]+matrix[12]*pvector[3];
    resultvector[1]=matrix[1]*pvector[0]+matrix[5]*pvector[1]+matrix[9]*pvector[2]+matrix[13]*pvector[3];
    resultvector[2]=matrix[2]*pvector[0]+matrix[6]*pvector[1]+matrix[10]*pvector[2]+matrix[14]*pvector[3];
    resultvector[3]=matrix[3]*pvector[0]+matrix[7]*pvector[1]+matrix[11]*pvector[2]+matrix[15]*pvector[3];
}

#define SWAP_ROWS_DOUBLE(a, b) { double *_tmp = a; (a)=(b); (b)=_tmp; }
#define SWAP_ROWS_FLOAT(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(c)*4+(r)]

//This code comes directly from GLU except that it is for float
int glhInvertMatrixf2(float *m, float *out)
{
    float wtmp[4][8];
    float m0, m1, m2, m3, s;
    float *r0, *r1, *r2, *r3;
    r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];
    r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1),
    r0[2] = MAT(m, 0, 2), r0[3] = MAT(m, 0, 3),
    r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
    r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1),
    r1[2] = MAT(m, 1, 2), r1[3] = MAT(m, 1, 3),
    r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
    r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1),
    r2[2] = MAT(m, 2, 2), r2[3] = MAT(m, 2, 3),
    r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
    r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1),
    r3[2] = MAT(m, 3, 2), r3[3] = MAT(m, 3, 3),
    r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
    /* choose pivot - or die */
    if (fabsf(r3[0]) > fabsf(r2[0]))
        SWAP_ROWS_FLOAT(r3, r2);
    if (fabsf(r2[0]) > fabsf(r1[0]))
        SWAP_ROWS_FLOAT(r2, r1);
    if (fabsf(r1[0]) > fabsf(r0[0]))
        SWAP_ROWS_FLOAT(r1, r0);
    if (0.0 == r0[0])
        return 0;
    /* eliminate first variable     */
    m1 = r1[0] / r0[0];
    m2 = r2[0] / r0[0];
    m3 = r3[0] / r0[0];
    s = r0[1];
    r1[1] -= m1 * s;
    r2[1] -= m2 * s;
    r3[1] -= m3 * s;
    s = r0[2];
    r1[2] -= m1 * s;
    r2[2] -= m2 * s;
    r3[2] -= m3 * s;
    s = r0[3];
    r1[3] -= m1 * s;
    r2[3] -= m2 * s;
    r3[3] -= m3 * s;
    s = r0[4];
    if (s != 0.0) {
        r1[4] -= m1 * s;
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r0[5];
    if (s != 0.0) {
        r1[5] -= m1 * s;
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r0[6];
    if (s != 0.0) {
        r1[6] -= m1 * s;
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r0[7];
    if (s != 0.0) {
        r1[7] -= m1 * s;
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }
    /* choose pivot - or die */
    if (fabsf(r3[1]) > fabsf(r2[1]))
        SWAP_ROWS_FLOAT(r3, r2);
    if (fabsf(r2[1]) > fabsf(r1[1]))
        SWAP_ROWS_FLOAT(r2, r1);
    if (0.0 == r1[1])
        return 0;
    /* eliminate second variable */
    m2 = r2[1] / r1[1];
    m3 = r3[1] / r1[1];
    r2[2] -= m2 * r1[2];
    r3[2] -= m3 * r1[2];
    r2[3] -= m2 * r1[3];
    r3[3] -= m3 * r1[3];
    s = r1[4];
    if (0.0 != s) {
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r1[5];
    if (0.0 != s) {
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r1[6];
    if (0.0 != s) {
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r1[7];
    if (0.0 != s) {
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }
    /* choose pivot - or die */
    if (fabsf(r3[2]) > fabsf(r2[2]))
        SWAP_ROWS_FLOAT(r3, r2);
    if (0.0 == r2[2])
        return 0;
    /* eliminate third variable */
    m3 = r3[2] / r2[2];
    r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
    r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];
    /* last check */
    if (0.0 == r3[3])
        return 0;
    s = 1.0 / r3[3];		/* now back substitute row 3 */
    r3[4] *= s;
    r3[5] *= s;
    r3[6] *= s;
    r3[7] *= s;
    m2 = r2[3];			/* now back substitute row 2 */
    s = 1.0 / r2[2];
    r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
    r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
    m1 = r1[3];
    r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
    r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
    m0 = r0[3];
    r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
    r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
    m1 = r1[2];			/* now back substitute row 1 */
    s = 1.0 / r1[1];
    r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
    r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
    m0 = r0[2];
    r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
    r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
    m0 = r0[1];			/* now back substitute row 0 */
    s = 1.0 / r0[0];
    r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
    r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
    MAT(out, 0, 0) = r0[4];
    MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6];
    MAT(out, 0, 3) = r0[7], MAT(out, 1, 0) = r1[4];
    MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6];
    MAT(out, 1, 3) = r1[7], MAT(out, 2, 0) = r2[4];
    MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6];
    MAT(out, 2, 3) = r2[7], MAT(out, 3, 0) = r3[4];
    MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6];
    MAT(out, 3, 3) = r3[7];
    return 1;
}
int glhUnProjectf(float winx, float winy, float winz, float *modelview, float *projection, int *viewport, float *objectCoordinate)
{
    //Transformation matrices
    float m[16], A[16];
    float in[4], out[4];
    //Calculation for inverting a matrix, compute projection x modelview
    //and store in A[16]
    MultiplyMatrices4by4OpenGL_FLOAT(A, projection, modelview);
    //Now compute the inverse of matrix A
    if(glhInvertMatrixf2(A, m)==0)
        return 0;
    //Transformation of normalized coordinates between -1 and 1
    in[0]=(winx-(float)viewport[0])/(float)viewport[2]*2.0-1.0;
    in[1]=(winy-(float)viewport[1])/(float)viewport[3]*2.0-1.0;
    in[2]=2.0*winz-1.0;
    in[3]=1.0;
    //Objects coordinates
    MultiplyMatrixByVector4by4OpenGL_FLOAT(out, m, in);
    if(out[3]==0.0)
        return 0;
    out[3]=1.0/out[3];
    objectCoordinate[0]=out[0]*out[3];
    objectCoordinate[1]=out[1]*out[3];
    objectCoordinate[2]=out[2]*out[3];
    return 1;
}


int glhProjectf(float objx, float objy, float objz, float *modelview, float *projection, int *viewport, float *windowCoordinate)
{
    //Transformation vectors
    float fTempo[8];
    //Modelview transform
    fTempo[0]=modelview[0]*objx+modelview[4]*objy+modelview[8]*objz+modelview[12];  //w is always 1
    fTempo[1]=modelview[1]*objx+modelview[5]*objy+modelview[9]*objz+modelview[13];
    fTempo[2]=modelview[2]*objx+modelview[6]*objy+modelview[10]*objz+modelview[14];
    fTempo[3]=modelview[3]*objx+modelview[7]*objy+modelview[11]*objz+modelview[15];
    //Projection transform, the final row of projection matrix is always [0 0 -1 0]
    //so we optimize for that.
    fTempo[4]=projection[0]*fTempo[0]+projection[4]*fTempo[1]+projection[8]*fTempo[2]+projection[12]*fTempo[3];
    fTempo[5]=projection[1]*fTempo[0]+projection[5]*fTempo[1]+projection[9]*fTempo[2]+projection[13]*fTempo[3];
    fTempo[6]=projection[2]*fTempo[0]+projection[6]*fTempo[1]+projection[10]*fTempo[2]+projection[14]*fTempo[3];
    fTempo[7]=-fTempo[2];
    //The result normalizes between -1 and 1
    if(fTempo[7]==0.0)	//The w value
        return 0;
    fTempo[7]=1.0/fTempo[7];
    //Perspective division
    fTempo[4]*=fTempo[7];
    fTempo[5]*=fTempo[7];
    fTempo[6]*=fTempo[7];
    //Window coordinates
    //Map x, y to range 0-1
    windowCoordinate[0]=(fTempo[4]*0.5+0.5)*viewport[2]+viewport[0];
    windowCoordinate[1]=(fTempo[5]*0.5+0.5)*viewport[3]+viewport[1];
    //This is only correct when glDepthRange(0.0, 1.0)
    windowCoordinate[2]=(1.0+fTempo[6])*0.5;	//Between 0 and 1
    return 1;
}

namespace njli
{
    struct OcclusionBuffer
    {
        struct WriteOCL
        {
            static inline bool Process(btScalar& q,btScalar v) { if(q<v) q=v;return(false); }
        };
        struct QueryOCL
        {
            static inline bool Process(btScalar& q,btScalar v) { return(q<=v); }
        };
        bool initialized;
        btAlignedObjectArray<btScalar> buffer;
        s32 sizes[2];
        btScalar scales[2];
        btScalar offsets[2];
        btScalar wtrs[16];
        btVector3 eye;
        btVector3 neardist;
        btScalar ocarea;
        btScalar qrarea;
        Camera *m_Camera;
        
        void setCamera(Camera *camera)
        {
            m_Camera = camera;
        }
        OcclusionBuffer():
        m_Camera(NULL)
        {
            initialized=false;
            neardist=btVector3(2,2,2);
            ocarea=(btScalar)0;
            qrarea=(btScalar)0;
        }
        void setup(s32 w,s32 h)
        {
            initialized=true;
            sizes[0]=w;
            sizes[1]=h;
            scales[0]=w/2;
            scales[1]=h/2;
            offsets[0]=scales[0]+0.5;
            offsets[1]=scales[1]+0.5;
            
            clear();
        }
        void clear()
        {
            buffer.resize(0);
            buffer.resize(sizes[0]*sizes[1],0);
        }
        void initialize()
        {
            if(!initialized)
            {
                setup(128,128);
            }
            DEBUG_ASSERT(m_Camera);
            DEBUG_ASSERT(m_Camera->getParent());
            
            btTransform cameraLocationMatrix(m_Camera->getParent()->getWorldTransform().inverse());
            btTransform projectionMatrix(m_Camera->getProjection());
            btTransform mvp(projectionMatrix * cameraLocationMatrix);
            mvp.getOpenGLMatrix(wtrs);
            clear();
        }
        btVector4	transform(const btVector3& x) const
        {
            btVector4	t;
            t[0]	=	x[0]*wtrs[0]+x[1]*wtrs[4]+x[2]*wtrs[8]+wtrs[12];
            t[1]	=	x[0]*wtrs[1]+x[1]*wtrs[5]+x[2]*wtrs[9]+wtrs[13];
            t[2]	=	x[0]*wtrs[2]+x[1]*wtrs[6]+x[2]*wtrs[10]+wtrs[14];
            t[3]	=	x[0]*wtrs[3]+x[1]*wtrs[7]+x[2]*wtrs[11]+wtrs[15];
            return(t);
        }
        static bool	project(btVector4* p,s32 n)
        {
            for(s32 i=0;i<n;++i)
            {
                p[i][2]=1/p[i][3];
                p[i][0]*=p[i][2];
                p[i][1]*=p[i][2];
            }
            return(true);
        }
        template <const s32 NP>
        static s32	clip(const btVector4* pi,btVector4* po)
        {
            btScalar	s[NP];
            s32			m=0;
            for(s32 i=0;i<NP;++i)
            {
                s[i]=pi[i][2]+pi[i][3];
                if(s[i]<0) m+=1<<i;
            }
            if(m==((1<<NP)-1)) return(0);
            if(m!=0)
            {
                s32 n=0;
                for(s32 i=NP-1,j=0;j<NP;i=j++)
                {
                    const btVector4&	a=pi[i];
                    const btVector4&	b=pi[j];
                    const btScalar		t=s[i]/(a[3]+a[2]-b[3]-b[2]);
                    if((t>0)&&(t<1))
                    {
                        po[n][0]	=	a[0]+(b[0]-a[0])*t;
                        po[n][1]	=	a[1]+(b[1]-a[1])*t;
                        po[n][2]	=	a[2]+(b[2]-a[2])*t;
                        po[n][3]	=	a[3]+(b[3]-a[3])*t;
                        ++n;
                    }
                    if(s[j]>0) po[n++]=b;
                }
                return(n);
            }
            for(s32 i=0;i<NP;++i) po[i]=pi[i];
            return(NP);
        }
        template <typename POLICY>
        inline bool	draw(	const btVector4& a,
                         const btVector4& b,
                         const btVector4& c,
                         const btScalar minarea)
        {
            const btScalar		a2=(b-a).cross(c-a)[2];
            if(a2>0)
            {
                if(a2<minarea)	return(true);
                const s32		x[]={	(s32)(a.x()*scales[0]+offsets[0]),
                    (s32)(b.x()*scales[0]+offsets[0]),
                    (s32)(c.x()*scales[0]+offsets[0])};
                const s32		y[]={	(s32)(a.y()*scales[1]+offsets[1]),
                    (s32)(b.y()*scales[1]+offsets[1]),
                    (s32)(c.y()*scales[1]+offsets[1])};
                const btScalar	z[]={	a.z(),b.z(),c.z()};
                const s32		mix=btMax(0,btMin(x[0],btMin(x[1],x[2])));
                const s32		mxx=btMin(sizes[0],1+btMax(x[0],btMax(x[1],x[2])));
                const s32		miy=btMax(0,btMin(y[0],btMin(y[1],y[2])));
                const s32		mxy=btMin(sizes[1],1+btMax(y[0],btMax(y[1],y[2])));
                const s32		width=mxx-mix;
                const s32		height=mxy-miy;
                if((width*height)>0)
                {
                    const s32		dx[]={	y[0]-y[1],
                        y[1]-y[2],
                        y[2]-y[0]};
                    const s32		dy[]={	x[1]-x[0]-dx[0]*width,
                        x[2]-x[1]-dx[1]*width,
                        x[0]-x[2]-dx[2]*width};
                    const s32		a=x[2]*y[0]+x[0]*y[1]-x[2]*y[1]-x[0]*y[2]+x[1]*y[2]-x[1]*y[0];
                    const btScalar	ia=1/(btScalar)a;
                    const btScalar	dzx=ia*(y[2]*(z[1]-z[0])+y[1]*(z[0]-z[2])+y[0]*(z[2]-z[1]));
                    const btScalar	dzy=ia*(x[2]*(z[0]-z[1])+x[0]*(z[1]-z[2])+x[1]*(z[2]-z[0]))-(dzx*width);
                    s32				c[]={	miy*x[1]+mix*y[0]-x[1]*y[0]-mix*y[1]+x[0]*y[1]-miy*x[0],
                        miy*x[2]+mix*y[1]-x[2]*y[1]-mix*y[2]+x[1]*y[2]-miy*x[1],
                        miy*x[0]+mix*y[2]-x[0]*y[2]-mix*y[0]+x[2]*y[0]-miy*x[2]};
                    btScalar		v=ia*((z[2]*c[0])+(z[0]*c[1])+(z[1]*c[2]));
                    btScalar*		scan=&buffer[miy*sizes[1]];
                    for(s32 iy=miy;iy<mxy;++iy)
                    {
                        for(s32 ix=mix;ix<mxx;++ix)
                        {
                            if((c[0]>=0)&&(c[1]>=0)&&(c[2]>=0))
                            {
                                if(POLICY::Process(scan[ix],v)) return(true);
                            }
                            c[0]+=dx[0];c[1]+=dx[1];c[2]+=dx[2];v+=dzx;
                        }
                        c[0]+=dy[0];c[1]+=dy[1];c[2]+=dy[2];v+=dzy;
                        scan+=sizes[0];
                    }
                }
            }
            return(false);
        }
        template <const s32 NP,typename POLICY>
        inline bool	clipDraw(	const btVector4* p,
                             btScalar minarea)
        {
            btVector4	o[NP*2];
            const s32	n=clip<NP>(p,o);
            bool		earlyexit=false;
            project(o,n);
            for(s32 i=2;i<n;++i)
            {
                earlyexit|=draw<POLICY>(o[0],o[i-1],o[i],minarea);
            }
            return(earlyexit);
        }
        void appendOccluder(	const btVector3& a,
                            const btVector3& b,
                            const btVector3& c)
        {
            const btVector4	p[]={transform(a),transform(b),transform(c)};
            clipDraw<3,WriteOCL>(p,ocarea);
        }
        void appendOccluder(	const btVector3& a,
                            const btVector3& b,
                            const btVector3& c,
                            const btVector3& d)
        {
            const btVector4	p[]={transform(a),transform(b),transform(c),transform(d)};
            clipDraw<4,WriteOCL>(p,ocarea);
        }
        void appendOccluder( const btVector3& c,
                            const btVector3& e)
        {
            const btVector4	x[]={	transform(btVector3(c[0]-e[0],c[1]-e[1],c[2]-e[2])),
                transform(btVector3(c[0]+e[0],c[1]-e[1],c[2]-e[2])),
                transform(btVector3(c[0]+e[0],c[1]+e[1],c[2]-e[2])),
                transform(btVector3(c[0]-e[0],c[1]+e[1],c[2]-e[2])),
                transform(btVector3(c[0]-e[0],c[1]-e[1],c[2]+e[2])),
                transform(btVector3(c[0]+e[0],c[1]-e[1],c[2]+e[2])),
                transform(btVector3(c[0]+e[0],c[1]+e[1],c[2]+e[2])),
                transform(btVector3(c[0]-e[0],c[1]+e[1],c[2]+e[2]))};
            static const s32	d[]={	1,0,3,2,
                4,5,6,7,
                4,7,3,0,
                6,5,1,2,
                7,6,2,3,
                5,4,0,1};
            for(u32 i=0;i<(sizeof(d)/sizeof(d[0]));)
            {
                const btVector4	p[]={	x[d[i++]],
                    x[d[i++]],
                    x[d[i++]],
                    x[d[i++]]};
                clipDraw<4,WriteOCL>(p,ocarea);
            }
        }
        void appendOccluder( const btVector3& occluderInnerBoxCollisionShapeHalfExtent,
                            const btTransform& collisionObjectWorldTransform
                            )   {
            const btVector3 c(collisionObjectWorldTransform.getOrigin());
            const btVector3& e = occluderInnerBoxCollisionShapeHalfExtent;
            const btMatrix3x3& basis = collisionObjectWorldTransform.getBasis();
            const btVector4   x[]={   transform(c+basis*btVector3(-e[0],-e[1],-e[2])),
                transform(c+basis*btVector3(+e[0],-e[1],-e[2])),
                transform(c+basis*btVector3(+e[0],+e[1],-e[2])),
                transform(c+basis*btVector3(-e[0],+e[1],-e[2])),
                transform(c+basis*btVector3(-e[0],-e[1],+e[2])),
                transform(c+basis*btVector3(+e[0],-e[1],+e[2])),
                transform(c+basis*btVector3(+e[0],+e[1],+e[2])),
                transform(c+basis*btVector3(-e[0],+e[1],+e[2]))};
            static const s32   d[]={   1,0,3,2,
                4,5,6,7,
                4,7,3,0,
                6,5,1,2,
                7,6,2,3,
                5,4,0,1};
            for(u32 i=0;i<(sizeof(d)/sizeof(d[0]));)
            {
                const btVector4   p[]={   x[d[i++]],
                    x[d[i++]],
                    x[d[i++]],
                    x[d[i++]]};
                clipDraw<4,WriteOCL>(p,ocarea);
            }
        }
        inline bool	queryOccluder(	const btVector3& a,
                                  const btVector3& b,
                                  const btVector3& c)
        {
            const btVector4	p[]={transform(a),transform(b),transform(c)};
            return(clipDraw<3,QueryOCL>(p,qrarea));
        }
        inline bool	queryOccluder(	const btVector3& a,
                                  const btVector3& b,
                                  const btVector3& c,
                                  const btVector3& d)
        {
            const btVector4	p[]={transform(a),transform(b),transform(c),transform(d)};
            return(clipDraw<4,QueryOCL>(p,qrarea));
        }
        inline bool	queryOccluder(	const btVector3& c,
                                  const btVector3& e)
        {
            const btVector4	x[]={	transform(btVector3(c[0]-e[0],c[1]-e[1],c[2]-e[2])),
                transform(btVector3(c[0]+e[0],c[1]-e[1],c[2]-e[2])),
                transform(btVector3(c[0]+e[0],c[1]+e[1],c[2]-e[2])),
                transform(btVector3(c[0]-e[0],c[1]+e[1],c[2]-e[2])),
                transform(btVector3(c[0]-e[0],c[1]-e[1],c[2]+e[2])),
                transform(btVector3(c[0]+e[0],c[1]-e[1],c[2]+e[2])),
                transform(btVector3(c[0]+e[0],c[1]+e[1],c[2]+e[2])),
                transform(btVector3(c[0]-e[0],c[1]+e[1],c[2]+e[2]))};
            for(s32 i=0;i<8;++i)
            {
                if((x[i][2]+x[i][3])<=0) return(true);
            }
            static const s32	d[]={	1,0,3,2,
                4,5,6,7,
                4,7,3,0,
                6,5,1,2,
                7,6,2,3,
                5,4,0,1};
            for(u32 i=0;i<(sizeof(d)/sizeof(d[0]));)
            {
                const btVector4	p[]={	x[d[i++]],
                    x[d[i++]],
                    x[d[i++]],
                    x[d[i++]]};
                if(clipDraw<4,QueryOCL>(p,qrarea)) return(true);
            }
            return(false);
        }
        
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    class Node;
    struct OcclusionBuffer;
    
    
    class	SceneRenderer : public btDbvt::ICollide
    {
        typedef std::pair<btScalar, Node*> Pair;
        typedef std::multimap<btScalar, Node*> MultiMap;
        typedef btAlignedObjectArray<Node*> Array;
        
        s32 m_drawn;
        OcclusionBuffer* m_ocb;
        Camera *m_Camera;
        
        MultiMap m_TranslucentEntities;
        Array m_OpaqueEntities;
        
        SceneRenderer();
        SceneRenderer(const SceneRenderer &copy);
        SceneRenderer &operator=(const SceneRenderer &rhs);
    public:
        SceneRenderer(Camera *camera);
        
        bool Descent(const btDbvtNode* node);
        void Process(const btDbvtNode* node,btScalar depth);
        void Process(const btDbvtNode* leaf);
        
        virtual SIMD_FORCE_INLINE OcclusionBuffer*	getOcclusionBuffer()
        {
            btAssert(m_ocb);
            return m_ocb;
        }
        virtual SIMD_FORCE_INLINE const OcclusionBuffer* getOcclusionBuffer() const
        {
            btAssert(m_ocb);
            return m_ocb;
        }
        virtual SIMD_FORCE_INLINE void	setOcclusionBuffer(OcclusionBuffer* ocb)
        {
            m_ocb = ocb;
        }
        
        s32 getNumObjectsDrawn()const;
        
        void render();
    };
    
    SceneRenderer::SceneRenderer(Camera *camera) :
    m_drawn(0),
    m_ocb(NULL),
    m_Camera(camera)
    {
        DEBUG_ASSERT(m_Camera);
    }
    bool SceneRenderer::Descent(const btDbvtNode* node)
    {
        if(m_ocb)
            return (m_ocb->queryOccluder(node->volume.Center(),node->volume.Extents()));
        return false;
    }
    void SceneRenderer::Process(const btDbvtNode* node,btScalar depth)
    {
        Process(node);
    }
    void SceneRenderer::Process(const btDbvtNode* leaf)
    {
        DEBUG_ASSERT(m_Camera);
        DEBUG_ASSERT(m_Camera->getParent());
        
        btBroadphaseProxy *proxy = static_cast<btBroadphaseProxy*>(leaf->data);
        btCollisionObject *co = static_cast<btCollisionObject*>(proxy->m_clientObject);
        Node *entity = static_cast<Node*>(co->getUserPointer());
        
        
        if(entity->getOpacity() != 1.0)
        {
            btScalar distance = btDistance(entity->getOrigin(), m_Camera->getParent()->getOrigin());
            
            m_TranslucentEntities.insert(Pair(distance, entity));
        }
        else
        {
            m_OpaqueEntities.push_back(entity);
        }
        
        if(m_ocb)
        {
            static btVector3 aabbMin;
            static btVector3 aabbMax;
            co->getCollisionShape()->getAabb(btTransform::getIdentity(),aabbMin,aabbMax);   // Actually here I should get the MINIMAL aabb that can be nested INSIDE the shape (ie. only btBoxShapes work)
            m_ocb->appendOccluder((aabbMax-aabbMin)*btScalar(0.5f),co->getWorldTransform());   // Note that only a btVector3 (the inner box shape half extent) seems to be needed...
        }
    }
    
    s32 SceneRenderer::getNumObjectsDrawn()const
    {
        return m_drawn;
    }
    
    void SceneRenderer::render()
    {
//        DEBUG_ASSERT(m_Camera);
//        
//        m_drawn = m_TranslucentEntities.size() + m_OpaqueEntities.size();
//        
//        for (MultiMap::reverse_iterator iter = m_TranslucentEntities.rbegin();
//             iter != m_TranslucentEntities.rend();
//             ++iter)
//        {
//            iter->second->render(m_Camera);
//        }
//        m_TranslucentEntities.clear();
//        
//        for(s32 i = 0; i < m_OpaqueEntities.size(); ++i)
//        {
//            m_OpaqueEntities[i]->render(m_Camera);
//        }
//        m_OpaqueEntities.clear();
    }
    
    Camera::Camera():
    AbstractFactoryObject(this),
//    m_Name("MyCamera"),
    m_Near(0.1f),
    m_Far(1000.0f),
    m_Fov(45.0f),
    m_Orthographic(false),
    m_RenderCategory(JLI_BIT_CATEGORY_NONE),
    m_OcclusionBuffer(new OcclusionBuffer()),
    m_SceneRenderer(new SceneRenderer(this)),
    m_projectionMatrix(new btTransform(btTransform::getIdentity())),
//    m_PropertyChanged(true),
    m_ProjectionMatrixArray(new f32[16]),
    m_ModelViewMatrixArray(new f32[16]),
    m_ViewPort(new s32[4]),
    m_ModelMatrix(new btScalar[16]),
    m_ProjectionMatrix(new btScalar[16])
    {
        
    }
    
    Camera::Camera(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
//    m_Name("MyCamera"),
    m_Near(0.1f),
    m_Far(1000.0f),
    m_Fov(45.0f),
    m_Orthographic(false),
    m_RenderCategory(JLI_BIT_CATEGORY_NONE),
    m_OcclusionBuffer(new OcclusionBuffer()),
    m_SceneRenderer(new SceneRenderer(this)),
    m_projectionMatrix(new btTransform(btTransform::getIdentity())),
//    m_PropertyChanged(true),
    m_ProjectionMatrixArray(new f32[16]),
    m_ModelViewMatrixArray(new f32[16]),
    m_ViewPort(new s32[4]),
    m_ModelMatrix(new btScalar[16]),
    m_ProjectionMatrix(new btScalar[16])
    {
        
    }
    
    Camera::Camera(const Camera &copy):
    AbstractFactoryObject(this),
    m_Near(copy.getZNear()),
    m_Far(copy.getZFar()),
    m_Fov(copy.getFov()),
    m_Orthographic(copy.isOrthographic()),
    m_RenderCategory(copy.getRenderCategory()),
    m_OcclusionBuffer(new OcclusionBuffer()),
    m_SceneRenderer(new SceneRenderer(this)),
    m_projectionMatrix(new btTransform(btTransform::getIdentity())),
//    m_PropertyChanged(true),
    m_ProjectionMatrixArray(new f32[16]),
    m_ModelViewMatrixArray(new f32[16]),
    m_ViewPort(new s32[4]),
    m_ModelMatrix(new btScalar[16]),
    m_ProjectionMatrix(new btScalar[16])
    {
        //TODO: Implement...
    }
    
    Camera::~Camera()
    {
        delete [] m_ProjectionMatrix;m_ProjectionMatrix=NULL;
        delete [] m_ModelMatrix;m_ModelMatrix=NULL;
        delete [] m_ViewPort;m_ViewPort=NULL;
        
        delete [] m_ModelViewMatrixArray;m_ModelViewMatrixArray=NULL;
        delete [] m_ProjectionMatrixArray;m_ProjectionMatrixArray=NULL;
        delete m_projectionMatrix;m_projectionMatrix=NULL;
        delete m_SceneRenderer;m_SceneRenderer=NULL;
        delete m_OcclusionBuffer;m_OcclusionBuffer=NULL;
    }
    
    Camera &Camera::operator=(const Camera &rhs)
    {
        if(this != &rhs)
        {
            m_Near = rhs.getZNear();
            m_Far = rhs.getZFar();
            m_Fov = rhs.getFov();
            m_Orthographic = rhs.isOrthographic();
            m_RenderCategory = rhs.getRenderCategory();
            //TODO: Implement...
        }
        return *this;
    }
    
    s32	Camera::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Camera::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Camera::getClassName()const
    {
        return "Camera";
    }
    
    s32 Camera::getType()const
    {
        return Camera::type();
    }
    
    Camera::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Camera **Camera::createArray(const u32 size)
    {
        return (Camera**)World::getInstance()->getWorldFactory()->createArray(Camera::type(), size);
    }
    
    void Camera::destroyArray(Camera **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Camera *Camera::create()
    {
        return dynamic_cast<Camera*>(World::getInstance()->getWorldFactory()->create(Camera::type()));
    }
    
    Camera *Camera::create(const CameraBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Camera*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Camera *Camera::clone(const Camera &object)
    {
        return dynamic_cast<Camera*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Camera *Camera::copy(const Camera &object)
    {
        return dynamic_cast<Camera*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Camera::destroy(Camera *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Camera::load(Camera &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
        {
            // stack now contains: -1 => value; -2 => key; -3 => table
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                Camera::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
//                    swig_lua_userdata *usr;
//                    swig_type_info *type;
//                    assert(lua_isuserdata(L,index));
//                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
//                    type = usr->type;
//                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
//                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 Camera::type()
    {
        return JLI_OBJECT_TYPE_Camera;
    }
    
    
    void Camera::setZNear(const f32 val)
    {
        m_Near = val;
//        enablePropertyChanged();
        if(m_Orthographic)
        {
            *m_projectionMatrix = makeOrtho(0, njli::World::getInstance()->getViewportDimensions().x(),
                                            0, njli::World::getInstance()->getViewportDimensions().y(),
                                            getZNear(), getZFar());
            
            getProjection().getOpenGLMatrix(m_ProjectionMatrixArray);
        }
        else
        {
            *m_projectionMatrix = makeFrustum(m_ProjectionMatrixArray, getFov(), njli::World::getInstance()->getAspectRatio(), getZNear(), getZFar());
        }
    }
    
    f32 Camera::getZNear()const
    {
        return m_Near;
    }
    
    void Camera::setZFar(const f32 val)
    {
        m_Far = val;
//        enablePropertyChanged();
        if(m_Orthographic)
        {
            *m_projectionMatrix = makeOrtho(0, njli::World::getInstance()->getViewportDimensions().x(),
                                            0, njli::World::getInstance()->getViewportDimensions().y(),
                                            getZNear(), getZFar());
            
            getProjection().getOpenGLMatrix(m_ProjectionMatrixArray);
        }
        else
        {
            *m_projectionMatrix = makeFrustum(m_ProjectionMatrixArray, getFov(), njli::World::getInstance()->getAspectRatio(), getZNear(), getZFar());
        }
    }
    
    f32 Camera::getZFar()const
    {
        return m_Far;
    }
    
    void Camera::setFov(const f32 val)
    {
        m_Fov = fmod(fabsf(val), 360.0f);
//        enablePropertyChanged();
        if(m_Orthographic)
        {
            *m_projectionMatrix = makeOrtho(0, njli::World::getInstance()->getViewportDimensions().x(),
                                            0, njli::World::getInstance()->getViewportDimensions().y(),
                                            getZNear(), getZFar());
            
            getProjection().getOpenGLMatrix(m_ProjectionMatrixArray);
        }
        else
        {
            *m_projectionMatrix = makeFrustum(m_ProjectionMatrixArray, getFov(), njli::World::getInstance()->getAspectRatio(), getZNear(), getZFar());
        }
    }
    
    f32 Camera::getFov()const
    {
        return m_Fov;
    }
    
    void Camera::enableOrthographic(const bool enable, const f32 near, const f32 far)
    {
        m_Orthographic = enable;
        
        if(m_Orthographic)
        {
            m_Near = near;
            m_Far = far;
            
            *m_projectionMatrix = makeOrtho(0, njli::World::getInstance()->getViewportDimensions().x(),
                                            0, njli::World::getInstance()->getViewportDimensions().y(),
                                            getZNear(), getZFar());
            
            getProjection().getOpenGLMatrix(m_ProjectionMatrixArray);
        }
        else
        {
            m_Near = 0.1f;
            m_Far = 1000.0f;
            
            *m_projectionMatrix = makeFrustum(m_ProjectionMatrixArray, getFov(), njli::World::getInstance()->getAspectRatio(), getZNear(), getZFar());
        }
        
//        enablePropertyChanged(enable != m_Orthographic);
//        if(isOrthographic())
//        {
////            setZFar(-1.0f);
////            setZNear(1.0f);
//            
//            setZFar(-1000.0f);
//            setZNear(1000.0f);
//            
//        }
        if(getParent())
            getParent()->setTransform(btTransform::getIdentity());
        if(getParent())
            getParent()->setOrientation(btQuaternion::getIdentity());
    }
    
    bool Camera::isOrthographic()const
    {
        return m_Orthographic;
    }
    
    void Camera::setRenderCategory(const njliBitCategories category)
    {
        m_RenderCategory = category;
    }
    
    njliBitCategories Camera::getRenderCategory()const
    {
        return m_RenderCategory;
    }
    
    void Camera::addRenderCategory(const njliBitCategories category)
    {
        m_RenderCategory = (njliBitCategories)On(m_RenderCategory, category);
    }
    
    void Camera::removeRenderCategory(const njliBitCategories category)
    {
        m_RenderCategory = (njliBitCategories)Off(m_RenderCategory, category);
    }
    
    bool Camera::hasRenderCategory(const njliBitCategories category)
    {
        return IsOn(m_RenderCategory, category);
    }
    
    btVector3 Camera::unProject(const btVector2 &windowPosition)const
    {
        njli::World::getInstance()->getViewPort(m_ViewPort);
        
        
        btTransform modMatrix(getParent()->getWorldTransform());
        modMatrix.setRotation(getParent()->getOrientation());
        modMatrix.getOpenGLMatrix(m_ModelMatrix);
        
        f32 wx0, wy0, wz0;
        getProjection().getOpenGLMatrix(m_ProjectionMatrix);
        
        gluUnProject((f32)windowPosition.x(),
                     (f32)windowPosition.y(),
                     0.0,
                     m_ModelMatrix,
                     m_ProjectionMatrix,
                     m_ViewPort,
                     &wx0,
                     &wy0,
                     &wz0);
        return btVector3(wx0, wy0, wz0);
    }
    
    btVector2 Camera::project(const btVector3 &objectPosition)const
    {
        njli::World::getInstance()->getViewPort(m_ViewPort);
        
        btTransform modMatrix(getParent()->getWorldTransform());
        modMatrix.setRotation(getParent()->getOrientation());
        modMatrix.getOpenGLMatrix(m_ModelMatrix);
        
        f32 wx0, wy0, wz0;wx0=wy0=wz0=0;
        getProjection().getOpenGLMatrix(m_ProjectionMatrix);
        
        gluProject(objectPosition.x(),
                   objectPosition.y(),
                   objectPosition.z(),
                   m_ModelMatrix,
                   m_ProjectionMatrix,
                   m_ViewPort,
                   &wx0,
                   &wy0,
                   &wz0);
        return btVector2(wx0, wy0);
    }
    
    void Camera::getTouchRay(const btVector2 &windowPosition, btVector3 &from, btVector3 &to)
    {
        if(m_Orthographic)
        {
            from = unProject(windowPosition);
            to = from;
            to.setZ(to.z() * getZFar());
        }
        else
        {
            njli::World::getInstance()->getViewPort(m_ViewPort);
            
            
            btTransform modMatrix(getParent()->getWorldTransform());
            modMatrix.setRotation(getParent()->getOrientation());
            modMatrix.getOpenGLMatrix(m_ModelMatrix);
            
            
            getProjection().getOpenGLMatrix(m_ProjectionMatrix);
            
            f32 wx0, wy0, wz0;
            gluUnProject((f32)windowPosition.x(),
                         (f32)windowPosition.y(),
                         0.0,
                         m_ModelMatrix,
                         m_ProjectionMatrix,
                         m_ViewPort,
                         &wx0,
                         &wy0,
                         &wz0);
            from = btVector3(wx0, wy0, wz0);
            
            f32 wx1, wy1, wz1;
            gluUnProject((f32)windowPosition.x(),
                         (f32)windowPosition.y(),
                         1.0,
                         m_ModelMatrix,
                         m_ProjectionMatrix,
                         m_ViewPort,
                         &wx1,
                         &wy1,
                         &wz1);
            to = btVector3(wx1, wy1, wz1);
            to *= getZFar();
        }
        
    }
    
    btVector3 Camera::getForwardVector()const
    {
        DEBUG_ASSERT(getParent());
        
        btVector3 lookAt(0.0f, 0.0f, 1.0f);
        lookAt = quatRotate(getParent()->getOrientation(), lookAt);
        return lookAt;
    }
    
    btVector3 Camera::getUpVector()const
    {
        DEBUG_ASSERT(getParent());
        
        btVector3 up(0.0f, 1.0f, 0.0f);
        up = quatRotate(getParent()->getOrientation(), up);
        return up;
    }
    
    btVector3 Camera::getSideVector()const
    {
        return getForwardVector().cross(getUpVector());
    }
    
    void Camera::lookAt(const btVector3 &target, const btVector3 &up)
    {
        btTransform _btTransform(makeLookAt(getParent()->getOrigin().getX(),
                                            getParent()->getOrigin().getY(),
                                            getParent()->getOrigin().getZ(),
                                            target.getX(),
                                            target.getY(),
                                            target.getZ(),
                                            up.getX(),
                                            up.getY(),
                                            up.getZ()));
        btQuaternion q;
        _btTransform.inverse().getBasis().getRotation(q);
        
        getParent()->setOrientation(q);
    }
    
    bool Camera::rayTestClosest(const btVector2 &screenPosition,
                                PhysicsRayContact &rayContact,
                                njliBitCategories collisionGroup,
                                njliBitCategories collisionMask)const
    {
        return getParent()->rayTestClosest(screenPosition, rayContact, collisionGroup, collisionMask);
    }
    
    bool Camera::rayTestAll(const btVector2 &screenPosition,
                            btAlignedObjectArray<PhysicsRayContact*> &rayContacts,
                            s32 &numContacts,
                            njliBitCategories collisionGroup,
                            njliBitCategories collisionMask)const
    {
        return getParent()->rayTestAll(screenPosition, rayContacts, numContacts, collisionGroup, collisionMask);
    }
    
    void Camera::cull(btDbvtBroadphase*	pbp)
    {
        render(pbp->m_sets[1].m_root, pbp->m_sets[0].m_root, getForwardVector());
    }
    
    Node *Camera::getParent()
    {
//        DEBUG_ASSERT(dynamic_cast<Node*>(AbstractDecorator::getParent()));
        return dynamic_cast<Node*>(AbstractDecorator::getParent());
    }
    
    const Node *Camera::getParent()const
    {
//        DEBUG_ASSERT(dynamic_cast<const Node*>(AbstractDecorator::getParent()));
        return dynamic_cast<const Node*>(AbstractDecorator::getParent());
    }
    
//    void Camera::updateProjection()
//    {
////        if(m_Orthographic)
////        {
////            m_Near = 1000.0f;
////            m_Far = -1000.0f;
////            
////            *m_projectionMatrix = makeOrtho(0, njli::World::getInstance()->getViewportDimensions().x(),
////                                            0, njli::World::getInstance()->getViewportDimensions().y(),
////                                            getZNear(), getZFar());
////            
////            getProjection().getOpenGLMatrix(m_ProjectionMatrixArray);
////        }
////        else
////        {
////            m_Near = 0.1f;
////            m_Far = 1000.0f;
////            
////            *m_projectionMatrix = makeFrustum(m_ProjectionMatrixArray, getFov(), njli::World::getInstance()->getAspectRatio(), getZNear(), getZFar());
////        }
//        
//        
//        
//        
//        
//        
//        
//        
////        if(isPropertyChanged())
////        {
////            if(m_Orthographic)
////            {
////                *m_projectionMatrix = makeOrtho(0, njli::World::getInstance()->getViewportDimensions().x(),
////                                                0, njli::World::getInstance()->getViewportDimensions().y(),
////                                                getZNear(), getZFar());
////                
////                getProjection().getOpenGLMatrix(m_ProjectionMatrixArray);
////            }
////            else
////            {
////                *m_projectionMatrix = makeFrustum(m_ProjectionMatrixArray, getFov(), njli::World::getInstance()->getAspectRatio(), getZNear(), getZFar());
////            }
////        }
//    }
    
    void Camera::updateViewSize()
    {
        if(m_Orthographic)
        {
            *m_projectionMatrix = makeOrtho(0, njli::World::getInstance()->getViewportDimensions().x(),
                                            0, njli::World::getInstance()->getViewportDimensions().y(),
                                            getZNear(), getZFar());
            
            getProjection().getOpenGLMatrix(m_ProjectionMatrixArray);
        }
        else
        {
            *m_projectionMatrix = makeFrustum(m_ProjectionMatrixArray, getFov(), njli::World::getInstance()->getAspectRatio(), getZNear(), getZFar());
        }
    }
    
    const btTransform &Camera::getProjection()const
    {
        return *m_projectionMatrix;
    }
    
    const f32 *Camera::getProjectionMatrixArray()
    {
//        static f32 p[16];
//        getProjection().getOpenGLMatrix(p);//m_ProjectionMatrixArray);
        f32 p[16];
        memcpy(p, m_ProjectionMatrixArray, sizeof(p));
        return m_ProjectionMatrixArray;
    }
    
    
//    const f32 *Camera::getModelViewMatrixArray()
//    {
//        if(getParent())
//            getParent()->getWorldTransform().getOpenGLMatrix(m_ModelViewMatrixArray);
//        else
//            btTransform::getIdentity().getOpenGLMatrix(m_ModelViewMatrixArray);
//        
//        return m_ModelViewMatrixArray;
//    }
    
    btTransform Camera::getModelView() const
    {
        if(getParent())
            return getParent()->getWorldTransform();
        return btTransform::getIdentity();
    }
    
    void Camera::getViewBounds(f32 &left, f32 &right, f32 &bottom, f32 &top, f32 &farLeft, f32 &farRight, f32 &farBottom, f32 &farTop)const
    {
        btScalar planesFraction = getZFar() / getZNear();
        
        if(m_Orthographic)
        {
            top = njli::World::getInstance()->getViewportDimensions().y();
            bottom = 0;
            
            left = 0;
            right = njli::World::getInstance()->getViewportDimensions().x();
            
            planesFraction = 1.0f;
            
        }
        else
        {
            f32 aspectRatio = njli::World::getInstance()->getAspectRatio();
            DEBUG_ASSERT(!isnan(aspectRatio));
            
            top = getZNear() * btTan(btRadians(getFov()));
            bottom = -top;
            left = bottom * aspectRatio;
            right = top * aspectRatio;
        }
        
        farLeft = left * planesFraction;
        farRight = right * planesFraction;
        farBottom = bottom * planesFraction;
        farTop = top * planesFraction;
    }
    
    btVector3 Camera::getTopLeftVector()const
    {
        f32 left, right, bottom, top, farLeft, farRight, farBottom, farTop;
        getViewBounds(left, right, bottom, top, farLeft, farRight, farBottom, farTop);
        
        btVector3 nearPosition(left, top, getZNear());
        btVector3 farPosition(farLeft, farTop, getZFar());
        
        btVector3 vector(farPosition - nearPosition);
        vector.normalize();
        
        vector = vector.rotate(getParent()->getOrientation().getAxis(), getParent()->getOrientation().getAngle());
        vector += getParent()->getOrigin();
        
        return vector;
    }
    
    btVector3 Camera::getTopRightVector()const
    {
        f32 left, right, bottom, top, farLeft, farRight, farBottom, farTop;
        getViewBounds(left, right, bottom, top, farLeft, farRight, farBottom, farTop);
        
        btVector3 nearPosition(right, top, getZNear());
        btVector3 farPosition(farRight, farTop, getZFar());
        
        btVector3 vector(farPosition - nearPosition);
        vector.normalize();
        
        vector = vector.rotate(getParent()->getOrientation().getAxis(), getParent()->getOrientation().getAngle());
        vector += getParent()->getOrigin();
        
        return vector;
    }
    
    btVector3 Camera::getBottomLeftVector()const
    {
        f32 left, right, bottom, top, farLeft, farRight, farBottom, farTop;
        getViewBounds(left, right, bottom, top, farLeft, farRight, farBottom, farTop);
        
        btVector3 nearPosition(left, bottom, getZNear());
        btVector3 farPosition(farLeft, farBottom, getZFar());
        
        btVector3 vector(farPosition - nearPosition);
        vector.normalize();
        
        vector = vector.rotate(getParent()->getOrientation().getAxis(), getParent()->getOrientation().getAngle());
        vector += getParent()->getOrigin();
        
        return vector;
    }
    
    btVector3 Camera::getBottomRightVector()const
    {
        f32 left, right, bottom, top, farLeft, farRight, farBottom, farTop;
        getViewBounds(left, right, bottom, top, farLeft, farRight, farBottom, farTop);
        
        btVector3 nearPosition(right, bottom, getZNear());
        btVector3 farPosition(farRight, farBottom, getZFar());
        
        btVector3 vector(farPosition - nearPosition);
        vector.normalize();
        
        vector = vector.rotate(getParent()->getOrientation().getAxis(), getParent()->getOrientation().getAngle());
        vector += getParent()->getOrigin();
        
        return vector;    }
    
    void Camera::render(const btDbvtNode* root1,
                        const btDbvtNode* root2,
                        const btVector3& sortaxis,
                        const btVector3 *eye)
    {
        DEBUG_ASSERT(getParent());
        
//        updateProjection();
        
        const btVector3 &origin = getParent()->getOrigin();
        const btVector3 &heading = getForwardVector();
        const btScalar far = getZFar();
        
        btVector3 planeNormals[5];
        btScalar planeOffsets[5];
        
        const s32 count=5;
        
        btVector3		c00(getTopLeftVector());
        btVector3		c10(getTopRightVector());
        btVector3		c01(getBottomLeftVector());
        btVector3		c11(getBottomRightVector());
        
        planeNormals[0]	=	c01.cross(c00).normalized();
        planeNormals[1]	=	c10.cross(c11).normalized();
        planeNormals[2]	=	c00.cross(c10).normalized();
        planeNormals[3]	=	c11.cross(c01).normalized();
        planeNormals[4]	=	-heading;
        planeOffsets[4]	=	-(origin+heading*(far)).dot(planeNormals[4]);
        for(s32 i=0;i<4;++i)
            planeOffsets[i]=-(origin.dot(planeNormals[i]));
        
        if(eye != NULL)
        {
            m_OcclusionBuffer->initialize();
            m_OcclusionBuffer->eye=*eye;
            m_SceneRenderer->setOcclusionBuffer(m_OcclusionBuffer);
            btDbvt::collideOCL(root1,planeNormals,planeOffsets,sortaxis,count,*m_SceneRenderer);
            btDbvt::collideOCL(root2,planeNormals,planeOffsets,sortaxis,count,*m_SceneRenderer);
        }
        else
        {
            m_SceneRenderer->setOcclusionBuffer(NULL);
            btDbvt::collideKDOP(root1,planeNormals,planeOffsets,count,*m_SceneRenderer);
            btDbvt::collideKDOP(root2,planeNormals,planeOffsets,count,*m_SceneRenderer);
        }
        m_SceneRenderer->render();
        
        //    s32 visiblecount=m_SceneRenderer->getNumObjectsDrawn();
        //    NSLog(@"%d visible\n", visiblecount);
    }
    
//    bool Camera::isPropertyChanged()const
//    {
//        return m_PropertyChanged;
//    }
//    
//    void Camera::enablePropertyChanged(bool enable)
//    {
//        m_PropertyChanged = enable;
//    }
}
