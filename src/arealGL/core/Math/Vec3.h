//  Vec3.h
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
/// MODIFIED (SIMPLIFIED) VERSION OF: glm::vec3
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

#ifndef Vec3_h
#define Vec3_h

#include "Math.h"

namespace arealGLx {
    
    template <class T>
    class _Vec3 {
        
    public:
        T x, y, z;
        
        _Vec3() : x(0), y(0), z(0) {}
        _Vec3(T v) : x(v), y(v), z(v) {}
        _Vec3(T x,T y, T z) : x(x), y(y), z(z) {}
        _Vec3(const _Vec3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
        _Vec3(_Vec3&& rhs) : x(std::move(rhs.x)), y(std::move(rhs.y)), z(std::move(rhs.z)) {}
        
        // random access operator
        T& operator[](const int& i) { return (&x)[i]; /* not save ! */ }
        const T& operator[](const int& i) const { return (&x)[i]; /* not save ! */ }
        // operator =
        _Vec3& operator=(const _Vec3& rhs) { this->x = rhs.x; this->y = rhs.y; this->z = rhs.z; return *this; }
        // operator +=
        _Vec3& operator+=(const T& v) { this->x += v; this->y += v; this->z += v; return *this; }
        _Vec3& operator+=(const _Vec3& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
        // operator -=
        _Vec3& operator-=(const T& v) { this->x -= v; this->y -= v; this->z -= v; return *this; }
        _Vec3& operator-=(const _Vec3& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
        // operator *=
        _Vec3& operator*=(const T& v) { this->x *= v; this->y *= v; this->z *= v; return *this; }
        _Vec3& operator*=(const _Vec3& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
        // operator /=
        _Vec3& operator/=(const T& v) { this->x /= v; this->y /= v; this->z /= v; return *this; }
        _Vec3& operator/=(const _Vec3& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this; }
        // operator ++ and --
        _Vec3& operator++() { ++this->x; ++this->y; ++this->z; return *this; }
        _Vec3& operator--() { --this->x; --this->y; --this->z; return *this; }
        // operator == and !=
        bool operator==(const _Vec3& rhs) { return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z); }
        bool operator!=(const _Vec3& rhs) { return (this->x != rhs.x) || (this->y != rhs.y) || (this->z != rhs.z); }
        
        void normalize () { float length = mag(); x /= length; y /= length; z /= length; }
        _Vec3 cross(const _Vec3& rhs) { return _Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x); }
        T dot(const _Vec3& rhs) { return x * rhs.x + y * rhs.y + z * rhs.z; }
        T mag() const { return sqrt(x * x + y * y + z * z); }
        T dist(const _Vec3& rhs) const { float a = x - rhs.x; float b = y - rhs.y; float c = z - rhs.z; return sqrt(a * a + b * b + c * c); }
        
    };
    
    typedef _Vec3<int> vec3i;
    typedef _Vec3<float> vec3;
    typedef _Vec3<double> vec3d;
    
    template <typename T>
    _Vec3<T> normalize (const _Vec3<T>& rhs) { return _Vec3<T>(rhs / (float)sqrt((rhs.x * rhs.x) + (rhs.y * rhs.y) + (rhs.z * rhs.z))); }
    template <typename T>
    _Vec3<T> cross(const _Vec3<T>& v1, const _Vec3<T>& v2) { return _Vec3<T>(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z); }
    template <typename T>
    T dot(const _Vec3<T>& v1, const _Vec3<T>& v2) { _Vec3<T> tmp(v1 * v2); return tmp.x + tmp.y + tmp.z; }
    
    // operator +
    template <typename T>
    _Vec3<T> operator+(const _Vec3<T>& rhs, const T& v) { return _Vec3<T>( rhs.x + v, rhs.y + v, rhs.z + v); }
    template <typename T>
    _Vec3<T> operator+(const T& v, const _Vec3<T>& rhs) { return _Vec3<T>( rhs.x + v, rhs.y + v, rhs.z + v); }
    template <typename T>
    _Vec3<T> operator+(const _Vec3<T>& lhs, const _Vec3<T>& rhs) { return _Vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
    // operator -
    template <typename T>
    _Vec3<T> operator-(const _Vec3<T>& rhs, const T& v) { return _Vec3<T>( rhs.x - v, rhs.y - v, rhs.z - v); }
    template <typename T>
    _Vec3<T> operator-(const T& v, const _Vec3<T>& rhs) { return _Vec3<T>( rhs.x - v, rhs.y - v, rhs.z - v); }
    template <typename T>
    _Vec3<T> operator-(const _Vec3<T>& lhs, const _Vec3<T>& rhs) { return _Vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
    // operator *
    template <typename T>
    _Vec3<T> operator*(const _Vec3<T>& rhs, const T& v) { return _Vec3<T>( rhs.x * v, rhs.y * v, rhs.z * v); }
    template <typename T>
    _Vec3<T> operator*(const T& v, const _Vec3<T>& rhs) { return _Vec3<T>( rhs.x * v, rhs.y * v, rhs.z * v); }
    template <typename T>
    _Vec3<T> operator*(const _Vec3<T>& lhs, const _Vec3<T>& rhs) { return _Vec3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
    // operator /
    template <typename T>
    _Vec3<T> operator/(const _Vec3<T>& rhs, const T& v) { return _Vec3<T>( rhs.x / v, rhs.y / v, rhs.z / v); }
    template <typename T>
    _Vec3<T> operator/(const T& v, const _Vec3<T>& rhs) { return _Vec3<T>( rhs.x / v, rhs.y / v, rhs.z / v); }
    template <typename T>
    _Vec3<T> operator/(const _Vec3<T>& lhs, const _Vec3<T>& rhs) { return _Vec3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }
    
}

#endif
