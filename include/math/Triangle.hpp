#pragma once

#include "Point2.hpp"
#include "Point3.hpp"
#include "Vector2.hpp"

NAMESPACE_BEGIN(Hinae)

using Trianglef = Triangle<f32>;
using Triangled = Triangle<f64>;
using Trianglei = Triangle<isize>;

template <arithmetic T>
struct Barycentric_Coordinates
{
    T alpha, beta, gamma;
    
    Barycentric_Coordinates() = default;
    Barycentric_Coordinates(const Barycentric_Coordinates&) = default;
    Barycentric_Coordinates(Barycentric_Coordinates&&) = default;
    ~Barycentric_Coordinates() = default;
    Barycentric_Coordinates& operator = (const Barycentric_Coordinates&) = default;
    Barycentric_Coordinates& operator = (Barycentric_Coordinates&&) = default;
    auto operator <=> (const Barycentric_Coordinates<T>&) const = delete;

    Barycentric_Coordinates(T f1, T f2, T f3) :
        alpha(f1), beta(f2), gamma(f3) {}
    
    bool is_negative() const noexcept
    {
        return alpha < ZERO<T> || beta < ZERO<T> || gamma < ZERO<T>;
    }

    template <typename U>
    T interpolated(const U& t1, const U& t2, const U& t3, T w) const
    {
        assert(!std::isnan(w));
        return (t1 * alpha + t2 * beta + t3 * gamma) * w;
    }

    void operator *= (T f) noexcept
    {
        assert(!std::isnan(f));
        alpha *= f;
        beta  *= f;
        gamma *= f;
    }

    void correct(T z1, T z2, T z3) noexcept
    {
        assert(!is_zero(z1) && !is_zero(z2) && !is_zero(z3));
        alpha /= z1;
        beta  /= z2;
        gamma /= z3;
    }
};

template <arithmetic T>
struct Triangle
{
    Point3<T> A, B, C;

    Triangle() = default;
    Triangle(const Triangle&) = default;
    Triangle(Triangle&&) = default;
    ~Triangle() = default;
    Triangle& operator = (const Triangle&) = default;
    Triangle& operator = (Triangle&&) = default;
    auto operator <=> (const Triangle<T>&) const = default;

    Triangle(const Point3<T>& p1, const Point3<T>& p2, const Point3<T>& p3) :
        A(p1), B(p2), C(p3) {}

    bool inside(const Point2<T>& P) const
    {
        const Vector2<T> AB = cast<Point2>(B) - cast<Point2>(A);
        const Vector2<T> BC = cast<Point2>(C) - cast<Point2>(B);
        const Vector2<T> CA = cast<Point2>(A) - cast<Point2>(C);

        const Vector2<T> AP = P - cast<Point2>(A);
        const Vector2<T> BP = P - cast<Point2>(B);
        const Vector2<T> CP = P - cast<Point2>(C);

        return cross(AB, AP) >= ZERO<T>
            && cross(BC, BP) >= ZERO<T>
            && cross(CA, CP) >= ZERO<T>;
    }

    Barycentric_Coordinates<T> barycentric2D(const Point2<T>& P) const
    {
        const Vector2<T> AP = P - cast<Point2>(A); 
        const Vector2<T> BP = P - cast<Point2>(B); 
        const Vector2<T> CP = P - cast<Point2>(C); 
        return
        {
            cross(BP, CP),
            cross(CP, AP),
            cross(AP, BP)
        };
    }
};

NAMESPACE_END(Hinae)
