#include <math/basic.hpp>
#include <math/Vector3.hpp>
#include <math/Point3.hpp>
#include <math/Matrix4.hpp>

#include "tools.hpp"

using namespace star;

static void base_test()
{
	EXPECT_EQ(0, ZERO<int>);
	EXPECT_EQ(1, ONE<int>);

	EXPECT_EQ(true, is_zero(0));
	EXPECT_EQ(false, is_zero(1));

	EXPECT_EQ(false, is_one(0));
	EXPECT_EQ(true, is_one(1));

	EXPECT_EQ(true, is_odd(1));
	EXPECT_EQ(true, is_even(2));

	EXPECT_EQ(1, abs(-1));
	EXPECT_EQ(1, abs(1));

	EXPECT_EQ(1, max(-1, 0, 1));
	EXPECT_EQ(3, max(1, 2, 3));
	EXPECT_EQ(-1, max(-1, -2, -3));

	EXPECT_EQ(-1, min(-1, 0, 1));
	EXPECT_EQ(1, min(1, 2, 3));
	EXPECT_EQ(-3, min(-1, -2, -3));

	EXPECT_EQ(0, clamp(0, -1, 255));
	EXPECT_EQ(255, clamp(0, 0721, 255));
	EXPECT_EQ(11, clamp(0, 11, 255));

	EXPECT_EQ(0, sign(0));
	EXPECT_EQ(1, sign(2));
	EXPECT_EQ(-1, sign(-2));

	EXPECT_EQ(0.5, reciprocal(2.0));

	EXPECT_EQ(180.0, to_degree(PI<double>));
	EXPECT_EQ(PI<double>, to_radian(180.0));

	EXPECT_EQ(16, pow4(2));
	EXPECT_EQ(32, pow5(2));
}

static void vector3_test()
{
	Vector3 v1{ 0, 1, 2 };
	Vector3 v2{ 2, 1, 0 };

	EXPECT_EQ(Vector3(0, -1, -2), -v1);

	EXPECT_EQ(Vector3(2, 2, 2), v1 + v2);
	EXPECT_EQ(Vector3(-2, 0, 2), v1 - v2);
	EXPECT_EQ(Vector3(0, 1, 0), v1 * v2);
	EXPECT_EQ(Vector3(2, 2, 2), Vector3(4) / Vector3(2));

	EXPECT_EQ(5, v1.norm2());
	EXPECT_EQ(5, Vector3(3, 4, 0).norm());

	EXPECT_EQ(Vector3(1, 1, 1), Vector3(-1, -1, -1).abs());

	EXPECT_EQ(2, v2.max_component());
	EXPECT_EQ(0, v2.min_component());
	EXPECT_EQ(Axia::X, v2.max_dimension());
	EXPECT_EQ(Axia::Z, v2.min_dimension());

	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(2, v1[2]);

	EXPECT_EQ(1, dot(v1, v2));
	EXPECT_EQ(Vector3(-2, 4, -2), cross(v1, v2));

	EXPECT_EQ(Vector3(1, 2, 3), 1 + v1);
}
static void point3_test()
{
	Point3 p{ 0, 1, 2 };
	Point3 q{ 2, 1, 0 };

	EXPECT_EQ(Vector3(0, -1, -2), -p);
	EXPECT_EQ(Vector3(-2, 0, 2), p - q);

	EXPECT_EQ(0, p[0]);
	EXPECT_EQ(1, p[1]);
	EXPECT_EQ(2, p[2]);

	EXPECT_EQ(5, distance(Point3(0, 0, 5), Point3(0)));
	EXPECT_EQ(3, distance2(Point3(1, 1, 1), Point3(0)));
}

static void matrix4_test()
{
	auto m1 = Matrix4i::identity();
	Matrix4i m2
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	EXPECT_EQ(m2, m1);

	auto m3 = Matrix4i::fill(2);
	auto m4 = Matrix4i::fill(1);

	EXPECT_EQ(m3, m4 * 2);

	EXPECT_EQ(Matrix4i::fill(16), m3 * m3);

	Matrix4i m5
	{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};

	Matrix4i m6
	{
		1, 5, 9, 13,
		2, 6, 10, 14,
		3, 7, 11, 15,
		4, 8, 12, 16
	};

	EXPECT_EQ(m6, m5.transpose());
}

int main()
{
	vector3_test();
	point3_test();
	base_test();
	matrix4_test();
	TEST_RESULT();
}
