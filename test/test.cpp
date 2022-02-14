#include <Hinae/basic.hpp>

#include <Hinae/Vector2.hpp>
#include <Hinae/Vector3.hpp>

#include <Hinae/Point2.hpp>
#include <Hinae/Point3.hpp>

#include <Hinae/Matrix4.hpp>
#include <Hinae/Transform.hpp>

#include <Hinae/Triangle.hpp>

#include "tools.hpp"

using namespace Hinae;

static void base_test()
{
	static_assert(ZERO<decltype(0)> == 0);
	static_assert(ONE<decltype(1)>  == 1);
	
	static_assert(is_zero(0)  == true);
	static_assert(is_zero(-0) == true);
	static_assert(is_zero(1)  == false);
	static_assert(is_zero(-1) == false);

	static_assert(is_one(0)  == false);
	static_assert(is_one(-0) == false);
	static_assert(is_one(1)  == true);
	static_assert(is_one(-1) == false);

	static_assert(is_odd(0)  == false);
	static_assert(is_odd(-0) == false);
	static_assert(is_odd(1)  == true);
	static_assert(is_odd(-1) == true);
	
	static_assert(is_even(0)  == true);
	static_assert(is_even(-0) == true);
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

	EXPECT_EQ(Vector3(1, 1, 1), Vector3(-1, -1, -1).abs());

	static_assert(v1.max_component() == 2);
	static_assert(v1.min_component() == 0);
	static_assert(v1.max_dimension() == Axis::Z);
	static_assert(v1.min_dimension() == Axis::X);

	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(2, v1[2]);

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

	EXPECT_EQ(Vector2(1, 1), Vector2(-1, -1).abs());

	static_assert(v1.max_component() == 1);
	static_assert(v1.min_component() == 0);
	static_assert(v1.max_dimension() == Axis::Y);
	static_assert(v1.min_dimension() == Axis::X);

	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);

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
}

static void matrix4_test()
{
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
		Transform<f32>::rotate<Axis::X>(30);
		Transform<f32>::rotate<Axis::Y>(45);
		Transform<f32>::rotate<Axis::Z>(60);
	}
}

static void triangle_test()
{
	f32 n = 2;
	Triangle t
	{
		Point3f{n, 0, 0},
		Point3f{0, n, 0},
		Point3f{0, 0, 0}
	};

	EXPECT_EQ(true, t.barycentric2D(Point2f{0.25, 0.25}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{0.75, 0.5}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{0.5, 0.5}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{0.5, 0.75}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{0.75, 0.75}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{1.25, 0.25}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{0.25, 1.25}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{1.5, 0.5}).is_inside());
	EXPECT_EQ(true, t.barycentric2D(Point2f{0.5, 1.5}).is_inside());

	EXPECT_EQ(false, t.barycentric2D(Point2f{2, 2}).is_inside());
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

	triangle_test();

	TEST_RESULT();
}
