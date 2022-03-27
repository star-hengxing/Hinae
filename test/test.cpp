#include <Hinae/basic.hpp>

#include <Hinae/Vector2.hpp>
#include <Hinae/Vector3.hpp>

#include <Hinae/Point2.hpp>
#include <Hinae/Point3.hpp>

#include <Hinae/Transform.hpp>
#include <Hinae/Matrix4.hpp>

#include <Hinae/Quaternion.hpp>
#include <Hinae/Bounds3.hpp>
#include <Hinae/Ray3.hpp>

#include <Hinae/Trigonometric.hpp>

#include "tools.hpp"

using namespace Hinae;

static void base_test()
{
	static_assert(ZERO<decltype(0)> == 0);
	static_assert(ONE<decltype(1)>  == 1);
	
	static_assert(is_zero(0)  == true);
	static_assert(is_zero(1)  == false);
	static_assert(is_zero(-1) == false);

	static_assert(is_one(0)  == false);
	static_assert(is_one(1)  == true);
	static_assert(is_one(-1) == false);

	static_assert(is_odd(0)  == false);
	static_assert(is_odd(1)  == true);
	static_assert(is_odd(-1) == true);
	
	static_assert(is_even(0)  == true);
	static_assert(is_even(1)  == false);
	static_assert(is_even(-1) == false);

	// 浮点数请用 std::abs
	static_assert(Hinae::abs(1)  == 1);
	static_assert(Hinae::abs(-1) == 1);

	static_assert(max(-3, -2, -1) == -1);
	static_assert(max(-2, -1, 0)  == 0);
	static_assert(max(-1, 0, 1)   == 1);
	static_assert(max(0, 1, 2)    == 2);
	static_assert(max(1, 2, 3)    == 3);

	static_assert(min(-3, -2, -1) == -3);
	static_assert(min(-2, -1, 0)  == -2);
	static_assert(min(-1, 0, 1)   == -1);
	static_assert(min(0, 1, 2)    == 0);
	static_assert(min(1, 2, 3)    == 1);

	static_assert(clamp(0, -1, 255)  == 0);
	static_assert(clamp(0, 256, 255) == 255);
	static_assert(clamp(0, 1, 255)   == 1);

	static_assert(sign(0)  == 0);
	static_assert(sign(1)  == 1);
	static_assert(sign(-2) == -1);
	static_assert(sign(2)  == 1);

	static_assert(reciprocal(2.0) == 1.0 / 2.0);

	static_assert(to_degree(PI<double>) == 180.0);
	static_assert(to_radian(180.0)      == PI<double>);

	static_assert(pow4(2) == 16);
	static_assert(pow5(2) == 32);
}

static void vector3_test()
{
	constexpr Vector3 v1{0, 1, 2};
	constexpr Vector3 v2{2, 4, 8};
	
	static_assert(-v1 == Vector3{0, -1, -2});

	static_assert(v2 + 2 == Vector3{4, 6, 10});
	static_assert(v2 - 2 == Vector3{0, 2, 6});
	static_assert(v2 * 2 == Vector3{4, 8, 16});
	constexpr auto v3 = static_cast<Vector3<f32>>(v2) / 2;
	constexpr auto v4 = static_cast<Vector3<int>>(v3);
	static_assert(v4 == Vector3{1, 2, 4});

	static_assert(v1 + v2 == Vector3{2, 5, 10});
	static_assert(v1 - v2 == Vector3{-2, -3, -6});
	static_assert(v1 * v2 == Vector3{0, 4, 16});
	static_assert(v2 / v2 == Vector3{1});

	static_assert(v2.norm2() == 84);
	EXPECT_EQ(5, Vector3(3, 4, 0).norm());

	EXPECT_EQ(Vector3(1, 1, 1), abs(Vector3(-1, -1, -1)));

	static_assert(v1.max_component() == 2);
	static_assert(v1.min_component() == 0);
	static_assert(v1.max_dimension() == Axis::Z);
	static_assert(v1.min_dimension() == Axis::X);

	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(2, v1[2]);
	EXPECT_EQ(0, v1[Axis::X]);
	EXPECT_EQ(1, v1[Axis::Y]);
	EXPECT_EQ(2, v1[Axis::Z]);

	static_assert(dot(v1, v2)   == 20);
	static_assert(cross(v1, v2) == Vector3{0, 4, -2});

	static_assert(2 + v1 == Vector3{2, 3, 4});
	static_assert(2 * v1 == Vector3{0, 2, 4});
}

static void vector2_test()
{
	constexpr Vector2 v1{0, 1};
	constexpr Vector2 v2{4, 2};

	static_assert(-v1 == Vector2{0, -1});

	static_assert(v2 + 2 == Vector2{6, 4});
	static_assert(v2 - 2 == Vector2{2, 0});
	static_assert(v2 * 2 == Vector2{8, 4});
	constexpr auto v3 = static_cast<Vector2<f32>>(v2) / 2;
	constexpr auto v4 = static_cast<Vector2<int>>(v3);
	static_assert(v4 == Vector2{2, 1});

	static_assert(v1 + v2 == Vector2{4, 3});
	static_assert(v1 - v2 == Vector2{-4, -1});
	static_assert(v1 * v2 == Vector2{0, 2});
	static_assert(v2 / v2 == Vector2{1});

	static_assert(v2.norm2() == 20);
	EXPECT_EQ(5, Vector2(3, 4).norm());

	EXPECT_EQ(Vector2(1, 1), abs(Vector2(-1, -1)));

	static_assert(v1.max_component() == 1);
	static_assert(v1.min_component() == 0);
	static_assert(v1.max_dimension() == Axis::Y);
	static_assert(v1.min_dimension() == Axis::X);

	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(0, v1[Axis::X]);
	EXPECT_EQ(1, v1[Axis::Y]);

	static_assert(dot(v1, v2)   == 2);
	static_assert(cross(v1, v2) == -4);

	static_assert(2 + v1 == Vector2{2, 3});
	static_assert(2 * v1 == Vector2{0, 2});
}

static void point3_test()
{
	constexpr Point3 p1{0, 1, 2};
	constexpr Point3 p2 = static_cast<Point3<int>>(Point3{2.0f, 1.0f, 0.0f});

	constexpr Point3 p3 = Point3{0, 1, 2} + Vector3{1, 2, 3};
	static_assert(p3 == Point3{1, 3, 5});

	static_assert(-p1     == Vector3{0, -1, -2});
	static_assert(p1 - p2 == Vector3{-2, 0,  2});

	static_assert(distance2(Point3{1, 1, 1}, Point3{0}) == 3);
	EXPECT_EQ(5, distance(Point3{0, 0, 5}, Point3{0}));

	EXPECT_EQ(0, p1[0]);
	EXPECT_EQ(1, p1[1]);
	EXPECT_EQ(2, p1[2]);
	EXPECT_EQ(0, p1[Axis::X]);
	EXPECT_EQ(1, p1[Axis::Y]);
	EXPECT_EQ(2, p1[Axis::Z]);
}

static void point2_test()
{
	constexpr Point2 p1{0, 1};
	constexpr Point2 p2 = static_cast<Point2<int>>(Point2f{2.0f, 1.0f});

	constexpr Point2 p3 = Point2{0, 1} + Vector2{1, 2};
	static_assert(p3 == Point2{1, 3});

	static_assert(-p1 	  == Vector2{0, -1});
	static_assert(p1 - p2 == Vector2{-2, 0});

	static_assert(distance2(Point2{1, 1}, Point2{0}) == 2);
	EXPECT_EQ(5, distance(Point2{0, 5}, Point2{0}));

	EXPECT_EQ(0, p1[0]);
	EXPECT_EQ(1, p2[1]);
	EXPECT_EQ(0, p1[Axis::X]);
	EXPECT_EQ(1, p2[Axis::Y]);
}

static void matrix4_test()
{
	{
		constexpr Matrix4i m1
		{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
		};
		static_assert(Vector3i{1, 2, 3}    == m1.row(0));
		static_assert(Vector3i{5, 6, 7}    == m1.row(1));
		static_assert(Vector3i{9, 10, 11}  == m1.row(2));
		static_assert(Vector3i{13, 14, 15} == m1.row(3));
		static_assert(Vector3i{1, 5, 9}    == m1.column(0));
		static_assert(Vector3i{2, 6, 10}   == m1.column(1));
		static_assert(Vector3i{3, 7, 11}   == m1.column(2));
		static_assert(Vector3i{4, 8, 12}   == m1.column(3));
	}

	{
		constexpr auto m1 = Matrix4i::identity();
		constexpr Matrix4i m2
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		static_assert(m1 == m2);
	}

	{
		constexpr auto m1 = Matrix4i::fill(2);
		constexpr auto m2 = Matrix4i::fill(1);
		static_assert(m1 == m2 * 2);
		EXPECT_EQ(Matrix4i::fill(16), m1 * m1);
	}
	
	{
		constexpr Matrix4i m1
		{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
		};

		constexpr Matrix4i m2
		{
			1, 5, 9, 13,
			2, 6, 10, 14,
			3, 7, 11, 15,
			4, 8, 12, 16
		};

		static_assert(m1 == m2.transpose());
	}
}

static void transform_test()
{
	{
		constexpr Matrix4<int> m
		{
			2, 0, 0, 0,
			0, 2, 0, 0,
			0, 0, 2, 0,
			0, 0, 0, 1
		};

		static_assert(m == Transform<int>::scale(2));
		static_assert(m == Transform<int>::scale(2, 2, 2));
	}

	{
		constexpr Matrix4<int> m
		{
			1, 0, 0, 1,
			0, 1, 0, 2,
			0, 0, 1, 3,
			0, 0, 0, 1
		};
		static_assert(m == Transform<int>::translate({1, 2, 3}));
	}

	{
		constexpr Vector3 v{1, 2, 3};
		constexpr auto m = Transform<int>::scale(2);
		EXPECT_EQ(v * 2, m * v);
	}

	{
		constexpr Point3 p{1, 2, 3};
		constexpr Vector3 offset{-1, -2, -3}; 
		constexpr auto m = Transform<int>::translate(offset);

		EXPECT_EQ(Point3{0}, m * p);
		EXPECT_EQ(Point4(0, 0, 0, 1), m * Point4(p));
	}

	{
		constexpr Vector3f y{0, 1, 0};
		const auto q = Quaternionf::rotate(PI_OVER_2<f32>, y);

		constexpr Vector3f v{0, 0, 5};
		const auto v1 = Vector3<int>{Transform<f32>::rotate<Axis::Y>(90) * v};
		auto tmp = Transform<f32>::rotate(q) * v;
		tmp.x = std::ceil(tmp.x);
		const auto v2 = Vector3<int>{tmp};
		const auto v3 = Vector3<int>{(q * Quaternion<f32>::pure(v) * q.inverse()).image};

		constexpr Vector3 dst{5, 0, 0};
		EXPECT_EQ(dst, v1);
		EXPECT_EQ(dst, v2);
		EXPECT_EQ(dst, v3);
	}
}

static void bounds3_test()
{
	constexpr auto p1 = Point3{0}, p2 = Point3{10};
	constexpr Bounds3 b{p1, p2};

	EXPECT_EQ(p1, b[0]);
	EXPECT_EQ(p2, b[1]);

	static_assert(b.inside(p1) == true);
	static_assert(b.inside(p2) == true);
	static_assert(b.inside(Point3{5}) == true);
	static_assert(b.inside(Point3{11}) == false);
	static_assert(b.inside(Point3{-1}) == false);

	static_assert(b.diagonal() == p2 - p1);

	constexpr Bounds3 b1{p1, Point3{5, 10, 15}};
	static_assert(b1.max_extent() == Axis::Z);

	static_assert(b.centroid() == Point3{5});
	static_assert(b.surface_area() == 600);
	static_assert(Union(b, Point3{5}) == b);
	static_assert(Union(Bounds3{p1}, Bounds3{p2}) == b);
	
	constexpr Bounds3 b2{p1, Point3{4}};
	constexpr Bounds3 b3{Point3{2}, p2};
	static_assert(intersect(b2, b3) == Bounds3{Point3{2}, Point3{4}});
	static_assert(overlaps(b2, b3) == true);
}

static void ray3_test()
{
	constexpr Ray3 ray{Point3{0, 0, 0}, Vector3{1, 2, 3}};
	constexpr auto t = 2;
	constexpr auto p = Point3{2, 4, 6};
	
	EXPECT_EQ(t, ray.inv_at<Axis::X>(p[Axis::X]));
	EXPECT_EQ(t, ray.inv_at<Axis::Y>(p[Axis::Y]));
	EXPECT_EQ(t, ray.inv_at<Axis::Z>(p[Axis::Z]));

	EXPECT_EQ(2, ray.at<Axis::X>(2));
	EXPECT_EQ(4, ray.at<Axis::Y>(2));
	EXPECT_EQ(6, ray.at<Axis::Z>(2));

	static_assert(ray.at(t) == p);
}

static void quaternion_test()
{
	constexpr auto v = Vector3{1, 2, 3};
	constexpr auto real = 2;
	constexpr auto q = Quaternion{real, v};
	static_assert(q + 2 == Quaternion{4, {3, 4, 5}});
	static_assert(q * 2 == Quaternion{4, {2, 4, 6}});
	static_assert(q.conjugate() == Quaternion{real, -v});
	static_assert(q.norm2() == 18);

	constexpr auto pure = Quaternion<int>::pure(v);
	static_assert(pure == Quaternion{0, v});
	constexpr auto unit = Quaternion{1, {0, 0, 0}};
	EXPECT_EQ(1, unit.norm());
	static_assert(unit.inverse() == unit.conjugate());
	static_assert(unit.conjugate().conjugate() == unit);

	static_assert(pure * pure == Quaternion{-14, {0, 0, 0}}) ;

	constexpr Quaternion q1 {1, 2, 3, 4};
	constexpr Quaternion q2 {5, 6, 7, 8};
	static_assert(q1 * q2 == Quaternion{-60, 12, 30, 24});
	static_assert(q2 * q1 == Quaternion{-60, 20, 14, 32});
}

static void trigonometric_test()
{
	static_assert(sin_to_cos2(1) == 0);
	static_assert(sin_to_cos2(0) == 1);
	static_assert(sin_to_cos2(0.5) == 0.75);

	static_assert(cos_to_sin2(1) == 0);
	static_assert(cos_to_sin2(0) == 1);
	static_assert(cos_to_sin2(0.5) == 0.75);

	{
		const auto value = std::sqrt(1 - 0.5);
		EXPECT_EQ(0, sin2_to_cos(1));
		EXPECT_EQ(value, sin2_to_cos(0.5));

		EXPECT_EQ(0, cos2_to_sin(1));
		EXPECT_EQ(value, cos2_to_sin(0.5));
	}

	{
		const auto value = std::sqrt(1 - 0.5 * 0.5);
		EXPECT_EQ(0, sin_to_cos(1));
		EXPECT_EQ(value, sin_to_cos(0.5));

		EXPECT_EQ(0, cos_to_sin(1));
		EXPECT_EQ(value, cos_to_sin(0.5));
	}
}

int main()
{
	base_test();

	vector2_test();
	vector3_test();

	point2_test();
	point3_test();
	
	matrix4_test();
	transform_test();

	quaternion_test();
	bounds3_test();
	ray3_test();

	trigonometric_test();

	TEST_RESULT();
}
