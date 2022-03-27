#pragma once

#include <optional>

#include "Trigonometric.hpp"

NAMESPACE_BEGIN(Hinae)

template <arithmetic T>
constexpr Vector3<T> reflect(const Vector3<T>& wi, const Vector3<T>& n)
{
    return wi - 2 * dot(wi, n) * n;
}

template <arithmetic T>
constexpr std::optional<Vector3<T>>
refract(const Vector3<T>& wi, const Vector3<T>& n, T eta)
{
    const T cos_theta_i = dot(wi, n);
    const T sin2_theta_i = cos_to_sin2(cos_theta_i);
    const T sin2_theta_t = eta * eta * sin2_theta_i;

    if(sin2_theta_t >= 1) return {};

    const T cos_theta_t = sin2_to_cos(sin2_theta_t);
    return std::make_optional(eta * wi - (eta * cos_theta_i - cos_theta_t) * n);
}

NAMESPACE_END(Hinae)
