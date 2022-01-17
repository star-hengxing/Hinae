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

    Vector3() = default;
    auto operator <=> (const Vector3<T>&) const = default;

    Vector3<T> operator - () const { return {-x, -y, -z}; }

    Vector3<T> operator + (T rhs) const { return {x + rhs, y + rhs, z + rhs}; }
    Vector3<T> operator - (T rhs) const { return {x - rhs, y - rhs, z - rhs}; }
    Vector3<T> operator * (T rhs) const { return {x * rhs, y * rhs, z * rhs}; }
    Vector3<T> operator / (T rhs) const { return (*this) * reciprocal(rhs); }

    Vector3<T> operator + (const Vector3<T>& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
    Vector3<T> operator - (const Vector3<T>& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
    Vector3<T> operator * (const Vector3<T>& rhs) const { return {x * rhs.x, y * rhs.y, z * rhs.z}; }
    Vector3<T> operator / (const Vector3<T>& rhs) const { return {x / rhs.x, y / rhs.y, z / rhs.z}; }

    void operator += (T rhs) { x += rhs; y += rhs; z += rhs; }
    void operator -= (T rhs) { x -= rhs; y -= rhs; z -= rhs; }
    void operator *= (T rhs) { x *= rhs; y *= rhs; z *= rhs; }
    void operator /= (T rhs) { (*this) *= reciprocal(rhs); }

    void operator += (const Vector3<T>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }
    void operator -= (const Vector3<T>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
    void operator *= (const Vector3<T>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; }
    void operator /= (const Vector3<T>& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; }

    T norm2() const { return x * x + y * y + z * z; }
    T norm()  const { return static_cast<T>(std::sqrt(norm2())); }

    void normalize() { (*this) /= norm(); }
    Vector3<T> normalized() const { return (*this) / norm(); }

    Vector3<T> abs() const { return { Hinae::abs(x), Hinae::abs(y), Hinae::abs(z) }; }

    T max_component() const { return max(x, y, z); }

    T min_component() const { return min(x, y, z); }

    Axis max_dimension() const
    {
        return (x > y) ? ( x > z ? Axis::X : Axis::Z ) : ( y > z ? Axis::Y : Axis::Z );
    }

    Axis min_dimension() const
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
constexpr Vector3<T> operator + (T lhs, const Vector3<T>& rhs) { return rhs + lhs; }
template <arithmetic T>
constexpr Vector3<T> operator - (T lhs, const Vector3<T>& rhs) { return rhs - lhs; }
template <arithmetic T>
constexpr Vector3<T> operator * (T lhs, const Vector3<T>& rhs) { return rhs * lhs; }
template <arithmetic T>
constexpr Vector3<T> operator / (T lhs, const Vector3<T>& rhs) { return Vector3<T>(lhs) / rhs; }

template <arithmetic T>
std::ostream& operator << (std::ostream& os, const Vector3<T>& v)
{
    return os << std::make_tuple(v.x, v.y, v.z);
}

NAMESPACE_END(Hinae)
