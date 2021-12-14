#pragma once

#include "Vector2.hpp"

NAMESPACE_BEGIN(Hinae)

using Point2f = Point2<f32>;
using Point2d = Point2<f64>;
using Point2i = Point2<size_t>;

template <arithmetic T>
struct Point2
{
    T x, y;
    
    Point2(T v) : x(v), y(v) {}
    Point2(T x, T y) : x(x), y(y) {}

    Point2() = default;
    Point2(const Point2&) = default;
    Point2(Point2&&) = default;
    ~Point2() = default;
    Point2& operator = (const Point2&) = default;
    Point2& operator = (Point2&&) = default;
    auto operator <=> (const Point2<T>&) const = default;

    Vector2<T> operator - () const { return Vector2<T>(-x, -y); }

    T operator [] (size_t i) const
    { 
        assert(i <= 1);
        return (&x)[i];
    }
    
    T& operator [] (size_t i)
    { 
        assert(i <= 1);
        return (&x)[i];
    }
};

template <arithmetic T>
Vector2<T> operator - (const Point2<T>& lhs, const Point2<T>& rhs) noexcept
{
    return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <arithmetic T>
T distance(const Point2<T>& lhs, const Point2<T>& rhs) noexcept
{
    return (lhs - rhs).norm();
}

template <arithmetic T>
T distance2(const Point2<T>& lhs, const Point2<T>& rhs) noexcept
{
    return (lhs - rhs).norm2();
}

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Point2<T>& v)
{
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}

NAMESPACE_END(Hinae)
