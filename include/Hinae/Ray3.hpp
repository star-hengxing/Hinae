#pragma once

#include "Vector3.hpp"
#include "Point3.hpp"

NAMESPACE_BEGIN(Hinae)

using Ray3f = Ray3<f32>;
using Ray3d = Ray3<f64>;
using Ray3i = Ray3<isize>;

template <arithmetic T>
struct Ray3
{
    Point3<T> point;
    Vector3<T> direction;

    constexpr Ray3() = default;
    constexpr Ray3(const Point3<T>& point, const Vector3<T>& direction)
        : point(point)
        , direction(direction) {}

    constexpr Point3<T> at(T t) const { return point + direction * t; }
    
    constexpr T inv_at(const Point3<T>& p) const
    {
        assert(!is_zero(direction.x));
        return (p.x - point.x) / direction.x;
    }

    template <Axis axis>
    constexpr T at(T t) const
    {
        if constexpr(axis == Axis::X)
            return point.x + direction.x * t;
        else if constexpr(axis == Axis::Y)
            return point.y + direction.y * t;
        else if constexpr(axis == Axis::Z)
            return point.z + direction.z * t;
    }
};

NAMESPACE_END(Hinae)
