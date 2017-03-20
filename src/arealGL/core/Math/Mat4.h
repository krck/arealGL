//  Mat4.h
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
/// MODIFIED (SIMPLIFIED) VERSION OF: glm::mat4
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

#ifndef Mat4_h
#define Mat4_h

#include "Math.h"
#include "Vec4.h"

namespace arealGLx {
    
    template <class T>
    class _Mat4 {
        
        typedef _Vec4<T> row;           // X X X X
        
    public:
        row e[4];                       // four rows = 4 x 4 = 16 elements
        
        _Mat4() :e{row(1,0,0,0),row(0,1,0,0),row(0,0,1,0),row(0,0,0,1)} { }
        _Mat4(const T& v) :e{row(v,v,v,v),row(v,v,v,v),row(v,v,v,v),row(v,v,v,v)} { }
        _Mat4(_Vec4<T> rows[4]) :e{rows[0],rows[1],rows[2],rows[3]} { }
        _Mat4(const _Vec4<T>& v0, const _Vec4<T>& v1, const _Vec4<T>& v2, const _Vec4<T>& v3) :e{v0,v1,v2,v3} {}
        _Mat4(const T& x0, const T& y0, const T& z0, const T& w0, const T& x1, const T& y1, const T& z1, const T& w1,
              const T& x2, const T& y2, const T& z2, const T& w2, const T& x3, const T& y3, const T& z3, const T& w3 )
                { this->e[0] = row(x0,y0,z0,w0); this->e[1] = row(x1,y1,z1,w1); this->e[2] = row(x2,y2,z2,w2); this->e[3] = row(x3,y3,z3,w3); }
        _Mat4(const _Mat4& rhs) : e{rhs[0],rhs[1],rhs[2],rhs[3]} {}
        _Mat4(_Mat4&& rhs) : e{std::move(rhs[0]),std::move(rhs[1]),std::move(rhs[2]),std::move(rhs[3])} {}
        
        // random access operator
        _Vec4<T>& operator[](const int& i) { return this->e[i]; /* not save ! */ }
        const _Vec4<T>& operator[](const int& i) const { return this->e[i]; /* not save ! */ }
        // operator =
        _Mat4& operator=(const _Mat4& r) { this->e[0] = r[0]; this->e[1] = r[1]; this->e[2] = r[2]; this->e[3] = r[3]; return *this; }
        // operator +=
        _Mat4& operator+=(T v) { this->e[0] += v; this->e[1] += v; this->e[2] += v; this->e[3] += v; return *this; }
        _Mat4& operator+=(const _Mat4& r) { this->e[0] += r[0]; this->e[1] += r[1]; this->e[2] += r[2]; this->e[3] += r[3]; return *this; }
        // operator -=
        _Mat4& operator-=(T v) { this->e[0] -= v; this->e[1] -= v; this->e[2] -= v; this->e[3] -= v; return *this; }
        _Mat4& operator-=(const _Mat4& r)  { this->e[0] -= r[0]; this->e[1] -= r[1]; this->e[2] -= r[2]; this->e[3] -= r[3]; return *this; }
        // operator *=
        _Mat4& operator*=(T v) { this->e[0] *= v; this->e[1] *= v; this->e[2] *= v; this->e[3] *= v; return *this; }
        _Mat4& operator*=(const _Mat4& r) { return (*this = *this * r); }
        // operator /=
        _Mat4& operator/=(T v) { this->e[0] /= v; this->e[1] /= v; this->e[2] /= v; this->e[3] /= v; return *this; }
        _Mat4& operator/=(const _Mat4& r) { return (*this = *this * inverse_mat(r)); }
        // operator ++ and --
        _Mat4& operator++() { ++this->e[0]; ++this->e[1]; ++this->e[2]; ++this->e[3]; return *this; }
        _Mat4& operator--() { --this->e[0]; --this->e[1]; --this->e[2]; --this->e[3]; return *this; }
        // operator == and !=
        bool operator==(const _Mat4& r) { return (this->e[0] == r[0]) && (this->e[1] == r[1]) && (this->e[2] == r[2]) && (this->e[3] == r[3]); }
        bool operator!=(const _Mat4& r) { return (this->e[0] != r[0]) || (this->e[1] != r[1]) || (this->e[2] != r[2]) || (this->e[3] != r[3]); }
        
        _Mat4 identity() { return _Mat4(); }
        
    };
    
    typedef _Mat4<int> mat4i;
    typedef _Mat4<float> mat4;
    typedef _Mat4<double> mat4d;

    // operator +
    template <typename T>
    _Mat4<T> operator+(const _Mat4<T>& rhs, const T& v) { return _Mat4<T>(rhs[0] + v, rhs[1] + v, rhs[2] + v, rhs[3] + v); }
    template <typename T>
    _Mat4<T> operator+(const T& v, const _Mat4<T>& rhs) { return _Mat4<T>(rhs[0] + v, rhs[1] + v, rhs[2] + v, rhs[3] + v); }
    template <typename T>
    _Mat4<T> operator+(const _Mat4<T>& lhs, const _Mat4<T>& rhs) { return _Mat4<T>(lhs[0]+rhs[0], lhs[1]+rhs[1], lhs[2]+rhs[2], lhs[3]+rhs[3]); }
    // operator -
    template <typename T>
    _Mat4<T> operator-(const _Mat4<T>& rhs, const T& v) { return _Mat4<T>(rhs[0] - v, rhs[1] - v, rhs[2] - v, rhs[3] - v); }
    template <typename T>
    _Mat4<T> operator-(const T& v, const _Mat4<T>& rhs) { return _Mat4<T>(rhs[0] - v, rhs[1] - v, rhs[2] - v, rhs[3] - v); }
    template <typename T>
    _Mat4<T> operator-(const _Mat4<T>& lhs, const _Mat4<T>& rhs) { return _Mat4<T>(lhs[0]-rhs[0], lhs[1]-rhs[1], lhs[2]-rhs[2], lhs[3]-rhs[3]); }
    // operator *
    template <typename T>
    _Mat4<T> operator*(const _Mat4<T>& rhs, const T& v) { return _Mat4<T>(rhs[0] * v, rhs[1] * v, rhs[2] * v, rhs[3] * v); }
    template <typename T>
    _Mat4<T> operator*(const T& v, const _Mat4<T>& rhs) { return _Mat4<T>(rhs[0] * v, rhs[1] * v, rhs[2] * v, rhs[3] * v); }
    template <typename T>
    _Mat4<T> operator*(const _Mat4<T>& lhs, const _Mat4<T>& rhs) {
        _Mat4<T> Result;
        Result[0] = lhs[0] * rhs[0][0] + lhs[1] * rhs[0][1] + lhs[2] * rhs[0][2] + lhs[3] * rhs[0][3];
        Result[1] = lhs[0] * rhs[1][0] + lhs[1] * rhs[1][1] + lhs[2] * rhs[1][2] + lhs[3] * rhs[1][3];
        Result[2] = lhs[0] * rhs[2][0] + lhs[1] * rhs[2][1] + lhs[2] * rhs[2][2] + lhs[3] * rhs[2][3];
        Result[3] = lhs[0] * rhs[3][0] + lhs[1] * rhs[3][1] + lhs[2] * rhs[3][2] + lhs[3] * rhs[3][3];
        return Result;
    }
    // operator /
    template <typename T>
    _Mat4<T> operator/(const _Mat4<T>& rhs, const T& v) { return _Mat4<T>(rhs[0] / v, rhs[1] / v, rhs[2] / v, rhs[3] / v); }
    template <typename T>
    _Mat4<T> operator/(const T& v, const _Mat4<T>& rhs) { return _Mat4<T>(rhs[0] / v, rhs[1] / v, rhs[2] / v, rhs[3] / v); }
    template <typename T>
    _Mat4<T> operator/(const _Mat4<T>& lhs, const _Mat4<T>& rhs) { _Mat4<T> matcopy(lhs); return (matcopy /= rhs); }

    
}

#endif
