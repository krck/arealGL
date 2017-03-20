//  Vec2.h
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
/// MODIFIED (SIMPLIFIED) VERSION OF: glm::vec2
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

#ifndef Vec2_h
#define Vec2_h

#include "Math.h"

namespace arealGLx {
    
    template <class T>
    class _Vec2 {

    public:
        T x, y;
        
        _Vec2() : x(0), y(0) {}
        _Vec2(T v) : x(v), y(v) {}
        _Vec2(T x,T y) : x(x), y(y) {}
        _Vec2(const _Vec2& rhs) : x(rhs.x), y(rhs.y) {}
        _Vec2(_Vec2&& rhs) : x(std::move(rhs.x)), y(std::move(rhs.y)) {}

        // random access operator
        T& operator[](const int& i) { return (&x)[i]; /* not save ! */ }
        const T& operator[](const int& i) const { return (&x)[i]; /* not save ! */ }
        // operator =
        _Vec2& operator=(const _Vec2& rhs) { this->x = rhs.x; this->y = rhs.y; return *this; }
        // operator +=
        _Vec2& operator+=(const T& v) { this->x += v; this->y += v; return *this; }
        _Vec2& operator+=(const _Vec2& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
        // operator -=
        _Vec2& operator-=(const T& v) { this->x -= v; this->y -= v; return *this; }
        _Vec2& operator-=(const _Vec2& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
        // operator *=
        _Vec2& operator*=(const T& v) { this->x *= v; this->y *= v; return *this; }
        _Vec2& operator*=(const _Vec2& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
        // operator /=
        _Vec2& operator/=(const T& v) { this->x /= v; this->y /= v; return *this; }
        _Vec2& operator/=(const _Vec2& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
        // operator ++ and --
        _Vec2& operator++() { ++this->x; ++this->y; return *this; }
        _Vec2& operator--() { --this->x; --this->y; return *this; }
        // operator == and !=
        bool operator==(const _Vec2& rhs) { return (this->x == rhs.x) && (this->y == rhs.y); }
        bool operator!=(const _Vec2& rhs) { return (this->x != rhs.x) || (this->y != rhs.y); }
        
        void normalize () { this /= len(this); }
        _Vec2 cross(const _Vec2& rhs) { return (this->x * rhs.y) + (this->y * rhs.x); }
        
        // T dot(const _Vec2& rhs) { _Vec2 tmp(this * rhs); return tmp.x + tmp.y; }
        // T dist(const _Vec2& rhs) const { return len(this - rhs); }
        // _Vec2 ortho() const { }
        // _Vec2 rotate(const float& angle) const { }
        
    private:
        T lenSq() const { return (*this * *this); }
        T len() const { return sqrt(lenSq()); }
        T len(const _Vec2& rhs) { return sqrt(rhs.x * rhs.x + rhs.y * rhs.y); }
        
    };
    
    typedef _Vec2<int> vec2i;
    typedef _Vec2<float> vec2;
    typedef _Vec2<double> vec2d;
    
    template <typename T>
    _Vec2<T> normalize (const _Vec2<T>& rhs) { return _Vec2<T>(rhs / (float)sqrt((rhs.x * rhs.x) + (rhs.y * rhs.y))); }
    template <typename T>
    _Vec2<T> cross(const _Vec2<T>& v1, const _Vec2<T>& v2) { return _Vec2<T>(v1.x * v2.x + v1.y * v2.y); }
    // template <typename T>
    // T dot(const _Vec2& v1, const _Vec2& v2) { _Vec2 tmp(v1 * v2); return tmp.x + tmp.y; }
    
    // operator +
    template <typename T>
    _Vec2<T> operator+(const _Vec2<T>& rhs, const T& v) { return _Vec2<T>(rhs.x + v, rhs.y + v); }
    template <typename T>
    _Vec2<T> operator+(const T& v, const _Vec2<T>& rhs) { return _Vec2<T>(rhs.x + v, rhs.y + v); }
    template <typename T>
    _Vec2<T> operator+(const _Vec2<T>& lhs, const _Vec2<T>& rhs) { return _Vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y); }
    // operator -
    template <typename T>
    _Vec2<T> operator-(const _Vec2<T>& rhs, const T& v) { return _Vec2<T>(rhs.x - v, rhs.y - v); }
    template <typename T>
    _Vec2<T> operator-(const T& v, const _Vec2<T>& rhs) { return _Vec2<T>(rhs.x - v, rhs.y - v); }
    template <typename T>
    _Vec2<T> operator-(const _Vec2<T>& lhs, const _Vec2<T>& rhs) { return _Vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y); }
    // operator *
    template <typename T>
    _Vec2<T> operator*(const _Vec2<T>& rhs, const T& v) { return _Vec2<T>(rhs.x * v, rhs.y * v); }
    template <typename T>
    _Vec2<T> operator*(const T& v, const _Vec2<T>& rhs) { return _Vec2<T>(rhs.x * v, rhs.y * v); }
    template <typename T>
    _Vec2<T> operator*(const _Vec2<T>& lhs, const _Vec2<T>& rhs) { return _Vec2<T>(lhs.x * rhs.x, lhs.y * rhs.y); }
    // operator /
    template <typename T>
    _Vec2<T> operator/(const _Vec2<T>& rhs, const T& v) { return _Vec2<T>(rhs.x / v, rhs.y / v); }
    template <typename T>
    _Vec2<T> operator/(const T& v, const _Vec2<T>& rhs) { return _Vec2<T>(rhs.x / v, rhs.y / v); }
    template <typename T>
    _Vec2<T> operator/(const _Vec2<T>& lhs, const _Vec2<T>& rhs) { return _Vec2<T>(lhs.x / rhs.x, lhs.y / rhs.y); }
    
}

#endif
