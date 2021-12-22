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
    
    Vector2(T v) : x(v), y(v) {}
    Vector2(T x, T y) : x(x), y(y) {}

    Vector2() = default;
    Vector2(const Vector2&) = default;
    Vector2(Vector2&&) = default;
    ~Vector2() = default;
    Vector2& operator = (const Vector2&) = default;
    Vector2& operator = (Vector2&&) = default;

    auto operator <=> (const Vector2<T>&) const = default;

    Vector2<T> operator - () const { return Vector2<T>(-x, -y); }

    Vector2<T> operator + (T rhs) const { return Vector2<T>(x + rhs, y + rhs); }
    Vector2<T> operator - (T rhs) const { return Vector2<T>(x - rhs, y - rhs); }
    Vector2<T> operator * (T rhs) const { return Vector2<T>(x * rhs, y * rhs); }
    Vector2<T> operator / (T rhs) const { return (*this) * reciprocal(rhs); }

    Vector2<T> operator + (const Vector2<T>& rhs) const { return Vector2<T>(x + rhs.x, y + rhs.y); }
    Vector2<T> operator - (const Vector2<T>& rhs) const { return Vector2<T>(x - rhs.x, y - rhs.y); }
    Vector2<T> operator * (const Vector2<T>& rhs) const { return Vector2<T>(x * rhs.x, y * rhs.y); }
    Vector2<T> operator / (const Vector2<T>& rhs) const { return Vector2<T>(x / rhs.x, y / rhs.y); }

    Vector2<T>& operator += (T rhs) const { x += rhs.x; y += rhs.y; }
    Vector2<T>& operator -= (T rhs) const { x -= rhs.x; y -= rhs.y; }
    Vector2<T>& operator *= (T rhs) const { x *= rhs.x; y *= rhs.y; }
    Vector2<T>& operator /= (T rhs) const { (*this) *= reciprocal(rhs); }

    T norm2() const { return x * x + y * y; }
    T norm()  const { return static_cast<T>(std::sqrt(norm2())); }

    void normalize() { (*this) *= reciprocal(norm()); }
    Vector2<T> normalized() const { return (*this) * reciprocal(norm()); }

    Vector2<T> abs() const { return { Hinae::abs(x), Hinae::abs(y) }; }

    T max_component() const { return max(x, y); }

    T min_component() const { return min(x, y); }

    Axia max_dimension() const { return (x > y ? Axia::X : Axia::Y); }

    Axia min_dimension() const { return (x < y ? Axia::X : Axia::Y); }

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
T dot(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <arithmetic T>
T cross(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

template <arithmetic T>
Vector2<T> operator + (T lhs, const Vector2<T>& rhs) { return rhs + lhs; }
template <arithmetic T>
Vector2<T> operator - (T lhs, const Vector2<T>& rhs) { return rhs - lhs; }
template <arithmetic T>
Vector2<T> operator * (T lhs, const Vector2<T>& rhs) { return rhs * lhs; }
template <arithmetic T>
Vector2<T> operator / (T lhs, const Vector2<T>& rhs) { return Vector2<T>(lhs) / rhs; }

template <arithmetic T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
{
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}

NAMESPACE_END(Hinae)
