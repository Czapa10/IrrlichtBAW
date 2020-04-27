#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include "doctest.h"

#include "../../include/irr/core/math/vec4.hpp"

#define CHECK_VEC4(v, _x, _y, _z, _w) \
	CHECK(v.x == _x); \
	CHECK(v.y == _y); \
	CHECK(v.z == _z); \
	CHECK(v.w == _w);

#define CHECK_VEC4_1(v, s) \
	CHECK(v.x == s); \
	CHECK(v.y == s); \
	CHECK(v.z == s); \
	CHECK(v.w == s); \

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
