#pragma once

#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "Point3.hpp"

NAMESPACE_BEGIN(Hinae)

template <arithmetic T>
Vector3<T> operator * (const Matrix4<T>& lhs, const Vector3<T>& rhs)
{
    const T x = rhs.x, y = rhs.y, z = rhs.z;
    return
    {
        lhs[0][0] * x + lhs[0][1] * y + lhs[0][2] * z,
        lhs[1][0] * x + lhs[1][1] * y + lhs[1][2] * z,
        lhs[2][0] * x + lhs[2][1] * y + lhs[2][2] * z,
    };
}

template <arithmetic T>
Point3<T> operator * (const Matrix4<T>& lhs, const Point3<T>& rhs)
{
    const T x  = rhs.x, y = rhs.y, z = rhs.z;
    const T xp = lhs[0][0] * x + lhs[0][1] * y + lhs[0][2] * z + lhs[0][3];
    const T yp = lhs[1][0] * x + lhs[1][1] * y + lhs[1][2] * z + lhs[1][3];
    const T zp = lhs[2][0] * x + lhs[2][1] * y + lhs[2][2] * z + lhs[2][3];
    const T wp = lhs[3][0] * x + lhs[3][1] * y + lhs[3][2] * z + lhs[3][3];
    if(wp == ONE<T>)
    {
        return { xp, yp, zp };
    }
    else
    {
        const T inv = reciprocal(wp);
        return { xp * inv, yp * inv, zp * inv };
    }
}

template <arithmetic T>
class Transform
{
public:
    Transform() = default;
    Transform(const Transform&) = default;
    Transform(Transform&&) = default;
    ~Transform() = default;
    Transform& operator = (const Transform&) = default;
    Transform& operator = (Transform&&) = default;

    static Matrix4<T> scale(T value)
    {
        return scale(value, value, value);
    }

    static Matrix4<T> scale(T x, T y, T z)
    {
        return
        {
            x,       ZERO<T>, ZERO<T>, ZERO<T>,
            ZERO<T>, y,       ZERO<T>, ZERO<T>,
            ZERO<T>, ZERO<T>, z,       ZERO<T>,
            ZERO<T>, ZERO<T>, ZERO<T>, ONE<T>
        };
    }

    static Matrix4<T> translate(const Vector3<T>& v)
    {
        return
        {
            ONE<T>,  ZERO<T>, ZERO<T>, v.x,
            ZERO<T>, ONE<T>,  ZERO<T>, v.y,
            ZERO<T>, ZERO<T>, ONE<T>,  v.z,
            ZERO<T>, ZERO<T>, ZERO<T>, ONE<T>
        };
    }

    template <Axia axia>
    static Matrix4<T> rotate(T degree)
    {
        const T radian = to_radian(degree);
        const T s = std::sin(radian);
        const T c = std::cos(radian);
        if constexpr(axia == Axia::X)
        {
            return
            {
                ONE<T>, ZERO<T>,  ZERO<T>, ZERO<T>,
                ZERO<T>, c,       -s,      ZERO<T>,
                ZERO<T>, s,        c,      ZERO<T>,
                ZERO<T>, ZERO<T>, ZERO<T>, ONE<T>
            };
        }
        else if constexpr(axia == Axia::Y)
        {
            return
            {
                c,       ZERO<T>, s,       ZERO<T>,
                ZERO<T>, ONE<T>,  ZERO<T>, ZERO<T>,
                -s,      ZERO<T>, c,       ZERO<T>,
                ZERO<T>, ZERO<T>, ZERO<T>, ONE<T>
            };
        }
        else if constexpr(axia == Axia::Z)
        {
            return
            {
                c,       -s,      ZERO<T>, ZERO<T>,
                s,        c,      ZERO<T>, ZERO<T>,
                ZERO<T>, ZERO<T>, ONE<T>,  ZERO<T>,
                ZERO<T>, ZERO<T>, ZERO<T>, ONE<T>
            };
        }
    }
    
    static Matrix4<T> look_at(const Point3<T>& pos, const Point3<T>& at, const Vector3<T>& up)
    {
        const Vector3<T> forward = (at - pos).normalized();
		const Vector3<T> right = cross(forward, up).normalized();
		const Vector3<T> Up    = cross(right, forward);
        const auto eye = cast<Vector3>(pos);
        return
        {
            right.x, Up.x, -forward.x, -dot(right,   eye),
            right.y, Up.y, -forward.y, -dot(Up,      eye),
            right.z, Up.z, -forward.z,  dot(forward, eye),
            ZERO<T>, ZERO<T>,  ZERO<T>,  ONE<T>
        };
    }

    static Matrix4<T> orthographic(T width, T height, T z_near, T z_far)
    {
        assert(width > 0 && height > 0 && z_near >= 0 && z_far > z_near);
        const T a11 = 2 / width;
        const T a22 = 2 / height;
        const T a32 = 2 / (z_near - z_far);
        const T a33 = (z_far + z_near) / (z_near - z_far);
        return
        {
            a11,     ZERO<T>, ZERO<T>, ZERO<T>,
            ZERO<T>, a22,     ZERO<T>, ZERO<T>,
            ZERO<T>, ZERO<T>, a32,     a33,  
            ZERO<T>, ZERO<T>, ZERO<T>, ONE<T>
        };
    }

    static Matrix4<T> perspective(T fov, T aspect, T z_near, T z_far)
    {
		const T tan = std::tan(fov / static_cast<T>(2));
		const T cot = 1 / tan;

        const T a11 = cot / aspect;
        const T a22 = cot;
        const T a32 = (z_far + z_near) / (z_near - z_far);
        const T a33 = (static_cast<T>(2) * z_far * z_near) / (z_near - z_far);
        return
        {
            a11,     ZERO<T>, ZERO<T>, ZERO<T>,
            ZERO<T>, a22,     ZERO<T>, ZERO<T>,
            ZERO<T>, ZERO<T>, a32,     a33,  
            ZERO<T>, ZERO<T>, -ONE<T>, ZERO<T>
        };
    }
};

NAMESPACE_END(Hinae)
