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

using u8  = uint_fast8_t;
using u16 = uint_fast16_t;
using u32 = uint_fast32_t;
using u64 = uint_fast64_t;

using i8  = int_fast8_t;
using i16 = int_fast16_t;
using i32 = int_fast32_t;
using i64 = int_fast64_t;

using usize = std::size_t;
using isize = std::make_signed<usize>::type;

using f32 = float;
using f64 = double;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept signed_numeric = std::is_signed_v<T>;

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
struct Ray3;

template <arithmetic T>
struct Bounds3;

template <arithmetic T>
struct Quaternion;

template <arithmetic T, u32 a, u32 c, u32 m>
struct Linear_congruential_generator;

enum class Axis : usize { X = 0, Y = 1, Z = 2 };

template <arithmetic T>
constexpr bool is_zero(T x) { return x == ZERO<T>; }

template <arithmetic T>
constexpr bool is_one(T x) { return x == ONE<T>; }

template <std::integral T>
constexpr bool is_odd(T x) { return x % 2 != 0; }

template <std::integral T>
constexpr bool is_even(T x) { return x % 2 == 0; }

template <std::signed_integral T>
constexpr T abs(T x) { return x >= ZERO<T> ? x : -x; }

template <arithmetic T>
constexpr T clamp(T low, T value, T high)
{
    if(value <= low)       return low;
    else if(value >= high) return high;
    else                   return value;
}

template <signed_numeric T>
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

template <arithmetic T>
constexpr T max(T x, T y)
{
    return (x > y ? x : y);
}

template <arithmetic T>
constexpr T min(T x, T y)
{
    return (x < y ? x : y);
}

template <arithmetic T>
constexpr T max(T x, T y, T z)
{
    return max(x, max(y, z));
}

template <arithmetic T>
constexpr T min(T x, T y, T z)
{
    return min(x, min(y, z));
}

template <template <arithmetic> typename T, arithmetic U>
constexpr T<U> max(const T<U>& g1, const T<U>& g2)
{
    if constexpr(sizeof(T<U>) / sizeof(U) == 2)
    {
        return {max(g1.x, g2.x), max(g1.y, g2.y)};
    }
    else
    {
        static_assert(sizeof(T<U>) / sizeof(U) ==  3);
        return {max(g1.x, g2.x), max(g1.y, g2.y), max(g1.z, g2.z)};
    }
}

template <template <arithmetic> typename T, arithmetic U>
constexpr T<U> min(const T<U>& g1, const T<U>& g2)
{
    if constexpr(sizeof(T<U>) / sizeof(U) == 2)
    {
        return {min(g1.x, g2.x), min(g1.y, g2.y)};
    }
    else
    {
        static_assert(sizeof(T<U>) / sizeof(U) ==  3);
        return {min(g1.x, g2.x), min(g1.y, g2.y), min(g1.z, g2.z)};
    }
}

template <template <arithmetic> typename T, arithmetic U>
constexpr T<U> clamp(U low, const T<U>& x, U high)
{
    T<U> ret;
    for(usize i = 0; i < sizeof(T<U>) / sizeof(U); i++)
        ret[i] = std::clamp(low, x[i], high);
    return ret;
}

template <template <arithmetic> typename T, arithmetic U>
constexpr T<U> abs(const T<U>& x)
{
    T<U> ret;
    for(usize i = 0; i < sizeof(T<U>) / sizeof(U); i++)
        ret[i] = std::abs(x[i]);
    return ret;
}

template <template <arithmetic> typename T, arithmetic U>
constexpr T<U> ceil(const T<U>& x)
{
    T<U> ret;
    for(usize i = 0; i < sizeof(T<U>) / sizeof(U); i++)
        ret[i] = std::ceil(x[i]);
    return ret;
}

template <template <arithmetic> typename T, arithmetic U>
constexpr T<U> floor(const T<U>& x)
{
    T<U> ret;
    for(usize i = 0; i < sizeof(T<U>) / sizeof(U); i++)
        ret[i] = std::floor(x[i]);
    return ret;
}

template <template <arithmetic> typename T, arithmetic U>
constexpr T<U> pow(const T<U>& x, U exp)
{
    T<U> ret;
    for(usize i = 0; i < sizeof(T<U>) / sizeof(U); i++)
        ret[i] = std::pow(x[i], exp);
    return ret;
}

template <template <arithmetic> typename T, arithmetic U, typename W>
constexpr T<U> lerp(const T<U>& left, const T<U>& right, const W& w)
{
    return left + (right - left) * w;
}

template
<
	template <arithmetic> typename To,   arithmetic U,
	template <arithmetic> typename From, arithmetic T
>
constexpr To<U> as(const From<T>& from)
{
	static_assert(sizeof(To<U>) / sizeof(U) <= sizeof(From<T>) / sizeof(T));
	To<U> to;
    for(usize i = 0; i < sizeof(To<U>) / sizeof(U); i++)
        to[i] = static_cast<U>(from[i]);
    return to;
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
