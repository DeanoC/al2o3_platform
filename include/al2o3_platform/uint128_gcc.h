#pragma once

// GCC/Clang support a 128 bit type for all operation however no uint128_t is defined
// for cross platform we support a C interface of just bit ops, compares and moves

#if AL2O3_CPU_FAMILY != AL2O3_CPU_X64

typedef unsigned __int128 platform_uint128_t;

AL2O3_FORCE_INLINE platform_uint128_t platform_LoadUpper128From64(uint64_t const a) {
	return (uint128_t)a;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Load128From64(uint64_t const a) {
	return ((uint128_t)a) << 64ull;
}

AL2O3_FORCE_INLINE bool platform_CompareToZero128(platform_uint128_t const a) {
	return a == 0;
}

AL2O3_FORCE_INLINE bool platform_Compare128(platform_uint128_t const a, platform_uint128_t const b) {
	return a != b;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Or128(platform_uint128_t const a, platform_uint128_t const b) {
	return a | b;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_And128(platform_uint128_t const a, platform_uint128_t const b) {
	return a & b;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Xor128(platform_uint128_t const a, platform_uint128_t const b) {
	return a ^ b;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Not128(platform_uint128_t const a) {
	return !a;
}

AL2O3_FORCE_INLINE uint64_t platform_GetLower128(platform_uint128_t const a) {
	return (uint64_t)(a >> 64ull);
}

AL2O3_FORCE_INLINE uint64_t platform_GetUpper128(platform_uint128_t const a) {
	return (uint64_t)(a);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ClearLower128(platform_uint128_t const a) {
	return (a << 64ull) >> 64ull;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ClearUpper128(platform_uint128_t const a) {
	static const uint64_t mask = ~0ull;
	return a & platform_Load128From64(mask);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_SwapUpperAndLower128(platform_uint128_t const a) {
	uint128_t const upperOnly = platform_ClearLower128(a);
	uint128_t const lowerOnly = platform_ClearUpper128(a);
	uint128_t const b = lowerOnly << 64ull;
	uint128_t const c = upperOnly >> 64ull;
	return b | c;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ShiftUpperToLower128(platform_uint128_t const a) {
	return a << 64ull;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ShiftLowerToUpper128(platform_uint128_t const a) {
	return a >> 64ull;
}

#else

#include <x86intrin.h>

typedef __m128i platform_uint128_t;

AL2O3_FORCE_INLINE platform_uint128_t platform_LoadUpper128From64(uint64_t const a) {
	return _mm_loadl_epi64((__m128i*)&a);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Load128From64(uint64_t const a) {
	return _mm_bslli_si128( _mm_loadl_epi64((__m128i*)&a),8);
}


AL2O3_FORCE_INLINE bool platform_CompareToZero128(platform_uint128_t const a) {
	return _mm_movemask_epi8(_mm_cmpeq_epi8(a, _mm_setzero_si128())) == 0xFFFF;
}

AL2O3_FORCE_INLINE bool platform_Compare128(platform_uint128_t const a, platform_uint128_t const b) {
	return _mm_movemask_epi8(_mm_cmpeq_epi8(a, b)) != 0xFFFF;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Or128(platform_uint128_t const a, platform_uint128_t const b) {
	return _mm_or_si128(a, b);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_And128(platform_uint128_t const a, platform_uint128_t const b) {
	return _mm_and_si128(a, b);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Xor128(platform_uint128_t const a, platform_uint128_t const b) {
	return _mm_xor_si128(a, b);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_Not128(platform_uint128_t const a) {
	return _mm_xor_si128(_mm_cmpeq_epi32(a,a), a);
}

AL2O3_FORCE_INLINE uint64_t platform_GetLower128(platform_uint128_t const a) {
	uint64_t ret; // I know this look wrong but its actually a 64 bit move not 128!
	_mm_storel_epi64((__m128i*)&ret, _mm_bsrli_si128(a, 8));
	return ret;
}

AL2O3_FORCE_INLINE uint64_t platform_GetUpper128(platform_uint128_t const a) {
	uint64_t ret; // I know this look wrong but its actually a 64 bit move not 128!
	_mm_storel_epi64((__m128i*)&ret, a);
	return ret;
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ClearLower128(platform_uint128_t const a) {
	return (_mm_bsrli_si128(_mm_bslli_si128(a, 8),8));
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ClearUpper128(platform_uint128_t const a) {
	static const uint64_t mask = ~0ull;
	return _mm_and_si128(a, platform_Load128From64(mask));
}

AL2O3_FORCE_INLINE platform_uint128_t platform_SwapUpperAndLower128(platform_uint128_t const a) {
	platform_uint128_t const upperOnly = platform_ClearLower128(a);
	platform_uint128_t const lowerOnly = platform_ClearUpper128(a);
	platform_uint128_t const b = _mm_bslli_si128(lowerOnly, 8);
	platform_uint128_t const c = _mm_bsrli_si128(upperOnly, 8);
	return _mm_or_si128(b, c);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ShiftUpperToLower128(platform_uint128_t const a) {
	return _mm_bslli_si128(a, 8);
}

AL2O3_FORCE_INLINE platform_uint128_t platform_ShiftLowerToUpper128(platform_uint128_t const a) {
	return _mm_bsrli_si128(a, 8);
}

#endif