#pragma once

#include "basic.hpp"

NAMESPACE_BEGIN(Hinae)

using Vector3f = Vector3<f32>;
using Vector3d = Vector3<f64>;
using Vector3i = Vector3<isize>;

template <arithmetic T>
struct Vector3
{
    T x, y, z;
    
    constexpr Vector3(T v) : x(v), y(v), z(v) {}
    constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    template <arithmetic U>
    constexpr explicit Vector3(const Vector3<U>& p)
        : x(static_cast<T>(p.x))
        , y(static_cast<T>(p.y))
        , z(static_cast<T>(p.z)) {}

    constexpr Vector3() = default;
    constexpr auto operator <=> (const Vector3<T>&) const = default;

    constexpr Vector3<T> operator - () const { return {-x, -y, -z}; }

    constexpr Vector3<T> operator + (T rhs) const { return {x + rhs, y + rhs, z + rhs}; }
    constexpr Vector3<T> operator - (T rhs) const { return {x - rhs, y - rhs, z - rhs}; }
    constexpr Vector3<T> operator * (T rhs) const { return {x * rhs, y * rhs, z * rhs}; }
    constexpr Vector3<T> operator / (T rhs) const { return (*this) * reciprocal(rhs); }

    constexpr Vector3<T> operator + (const Vector3<T>& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
    constexpr Vector3<T> operator - (const Vector3<T>& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
    constexpr Vector3<T> operator * (const Vector3<T>& rhs) const { return {x * rhs.x, y * rhs.y, z * rhs.z}; }
    constexpr Vector3<T> operator / (const Vector3<T>& rhs) const { return {x / rhs.x, y / rhs.y, z / rhs.z}; }

    void operator += (T rhs) { x += rhs; y += rhs; z += rhs; }
    void operator -= (T rhs) { x -= rhs; y -= rhs; z -= rhs; }
    void operator *= (T rhs) { x *= rhs; y *= rhs; z *= rhs; }
    void operator /= (T rhs) { (*this) *= reciprocal(rhs); }

    void operator += (const Vector3<T>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }
    void operator -= (const Vector3<T>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
    void operator *= (const Vector3<T>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; }
    void operator /= (const Vector3<T>& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; }

    constexpr T norm2() const { return x * x + y * y + z * z; }
    T norm()  const { return static_cast<T>(std::sqrt(norm2())); }

    void normalize() { (*this) /= norm(); }
    Vector3<T> normalized() const { return (*this) / norm(); }

    Vector3<T> abs() const
    {
        if constexpr(std::is_same_v<f32, T> || std::is_same_v<f64, T>)
            return {std::abs(x), std::abs(y), std::abs(z)};
        else
            return {Hinae::abs(x), Hinae::abs(y), Hinae::abs(y)};
    }

    constexpr T max_component() const { return max(x, y, z); }

    constexpr T min_component() const { return min(x, y, z); }

    constexpr Axis max_dimension() const
    {
        return (x > y) ? ( x > z ? Axis::X : Axis::Z ) : ( y > z ? Axis::Y : Axis::Z );
    }

    constexpr Axis min_dimension() const
    {
        return (x < y) ? ( x < z ? Axis::X : Axis::Z ) : ( y < z ? Axis::Y : Axis::Z );
    }

    T operator [] (usize i) const
    { 
        assert(i <= 2);
        return (&x)[i];
    }
    
    T& operator [] (usize i)
    { 
        assert(i <= 2);
        return (&x)[i];
    }
};

template <arithmetic T>
constexpr T dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <arithmetic T>
constexpr Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return
    {
        (lhs.y * rhs.z) - (lhs.z * rhs.y),
        (lhs.z * rhs.x) - (lhs.x * rhs.z),
        (lhs.x * rhs.y) - (lhs.y * rhs.x)
    };
}

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
constexpr Vector3<T> operator + (T lhs, const Vector3<T>& rhs) { return rhs + lhs; }
template <arithmetic T>
constexpr Vector3<T> operator * (T lhs, const Vector3<T>& rhs) { return rhs * lhs; }

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Vector3<T>& v)
{
    return os << std::make_tuple(v.x, v.y, v.z);
}

NAMESPACE_END(Hinae)
