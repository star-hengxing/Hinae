#pragma once

#include <cassert>
#include <cmath>

#include <iostream>
#include <concepts>
#include <limits>

#ifndef NAMESPACE_BEGIN
#define NAMESPACE_BEGIN(name) namespace name {
#endif

#ifndef NAMESPACE_END
#define NAMESPACE_END(name) }
#endif

NAMESPACE_BEGIN(Hinae)

template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template <arithmetic T>
constexpr T ZERO = static_cast<T>(0);

template <arithmetic T>
constexpr T ONE = static_cast<T>(1);

template <arithmetic T>
constexpr T MAX_NUMBER = std::numeric_limits<T>::max();

template <std::floating_point T>
constexpr T PI = static_cast<T>(3.14159265358979323846);

template <std::floating_point T>
constexpr T INV_PI = static_cast<T>(0.31830988618379067154);

template <std::floating_point T>
constexpr T INV_2PI = static_cast<T>(0.15915494309189533577);

template <std::floating_point T>
constexpr T INV_4PI = static_cast<T>(0.07957747154594766788);

template <std::floating_point T>
constexpr T PI_OVER_2 = static_cast<T>(1.57079632679489661923);

template <std::floating_point T>
constexpr T PI_OVER_4 = static_cast<T>(0.78539816339744830961);

template <std::floating_point T>
constexpr T SQRT2 = static_cast<T>(1.41421356237309504880);

template <arithmetic T>
struct Vector3;

template <arithmetic T>
struct Point3;

template <arithmetic T>
struct Matrix4;

template <
	template <arithmetic T> typename To,
	template <arithmetic T> typename From,
	arithmetic T>
To<T> cast(const From<T>& geometry)
{
	static_assert(sizeof(To<T>) <= sizeof(From<T>));
	if constexpr(sizeof(To<T>) == sizeof(T) * 2)
	{
		return To<T>(geometry.x, geometry.y);
	}
	else if constexpr(sizeof(To<T>) == sizeof(T) * 3)
	{
		return To<T>(geometry.x, geometry.y, geometry.z);
	}
	else
	{
		static_assert(sizeof(To<T>) == sizeof(T) * 4);
		return To<T>(geometry.x, geometry.y, geometry.z, ONE<T>);
	}
}

template <arithmetic T>
constexpr bool is_zero(T x) { return x == ZERO<T>; }

template <arithmetic T>
constexpr bool is_one(T x) { return x == ONE<T>; }

template <std::integral T>
constexpr bool is_odd(T x) { return x % 2 != 0; }

template <std::integral T>
constexpr bool is_even(T x) { return x % 2 == 0; }

template <arithmetic T>
constexpr T abs(T x) { return x >= ZERO<T> ? x : -x; }

template <arithmetic T>
constexpr T max(T x, T y, T z)
{
    return (x > y) ? ( x > z ? x : z ) : ( y > z ? y : z );
}

template <arithmetic T>
constexpr T min(T x, T y, T z)
{
    return (x < y) ? ( x < z ? x : z ) : ( y < z ? y : z );
}

template <arithmetic T>
T clamp(T low, T value, T high)
{
    if(value <= low)       return low;
    else if(value >= high) return high;
    else                   return value;
}

template <arithmetic T>
constexpr T sign(T x)
{
    if(x > ZERO<T>)      return ONE<T>;
    else if(x < ZERO<T>) return -ONE<T>;
    else                 return ZERO<T>;
}

template <arithmetic T>
constexpr T reciprocal(T x)
{
    assert(!is_zero(x));
    return ONE<T> / x;
}

template <std::floating_point T>
constexpr T to_degree(T radian) { return (static_cast<T>(180) / PI<T>) * radian; }

template <std::floating_point T>
constexpr T to_radian(T degree) { return (PI<T> / static_cast<T>(180)) * degree; }

template <arithmetic T>
constexpr T pow4(T x)
{
    const T x2 = x * x;
    return x2 * x2;
}

template <arithmetic T>
constexpr T pow5(T x)
{
    const T x2 = x * x;
    return x2 * x2 * x;
}

enum class Axia : uint8_t
{
    X = 0,
    Y = 1,
    Z = 2
};

std::ostream& operator << (std::ostream& os, Axia axia)
{
    switch(axia)
    {
        case Axia::X : os << "Axia::X"; break;
        case Axia::Y : os << "Axia::Y"; break;
        case Axia::Z : os << "Axia::Z"; break;
        default:       os << "invaild type";
    }
    return os;
}

NAMESPACE_END(Hinae)
