#pragma once

#include <cassert>
#include <cmath>

#include <iostream>
#include <concepts>
#include <numbers>
#include <limits>
#include <tuple>

#ifndef NAMESPACE_BEGIN
#define NAMESPACE_BEGIN(name) namespace name {
#endif

#ifndef NAMESPACE_END
#define NAMESPACE_END(name) }
#endif

NAMESPACE_BEGIN(Hinae)

using u8  = uint_least8_t;
using u16 = uint_least16_t;
using u32 = uint_least32_t;
using u64 = uint_least64_t;

using i8  = int_least8_t;
using i16 = int_least16_t;
using i32 = int_least32_t;
using i64 = int_least64_t;

using usize = size_t;
using isize = long;

using f32 = float;
using f64 = double;

template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template <arithmetic T>
inline constexpr T ZERO = static_cast<T>(0);

template <arithmetic T>
inline constexpr T ONE = static_cast<T>(1);

template <arithmetic T>
inline constexpr T MAX_NUMBER = std::numeric_limits<T>::max();

template <arithmetic T>
inline constexpr T MIN_NUMBER = std::numeric_limits<T>::min();

template <std::floating_point T>
inline constexpr T INFINITY_ = std::numeric_limits<T>::infinity();

template <typename T>
inline constexpr T PI = std::numbers::pi_v<T>;

template <typename T>
inline constexpr T INV_PI = std::numbers::inv_pi_v<T>;

template <std::floating_point T>
inline constexpr T INV_2PI = static_cast<T>(0.15915494309189533577);

template <std::floating_point T>
inline constexpr T INV_4PI = static_cast<T>(0.07957747154594766788);

template <std::floating_point T>
inline constexpr T PI_OVER_2 = static_cast<T>(1.57079632679489661923);

template <std::floating_point T>
inline constexpr T PI_OVER_4 = static_cast<T>(0.78539816339744830961);

template <typename T>
inline constexpr T SQRT2 = std::numbers::sqrt2_v<T>;

template <arithmetic T>
struct Vector3;

template <arithmetic T>
struct Vector2;

template <arithmetic T>
struct Point4;

template <arithmetic T>
struct Point3;

template <arithmetic T>
struct Point2;

template <arithmetic T>
struct Matrix4;

template <arithmetic T>
struct Triangle;

template <arithmetic T, u32 a, u32 c, u32 m>
struct Linear_congruential_generator;

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
constexpr T max(T x, T y)
{
    return (x > y ? x : y);
}

template <arithmetic T>
constexpr T min(T x, T y, T z)
{
    return (x < y) ? ( x < z ? x : z ) : ( y < z ? y : z );
}

template <arithmetic T>
constexpr T min(T x, T y)
{
    return (x < y ? x : y);
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

enum class Axis : usize { X = 0, Y = 1, Z = 2 };

inline std::ostream& operator << (std::ostream& os, Axis axis)
{
    switch(axis)
    {
        using enum Axis;
        case  X: os << "Axis::X"; break;
        case  Y: os << "Axis::Y"; break;
        case  Z: os << "Axis::Z"; break;
        default: os << "invalid type";
    }
    return os;
}

template<typename... Ts>
std::ostream& operator << (std::ostream& os, const std::tuple<Ts...>& tuple)
{
    std::apply
    (
        [&os](const Ts&... args)
        {
            os << '(';
            std::size_t n{0};
            ((os << args << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ')';
        }, tuple
    );
    return os;
}

NAMESPACE_END(Hinae)
