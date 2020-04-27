#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include "doctest.h"

#include "../../include/irr/core/math/vec4.hpp"

#define APPROX(n) doctest::Approx(n).epsilon(0.01) 

#define CHECK_VEC4(_v, _x, _y, _z, _w) {\
	auto v = _v; \
	CHECK(v.x == _x); \
	CHECK(v.y == _y); \
	CHECK(v.z == _z); \
	CHECK(v.w == _w); }

#define CHECK_VEC4_APPROX(_v, _x, _y, _z, _w) {\
	auto v = _v; \
	CHECK(v.x == APPROX(_x)); \
	CHECK(v.y == APPROX(_y)); \
	CHECK(v.z == APPROX(_z)); \
	CHECK(v.w == APPROX(_w)); }

#define CHECK_VEC4_1(v, s) \
	CHECK_VEC4(v, s, s, s, s);

using namespace irr::core;

TEST_CASE("vec4 constructors")
{
	vec4 a;
	CHECK_VEC4_1(a, 0.f);
	
	vec4 b(5.f);
	CHECK_VEC4_1(b, 5.f);

	vec4 c(1.f, 2.f, 3.f, 4.f);
	CHECK_VEC4(c, 1.f, 2.f, 3.f, 4.f);

	float arr[] = {1.f, 2.f, 3.f, 4.f};
	vec4 d(arr);
	CHECK_VEC4(d, 1.f, 2.f, 3.f, 4.f);
	vec4 e(arr, aligned);

	__m128 m = _mm_setr_ps(1.f, 2.f, 3.f, 4.f);
	vec4 f(m);
	CHECK_VEC4(f, 1.f, 2.f, 3.f, 4.f);

	vec4 g(f);
	CHECK_VEC4(g, 1.f, 2.f, 3.f, 4.f);
}

TEST_CASE("vec4 vec4 operators")
{
	vec4 a(1.f, 2.f, 3.f, 4.f);
	vec4 b(-1.f, -4.f, 3.f, 5.f);

	CHECK_VEC4(a + b, 0.f, -2.f, 6.f, 9.f);
	CHECK_VEC4(a - b, 2.f, 6.f, 0.f, -1.f);
	CHECK_VEC4(a * b, -1.f, -8.f, 9.f, 20.f);
	CHECK_VEC4(a / b, -1.f, -0.5f, 1.f, 0.8f);

	a += b;
	CHECK_VEC4(a, 0.f, -2.f, 6.f, 9.f);

	a -= b;
	CHECK_VEC4(a, 1.f, 2.f, 3.f, 4.f); 

	a *= b;
	CHECK_VEC4(a, -1.f, -8.f, 9.f, 20.f);

	a /= b;
	CHECK_VEC4(a, 1.f, 2.f, 3.f, 4.f);
}

TEST_CASE("vec4 scalar operators")
{
	vec4 a(1.f, 2.f, 3.f, 4.f);

	CHECK_VEC4(a * 5.f, 5.f, 10.f, 15.f, 20.f);
	CHECK_VEC4(5.f * a, 5.f, 10.f, 15.f, 20.f);
	CHECK_VEC4(a / 2.f, 0.5f, 1.f, 1.5f, 2.f);
	CHECK_VEC4_APPROX(4.f / a, 4.f, 2.f, 1.33f, 1.f);
}
