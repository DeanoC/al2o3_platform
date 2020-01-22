#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>


#if __cplusplus >= 201103
#define AL2O3_DEFINE_ALIGNED(def, a) alignas(a) def
#else
#define AL2O3_DEFINE_ALIGNED(def, a) def __attribute__((aligned(a)))
#endif

#define AL2O3_EXPORT AL2O3_EXTERN_C
#define AL2O3_IMPORT AL2O3_EXTERN_C
#define AL2O3_EXPORT_CPP
#define AL2O3_THREAD_LOCAL __thread
#define AL2O3_FORCE_INLINE inline __attribute__((always_inline))
#define AL2O3_RESTRICT __restrict

#define AL2O3_DEBUG_BREAK() __builtin_trap();

#include "uint128_gcc.h"
