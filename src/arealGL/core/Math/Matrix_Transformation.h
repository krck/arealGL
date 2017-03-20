//  Matrix_Transformation.h
/*************************************************************************************
 *  arealGL (OpenGL graphics library)                                                *
 *-----------------------------------------------------------------------------------*
 *  Copyright (c) 2015, Peter Baumann                                                *
 *  All rights reserved.                                                             *
 *                                                                                   *
 *  Redistribution and use in source and binary forms, with or without               *
 *  modification, are permitted provided that the following conditions are met:      *
 *    1. Redistributions of source code must retain the above copyright              *
 *       notice, this list of conditions and the following disclaimer.               *
 *    2. Redistributions in binary form must reproduce the above copyright           *
 *       notice, this list of conditions and the following disclaimer in the         *
 *       documentation and/or other materials provided with the distribution.        *
 *    3. Neither the name of the organization nor the                                *
 *       names of its contributors may be used to endorse or promote products        *
 *       derived from this software without specific prior written permission.       *
 *                                                                                   *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  *
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    *
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
 *  DISCLAIMED. IN NO EVENT SHALL PETER BAUMANN BE LIABLE FOR ANY                    *
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       *
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     *
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      *
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    *
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     *
 *                                                                                   *
 *************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////
/// MODIFIED VERSION OF: glm-library matrix functions
///
/// OpenGL Mathematics (glm.g-truc.net)
/// Copyright (c) 2005 - 2014 G-Truc Creation (www.g-truc.net)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///////////////////////////////////////////////////////////////////////////////////

#ifndef Matrix_Transformation_h
#define Matrix_Transformation_h

#include <math.h>
#include "Mat4.h"
#include "Vec4.h"
#include "Vec3.h"

namespace arealGLx {
    
    
    template <typename T>
    _Mat4<T> translate (const _Mat4<T>& mat, const _Vec3<T>& vec) {
        _Mat4<T> result(mat);
        result[3] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3];
        return result;
    }
    
    
    template <typename T>
    _Mat4<T> rotate (const _Mat4<T>& mat, const T& angle, const _Vec3<T>& vec) {
        const T a = angle;
        const T c = cos(a);
        const T s = sin(a);
        _Vec3<T> axis = normalize(vec);
        _Vec3<T> temp((T(1) - c) * axis);
        _Mat4<T> Rotate = _Mat4<T>(0.0f);
        Rotate[0][0] = c + temp[0] * axis[0];
        Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
        Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];
        Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
        Rotate[1][1] = c + temp[1] * axis[1];
        Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];
        Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
        Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
        Rotate[2][2] = c + temp[2] * axis[2];
        _Mat4<T> Result = _Mat4<T>(0.0f);
        Result[0] = mat[0] * Rotate[0][0] + mat[1] * Rotate[0][1] + mat[2] * Rotate[0][2];
        Result[1] = mat[0] * Rotate[1][0] + mat[1] * Rotate[1][1] + mat[2] * Rotate[1][2];
        Result[2] = mat[0] * Rotate[2][0] + mat[1] * Rotate[2][1] + mat[2] * Rotate[2][2];
        Result[3] = mat[3];
        return Result;
    }
    
    
    template <typename T>
    _Mat4<T> scale (const _Mat4<T>& mat, const _Vec3<T>& vec) {
        _Mat4<T> Result = _Mat4<T>(0.0f);
        Result[0] = mat[0] * vec[0];
        Result[1] = mat[1] * vec[1];
        Result[2] = mat[2] * vec[2];
        Result[3] = mat[3];
        return Result;
    }
    
    
    template <typename T>
    _Mat4<T> inverse_mat(_Mat4<T>& m) {
        T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
        T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
        T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
        T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
        T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
        T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
        
        _Vec4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
        _Vec4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
        _Vec4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
        _Vec4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
        _Vec4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
        _Vec4<T> Fac5(Coef20, Coef20, Coef22, Coef23);
        
        _Vec4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
        _Vec4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
        _Vec4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
        _Vec4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
        
        _Vec4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
        _Vec4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
        _Vec4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
        _Vec4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
        
        _Vec4<T> SignA(+1, -1, +1, -1);
        _Vec4<T> SignB(-1, +1, -1, +1);
        _Mat4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
        
        _Vec4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);
        
        _Vec4<T> Dot0(m[0] * Row0);
        T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
        T OneOverDeterminant = static_cast<T>(1) / Dot1;
        return Inverse * OneOverDeterminant;
    }
    
    
    template <typename T>
    _Mat4<T> perspective(T fovy, T aspect, T zNear, T zFar) {
        T const tanHalfFovy = tan(fovy / static_cast<T>(2));
        _Mat4<T> Result(static_cast<T>(0));
        Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
        Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
        Result[2][2] = - (zFar + zNear) / (zFar - zNear);
        Result[2][3] = - static_cast<T>(1);
        Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
        return Result;
    }
    
    template <typename T>
    _Mat4<T> perspective(T fov, T width, T height, T zNear, T zFar) {
        if(width <= 0 || height <= 0 || fov <= 0) { return _Mat4<T>(); }
        const T rad = fov;
        const T h = cos(static_cast<T>(0.5) * rad) / sin(static_cast<T>(0.5) * rad);
        const T w = h * height / width;
        _Mat4<T> Result = _Mat4<T>(0.0f);
        Result[0][0] = w;
        Result[1][1] = h;
        Result[2][2] = - (zFar + zNear) / (zFar - zNear);
        Result[2][3] = - static_cast<T>(1);
        Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
        return Result;
    }
    
    
    template <typename T>
    _Mat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar) {
        _Mat4<T> Result = _Mat4<T>(1.0f);
        Result[0][0] = static_cast<T>(2) / (right - left);
        Result[1][1] = static_cast<T>(2) / (top - bottom);
        Result[2][2] = - static_cast<T>(2) / (zFar - zNear);
        Result[3][0] = - (right + left) / (right - left);
        Result[3][1] = - (top + bottom) / (top - bottom);
        Result[3][2] = - (zFar + zNear) / (zFar - zNear);
        return Result;
    }
    
    
    template <typename T>
    _Mat4<T> ortho(T left, T right, T bottom, T top ) {
        _Mat4<T> Result = _Mat4<T>(1.0f);
        Result[0][0] = static_cast<T>(2) / (right - left);
        Result[1][1] = static_cast<T>(2) / (top - bottom);
        Result[2][2] = - static_cast<T>(1);
        Result[3][0] = - (right + left) / (right - left);
        Result[3][1] = - (top + bottom) / (top - bottom);
        return Result;
    }
    
    
    template <typename T>
    _Mat4<T> lookAt(const _Vec3<T>& eye, const _Vec3<T>& center, const _Vec3<T>& up) {
        const _Vec3<T> f(normalize(center - eye));
        const _Vec3<T> s(normalize(cross(f, up)));
        const _Vec3<T> u(cross(s, f));
        _Mat4<T> Result = _Mat4<T>(1.0f);
        Result[0][0] = s.x;
        Result[1][0] = s.y;
        Result[2][0] = s.z;
        Result[0][1] = u.x;
        Result[1][1] = u.y;
        Result[2][1] = u.z;
        Result[0][2] =-f.x;
        Result[1][2] =-f.y;
        Result[2][2] =-f.z;
        Result[3][0] =-dot(s, eye);
        Result[3][1] =-dot(u, eye);
        Result[3][2] = dot(f, eye);
        return Result;
    }
    
    
}

#endif
