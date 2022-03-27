#pragma once

#include "Vector3.hpp"

NAMESPACE_BEGIN(Hinae)

template <arithmetic T>
constexpr T sin_to_cos2(T sin)
{
    return max(ZERO<T>, ONE<T> - sin * sin);
}

template <arithmetic T>
constexpr T cos_to_sin2(T cos)
{
    return max(ZERO<T>, ONE<T> - cos * cos);
}

template <arithmetic T>
constexpr T sin2_to_cos(T sin2)
{
    return std::sqrt(ONE<T> - sin2);
}

template <arithmetic T>
constexpr T cos2_to_sin(T cos2)
{
    return std::sqrt(ONE<T> - cos2);
}

template <arithmetic T>
constexpr T sin_to_cos(T sin)
{
    return std::sqrt(sin_to_cos2(sin));
}

template <arithmetic T>
constexpr T cos_to_sin(T cos)
{
    return std::sqrt(cos_to_sin2(cos));
}

NAMESPACE_END(Hinae)
