#ifndef Color_h
#define Color_h

#include <memory>
#include <glm\vec3.hpp>

namespace arealGL {

template <class T>
class _Color {
    
public:
    T r;	// red
    T g;	// green
    T b;	// blue
    T a;	// alpha
    
    _Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}		// white as default
    _Color(const _Color& rhs) = default;
    _Color(_Color&& rhs) noexcept = default;
    _Color(T red, T green, T blue) : r(red), g(green), b(blue), a(1) {}
    _Color(T red, T green, T blue, T alpha) : r(red), g(green), b(blue), a(alpha) {}
    
    // operator =
    _Color& operator=(const _Color& rhs) = default;
    _Color& operator=(_Color&& rhs) = default;
    // operator +=
    _Color& operator+=(T v) { this->r += v; this->g += v; this->b += v; this->a += v; return *this; }
    _Color& operator+=(const _Color& rhs) { this->r += rhs.r; this->g += rhs.g; this->b += rhs.b; this->a += rhs.a; return *this; }
    // operator -=
    _Color& operator-=(T v) { this->r -= v; this->g -= v; this->b -= v; this->a -= v; return *this; }
    _Color& operator-=(const _Color& rhs) { this->r -= rhs.r; this->g -= rhs.g; this->b -= rhs.b; this->a -= rhs.a; return *this; }
    // operator *=
    _Color& operator*=(T v) { this->r *= v; this->g *= v; this->b *= v; this->a *= v; return *this; }
    _Color& operator*=(const _Color& rhs) { this->r *= rhs.r; this->g *= rhs.g; this->b *= rhs.b; this->a *= rhs.a; return *this; }
    // operator /=
    _Color& operator/=(T v) { this->r /= v; this->g /= v; this->b /= v; this->a /= v; return *this; }
    _Color& operator/=(const _Color& rhs) { this->r /= rhs.r; this->g /= rhs.g; this->b /= rhs.b; this->a /= rhs.a; return *this; }
    // operator == and !=
    bool operator==(const _Color& rhs) { return (this->r == rhs.r) && (this->g == rhs.g) && (this->b == rhs.b) && (this->a == rhs.a); }
    bool operator!=(const _Color& rhs) { return (this->r != rhs.r) || (this->g != rhs.g) || (this->b != rhs.b) || (this->a != rhs.a); }
    
    // random access operator
    T& operator[](const int& i) { return (&r)[i]; /* not safe! */ }
    const T& operator[](const int& i) const { return (&r)[i]; /* not safe! */ }
    
    // Get RGB values as vec3
    glm::vec3 getRGB() const { return glm::vec3(r, g, b); }

};

// Predefined Color types
typedef _Color<float> Color;
typedef _Color<int> iColor;

// operator +
template <typename T>
_Color<T> operator+(const _Color<T>& rhs, T v) { return _Color<T>( rhs.r + v, rhs.g + v, rhs.b + v, rhs.a + v); }
template <typename T>
_Color<T> operator+(T v, const _Color<T>& rhs) { return _Color<T>( rhs.r + v, rhs.g + v, rhs.b + v, rhs.a + v); }
template <typename T>
_Color<T> operator+(const _Color<T>& lhs, const _Color<T>& rhs) { return _Color<T>(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a); }
// operator -
template <typename T>
_Color<T> operator-(const _Color<T>& rhs, T v) { return _Color<T>( rhs.r - v, rhs.g - v, rhs.b - v, rhs.a - v); }
template <typename T>
_Color<T> operator-(T v, const _Color<T>& rhs) { return _Color<T>( rhs.r - v, rhs.g - v, rhs.b - v, rhs.a - v); }
template <typename T>
_Color<T> operator-(const _Color<T>& lhs, const _Color<T>& rhs) { return _Color<T>(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a); }
// operator *
template <typename T>
_Color<T> operator*(const _Color<T>& rhs, T v) { return _Color<T>( rhs.r * v, rhs.g * v, rhs.b * v, rhs.a * v); }
template <typename T>
_Color<T> operator*(T v, const _Color<T>& rhs) { return _Color<T>( rhs.r * v, rhs.g * v, rhs.b * v, rhs.a * v); }
template <typename T>
_Color<T> operator*(const _Color<T>& lhs, const _Color<T>& rhs) { return _Color<T>(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a); }
// operator /
template <typename T>
_Color<T> operator/(const _Color<T>& rhs, T v) { return _Color<T>( rhs.r / v, rhs.g / v, rhs.b / v, rhs.a / v); }
template <typename T>
_Color<T> operator/(T v, const _Color<T>& rhs) { return _Color<T>( rhs.r / v, rhs.g / v, rhs.b / v, rhs.a / v); }
template <typename T>
_Color<T> operator/(const _Color<T>& lhs, const _Color<T>& rhs) { return _Color<T>(lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b, lhs.a / rhs.a); }
    
}

#endif
