#pragma once

#include "Point3.hpp"
#include "Vector3.hpp"

NAMESPACE_BEGIN(Hinae)

using Bounds3f = Bounds3<f32>;
using Bounds3d = Bounds3<f64>;
using Bounds3i = Bounds3<isize>;

template <arithmetic T>
struct Bounds3
{
    Point3<T> p_min, p_max;

    constexpr Bounds3() = default;
    constexpr auto operator <=> (const Bounds3<T>&) const = default;

    constexpr Bounds3(const Point3<T>& p) : p_min(p), p_max(p) {}

    constexpr Bounds3(const Point3<T>& p1, const Point3<T>& p2)
        : p_min({min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z)})
        , p_max({max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z)}) {}

    const Point3<T>& operator [] (usize i) const
    {
        assert(i < 2);
        return (&p_min)[i];
    }

    Point3<T>& operator [] (usize i)
    {
        assert(i < 2);
        return (&p_min)[i];
    }

    constexpr bool inside(const Point3<T>& p) const
    {
        return p.x >= p_min.x && p.x <= p_max.x
            && p.y >= p_min.y && p.y <= p_max.y
            && p.z >= p_min.z && p.z <= p_max.z;
    }

    constexpr Vector3<T> diagonal() const { return p_max - p_min; }

    constexpr Axis max_extent() const { return diagonal().max_dimension(); }

    constexpr Point3<T> centroid() const
    {
        return
        {
            p_min.x / 2 + p_max.x / 2,
            p_min.y / 2 + p_max.y / 2,
            p_min.z / 2 + p_max.z / 2
        };
    }

    constexpr T surface_area() const
    {
        const auto [x, y, z] = diagonal();
        return 2 * (x * y + x * z + y * z);
    }
};

template <arithmetic T> constexpr Bounds3<T>
Union(const Bounds3<T>& b, const Point3<T>& p)
{
    return {min(b.p_min, p), max(b.p_max, p)};
}

template <arithmetic T> constexpr Bounds3<T>
Union(const Bounds3<T>& b1, const Bounds3<T>& b2)
{
    return {min(b1.p_min, b2.p_min), max(b1.p_max, b2.p_max)};
}

template <arithmetic T> constexpr Bounds3<T>
intersect(const Bounds3<T>& b1, const Bounds3<T>& b2)
{
    return {max(b1.p_min, b2.p_min), min(b1.p_max, b2.p_max)};
}

template <arithmetic T> constexpr bool
overlaps(const Bounds3<T>& b1, const Bounds3<T>& b2)
{
    bool x = b1.p_max.x >= b2.p_min.x && b1.p_min.x <= b2.p_max.x;
    bool y = b1.p_max.y >= b2.p_min.y && b1.p_min.y <= b2.p_max.y;
    bool z = b1.p_max.z >= b2.p_min.z && b1.p_min.z <= b2.p_max.z;
    return x && y && z;
}

NAMESPACE_END(Hinae)
