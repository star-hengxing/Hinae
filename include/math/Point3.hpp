#pragma once

#include "Vector3.hpp"

NAMESPACE_BEGIN(Hinae)

using Point3f = Point3<f32>;
using Point3d = Point3<f64>;
using Point3i = Point3<size_t>;

template <arithmetic T>
struct Point3
{
    T x, y, z;
    
    Point3(T v) : x(v), y(v), z(v) {}
    Point3(T x, T y, T z) : x(x), y(y), z(z) {}

    Point3() = default;
    Point3(const Point3&) = default;
    Point3(Point3&&) = default;
    ~Point3() = default;
    Point3& operator = (const Point3&) = default;
    Point3& operator = (Point3&&) = default;
    auto operator <=> (const Point3<T>&) const = default;

    Vector3<T> operator - () const { return Vector3<T>(-x, -y, -z); }

    T operator [] (size_t i) const
    { 
        assert(i <= 2);
        return (reinterpret_cast<T*>(this))[i];
    }
    
    T& operator [] (size_t i)
    { 
        assert(i <= 2);
        return (reinterpret_cast<T*>(this))[i];
    }
};

template <arithmetic T>
Vector3<T> operator - (const Point3<T>& lhs, const Point3<T>& rhs) noexcept
{
    return Vector3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <arithmetic T>
T distance(const Point3<T>& lhs, const Point3<T>& rhs) noexcept
{
    return (lhs - rhs).norm();
}

template <arithmetic T>
T distance2(const Point3<T>& lhs, const Point3<T>& rhs) noexcept
{
    return (lhs - rhs).norm2();
}

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Point3<T>& v)
{
    os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return os;
}

NAMESPACE_END(Hinae)
