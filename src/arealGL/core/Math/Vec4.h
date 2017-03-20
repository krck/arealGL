//  Vec4.h
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
/// MODIFIED (SIMPLIFIED) VERSION OF: glm::vec4
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

#ifndef Vec4_h
#define Vec4_h

#include "Math.h"

namespace arealGLx {

    template <class T>
    class _Vec4 {

    public:
        T x, y, z, w;
        
        _Vec4() : x(0), y(0), z(0), w(0) {}
        _Vec4(T v) : x(v), y(v), z(v), w(v) {}
        _Vec4(T x,T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        _Vec4(const _Vec4& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
        _Vec4(_Vec4&& rhs) : x(std::move(rhs.x)), y(std::move(rhs.y)), z(std::move(rhs.z)), w(std::move(rhs.w)) {}
        
        // random access operator
        T& operator[](const int& i) { return (&x)[i]; /* not save ! */ }
        const T& operator[](const int& i) const { return (&x)[i]; /* not save ! */ }
        // operator =
        _Vec4& operator=(const _Vec4& rhs) { this->x = rhs.x; this->y = rhs.y; this->z = rhs.z; this->w = rhs.w; return *this; }
        // operator +=
        _Vec4& operator+=(const T& v) { this->x += v; this->y += v; this->z += v; this->w += v; return *this; }
        _Vec4& operator+=(const _Vec4& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; this->w += rhs.w; return *this; }
        // operator -=
        _Vec4& operator-=(const T& v) { this->x -= v; this->y -= v; this->z -= v; this->w -= v; return *this; }
        _Vec4& operator-=(const _Vec4& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; this->w -= rhs.w; return *this; }
        // operator *=
        _Vec4& operator*=(const T& v) { this->x *= v; this->y *= v; this->z *= v; this->w *= v; return *this; }
        _Vec4& operator*=(const _Vec4& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; this->w *= rhs.w; return *this; }
        // operator /=
        _Vec4& operator/=(const T& v) { this->x /= v; this->y /= v; this->z /= v; this->w /= v; return *this; }
        _Vec4& operator/=(const _Vec4& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; this->w /= rhs.w; return *this; }
        // operator ++ and --
        _Vec4& operator++() { ++this->x; ++this->y; ++this->z; ++this->w; return *this; }
        _Vec4& operator--() { --this->x; --this->y; --this->z; --this->w; return *this; }
        // operator == and !=
        bool operator==(const _Vec4& rhs) { return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z) && (this->w == rhs.w); }
        bool operator!=(const _Vec4& rhs) { return (this->x != rhs.x) || (this->y != rhs.y) || (this->z != rhs.z) || (this->w != rhs.w); }
        
        void normalize () { this /= len(this); }
        _Vec4 cross(const _Vec4& rhs) { return _Vec4(this->x * rhs.x + this->y * rhs.y + this->z * rhs.z + this->w * rhs.w); }
        
        // T dot(const _Vec4& rhs) { _Vec4 tmp(this * rhs); return (tmp.x + tmp.y) + (tmp.z + tmp.w); }
        // T dist(const _Vec4& rhs) const { return len(this - rhs); }
        // _Vec4 ortho() const { }
        // _Vec4 rotate(const float& angle) const { }
        
    private:
        T lenSq() const { return (*this * *this); }
        T len() const { return sqrt(lenSq()); }
        T len(const _Vec4& rhs) { return sqrt(rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z + rhs.w * rhs.w); }
        
    };
    
    typedef _Vec4<int> vec4i;
    typedef _Vec4<float> vec4;
    typedef _Vec4<double> vec4d;
    
    template <typename T>
    _Vec4<T> normalize (const _Vec4<T>& rhs) { return _Vec4<T>(rhs / (float)sqrt((rhs.x*rhs.x) + (rhs.y*rhs.y) + (rhs.z*rhs.z) + (rhs.w*rhs.w))); }
    template <typename T>
    _Vec4<T> cross(const _Vec4<T>& v1, const _Vec4<T>& v2) { return _Vec4<T>(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w); }
    // template <typename T>
    // T dot(const _Vec4& v1, const _Vec4& v2) { _Vec4 tmp(v1 * v2); return (tmp.x + tmp.y) + (tmp.z + tmp.w); }
    
    // operator +
    template <typename T>
    _Vec4<T> operator+(const _Vec4<T>& rhs, const T& v) { return _Vec4<T>( rhs.x + v, rhs.y + v, rhs.z + v, rhs.w + v); }
    template <typename T>
    _Vec4<T> operator+(const T& v, const _Vec4<T>& rhs) { return _Vec4<T>( rhs.x + v, rhs.y + v, rhs.z + v, rhs.w + v); }
    template <typename T>
    _Vec4<T> operator+(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return _Vec4<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
    // operator -
    template <typename T>
    _Vec4<T> operator-(const _Vec4<T>& rhs, const T& v) { return _Vec4<T>( rhs.x - v, rhs.y - v, rhs.z - v, rhs.w - v); }
    template <typename T>
    _Vec4<T> operator-(const T& v, const _Vec4<T>& rhs) { return _Vec4<T>( rhs.x - v, rhs.y - v, rhs.z - v, rhs.w - v); }
    template <typename T>
    _Vec4<T> operator-(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return _Vec4<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
    // operator *
    template <typename T>
    _Vec4<T> operator*(const _Vec4<T>& rhs, const T& v) { return _Vec4<T>( rhs.x * v, rhs.y * v, rhs.z * v, rhs.w * v); }
    template <typename T>
    _Vec4<T> operator*(const T& v, const _Vec4<T>& rhs) { return _Vec4<T>( rhs.x * v, rhs.y * v, rhs.z * v, rhs.w * v); }
    template <typename T>
    _Vec4<T> operator*(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return _Vec4<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }
    // operator /
    template <typename T>
    _Vec4<T> operator/(const _Vec4<T>& rhs, const T& v) { return _Vec4<T>( rhs.x / v, rhs.y / v, rhs.z / v, rhs.w / v); }
    template <typename T>
    _Vec4<T> operator/(const T& v, const _Vec4<T>& rhs) { return _Vec4<T>( rhs.x / v, rhs.y / v, rhs.z / v, rhs.w / v); }
    template <typename T>
    _Vec4<T> operator/(const _Vec4<T>& lhs, const _Vec4<T>& rhs) { return _Vec4<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }
    
}




#endif
