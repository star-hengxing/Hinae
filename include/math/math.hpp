#pragma once

#include <tuple>

#include "basic.hpp"

#include "Vector3.hpp"
#include "Point3.hpp"
#include "Matrix4.hpp"

#include "rng.hpp"

NAMESPACE_BEGIN(star)

template <std::floating_point T>
std::tuple<Vector3<T>, Vector3<T>> croodinate_system(const Vector3<T>& v)
{
    if(abs(v.x) > abs(v.y))
    {
        auto v2 = Vector3<T>(-v.z, ZERO<T>, v.x) / std::sqrt(v.x * v.x + v.z * v.z);
        return { v2, cross(v, v2) };
    }
    else
    {
        auto v2 = Vector3<T>(ZERO<T>, v.z, -v.y) / std::sqrt(v.y * v.y + v.z * v.z);
        return { v2, cross(v, v2) };
    }
}

template <std::floating_point T>
Vector3<T> uniform_on_sphere()
{
    T Xi1 = rand<T>();
    T Xi2 = rand<T>();

    T phi = 2 * PI<T> * Xi2;
    T t = 2 * std::sqrt(Xi1 * (1 - Xi1));

    T x = std::cos(phi) * t;
    T y = std::sin(phi) * t;
    T z = 1 - 2 * Xi1;

    return { x, y, z };
}

NAMESPACE_END(star)
