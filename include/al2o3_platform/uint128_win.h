#pragma once

#include <intrin.h>

typedef __m128i uint128_t;

AL2O3_FORCE_INLINE uint128_t platform_LoadUpper128From64(uint64_t const a) {
	return _mm_loadl_epi64((__m128i*)&a);
}

AL2O3_FORCE_INLINE uint128_t platform_Load128From64(uint64_t const a) {
	return _mm_bslli_si128( _mm_loadl_epi64((__m128i*)&a),8);
}

AL2O3_FORCE_INLINE bool platform_CompareToZero128(uint128_t const a) {
	return _mm_movemask_epi8(_mm_cmpeq_epi8(a, _mm_setzero_si128())) == 0xFFFF;
}

AL2O3_FORCE_INLINE bool platform_Compare128(uint128_t const a, uint128_t const b) {
	return _mm_movemask_epi8(_mm_cmpeq_epi8(a, b)) != 0xFFFF;
}

AL2O3_FORCE_INLINE uint128_t platform_Or128(uint128_t const a, uint128_t const b) {
	return _mm_or_si128(a, b);
}

AL2O3_FORCE_INLINE uint128_t platform_And128(uint128_t const a, uint128_t const b) {
	return _mm_and_si128(a, b);
}

AL2O3_FORCE_INLINE uint128_t platform_Xor128(uint128_t const a, uint128_t const b) {
	return _mm_xor_si128(a, b);
}

AL2O3_FORCE_INLINE uint128_t platform_Not128(uint128_t const a) {
	return _mm_xor_si128(_mm_cmpeq_epi32(a,a), a);
}

AL2O3_FORCE_INLINE uint64_t platform_GetLower128(uint128_t const a) {
	uint64_t ret; // I know this look wrong but its actually a 64 bit move not 128!
	_mm_storel_epi64((__m128i*)&ret, _mm_bsrli_si128(a, 8));
	return ret;
}

AL2O3_FORCE_INLINE uint64_t platform_GetUpper128(uint128_t const a) {
	uint64_t ret; // I know this look wrong but its actually a 64 bit move not 128!
	_mm_storel_epi64((__m128i*)&ret, a);
	return ret;
}

AL2O3_FORCE_INLINE uint128_t platform_ClearLower128(uint128_t const a) {
	return (_mm_bsrli_si128(_mm_bslli_si128(a, 8),8));
}

AL2O3_FORCE_INLINE uint128_t platform_ClearUpper128(uint128_t const a) {
	static const uint64_t mask = ~0ull;
	return _mm_and_si128(a, platform_Load128From64(mask));
}

AL2O3_FORCE_INLINE uint128_t platform_SwapUpperAndLower128(uint128_t const a) {
	uint128_t const upperOnly = platform_ClearLower128(a);
	uint128_t const lowerOnly = platform_ClearUpper128(a);
	uint128_t const b = _mm_bslli_si128(lowerOnly, 8);
	uint128_t const c = _mm_bsrli_si128(upperOnly, 8);
	return _mm_or_si128(b, c);
}

AL2O3_FORCE_INLINE uint128_t platform_ShiftUpperToLower128(uint128_t const a) {
	return _mm_bslli_si128(a, 8);
}

AL2O3_FORCE_INLINE uint128_t platform_ShiftLowerToUpper128(uint128_t const a) {
	return _mm_bsrli_si128(a, 8);
}


