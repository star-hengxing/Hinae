#pragma once

#include "basic.hpp"

NAMESPACE_BEGIN(Hinae)

using Vector2f = Vector2<f32>;
using Vector2d = Vector2<f64>;
using Vector2i = Vector2<isize>;

template <arithmetic T>
struct Vector2
{
    T x, y;
    
    constexpr Vector2(T v) : x(v), y(v) {}
    constexpr Vector2(T x, T y) : x(x), y(y) {}

    Vector2() = default;
    auto operator <=> (const Vector2<T>&) const = default;

    Vector2<T> operator - () const { return {-x, -y}; }

    Vector2<T> operator + (T rhs) const { return {x + rhs, y + rhs}; }
    Vector2<T> operator - (T rhs) const { return {x - rhs, y - rhs}; }
    Vector2<T> operator * (T rhs) const { return {x * rhs, y * rhs}; }
    Vector2<T> operator / (T rhs) const { return (*this) * reciprocal(rhs); }

    Vector2<T> operator + (const Vector2<T>& rhs) const { return {x + rhs.x, y + rhs.y}; }
    Vector2<T> operator - (const Vector2<T>& rhs) const { return {x - rhs.x, y - rhs.y}; }
    Vector2<T> operator * (const Vector2<T>& rhs) const { return {x * rhs.x, y * rhs.y}; }
    Vector2<T> operator / (const Vector2<T>& rhs) const { return {x / rhs.x, y / rhs.y}; }

    void operator += (T rhs) { x += rhs; y += rhs; }
    void operator -= (T rhs) { x -= rhs; y -= rhs; }
    void operator *= (T rhs) { x *= rhs; y *= rhs; }
    void operator /= (T rhs) { (*this) *= reciprocal(rhs); }

    void operator += (const Vector2<T>& rhs) { x += rhs.x; y += rhs.y; }
    void operator -= (const Vector2<T>& rhs) { x -= rhs.x; y -= rhs.y; }
    void operator *= (const Vector2<T>& rhs) { x *= rhs.x; y *= rhs.y; }
    void operator /= (const Vector2<T>& rhs) { x /= rhs.x; y /= rhs.y; }

    T norm2() const { return x * x + y * y; }
    T norm()  const { return static_cast<T>(std::sqrt(norm2())); }

    void normalize() { (*this) *= reciprocal(norm()); }
    Vector2<T> normalized() const { return (*this) * reciprocal(norm()); }

    Vector2<T> abs() const { return {Hinae::abs(x), Hinae::abs(y)}; }

    T max_component() const { return max(x, y); }

    T min_component() const { return min(x, y); }

    Axis max_dimension() const { return (x > y ? Axis::X : Axis::Y); }

    Axis min_dimension() const { return (x < y ? Axis::X : Axis::Y); }

    T operator [] (usize i) const
    { 
        assert(i <= 1);
        return (&x)[i];
    }
    
    T& operator [] (usize i)
    { 
        assert(i <= 1);
        return (&x)[i];
    }
};

template <arithmetic T>
constexpr T dot(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <arithmetic T>
constexpr T cross(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

template <arithmetic T>
constexpr Vector2<T> operator + (T lhs, const Vector2<T>& rhs) { return rhs + lhs; }
template <arithmetic T>
constexpr Vector2<T> operator - (T lhs, const Vector2<T>& rhs) { return rhs - lhs; }
template <arithmetic T>
constexpr Vector2<T> operator * (T lhs, const Vector2<T>& rhs) { return rhs * lhs; }
template <arithmetic T>
constexpr Vector2<T> operator / (T lhs, const Vector2<T>& rhs) { return Vector2<T>(lhs) / rhs; }

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Vector2<T>& v)
{
    return os << std::make_tuple(v.x, v.y);
}

NAMESPACE_END(Hinae)
