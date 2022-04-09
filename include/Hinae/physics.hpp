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
    return Vector3(eta * wi - (eta * cos_theta_i - cos_theta_t) * n);
}

NAMESPACE_BEGIN(Fresnel)

template <arithmetic T>
constexpr T dielectric(T cos_theta_i, T eta_i, T eta_t)
{
    cos_theta_i = clamp(-ONE<T>, cos_theta_i, ONE<T>);
    if(cos_theta_i < 0)
    {
        std::swap(eta_i, eta_t);
        cos_theta_i = std::abs(cos_theta_i); // cos = -cos
    }

    T sin_theta_i = sin_to_cos(cos_theta_i);
    T sin_theta_t = eta_i / eta_t * sin_theta_i;
    if(sin_theta_t >= 1) return 1;
    T cos_theta_t = sin_to_cos(sin_theta_t);

    T r_parl = ((eta_t * cos_theta_i) - (eta_i * cos_theta_t))
             / ((eta_t * cos_theta_i) + (eta_i * cos_theta_t));

    T r_perp = ((eta_i * cos_theta_i) - (eta_t * cos_theta_t))
             / ((eta_i * cos_theta_i) + (eta_t * cos_theta_t));

    return (pow2(r_parl) + pow2(r_perp)) / 2;
}

template <arithmetic T>
constexpr T conductor(
    T cos_theta_i,
    const Vector3<T>& eta_t,
    const Vector3<T>& eta_i,
    const Vector3<T>& k)
{
    cos_theta_i = clamp(-ONE<T>, cos_theta_i, ONE<T>);
    Vector3<T> eta = eta_t / eta_i;
    Vector3<T> eta_k = k / eta_i;

    T cos2_theta_i = cos_theta_i * cos_theta_i;
    T sin2_theta = 1 - cos2_theta_i;
    Vector3<T> eta2 = eta * eta;
    Vector3<T> eta_k2 = eta_k * eta_k;

    Vector3<T> t0 = eta2 - eta_k2 - sin2_theta;
    Vector3<T> a2_plus_b2 = Hinae::sqrt(t0 * t0 + 4 * eta2 * eta_k2);
    Vector3<T> t1 = a2_plus_b2 + cos2_theta_i;
    Vector3<T> a  = Hinae::sqrt(0.5f * (a2_plus_b2 + t0));
    Vector3<T> t2 = 2 * a * cos_theta_i;
    Vector3<T> Rs = (t1 - t2) / (t1 + t2);

    Vector3<T> t3 = cos2_theta_i * a2_plus_b2 + sin2_theta * sin2_theta;
    Vector3<T> t4 = t2 * sin2_theta;   
    Vector3<T> Rp = Rs * (t3 - t4) / (t3 + t4);

    return (Rp + Rs) / 2;
}

NAMESPACE_END(Fresnel)

NAMESPACE_END(Hinae)
