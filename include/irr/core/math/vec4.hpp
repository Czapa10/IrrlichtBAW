
// temporary macros

#define IRR_SSE4
//#define IRR_AVX
//#define IRR_NEON

#ifdef IRR_SSE4
#include <nmmintrin.h>
#endif

#ifdef IRR_AVX
#include <immintrin.h>
#endif

namespace irr
{
namespace core
{

#ifdef IRR_SSE4
using f32x4 = __m128;
#else
using f32x4 = float32x4_t;
#endif

struct aligned_t {};
constexpr aligned_t aligned{};

union alignas(16) vec4
{
	struct{
		float x; float y; float z; float w;
	};
	struct{
		float r; float g; float b; float a;
	};
	struct{
		float s; float t; float p; float q;
	};
	float ptr[4];

	inline vec4();
	inline vec4(float scalar);
	inline vec4(float x, float y, float z, float w);
	inline vec4(float* const array);
	inline vec4(float* const array, aligned_t);
	inline vec4(const f32x4& m);
	inline vec4(const vec4& other);

	inline f32x4 getAsRegister() const;
};

#ifdef IRR_SSE4
#include "backend/vec4_sse4.inl"
#endif

#ifdef IRR_AVX
#include "backend/vec4_avx.inl"
#endif

#ifdef IRR_NEON
#include "backend/vec4_neon.inl"
#endif

}
}

