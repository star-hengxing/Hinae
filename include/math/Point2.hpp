#pragma once

#include "Vector2.hpp"

NAMESPACE_BEGIN(Hinae)

using Point2f = Point2<f32>;
using Point2d = Point2<f64>;
using Point2i = Point2<isize>;

template <arithmetic T>
struct Point2
{
    T x, y;
    
    constexpr Point2(T v) : x(v), y(v) {}
    constexpr Point2(T x, T y) : x(x), y(y) {}

    template <arithmetic U>
    constexpr explicit Point2(const Point2<U>& p)
        : x(static_cast<T>(p.x))
        , y(static_cast<T>(p.y)) {}

    Point2() = default;
    auto operator <=> (const Point2<T>&) const = default;

    Vector2<T> operator - () const { return {-x, -y}; }

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
constexpr Vector2<T> operator - (const Point2<T>& lhs, const Point2<T>& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <arithmetic T>
constexpr T distance(const Point2<T>& lhs, const Point2<T>& rhs)
{
    return (lhs - rhs).norm();
}

template <arithmetic T>
constexpr T distance2(const Point2<T>& lhs, const Point2<T>& rhs)
{
    return (lhs - rhs).norm2();
}

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Point2<T>& v)
{
    return os << std::make_tuple(v.x, v.y);
}

NAMESPACE_END(Hinae)
