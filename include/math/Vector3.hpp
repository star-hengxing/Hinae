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
    
    Vector3(T v) : x(v), y(v), z(v) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vector3() = default;
    Vector3(const Vector3&) = default;
    Vector3(Vector3&&) = default;
    ~Vector3() = default;
    Vector3& operator = (const Vector3&) = default;
    Vector3& operator = (Vector3&&) = default;

    auto operator <=> (const Vector3<T>&) const = default;

    Vector3<T> operator - () const { return Vector3<T>(-x, -y, -z); }

    Vector3<T> operator + (T rhs) const { return Vector3<T>(x + rhs, y + rhs, z + rhs); }
    Vector3<T> operator - (T rhs) const { return Vector3<T>(x - rhs, y - rhs, z - rhs); }
    Vector3<T> operator * (T rhs) const { return Vector3<T>(x * rhs, y * rhs, z * rhs); }
    Vector3<T> operator / (T rhs) const { return (*this) * reciprocal(rhs); }

    Vector3<T> operator + (const Vector3<T>& rhs) const { return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3<T> operator - (const Vector3<T>& rhs) const { return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vector3<T> operator * (const Vector3<T>& rhs) const { return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z); }
    Vector3<T> operator / (const Vector3<T>& rhs) const { return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z); }

    Vector3<T>& operator += (T rhs) const { x += rhs.x; y += rhs.y; z += rhs.z; }
    Vector3<T>& operator -= (T rhs) const { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
    Vector3<T>& operator *= (T rhs) const { x *= rhs.x; y *= rhs.y; z *= rhs.z; }
    Vector3<T>& operator /= (T rhs) const { (*this) *= reciprocal(rhs); }

    T norm2() const { return x * x + y * y + z * z; }
    T norm()  const { return static_cast<T>(std::sqrt(norm2())); }

    void normalize() { (*this) *= reciprocal(norm()); }
    Vector3<T> normalized() const { return (*this) * reciprocal(norm()); }

    Vector3<T> abs() const { return { Hinae::abs(x), Hinae::abs(y), Hinae::abs(z) }; }

    T max_component() const { return max(x, y, z); }

    T min_component() const { return min(x, y, z); }

    Axia max_dimension() const
    {
        return (x > y) ? ( x > z ? Axia::X : Axia::Z ) : ( y > z ? Axia::Y : Axia::Z );
    }

    Axia min_dimension() const
    {
        return (x < y) ? ( x < z ? Axia::X : Axia::Z ) : ( y < z ? Axia::Y : Axia::Z );
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
T dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <arithmetic T>
Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return
    {
        (lhs.y * rhs.z) - (lhs.z * rhs.y),
        (lhs.z * rhs.x) - (lhs.x * rhs.z),
        (lhs.x * rhs.y) - (lhs.y * rhs.x)
    };
}

template <arithmetic T>
Vector3<T> operator + (T lhs, const Vector3<T>& rhs) { return rhs + lhs; }
template <arithmetic T>
Vector3<T> operator - (T lhs, const Vector3<T>& rhs) { return rhs - lhs; }
template <arithmetic T>
Vector3<T> operator * (T lhs, const Vector3<T>& rhs) { return rhs * lhs; }
template <arithmetic T>
Vector3<T> operator / (T lhs, const Vector3<T>& rhs) { return Vector3<T>(lhs) / rhs; }

template <arithmetic T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
{
    os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return os;
}

NAMESPACE_END(Hinae)
