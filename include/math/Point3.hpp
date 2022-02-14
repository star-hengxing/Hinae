#pragma once

#include "Vector3.hpp"

NAMESPACE_BEGIN(Hinae)

using Point3f = Point3<f32>;
using Point3d = Point3<f64>;
using Point3i = Point3<isize>;

template <arithmetic T>
struct Point3
{
    T x, y, z;
    
    constexpr Point3(T v) : x(v), y(v), z(v) {}
    constexpr Point3(T x, T y, T z) : x(x), y(y), z(z) {}

    template <arithmetic U>
    constexpr explicit Point3(const Point3<U>& p)
        : x(static_cast<T>(p.x))
        , y(static_cast<T>(p.y))
        , z(static_cast<T>(p.z)) {}

    Point3() = default;
    auto operator <=> (const Point3<T>&) const = default;

    Vector3<T> operator - () const { return {-x, -y, -z}; }

    Point3<T> operator + (const Vector3<T>& v) { return {x + v.x, y + v.y, z + v.z}; }

    T operator [] (usize i) const
    { 
        assert(i <= 2);
        return (&x)[i];
    }
    
    T& operator [] (usize i)
    { 
        assert(i <= 2);
        return (&x)[i];
    }
};

template <arithmetic T>
constexpr Vector3<T> operator - (const Point3<T>& lhs, const Point3<T>& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template <arithmetic T>
constexpr T distance(const Point3<T>& lhs, const Point3<T>& rhs)
{
    return (lhs - rhs).norm();
}

template <arithmetic T>
constexpr T distance2(const Point3<T>& lhs, const Point3<T>& rhs)
{
    return (lhs - rhs).norm2();
}

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Point3<T>& v)
{
    return os << std::make_tuple(v.x, v.y, v.z);
}

NAMESPACE_END(Hinae)
