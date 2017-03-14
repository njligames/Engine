//
//  ColorUtil.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 4/22/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef ColorUtil_h
#define ColorUtil_h

#include "btScalar.h"
#include "btTransform.h"
#include "Log.h"
#include "Util.h"
#include <math.h>
#include "btMatrix3x3.h"




#define RLUM    (0.3086)
#define GLUM    (0.6094)
#define BLUM    (0.0820)

#define OFFSET_R        3
#define OFFSET_G        2
#define OFFSET_B        1
#define OFFSET_A        0

namespace njli {
    class ColorUtil
    {
    private:
        ColorUtil();
        ColorUtil(const ColorUtil&);
        const ColorUtil &operator=(const ColorUtil&);
        
        static const btMatrix3x3 RGB_TO_YIQ;
        static const btMatrix3x3 YIQ_TO_RGB;
        
        static double U_VALUE(const double H)
        {
            return (cos(H*M_PI/180.0));
        }
        
        static double W_VALUE(const double H)
        {
            return (cos(H*M_PI/180.0));
        }
        
        /*
         Must be in YIQ color space
         http://beesbuzz.biz/code/hsv_color_transforms.php
         */
        static inline btMatrix3x3 HUE(const double hueTransformDegreeAmount)
        {
            
            const double U = U_VALUE(hueTransformDegreeAmount);
            
            const double W = W_VALUE(hueTransformDegreeAmount);
            
            return btMatrix3x3(1, 0,  0,
                               0, U, -W,
                               0, W,  U);
        }
        
        /*
         Must be in YIQ color space
         http://beesbuzz.biz/code/hsv_color_transforms.php
         */
        static inline btMatrix3x3 SATURATION(const double saturationAmount)
        {
            return btMatrix3x3(1, 0,                0,
                               0, saturationAmount, 0,
                               0, 0,                saturationAmount);
        }
        
        /*
         Must be in YIQ color space
         http://beesbuzz.biz/code/hsv_color_transforms.php
         */
        static inline btMatrix3x3 VALUE(const double valueAmount)
        {
            return btMatrix3x3(valueAmount, 0,           0,
                               0,           valueAmount, 0,
                               0,           0,           valueAmount);
        }
    public:
        
        static SIMD_FORCE_INLINE btTransform createMatrixFromArray(const btScalar *matrix)
        {
            DEBUG_ASSERT(matrix);
            
            btTransform t;
            t.setFromOpenGLMatrix(matrix);
            return t;
        }
        
        static SIMD_FORCE_INLINE btTransform createHueRotationMatrix(const double rot)
        {
            return btTransform(RGB_TO_YIQ * HUE(rot) * YIQ_TO_RGB);
        }
        
        static SIMD_FORCE_INLINE btTransform createBrightnessMatrix(const double brightness)
        {
            return btTransform(RGB_TO_YIQ * VALUE(brightness) * YIQ_TO_RGB);
        }
        
        static SIMD_FORCE_INLINE btTransform createBlackAndWhiteMatrix()
        {
            double mat[4][4];
            identmat((double*)mat);
            lummat(mat);
            
            btTransform ret;
            ret.setFromOpenGLMatrix((float*)mat);
            return ret;
        }
        
        static SIMD_FORCE_INLINE btTransform createSaturationMatrix(const double saturation)
        {
            return btTransform(RGB_TO_YIQ * SATURATION(saturation) * YIQ_TO_RGB);
        }
        
        static SIMD_FORCE_INLINE btTransform createColorOffsetMatrix(const btVector3 &colorOffset)
        {
            double mat[4][4];
            identmat((double*)mat);
            offsetmat(mat, colorOffset.x(), colorOffset.y(), colorOffset.z());
            
            btTransform ret;
            ret.setFromOpenGLMatrix((float*)mat);
            return ret;
        }
    protected:
        
        /*
         *	applymatrix -
         *		use a matrix to transform colors.
         */
        static SIMD_FORCE_INLINE void applymatrix(unsigned long *lptr,
                                                  double mat[4][4],
                                                  int n)
        {
            int ir, ig, ib, r, g, b;
            unsigned char *cptr;
            
            cptr = (unsigned char *)lptr;
            while(n--) {
                ir = cptr[OFFSET_R];
                ig = cptr[OFFSET_G];
                ib = cptr[OFFSET_B];
                r = ir*mat[0][0] + ig*mat[1][0] + ib*mat[2][0] + mat[3][0];
                g = ir*mat[0][1] + ig*mat[1][1] + ib*mat[2][1] + mat[3][1];
                b = ir*mat[0][2] + ig*mat[1][2] + ib*mat[2][2] + mat[3][2];
                if(r<0) r = 0;
                if(r>255) r = 255;
                if(g<0) g = 0;
                if(g>255) g = 255;
                if(b<0) b = 0;
                if(b>255) b = 255;
                cptr[OFFSET_R] = r;
                cptr[OFFSET_G] = g;
                cptr[OFFSET_B] = b;
                cptr += 4;
            }
        }
        
        /*
         *	matrixmult -
         *		multiply two matricies
         */
        static SIMD_FORCE_INLINE void matrixmult(const double a[4][4], const double b[4][4], double c[4][4])
        {
            int x, y;
            double temp[4][4];
            
            for(y=0; y<4 ; y++)
                for(x=0 ; x<4 ; x++) {
                    temp[y][x] = b[y][0] * a[0][x]
                    + b[y][1] * a[1][x]
                    + b[y][2] * a[2][x]
                    + b[y][3] * a[3][x];
                }
            for(y=0; y<4; y++)
                for(x=0; x<4; x++)
                    c[y][x] = temp[y][x];
        }
        
        /*
         *	identmat -
         *		make an identity matrix
         */
        static SIMD_FORCE_INLINE void identmat(double *matrix)
        {
            *matrix++ = 1.0;    /* row 1        */
            *matrix++ = 0.0;
            *matrix++ = 0.0;
            *matrix++ = 0.0;
            *matrix++ = 0.0;    /* row 2        */
            *matrix++ = 1.0;
            *matrix++ = 0.0;
            *matrix++ = 0.0;
            *matrix++ = 0.0;    /* row 3        */
            *matrix++ = 0.0;
            *matrix++ = 1.0;
            *matrix++ = 0.0;
            *matrix++ = 0.0;    /* row 4        */
            *matrix++ = 0.0;
            *matrix++ = 0.0;
            *matrix++ = 1.0;
        }
        
        /*
         *	xformpnt -
         *		transform a 3D point using a matrix
         */
        static SIMD_FORCE_INLINE void xformpnt(const double matrix[4][4],
                                               const double x,
                                               const double y,
                                               const double z,
                                               double *tx,
                                               double *ty,
                                               double *tz)
        {
            *tx = x*matrix[0][0] + y*matrix[1][0] + z*matrix[2][0] + matrix[3][0];
            *ty = x*matrix[0][1] + y*matrix[1][1] + z*matrix[2][1] + matrix[3][1];
            *tz = x*matrix[0][2] + y*matrix[1][2] + z*matrix[2][2] + matrix[3][2];
        }
        
        /*
         *	cscalemat -
         *		make a color scale marix
         */
        static SIMD_FORCE_INLINE void cscalemat(double mat[4][4],
                                                const double rscale,
                                                const double gscale,
                                                const double bscale)
        {
            double mmat[4][4];
            
            mmat[0][0] = rscale;
            mmat[0][1] = 0.0;
            mmat[0][2] = 0.0;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = 0.0;
            mmat[1][1] = gscale;
            mmat[1][2] = 0.0;
            mmat[1][3] = 0.0;
            
            
            mmat[2][0] = 0.0;
            mmat[2][1] = 0.0;
            mmat[2][2] = bscale;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = 0.0;
            mmat[3][1] = 0.0;
            mmat[3][2] = 0.0;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	lummat -
         *		make a luminance marix
         */

        static SIMD_FORCE_INLINE void lummat(double mat[4][4])
        {
            double mmat[4][4];
            double rwgt, gwgt, bwgt;
            
            rwgt = RLUM;
            gwgt = GLUM;
            bwgt = BLUM;
            mmat[0][0] = rwgt;
            mmat[0][1] = rwgt;
            mmat[0][2] = rwgt;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = gwgt;
            mmat[1][1] = gwgt;
            mmat[1][2] = gwgt;
            mmat[1][3] = 0.0;
            
            mmat[2][0] = bwgt;
            mmat[2][1] = bwgt;
            mmat[2][2] = bwgt;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = 0.0;
            mmat[3][1] = 0.0;
            mmat[3][2] = 0.0;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	saturatemat -
         *		make a saturation marix
         */
        static SIMD_FORCE_INLINE void saturatemat(double mat[4][4], const double sat)
        {
            double mmat[4][4];
            double a, b, c, d, e, f, g, h, i;
            double rwgt, gwgt, bwgt;
            
            rwgt = RLUM;
            gwgt = GLUM;
            bwgt = BLUM;
            
            a = (1.0-sat)*rwgt + sat;
            b = (1.0-sat)*rwgt;
            c = (1.0-sat)*rwgt;
            d = (1.0-sat)*gwgt;
            e = (1.0-sat)*gwgt + sat;
            f = (1.0-sat)*gwgt;
            g = (1.0-sat)*bwgt;
            h = (1.0-sat)*bwgt;
            i = (1.0-sat)*bwgt + sat;
            mmat[0][0] = a;
            mmat[0][1] = b;
            mmat[0][2] = c;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = d;
            mmat[1][1] = e;
            mmat[1][2] = f;
            mmat[1][3] = 0.0;
            
            mmat[2][0] = g;
            mmat[2][1] = h;
            mmat[2][2] = i;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = 0.0;
            mmat[3][1] = 0.0;
            mmat[3][2] = 0.0;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	offsetmat -
         *		offset r, g, and b
         */
        static SIMD_FORCE_INLINE void offsetmat(double mat[4][4],
                                                const double roffset,
                                                const double goffset,
                                                const double boffset)
        {
            double mmat[4][4];
            
            mmat[0][0] = 1.0;
            mmat[0][1] = 0.0;
            mmat[0][2] = 0.0;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = 0.0;
            mmat[1][1] = 1.0;
            mmat[1][2] = 0.0;
            mmat[1][3] = 0.0;
            
            mmat[2][0] = 0.0;
            mmat[2][1] = 0.0;
            mmat[2][2] = 1.0;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = roffset;
            mmat[3][1] = goffset;
            mmat[3][2] = boffset;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	xrotate -
         *		rotate about the x (red) axis
         */
        static SIMD_FORCE_INLINE void xrotatemat(double mat[4][4],
                                                 const double rs,
                                                 const double rc)
        {
            double mmat[4][4];
            
            mmat[0][0] = 1.0;
            mmat[0][1] = 0.0;
            mmat[0][2] = 0.0;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = 0.0;
            mmat[1][1] = rc;
            mmat[1][2] = rs;
            mmat[1][3] = 0.0;
            
            mmat[2][0] = 0.0;
            mmat[2][1] = -rs;
            mmat[2][2] = rc;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = 0.0;
            mmat[3][1] = 0.0;
            mmat[3][2] = 0.0;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	yrotate -
         *		rotate about the y (green) axis
         */
        static SIMD_FORCE_INLINE void yrotatemat(double mat[4][4],
                                                 const double rs,
                                                 const double rc)
        {
            double mmat[4][4];
            
            mmat[0][0] = rc;
            mmat[0][1] = 0.0;
            mmat[0][2] = -rs;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = 0.0;
            mmat[1][1] = 1.0;
            mmat[1][2] = 0.0;
            mmat[1][3] = 0.0;
            
            mmat[2][0] = rs;
            mmat[2][1] = 0.0;
            mmat[2][2] = rc;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = 0.0;
            mmat[3][1] = 0.0;
            mmat[3][2] = 0.0;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	zrotate -
         *		rotate about the z (blue) axis
         */
        static SIMD_FORCE_INLINE void zrotatemat(double mat[4][4],
                                                 const double rs,
                                                 const double rc)
        {
            double mmat[4][4];
            
            mmat[0][0] = rc;
            mmat[0][1] = rs;
            mmat[0][2] = 0.0;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = -rs;
            mmat[1][1] = rc;
            mmat[1][2] = 0.0;
            mmat[1][3] = 0.0;
            
            mmat[2][0] = 0.0;
            mmat[2][1] = 0.0;
            mmat[2][2] = 1.0;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = 0.0;
            mmat[3][1] = 0.0;
            mmat[3][2] = 0.0;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	zshear -
         *		shear z using x and y.
         */
        static SIMD_FORCE_INLINE void zshearmat(double mat[4][4],
                                                const double dx,
                                                const double dy)
        {
            double mmat[4][4];
            
            mmat[0][0] = 1.0;
            mmat[0][1] = 0.0;
            mmat[0][2] = dx;
            mmat[0][3] = 0.0;
            
            mmat[1][0] = 0.0;
            mmat[1][1] = 1.0;
            mmat[1][2] = dy;
            mmat[1][3] = 0.0;
            
            mmat[2][0] = 0.0;
            mmat[2][1] = 0.0;
            mmat[2][2] = 1.0;
            mmat[2][3] = 0.0;
            
            mmat[3][0] = 0.0;
            mmat[3][1] = 0.0;
            mmat[3][2] = 0.0;
            mmat[3][3] = 1.0;
            matrixmult(mmat,mat,mat);
        }
        
        /*
         *	simplehuerotatemat -
         *		simple hue rotation. This changes luminance
         */
        static SIMD_FORCE_INLINE void simplehuerotatemat(double mat[4][4],
                                                         const double rot)
        {
            double mag;
            double xrs, xrc;
            double yrs, yrc;
            double zrs, zrc;
            
            /* rotate the grey vector into positive Z */
            mag = sqrt(2.0);
            xrs = 1.0/mag;
            xrc = 1.0/mag;
            xrotatemat(mat,xrs,xrc);
            
            mag = sqrt(3.0);
            yrs = -1.0/mag;
            yrc = sqrt(2.0)/mag;
            yrotatemat(mat,yrs,yrc);
            
            /* rotate the hue */
            zrs = sin(rot*M_PI/180.0);
            zrc = cos(rot*M_PI/180.0);
            zrotatemat(mat,zrs,zrc);
            
            /* rotate the grey vector back into place */
            yrotatemat(mat,-yrs,yrc);
            xrotatemat(mat,-xrs,xrc);
        }
        
        /*
         *	huerotatemat -
         *		rotate the hue, while maintaining luminance.
         */
        static SIMD_FORCE_INLINE void huerotatemat(double mat[4][4],
                                                   const double rot)
        {
            double mmat[4][4];
            double mag;
            double lx, ly, lz;
            double xrs, xrc;
            double yrs, yrc;
            double zrs, zrc;
            double zsx, zsy;
            
            identmat((double*)mmat);
            
            /* rotate the grey vector into positive Z */
            mag = sqrt(2.0);
            xrs = 1.0/mag;
            xrc = 1.0/mag;
            xrotatemat(mmat,xrs,xrc);
            mag = sqrt(3.0);
            yrs = -1.0/mag;
            yrc = sqrt(2.0)/mag;
            yrotatemat(mmat,yrs,yrc);
            
            /* shear the space to make the luminance plane horizontal */
            xformpnt(mmat,RLUM,GLUM,BLUM,&lx,&ly,&lz);
            zsx = lx/lz;
            zsy = ly/lz;
            zshearmat(mmat,zsx,zsy);
            
            /* rotate the hue */
            zrs = sin(rot*M_PI/180.0);
            zrc = cos(rot*M_PI/180.0);
            zrotatemat(mmat,zrs,zrc);
            
            /* unshear the space to put the luminance plane back */
            zshearmat(mmat,-zsx,-zsy);
            
            /* rotate the grey vector back into place */
            yrotatemat(mmat,-yrs,yrc);
            xrotatemat(mmat,-xrs,xrc);
            
            matrixmult(mmat,mat,mat);
        }
    };

}

#endif /* ColorUtil_h */
