#pragma once

#include "Vector3.hpp"
#include "Point3.hpp"

NAMESPACE_BEGIN(Hinae)

template <arithmetic T>
constexpr std::tuple<Vector3<T>, Vector3<T>>
local_coordinate_system(const Vector3<T>& v1)
{
    const auto& [x, y, z] = v1;
    Vector3<T> v2;
    if(std::abs(x) > std::abs(y))
        v2 = Vector3<T>{-z, ZERO<T>, x} / std::sqrt(x * x + z * z);
    else
        v2 = Vector3<T>{ZERO<T>, z, -y} / std::sqrt(y * y + z * z);
    return {v2, cross(v1, v2)};
}

template <arithmetic T>
constexpr Point3<T> cartesian_to_spherical(const Point3<T>& p)
{
    const auto v = cast<Vector3>(p);
    const auto& [x, y, z] = v;

    const T radius = v.norm();
    const T theta  = std::acos(z / radius);
    const T phi    = std::atan2(y, x);
    return {radius, theta, phi};
}

template <arithmetic T>
constexpr Point3<T> spherical_to_cartesian(const Point3<T>& p)
{
    const auto& [r, theta, phi] = p;
    return
    {
        r * std::sin(theta) * std::cos(phi),
        r * std::sin(theta) * std::sin(phi),
        r * std::cos(theta)
    };
}

NAMESPACE_END(Hinae)
